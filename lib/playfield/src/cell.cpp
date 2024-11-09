#include "playfield/cell.h"

namespace
{
  static constexpr utils::Color ON_DOWN{ 255, 255, 255, 255 };
  static constexpr utils::Color MINE{ 255, 0, 0, 255 };
  static constexpr utils::Color EMPTY{ 0, 0, 255, 255 };
  static constexpr utils::Color HINT{0, 255, 0, 255};
}

namespace playfield
{
  
  Cell::Cell(utils::Pos pos, utils::Size size)
    : mRectangle{pos.xPos, pos.yPos, size.width, size.height}
  {
  }

  void Cell::setColor(utils::Color color)
  {
    mColor = color;
    mRectangle.setColor(color);
  }

  void Cell::draw(SDL_Renderer* const renderer) const
  {
    mRectangle.draw(renderer);
  }

  void Cell::onPressed()
  {
    if (isRevealed)
    {
      return;
    }
    mRectangle.setColor(ON_DOWN);
  }

  void Cell::onCellChanged(logic::CellType type)
  {
    switch (type)
    {
    case logic::CellType::EMPTY:
      mRectangle.setColor(EMPTY);
      break;
    case logic::CellType::HINT:
      mRectangle.setColor(HINT);
      break;
    case logic::CellType::MINE:
      mRectangle.setColor(MINE);
      break;
    }
    isRevealed = true;
  }

  void Cell::clearPressed()
  {
    mRectangle.setColor(mColor);
  }

}
