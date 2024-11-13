#pragma once

#include "utils/types.h"
#include "graphics/rectangle.h"
#include "graphics/text.h"

#include <string>

namespace playfield
{

  class Overlay
  {
  public:
    Overlay() = default;
    Overlay(utils::Pos pos, utils::Size size);
    void setMessage(const std::string& message, const utils::Color& color);
    void draw(SDL_Renderer* renderer);
    void setPosAndSize(utils::Pos pos, utils::Size size);
    void setOverlayColor(const utils::Color& color);
    void show();
    void hide();
    bool isShown() const;

  private:
    graphics::Rectangle mOverlay;
    graphics::Text mOverlayText;
    bool mShow{};
  };

}
