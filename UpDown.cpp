#include "UpDown.h"

namespace GUI  {
   UpDown::UpDown(const std::string & imageFile, Font * valFont, int buttonWidth, int minVal, int maxVal,
      int x, int y, unsigned int w, unsigned int h, int increment) : Control(x,y,w,h) {

      _img = ImageLoader::Load(imageFile.c_str());
      _font = valFont;
      _buttonWidth = buttonWidth;
      _value = minVal;
      _inc = increment;
      _minVal = minVal;
      _maxVal = maxVal;
      _state = None;
      _downTime = 0;
   }

   UpDown::~UpDown()  {
      ImageLoader::TryRelease(_img);
   }

   bool UpDown::Update(const ActionMap & actions, unsigned int tElapsed)  {
      const InputState & input = *actions.GetInputState();

      if ((input.mouseX <= Right()) && (input.mouseX >= x) &&
         (input.mouseY <= Bottom()) && (input.mouseY >= y))  {
         
         if (input.mbReleased & MOUSE_B1)  {

            _state = None;
            _downTime = 0;

         } else if (input.mbPressed & MOUSE_B1 || _state == UpClick || _state == DownClick)  {

            if (_state == None || _state > UpClick)
               _downTime = REPEAT_DELAY;

            if (input.mouseX <= x + width / 2)  {
               _state = DownClick;
               _downTime += tElapsed;

               while (_downTime > REPEAT_DELAY)  {
                  _value -= _inc;
                  _downTime = REPEAT_DELAY - _downTime;
               }
            } else {
               _state = UpClick;
               _downTime += tElapsed;

               while (_downTime > REPEAT_DELAY)  {
                  _value += _inc;
                  _downTime = REPEAT_DELAY - _downTime;
               }
            }
         } else {
            if (input.mouseX <= x + width / 2)  {
               _state = DownHover;
            } else {
               _state = UpHover;
            }
         }

         if (_value > _maxVal) 
            _value = _maxVal;
         else if (_value < _minVal) 
            _value = _minVal;

         return true;
      }

      _state = None;

      return false;
   }

   void UpDown::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      std::ostringstream os;

      os << _value << " ";
      std::string valstr = os.str();

      if (_font)  {
         _font->Draw(renderer, valstr, x - _font->Measure(valstr), y);
      }

      switch (_state)  {
         case None:
            renderer.Drawimage(_img, x, y, _buttonWidth, height, 0, 0, _buttonWidth, height);
            renderer.Drawimage(_img, x + _buttonWidth, y, _buttonWidth, height, _buttonWidth, 0, _buttonWidth, height);
            break;
         case UpClick:
            renderer.Drawimage(_img, x, y, _buttonWidth, height, 0, 0, _buttonWidth, height);
            renderer.Drawimage(_img, x + _buttonWidth, y, _buttonWidth, height, _buttonWidth, height, _buttonWidth, height);
            break;
         case UpHover:
            renderer.Drawimage(_img, x, y, _buttonWidth, height, 0, 0, _buttonWidth, height);
            renderer.Drawimage(_img, x + _buttonWidth, y, _buttonWidth, height, _buttonWidth, height + height, _buttonWidth, height);
            break;
         case DownClick:
            renderer.Drawimage(_img, x, y, _buttonWidth, height, 0, height, _buttonWidth, height);
            renderer.Drawimage(_img, x + _buttonWidth, y, _buttonWidth, height, _buttonWidth, 0, _buttonWidth, height);
            break;
         case DownHover:
            renderer.Drawimage(_img, x, y, _buttonWidth, height, 0, height + height, _buttonWidth, height);
            renderer.Drawimage(_img, x + _buttonWidth, y, _buttonWidth, height, _buttonWidth, 0, _buttonWidth, height);
            break;
      }
   }

}
