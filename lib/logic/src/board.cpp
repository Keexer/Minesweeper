#include "logic/board.h"

#include <cassert>
#include <ctime>
#include <queue>

namespace logic
{

  void Board::init(int colRowSize, int mines)
  {
    mColRowSize = colRowSize;
    mBoard.assign(colRowSize * colRowSize, { CellType::EMPTY, true, 0 });
    assert(mines < mColRowSize * mColRowSize && "Amount of mines are larger than game board");

    randomizeMines(mines);
    fillHints();
  }

  void Board::setClicked(int col, int row)
  {
    const int index = col * mColRowSize + row;
    auto& element = mBoard.at(index);
    if (element.isHidden)
    {
      if (element.type == CellType::MINE)
      {
        // handle game over
      }
      else if (element.type == CellType::EMPTY)
      {
        revealEmptyNeighbours(index);
        return;
      }

      element.isHidden = false;

      if (mOnChange)
      {
        mOnChange(col, row, element.type, element.neighbours);
      }
    }
  }

  void Board::setOnChange(OnCellChange&& onChange)
  {
    mOnChange = std::move(onChange);
  }

  void Board::randomizeMines(int mines)
  {
    srand(time(0));
    int minesSet = 0;
    while (minesSet < mines)
    {
      int random = rand() % (mColRowSize * mColRowSize);
      if (mBoard.at(random).type != CellType::MINE)
      {
        mBoard.at(random).type = CellType::MINE;
        ++minesSet;
      }
    }
  }

  void Board::fillHints()
  {
    for (int col = 0; col < mColRowSize; ++col)
    {
      for (int row = 0; row < mColRowSize; ++row)
      {
        const int index = col * mColRowSize + row;
        if (mBoard.at(index).type == CellType::MINE)
        {
          continue;
        }
        if (const int neighbourMines = getNeighbourMines(col, row, index); neighbourMines > 0)
        {
          mBoard.at(index).type = CellType::HINT;
          mBoard.at(index).neighbours = neighbourMines;
        }
      }
    }
  }

  int Board::getNeighbourMines(int col, int row, int index) const
  {
    int neighbours{};
    // up elements
    if (row > 0)
    {
      neighbours += mBoard.at(index - 1).type == CellType::MINE;
      // left
      if (col > 0)
      {
        neighbours += mBoard.at(index - 1 - mColRowSize).type == CellType::MINE;
      }
      // right
      if (col < (mColRowSize - 1))
      {
        neighbours += mBoard.at(index - 1 + mColRowSize).type == CellType::MINE;
      }
    }
    // down elements
    if (row < (mColRowSize - 1))
    {
      neighbours += mBoard.at(index + 1).type == CellType::MINE;
      // left
      if (col > 0)
      {
        neighbours += mBoard.at(index + 1 - mColRowSize).type == CellType::MINE;
      }
      // right
      if (col < (mColRowSize - 1))
      {
        neighbours += mBoard.at(index + 1 + mColRowSize).type == CellType::MINE;
      }
    }
    // left element
    if (col > 0)
    {
      neighbours += mBoard.at(index - mColRowSize).type == CellType::MINE;
    }
    // right element
    if (col < (mColRowSize - 1))
    {
      neighbours += mBoard.at(index + mColRowSize).type == CellType::MINE;
    }

    return neighbours;
  }

  void Board::revealEmptyNeighbours(int index)
  {
    std::vector<bool> visited(mBoard.size(), false);
    std::queue<int> emptyCell;
    emptyCell.push(index);

    auto checkLeft = [=, &emptyCell, &visited](int index)
      {
        const int nextIndex = index - mColRowSize;
        if (nextIndex >= 0 && !visited.at(nextIndex))
        {
          emptyCell.push(nextIndex);
        }
      };

    auto checkRight = [=, &emptyCell, &visited](int index)
      {
        const int nextIndex = index + mColRowSize;
        const int maxSize = mColRowSize * mColRowSize;
        if (nextIndex < maxSize && !visited.at(nextIndex))
        {
          emptyCell.push(nextIndex);
        }
      };

    while (!emptyCell.empty())
    {
      const int currentIndex = emptyCell.front();
      const auto currentType = mBoard.at(currentIndex).type;
      visited.at(emptyCell.front()) = currentType == CellType::EMPTY;

      if (currentType == CellType::EMPTY )
      {
        // check up
        int nextIndex{ currentIndex - 1 };
        if (currentIndex % mColRowSize > 0 && !visited.at(nextIndex))
        {
          emptyCell.push(nextIndex);
          checkLeft(nextIndex);
          checkRight(nextIndex);
        }
        // check down
        nextIndex = currentIndex + 1;
        if ((currentIndex + 1) % mColRowSize > 0 && !visited.at(nextIndex))
        {
          emptyCell.push(nextIndex);
          checkLeft(nextIndex);
          checkRight(nextIndex);
        }
        checkLeft(currentIndex);
        checkRight(currentIndex);
      }

      mOnChange(currentIndex / mColRowSize, currentIndex % mColRowSize, mBoard.at(currentIndex).type, mBoard.at(currentIndex).neighbours);
      emptyCell.pop();
    }
  }

}
