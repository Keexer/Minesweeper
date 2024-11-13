#include "playfield/overlay.h"

namespace playfield
{

  Overlay::Overlay(utils::Pos pos, utils::Size size)
    : mOverlay{pos.xPos, pos.yPos, size.width, size.height}
  {
  }

  void Overlay::setMessage(const std::string& message, const utils::Color& color)
  {
    mOverlayText.setMessage(message);
    mOverlayText.setColor(color);
  }

  void Overlay::draw(SDL_Renderer* renderer)
  {
    if (mShow)
    {
      mOverlay.draw(renderer);
    }
    mOverlayText.draw(renderer);
  }

  void Overlay::setPosAndSize(utils::Pos pos, utils::Size size)
  {
    mOverlay = { pos.xPos, pos.yPos, size.width, size.height };
  }

  void Overlay::setOverlayColor(const utils::Color& color)
  {
    mOverlay.setColor(color);
  }

  void Overlay::show()
  {
    mShow = true;
    mOverlayText.show();
    mOverlayText.setPosition(mOverlay.getSize() / 2);
  }

  void Overlay::hide()
  {
    mShow = false;
    mOverlayText.hide();
  }

  bool Overlay::isShown() const
  {
    return mShow;
  }

}
