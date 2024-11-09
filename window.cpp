#include "window.h"

#include "playfield/background.h"
#include "playfield/buttonField.h"

bool Window::init(int width, int height)
{
  mSize = { static_cast<float>(width), static_cast<float>(height) };

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed (%s)", SDL_GetError());
    return false;
  }

  if (!SDL_CreateWindowAndRenderer("SDL issue", width, height, 0, &mWindow, &mRenderer)) {
    SDL_Log("SDL_CreateWindowAndRenderer failed (%s)", SDL_GetError());
    SDL_Quit();
    return false;
  }

  return true;
}

int Window::run()
{
  static constexpr int colRowSize = 10;
  static constexpr int mines = 10;
  playfield::Background background{mSize};
  background.setColRow(colRowSize);
  background.init();
  playfield::ButtonField buttonField{ mSize };
  buttonField.setBoard(colRowSize, mines);

  while (1) {
    int finished = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        finished = 1;
        break;
      }
      else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
      {
        if (event.button.button == 1 || event.button.button == 3)
        {
          float mouseX;
          float mouseY;
          SDL_GetMouseState(&mouseX, &mouseY);
          buttonField.onPressed(mouseX, mouseY);
        }
      }
      else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
      {
        if (event.button.button == 1)
        {
          float mouseX;
          float mouseY;
          SDL_GetMouseState(&mouseX, &mouseY);
          buttonField.onRelease(mouseX, mouseY);
        }
      }
    }
    if (finished) {
      break;
    }

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    background.draw(mRenderer);
    buttonField.draw(mRenderer);

    SDL_RenderPresent(mRenderer);
  }

  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);

  SDL_Quit();

  return 0;
}

