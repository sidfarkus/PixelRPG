#pragma once

#include "Control.h"
#include "ImageLoader.h"
#include "Font.h"
#include <string>

namespace GUI  {
   class TextBox :  public Control, public IClickable  {
   public:
      TextBox(const char * image, Font * font, unsigned int borderwidth, int maxLength, int x, int y, unsigned int wide, unsigned int tall);
      virtual ~TextBox();

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

      inline void SetText(std::string & text) {_curText = text;}
      inline std::string GetText() {return _curText;}
      inline void SetMaxLength(int len) {_maxChars = len;}
      inline int GetMaxLength() {return _maxChars;}

      static const int BLINK_SPEED = 400;

   private:
      std::string _curText;
      IMAGEHANDLE _img;
      Font * _font;
      int _border;
      int _cursorDelay;
      int _maxChars;
      bool _allowEntry;
   };
}
