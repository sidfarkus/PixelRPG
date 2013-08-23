#pragma once

#include <string>
#include "Image.h"
#include "Control.h"
#include "Font.h"

namespace GUI  {
   class Label : public Control {
   public:
      Label(const char * text, Font * font, int x, int y);

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

      inline std::string GetText() const {return _text;}
      inline void SetText(std::string & text) {_text = text;}

   protected:
      Font * _font;
      std::string _text;
      Image _cache;
   };
}