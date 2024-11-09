#pragma once

#include "utils/types.h"
#include "graphics/rectangle.h"
#include "logic/board.h"

namespace playfield
{

  class Cell
  {
  public:
    Cell(utils::Pos pos, utils::Size size);
    void setColor(utils::Color color);
    void draw(SDL_Renderer* const renderer) const;
    void onPressed();
    void onCellChanged(logic::CellType type);
    void clearPressed();

  private:
    graphics::Rectangle mRectangle;
    utils::Color mColor;
    bool isRevealed{};
  };

}
