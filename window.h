#pragma once

#include "utils/types.h"
#include "graphics/fonts.h"

#include <SDL3/SDL.h>
/*
 * SDL3/SDL_main.h is explicitly not included such that a terminal window would appear on Windows.
 */

class Window
{
public:
  Window() {}
  bool init(int width, int heigh);
  int run();

private:
  SDL_Window* mWindow = nullptr;
  SDL_Renderer* mRenderer = nullptr;
  utils::Size mSize;
  graphics::Fonts mFonts;
};
