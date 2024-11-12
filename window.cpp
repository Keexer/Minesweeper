#include "window.h"

#include "playfield/background.h"
#include "playfield/buttonField.h"

#include "SDL3_ttf/SDL_ttf.h"

bool Window::init(int width, int height)
{
  mSize = { static_cast<float>(width), static_cast<float>(height) };

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed (%s)", SDL_GetError());
    return false;
  }

  if (!TTF_Init())
  {
    SDL_Log("TTF_Init failed");
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

  TTF_Font* font = TTF_OpenFont("C:/Repos/Minesweeper/Minesweeper/build/Debug/Tinos-Italic.ttf", 24);
  if (font == nullptr)
  {
    return false;
  }

  SDL_Color White{ 255,255,255, 255 };
  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, "Hello", 5, White);
  SDL_Texture* message = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage);
  SDL_FRect rect{ .0f, .0f, static_cast<float>(surfaceMessage->w), static_cast<float>(surfaceMessage->h) };
  SDL_DestroySurface(surfaceMessage);

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

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    background.draw(mRenderer);
    buttonField.draw(mRenderer);

    
    //SDL_RenderTexture(mRenderer, message, NULL, &rect);

    

    SDL_RenderPresent(mRenderer);
  }

  SDL_DestroyTexture(message);

  TTF_CloseFont(font);
  TTF_Quit();

  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);

  SDL_Quit();

  return 0;
}

