#pragma once

#include "Renderer.h"
#include "ImageLoader.h"
#include <string>

class Tileset  {
public:
   Tileset(const std::string & filename, int tilesize);
   ~Tileset();

   void DrawTile(RenderDevice::Renderer & render, int index, int tilex, int tiley);
   void DrawRandom(RenderDevice::Renderer & render, int x, int y);

   inline int TileSize() const {return _tilesize;}
   inline int NumTiles() const {return _numTiles;}

private:
   int _numTilesX, _numTiles;
   int _tilesize;
   IMAGEHANDLE _img;
}; 
