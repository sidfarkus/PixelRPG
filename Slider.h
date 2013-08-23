#pragma once

#include "Control.h"
#include "ImageLoader.h"

namespace GUI  {

   class Slider : public Control, public IDraggable  {
   public:
      Slider(const char * imagename, unsigned int buttonwidth, int minvalue, int maxvalue, unsigned int borderwidth, int x, int y, unsigned int wide, unsigned int tall);
      virtual ~Slider();

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

      inline int GetValue() {return _value;}
      inline void SetValue(int val) {_value = val;}
      inline void ValueChanged(void (*valChanged)(Slider *)) {_valChanged = valChanged;}

   private:
      int _value;
      int _minVal, _maxVal;
      unsigned int _bWidth, _border;
      IMAGEHANDLE _img;
      void (* _valChanged)(Slider *);

   };

}
