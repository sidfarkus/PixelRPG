#pragma once

#include "ImageLoader.h"
#include "Control.h"
#include "Button.h"
#include <string>

namespace GUI  {
   class SimpleButton : public Control, public IClickable {
   public:
      SimpleButton(const std::string & imageFile, int x, int y, int w, int h, int tu = 0, int tv = 0);
      virtual ~SimpleButton();

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

   private:
      IMAGEHANDLE _img;
      BUTTONSTATE _state;
      int _tu, _tv;
   };
}
