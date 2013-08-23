#include "Map.h"

Map::Map(const std::string & filename) : _map(filename.c_str()), _center(VIEWSIZE / 2, VIEWSIZE / 2) {
   // start the view at VIEWSIZE / 2, VIEWSIZE / 2
   for (int i = 0; i < VIEWSIZE * VIEWSIZE; i++)  {
      _view[i] = Cell(i % VIEWSIZE, i / VIEWSIZE);
   }
}

Map::Map(const Map & map) : _center(map._center)  {
   std::map<unsigned int, TileType *>::const_iterator i = map._tiletypes.begin();

   for (;i != map._tiletypes.end(); i++)
      _tiletypes[i->first] = new TileType(new Tileset(*(i->second->TileSet)), i->first);
}

Map::~Map()  {
   std::map<unsigned int, TileType *>::iterator i = _tiletypes.begin();

   for (;i != _tiletypes.end(); i++)  {
      delete i->second->TileSet;
      delete i->second;
   }
}

void Map::RegisterTileType(TileType * type)  {
   if (type->TileSet != NULL)  {
      std::map<unsigned int, TileType *>::iterator found = _tiletypes.find(type->Color);

      if (found != _tiletypes.end()) {
         _tiletypes[type->Color] = type;
      }
   }
}

void Map::RegisterTileType(Tileset * tileset, unsigned int color)  {
   if (tileset != NULL)  {
      std::map<unsigned int, TileType *>::iterator found = _tiletypes.find(color);

      //if (found != _tiletypes.end()) {
         _tiletypes[color] = new TileType(tileset, color);
      //}
   }
}

void Map::Load(const std::string & filename)  {
   if (_map.Load(filename.c_str()))  {
   }
}

void Map::DrawView(RenderDevice::Renderer & render, int viewX, int viewY)  {
   for (int i = 0; i < VIEWSIZE * VIEWSIZE; i++)  {
      _view[i].DrawVisible(render, viewX, viewY);
   }
}

void Map::SetView(MapCoord centerPoint)  {
   // get the pixels around the center point
   unsigned int pixels[VIEWSIZE * VIEWSIZE];
   _center = centerPoint;
   _map.GetPixels(pixels, VIEWSIZE, centerPoint.CellX - (VIEWSIZE / 2), centerPoint.CellY - (VIEWSIZE / 2));

   // for each view cell, update the x/y and generate the tiles for each
   for (int i = 0; i < VIEWSIZE * VIEWSIZE; i++)  {  
      std::map<unsigned int, TileType *>::iterator found = _tiletypes.find(pixels[i]);

      if (found != _tiletypes.end())  {
         _view[i].SetCellX(centerPoint.CellX + (i % VIEWSIZE - 1));
         _view[i].SetCellY(centerPoint.CellY + (i / VIEWSIZE - 1));
         _view[i].Generate(found->second->TileSet);
      }
   }

}

void Map::MoveView(Direction d)  {
   switch (d)  {
      case Up:
         break;
      case Down:
         break;
      case Left:
         break;
      case Right:
         break;
   }
}

void Map::GetMapRegion(int size, unsigned int * colors)  {
   _map.GetPixels(colors, size, _center.CellX - size / 2, _center.CellY - size / 2);
}
