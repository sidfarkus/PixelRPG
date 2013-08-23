#include "Slider.h"
#include "Resources.h"

namespace GUI  {
   Slider::Slider(const char * imagename, unsigned int buttonwidth, int minvalue, int maxvalue, 
      unsigned int borderwidth, int x, int y, unsigned int wide, unsigned int tall) : Control(x, y, wide, tall) {

      _img = ImageLoader::Load(imagename);
      _value = minvalue;
      _minVal = minvalue;
      _maxVal = maxvalue;
      _bWidth = buttonwidth;
      _border = borderwidth;
      _valChanged = NULL;
      _isDragging = false;
   }

   Slider::~Slider()  {
   }

   bool Slider::Update(const ActionMap & actions, unsigned int tElapsed)  {
      const InputState & input = *actions.GetInputState();

      int sliderpos = x + (_value - _minVal) * (width / (float) (_maxVal - _minVal)) - (_bWidth / 2.0f);

      if (input.mbReleased & MOUSE_B1)  {
         _isDragging = false;
         if (_onMouseUp) _onMouseUp(this);
      }

      if ((input.mouseX >= sliderpos) && (input.mouseX <= sliderpos + _bWidth) &&
           (input.mouseY >= y) && (input.mouseY <= y + height))  {

         if (input.mbPressed & MOUSE_B1)  {
            _isDragging = true;
            if (_onMouseDown) _onMouseDown(this);
         }

         return true;
      }

      if (_isDragging)  {
         int old = _value;
         if (input.mouseX >= x + width) 
            _value = _maxVal;
         else if (input.mouseX <= x)
            _value = _minVal;
         else
            _value = _minVal + (int) ((input.mouseX - x) / (float) width * (_maxVal - _minVal));

         if ((old != _value) && _valChanged)
            (*_valChanged)(this);
      }

      return false;
   }
    
   void Slider::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      unsigned int imgw = ImageLoader::GetImage(_img)->Width();

      renderer.Drawimage(_img, x + _border, y, width - _border - _border, height, _bWidth + _border, 0, imgw - _bWidth - _border - _border, 0, true);
      renderer.Drawimage(_img, x, y, _border, height, _bWidth, 0, _border);
      renderer.Drawimage(_img, x + width - _border, y, _border, height, imgw - _border, 0, _border);

      // button
      renderer.Drawimage(_img, x + (_value - _minVal) * (width / (float) (_maxVal - _minVal)) - (_bWidth / 2.0f), y, _bWidth, height, 0, 0, _bWidth);
   }

}
