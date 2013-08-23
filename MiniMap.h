#pragma once

#include <vector>
#include "Frame.h"
#include "Map.h"

namespace GUI  {
   class MiniMap : public Frame  {
   public:
      MiniMap(const char * borderImage, Map & map, int borderSize, int x, int y, int w, int h);
      virtual ~MiniMap();

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

      static const int CELLSIZE = 4; // Size of a drawn cell in the minimap

   private:
      unsigned int * _colors;
      Map & _map;
      IMAGEHANDLE _img;
      int _mapSize;
      bool _isBig;
      bool _mouseDown;
   };
}
