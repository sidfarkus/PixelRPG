#include "Cell.h"
#include "mersennetwister.h"
#include <limits.h>
#include <sstream>

extern Console console;

Cell::Cell()  {
   _cellx = 0;
   _celly = 0;
   _worldx = 0;
   _worldy = 0;
   _tileset = NULL;
}

Cell::Cell(int X, int Y)  {
   _cellx = X;
   _celly = Y;
   _worldx = X * CELLWIDTH;
   _worldy = Y * CELLWIDTH;
   _tileset = NULL;
}

Cell::~Cell()  {
}

void Cell::Generate(Tileset * tileset)  {
   _tileset = tileset;

   if (!tileset) return;

   MtRng32 mt(0);

   for (int i = 0; i < NUMTILES_PER_CELL * NUMTILES_PER_CELL; i++)  {
      TileID temp;
      temp.CellX = _cellx;
      temp.CellY = _celly;
      temp.TileX = i % NUMTILES_PER_CELL;
      temp.TileY = i / NUMTILES_PER_CELL;

      mt.init(*((unsigned int *) &temp));
      _tiles[i] = static_cast<int>(((float) mt.getInt() / (float) INT_MAX) * tileset->NumTiles());
   }
}

bool Cell::IsVisible(int x, int y, int w, int h) const  {
   return !((x + w <= _worldx) || (x >= _worldx + CELLWIDTH) || (y + h <= _worldy) || (y >= _worldy + CELLWIDTH));
}

void Cell::DrawVisible(RenderDevice::Renderer & render, int screenX, int screenY)  {
   if (!_tileset) return;

   if (IsVisible(screenX, screenY, render.ScreenWidth(), render.ScreenHeight()))  {

      // get intersection area
      int x = (_worldx > screenX) ? _worldx : screenX;
      int y = (_worldy > screenY) ? _worldy : screenY;
      int w = (_worldx + CELLWIDTH < screenX + render.ScreenWidth()) ? _worldx + CELLWIDTH - x : screenX + render.ScreenWidth() - x;
      int h = (_worldy + CELLWIDTH < screenY + render.ScreenHeight()) ? _worldy + CELLWIDTH - y : screenY + render.ScreenHeight() - y;

      // determine which cells are in the intersection area & render
      int xpos = x - screenX - (x % TILESIZE);    // screen x start
      int ypos = y - screenY - (y % TILESIZE);    // screen y start

      int xstart = (x - _worldx) / TILESIZE;
      int xend = xstart + w / TILESIZE + 2;
      if (xend > NUMTILES_PER_CELL) xend = NUMTILES_PER_CELL;

      int ystart = (y - _worldy) / TILESIZE;
      int yend = ystart + h / TILESIZE + 2;
      if (yend > NUMTILES_PER_CELL) yend = NUMTILES_PER_CELL;

      for (int j = ystart; j < yend; j++)  {
         for (int i = xstart; i < xend; i++) {
            _tileset->DrawTile(render, _tiles[i + j * NUMTILES_PER_CELL], xpos, ypos);
            xpos += TILESIZE;
         }
         xpos = x - screenX - (x % TILESIZE);
         ypos += TILESIZE;
      }
   }
}
