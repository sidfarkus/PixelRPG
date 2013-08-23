#pragma once

#include <string>
#include "WorldObject.h"
#include "ImageAnimation.h"

// A static map object (non-movable)
// 
class StaticObject  {
public:
   StaticObject(const std::string & name, const ImageAnimation & image);
   StaticObject(const std::string & name, const ImageAnimation & image, int x, int y, int w = 0, int h = 0);
   ~StaticObject();

   void Draw(RenderDevice::Renderer & render, unsigned int tElapsed, int sX, int sY);

   WORLDOBJ_PROPERTIES(_pos);
   inline int Width() const {return _width;}
   inline void SetWidth(int w) {_width = w;}
   inline int Height() const {return _height;}
   inline void SetHeight(int h) {_height = h;}
   inline const std::string & Name() {return _name;}

private:
   std::string _name;
   int _width, _height;
   WorldObject _pos;
   ImageAnimation _img;
};

