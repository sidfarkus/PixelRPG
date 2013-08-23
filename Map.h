#pragma once

#include "Renderer.h"
#include "Image.h"
#include "Tileset.h"
#include "Cell.h"
#include <string>
#include <map>

// Cell coords are in world map pixels
// Minor coords are relative to the entire world
struct MapCoord  {
   unsigned int CellX;
   unsigned int CellY;
   int X;
   int Y;

   MapCoord(int x, int y)  {
      CellX = x;
      CellY = y;
      X = Cell::CELLWIDTH * (x - 1);
      Y = Cell::CELLWIDTH * (y - 1);
   }
};

// Maps a color on the world map to a tileset to use
struct TileType {
   Tileset *    TileSet;
   unsigned int Color;

   TileType(Tileset * tileset, unsigned int color) {
      TileSet = tileset;
      Color = color;
   }
};

// Map holds a large image containing different colors corresponding to different
// terrain types.  Each pixel is a 10x10 grid of tiles in the world that are
// populated using thier position as a random seed to the tileset.
class Map  {
   enum Direction  {
      Up,
      Down,
      Left,
      Right,
      UpLeft,
      UpRight,
      DownLeft,
      DownRight
   };

public:
   Map(const std::string & filename);
   Map(const Map & map);
   ~Map();

   void RegisterTileType(TileType * type);
   void RegisterTileType(Tileset * tileset, unsigned int color);

   void Load(const std::string & filename);
   void SetView(MapCoord centerPoint);

   // moves the view one cell in the specified direction
   void MoveView(Direction d);
   void DrawView(RenderDevice::Renderer & render, int viewX, int viewY);

   void GetMapRegion(int size, unsigned int * colors);

   inline int Width() {return _map.Width();}
   inline int Height() {return _map.Height();}

   // Size across the loaded view of cells
   static const int VIEWSIZE = 5;
   
private:
   MapCoord _center;
   Image _map;
   Cell _view[VIEWSIZE * VIEWSIZE];
   std::map<unsigned int, TileType *> _tiletypes;
};
