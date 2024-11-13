#pragma once

#include "utils/types.h"
#include "playfield/cell.h"
#include "playfield/overlay.h"
#include "logic/board.h"

#include <vector>
#include <optional>

namespace playfield
{

  class ButtonField
  {
  public:
    ButtonField(utils::Size size);
    void setBoard(int sizeColRows, int mines);
    void draw(SDL_Renderer* const renderer);
    void onPressed(float posX, float posY);
    void onRelease(float posX, float posY);

  private:
    int calcCellId( float posX, float posY ) const;
    void onCellChange(int col, int row, logic::CellType type, int neighbours);
    void onGameOver(bool won);

    utils::Size mSize;
    int mSizeColRows;
    std::vector<Cell> mCells;
    std::optional<int> pressedCellId;
    logic::Board mBoard;
    Overlay mOverlay;
  };

}
