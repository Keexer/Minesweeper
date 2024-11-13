#include "graphics/fonts.h"

#include <cassert>

namespace graphics
{

  std::unordered_map<std::string, TTF_Font*> Fonts::mFonts;

  void Fonts::init()
  {
    TTF_Font* font = TTF_OpenFont("C:/Repos/Minesweeper/Minesweeper/build/Debug/Tinos-Italic.ttf", 24);
    if (font)
    {
      mFonts.insert({ "Tinos-Italic:24", font });
    }
  }

  TTF_Font* Fonts::getFont(const std::string& font)
  {
    if (!mFonts.contains(font))
    {
      assert(false && "Font does not exist");
      return nullptr;
    }
    return mFonts[font];
  }

}
