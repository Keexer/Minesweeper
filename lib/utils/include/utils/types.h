#pragma once

#include <cstdint>

namespace utils
{

  struct Pos
  {
    float xPos{};
    float yPos{};

    Pos operator/(int val)
    {
      return { xPos / val, yPos / val };
    }
  };

  struct Size
  {
    float width{};
    float height{};

    Pos operator/(int val)
    {
      return { width / val, height / val };
    }
  };

  struct Color
  {
    uint8_t r{};
    uint8_t g{};
    uint8_t b{};
    uint8_t a{};
  };

}
