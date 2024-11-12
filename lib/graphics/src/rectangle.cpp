#include "graphics/rectangle.h"

namespace graphics
{
  Rectangle::Rectangle(float xPos, float yPos, float width, float height)
    : mPos{xPos, yPos}
    , mSize{width, height}
  {
  }

  void Rectangle::setSize(utils::Size size)
  {
    mSize = size;
  }

  void Rectangle::moveTo(utils::Pos pos)
  {
    mPos = pos;
  }

  void Rectangle::setColor(utils::Color color)
  {
    mColor = color;
  }
  
  void Rectangle::draw(SDL_Renderer* renderer) const
  {
    SDL_FRect fillRect = { mPos.xPos, mPos.yPos, mSize.width, mSize.height };
    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
    SDL_RenderFillRect(renderer, &fillRect);
  }

  utils::Pos Rectangle::getPos() const
  {
    return mPos;
  }

  utils::Size Rectangle::getSize() const
  {
    return mSize;
  }

}
