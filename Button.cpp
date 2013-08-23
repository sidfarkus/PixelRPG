#include "Button.h"

namespace GUI  {

   Button::Button() : IClickable(), Frame() {
      _norm = -1; _hover = -1; _down = -1;
      _font = 0; _state = BUTTON_NORM;
   }

   Button::Button(const char * normPic, const char * hoverPic, const char * downPic, Font * font, int topborder, int bottomborder, int leftborder, int rightborder, 
      int x, int y, unsigned int wide, unsigned int tall, const char * caption) : 
   Frame(normPic, topborder, bottomborder, leftborder, rightborder, x, y, wide, tall), IClickable()
   {
      _norm = _img;
      _hover = ImageLoader::Load(hoverPic);
      _down = ImageLoader::Load(downPic);
      _font = font;
      _caption = caption;
      _state = BUTTON_NORM;
   }

   bool Button::Update(const ActionMap & actions, unsigned int tElapsed)  {
      const InputState & input = *actions.GetInputState();

      if (Collide(input.mouseX, input.mouseY))  {

         if (input.mbPressed & MOUSE_B1)  {
            _state = BUTTON_PRESS;
            _clicksound.Play();

            if (_onClick) (*_onClick)(this);

         }  else  if (_state != BUTTON_PRESS) {

            _state = BUTTON_HOVER;
            _hoversound.Play();

            if (_onHover) (*_onHover)(this);

         }  else if (input.mbReleased & MOUSE_B1) {

            _state = BUTTON_HOVER;

         }  else
            _state = BUTTON_HOVER;

      }  else  {
         if (_state == BUTTON_PRESS)  {
            if (input.mbReleased & MOUSE_B1 || !input.mbPressed & MOUSE_B1) _state = BUTTON_NORM;
         } else
            _state = BUTTON_NORM;
      }

      return false;
   }

   void Button::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {

      if (_state & BUTTON_NORM) 
         _img = _norm;
      else if (_state & BUTTON_PRESS)
         _img = _down;
      else if (_state & BUTTON_HOVER) 
         _img = _hover;

      Frame::Draw(renderer, tElapsed);

      if (!_font || !_font->IsLoaded()) return;
      int fwide = _font->Measure(_caption) / 2;
      _font->Draw(renderer, _caption, x + (width >> 1) - fwide, y+(height >> 1) - (_font->Height() >> 1));

   }

}
