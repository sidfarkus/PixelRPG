#include "Tileset.h"

Tileset::Tileset(const std::string & filename, int tilesize)  {
   _img = ImageLoader::Load(filename.c_str());
   _tilesize = tilesize;

   const Image * temp = ImageLoader::GetImage(_img);

   if (temp)  {
      _numTilesX = temp->Width() / tilesize;
      _numTiles = _numTilesX * (temp->Height() / tilesize);
   } else  {
      _numTiles = 0;
      _numTilesX = 0;
   }
}

Tileset::~Tileset()  {
   ImageLoader::TryRelease(_img);
}

void Tileset::DrawTile(RenderDevice::Renderer & render, int index, int tilex, int tiley)  {
   render.Drawimage(_img, tilex, tiley, _tilesize, _tilesize, index % _numTilesX * _tilesize, index / _numTilesX * _tilesize, _tilesize, _tilesize);
}

void Tileset::DrawRandom(RenderDevice::Renderer & render, int x, int y)  {
   DrawTile(render, rand() % _numTiles + 1, x, y);
}
