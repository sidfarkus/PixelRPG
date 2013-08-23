#pragma once

#include "ImageLoader.h"
#include "Image.h"
#include "Control.h"

namespace GUI  {
   class Frame : public Control {
   public:
      Frame();
      Frame(const char * texture, int topborder, int bottomborder, int leftborder, int rightborder, 
            int x, int y, unsigned int wide, unsigned int tall);

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

   protected:
      virtual bool Collide(int mx, int my);

      IMAGEHANDLE _img;
      int _top;
      int _bottom;
      int _left;
      int _right;
   };
}
