#pragma once

#include "Renderer.h"
#include "Tileset.h"
#include "Console.h"

// TileID is a unique integer representing a tile's position
// [ 12 bits Cell X ] [ 12 bits Cell Y ] [ 4 bits Tile X index] [ 4 bits Tile Y index ]
struct TileID  {
   unsigned int TileY : 4;
   unsigned int TileX : 4;
   unsigned int CellY : 12;
   unsigned int CellX : 12;
};

class Cell  {
public:
   Cell();
   Cell(int X, int Y);
   ~Cell();

   // Generates the tile indices for this cell
   void Generate(Tileset * tileset);

   // determines if this cell is visible in the passed rectangle (if there is an intersection)
   bool IsVisible(int x, int y, int w, int h) const;

   // x,y = upper left corner of the screen
   void DrawVisible(RenderDevice::Renderer & render, int screenX, int screenY);

   inline void SetCellX(int val) {_cellx = val; _worldx = val * CELLWIDTH;}
   inline int  CellX() {return _cellx;}
   inline void SetCellY(int val) {_celly = val; _worldy = val * CELLWIDTH;}
   inline int  CellY() {return _celly;}

   // Size in pixels of one tile
   static const int TILESIZE = 80;

   // Number of tiles across one cell (must be less than 16)
   static const int NUMTILES_PER_CELL = 5;

   // Width of a cell in pixels
   static const int CELLWIDTH = TILESIZE * NUMTILES_PER_CELL;

private:
   int _cellx;
   int _celly;
   int _worldx;
   int _worldy;
   Tileset * _tileset;
   int _tiles[NUMTILES_PER_CELL * NUMTILES_PER_CELL];
};
