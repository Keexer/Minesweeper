#include "playfield/buttonField.h"

namespace
{
  // ugly, defined in two places
  static constexpr float THICKNESS = 1.f;
}

namespace playfield
{

  ButtonField::ButtonField(utils::Size size)
    : mSize{size}
  {}

  void ButtonField::setBoard(int sizeColRows, int mines)
  {
    mBoard.init(sizeColRows, mines);
    mBoard.setOnChange([this](int col, int row, logic::CellType type) {onCellChange(col, row, type); });

    mSizeColRows = sizeColRows;

    const float cellWidth = (mSize.width - THICKNESS * sizeColRows) / sizeColRows;
    const float cellHeight = (mSize.height - THICKNESS * sizeColRows) / sizeColRows;
    const utils::Size cellSize{ cellWidth, cellHeight };
    const float verticalOffset = (mSize.width - THICKNESS) / sizeColRows;
    const float horizontalOffset = (mSize.height - THICKNESS) / sizeColRows;

    for (int col = 0; col < mSizeColRows; ++col)
    {
      for (int row = 0; row < mSizeColRows; ++row)
      {
        mCells.emplace_back(utils::Pos{ THICKNESS * (col + 1) + col * verticalOffset, THICKNESS * (row + 1) + row * horizontalOffset }, cellSize);
        mCells.back().setColor({ 255, 255, 0, 255 });
      }
    }
  }

  void ButtonField::draw(SDL_Renderer* const renderer) const
  {
    for (const auto& Cell : mCells)
    {
      Cell.draw(renderer);
    }
  }

  void ButtonField::onPressed(float posX, float posY)
  {
    pressedCellId = calcCellId(posX, posY);
    mCells.at(*pressedCellId).onPressed();
  }

  void ButtonField::onRelease(float posX, float posY)
  {
    if (pressedCellId && pressedCellId == calcCellId(posX, posY))
    {
      mBoard.setClicked(*pressedCellId / mSizeColRows, *pressedCellId % mSizeColRows);
    }
    else if (pressedCellId)
    {
      mCells.at(*pressedCellId).clearPressed();
    }

    pressedCellId = std::nullopt;
  }

  int ButtonField::calcCellId(float posX, float posY) const
  {
    const float verticalOffset = (mSize.width - THICKNESS) / mSizeColRows;
    const float horizontalOffset = (mSize.height - THICKNESS) / mSizeColRows;

    const int xPos = static_cast<int>(posX / verticalOffset);
    const int yPos = static_cast<int>(posY / horizontalOffset);

    return xPos * mSizeColRows + yPos;
  }

  void ButtonField::onCellChange(int col, int row, logic::CellType type)
  {
    mCells.at(col * mSizeColRows + row).onCellChanged(type);
  }

}
