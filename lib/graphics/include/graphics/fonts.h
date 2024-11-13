#pragma once

#include "SDL3_ttf/SDL_ttf.h"

#include <string>
#include <unordered_map>

namespace graphics
{

  class Fonts
  {
  public:
    void init();
    static TTF_Font* getFont(const std::string& font);

  private:
    static std::unordered_map<std::string, TTF_Font*> mFonts;
  };

}
