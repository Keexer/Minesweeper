#pragma once

#include "utils/types.h"
#include "graphics/rectangle.h"
#include "logic/board.h"
#include "graphics/text.h"

namespace playfield
{

  class Cell
  {
  public:
    Cell(utils::Pos pos, utils::Size size);
    void setColor(utils::Color color);
    void draw(SDL_Renderer* const renderer) const;
    void onPressed();
    void onCellChanged(logic::CellType type, int neighbours);
    void clearPressed();

  private:
    graphics::Rectangle mRectangle;
    utils::Color mColor;
    bool mIsRevealed{};
    graphics::Text mText;
  };

}
