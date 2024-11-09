#include "playfield/background.h"

namespace
{
  static constexpr float THICKNESS = 1.f;
}

namespace playfield
{
  Background::Background(utils::Size size)
    : mSize(size)
  {
  }

  void Background::setColRow(int sizeColRows)
  {
    mSizeColRows = sizeColRows;
  }

  void Background::init()
  {
    // create vertical lines
    const float verticalOffset = (mSize.width - THICKNESS) / mSizeColRows;
    for (int i = 0; i < (mSizeColRows + 1); ++i)
    {
      mBackgroundLines.emplace_back(verticalOffset * i, 0.0f, THICKNESS, mSize.height );
      mBackgroundLines.back().setColor({ 100, 100, 100, 100 });
    }

    // create horizontal lines
    const float horizontalOffset = (mSize.height - THICKNESS) / mSizeColRows;
    for (int i = 0; i < (mSizeColRows + 1); ++i)
    {
      mBackgroundLines.emplace_back(0.0f, horizontalOffset * i, mSize.width, THICKNESS);
      mBackgroundLines.back().setColor({ 100, 100, 100, 100 });
    }
  }

  void Background::draw(SDL_Renderer* const renderer) const
  {
    for (const auto& Rectangle : mBackgroundLines)
    {
      Rectangle.draw(renderer);
    }
  }

}
