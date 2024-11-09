#pragma once

#include <vector>
#include <utility>
#include <functional>

namespace logic
{

  enum class CellType : uint16_t
  {
    EMPTY = 0,
    HINT,
    MINE
  };

  using OnCellChange = std::function<void(int, int, CellType)>;

  class Board
  {
  public:
    void init(int colRowSize, int mines);
    void setClicked(int col, int row);
    void setOnChange(OnCellChange&& onChange);

  private:
    void randomizeMines(int mines);
    void fillHints();
    int getNeighbourMines(int col, int row, int index) const;
    void revealEmptyNeighbours(int index);

    struct Element
    {
      CellType type{};
      bool isHidden{ true };
      int neighbours{};
    };

    int mColRowSize{};
    std::vector<Element> mBoard;
    OnCellChange mOnChange;
  };

}
