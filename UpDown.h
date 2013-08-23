#pragma once

#include "Control.h"
#include "ImageLoader.h"
#include "Font.h"
#include <string>
#include <sstream>

namespace GUI  {
class UpDown : public Control  {
   public:
      UpDown(const std::string & imageFile, Font * valFont, int buttonWidth, int minVal, int maxVal, int x, int y, unsigned int w, unsigned int h, int increment = 1);
      virtual ~UpDown();

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

      inline int Value() {return _value;}
      inline void SetValue(int val) {_value = val;}

      static const int REPEAT_DELAY = 250;

   private:
      enum UpDownState : int {
         None,
         DownClick,
         UpClick,
         DownHover,
         UpHover    
      };

      IMAGEHANDLE _img;
      Font * _font;
      UpDownState _state;
      int _value;
      int _inc;
      int _minVal, _maxVal;
      int _buttonWidth;
      int _downTime;
   };
}
