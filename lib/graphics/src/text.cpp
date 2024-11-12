#include "graphics/text.h"

namespace graphics
{
  
  Text::Text(const std::string& message)
    : mMessage(message)
  {
  }

  Text::Text(const std::string& message, utils::Pos pos)
    : mMessage(message)
    , mPos(pos)
  {
  }

  Text::~Text()
  {
    if (mTexture)
    {
      SDL_DestroyTexture(mTexture);
    }
  }

  void Text::setPosition(utils::Pos pos)
  {
    mPos = pos;
  }

  void Text::setMessage(const std::string& message)
  {
    mMessage = message;
  }

  void Text::show()
  {
    mShow = true;
  }

  void Text::hide()
  {
    mShow = false;
  }

  void Text::draw(SDL_Renderer* renderer) const
  {
    if (mShow)
    {
      static TTF_Font* font = TTF_OpenFont("C:/Repos/Minesweeper/Minesweeper/build/Debug/Tinos-Italic.ttf", 24);
      SDL_Color White{ 255,255,255, 255 };
      SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, mMessage.c_str(), mMessage.size(), White);
      mTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
      SDL_FRect rect{ mPos.xPos, mPos.yPos, static_cast<float>(surfaceMessage->w), static_cast<float>(surfaceMessage->h) };
      SDL_DestroySurface(surfaceMessage);
      SDL_RenderTexture(renderer, mTexture, NULL, &rect);
    }
  }

}
