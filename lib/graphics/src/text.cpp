#include "graphics/text.h"

#include "graphics/fonts.h"

namespace graphics
{

  Text::Text()
  {
    init();
  }

  Text::Text(const std::string& message)
    : mMessage{ message }
  {
    init();
  }

  Text::Text(const std::string& message, utils::Pos pos)
    : mMessage{ message }
    , mPos{ pos }
  {
    init();
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

  void Text::setColor(const utils::Color& color)
  {
    mTextColor = color;
  }

  void Text::show()
  {
    mShow = true;
  }

  void Text::hide()
  {
    mShow = false;
  }

  void Text::draw(SDL_Renderer* renderer)
  {
    if (mShow)
    {
      SDL_Color color{ mTextColor.r, mTextColor.g, mTextColor.b, mTextColor.a };
      SDL_Surface* surfaceMessage = TTF_RenderText_Solid(mFont, mMessage.c_str(), mMessage.size(), color);
      mTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
      SDL_FRect rect{ mPos.xPos, mPos.yPos, static_cast<float>(surfaceMessage->w), static_cast<float>(surfaceMessage->h) };
      SDL_DestroySurface(surfaceMessage);
      SDL_RenderTexture(renderer, mTexture, NULL, &rect);
    }
  }

  void Text::init()
  {
    mFont = Fonts::getFont("Tinos-Italic:24");
    mTextColor = { 255, 255, 255, 255 };
  }

}
