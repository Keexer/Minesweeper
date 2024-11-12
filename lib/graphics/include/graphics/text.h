#pragma once

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "utils/types.h"

#include <string>

namespace graphics
{

  class Text
  {
  public:
    Text() = default;
    explicit Text(const std::string& message);
    Text(const std::string& message, utils::Pos pos);
    ~Text();
    Text(const Text&) = delete;
    Text(Text&&) = default;
    Text& operator=(const Text&) = delete;
    Text& operator=(Text&&) = default;

    void setPosition(utils::Pos pos);
    void setMessage(const std::string& message);
    void show();
    void hide();
    void draw(SDL_Renderer* renderer) const;

  private:
    std::string mMessage;
    utils::Pos mPos;
    mutable SDL_Texture* mTexture{};
    bool mShow{};
  };

}
