#include "MiniMap.h"

namespace GUI  {
   MiniMap::MiniMap(const char * borderImage, Map & map, int borderSize, int x, int y, int w, int h) : 
      Frame(borderImage, borderSize, borderSize, borderSize, borderSize, x, y, w, h), _map(map) 
   {
      _img = ImageLoader::Load(borderImage);
      _mapSize = (std::min<int>(Width(), Height()) - borderSize * 2) / CELLSIZE + 2;

      _colors = new unsigned int[_mapSize * _mapSize];
      _isBig = false;
      _mouseDown = false;
   }

   MiniMap::~MiniMap()  {
      delete[] _colors;
   }

   bool MiniMap::Update(const ActionMap & actions, unsigned int tElapsed)  {
      bool hover = Collide(actions.GetInputState()->mouseX, actions.GetInputState()->mouseY);

      if (hover && !_mouseDown && actions.GetState("click") == ActionState::Pressed)  {
         _mouseDown = true;

         if (!_isBig)  {
            _isBig = true;
            _mapSize = (std::min<int>(Width(), Height()) - _left * 2) / (CELLSIZE / 2) + 1;

            delete[] _colors;
            _colors = new unsigned int[_mapSize * _mapSize];

         } else {
            _isBig = false;
            _mapSize = (std::min<int>(Width(), Height()) - _left * 2) / CELLSIZE + 1;

            delete[] _colors;
            _colors = new unsigned int[_mapSize * _mapSize];
         }
      } else if (actions.GetState("click") == ActionState::Released)  {
         _mouseDown = false;
      }

      return hover;
   }

   void MiniMap::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      int curx = X() + _left, cury = Y() + _top;
      int cellSize = (_isBig) ? CELLSIZE / 2 : CELLSIZE;
      _map.GetMapRegion(_mapSize, _colors);

      Frame::Draw(renderer, tElapsed);

      //renderer.Setclip(X() + _left, Y() + _top, Width() - _left - _right, Height() - _top - _bottom);
      for (int i = 0; i < _mapSize * _mapSize; i++)  {
         if (i % _mapSize == _mapSize - 1)  {
            cury += cellSize;
            curx = X() + _left;
            continue;
         }

         renderer.Fillrect(curx, cury, cellSize, cellSize, LongToColor(_colors[i]));
         curx += cellSize;
      }

      //renderer.Resetclip();

      renderer.Fillrect(X() + Width() / 2, Y() + Height() / 2, 1, 1, Color::White);
   }
}
