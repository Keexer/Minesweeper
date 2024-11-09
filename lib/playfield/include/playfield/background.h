#pragma once

#include "utils/types.h"
#include "graphics/rectangle.h"

#include <vector>

namespace playfield
{

  class Background
  {
  public:
    Background(utils::Size size);
    void setColRow(int sizeColRows);
    void init();
    void draw(SDL_Renderer* const renderer) const;

  private:
    utils::Size mSize;
    int mSizeColRows{};
    std::vector<graphics::Rectangle> mBackgroundLines;
  };

}
