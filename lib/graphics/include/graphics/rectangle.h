#pragma once

#include "utils/types.h"

#include <SDL3/SDL.h>

namespace graphics
{

  class Rectangle
  {
  public:
    Rectangle() = default;
    Rectangle(float xPos, float yPos, float width, float height);
    void setSize(utils::Size size);
    void moveTo(utils::Pos pos);
    void setColor(utils::Color color);
    void draw(SDL_Renderer* renderer) const;
    utils::Pos getPos() const;
    utils::Size getSize() const;

  private:
    utils::Pos mPos;
    utils::Size mSize;
    utils::Color mColor;
  };

}
