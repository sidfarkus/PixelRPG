#include "SimpleButton.h"

namespace GUI  {
   SimpleButton::SimpleButton(const std::string & imageFile, int x, int y, int w, int h, int tu, int tv) : Control(x,y,w,h) {
      _img = ImageLoader::Load(imageFile.c_str());
      _tu = tu;
      _tv = tv;
   }

   SimpleButton::~SimpleButton()  {
      ImageLoader::TryRelease(_img);
   }

   bool SimpleButton::Update(const ActionMap & actions, unsigned int tElapsed)  {
      const InputState & input = *actions.GetInputState();
      if (Collide(input.mouseX, input.mouseY))  {

         if (input.mbPressed & MOUSE_B1)  {
            _state = BUTTON_PRESS;

            if (_onClick) (*_onClick)(this);

         }  else  if (_state != BUTTON_PRESS) {

            _state = BUTTON_HOVER;

            if (_onHover) (*_onHover)(this);

         }  else if (input.mbReleased & MOUSE_B1) {

            _state = BUTTON_HOVER;

         }  else
            _state = BUTTON_HOVER;

          return true;

      }  else  {
         if (_state == BUTTON_PRESS)  {
            if (input.mbReleased & MOUSE_B1 || !input.mbPressed & MOUSE_B1) _state = BUTTON_NORM;
         } else
            _state = BUTTON_NORM;
      }

      return false;
   }

   void SimpleButton::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      switch (_state)  {
         case BUTTON_PRESS:
            renderer.Drawimage(_img, x, y, width, height, width + width, 0, width, height);
            break;
         case BUTTON_HOVER:
            renderer.Drawimage(_img, x, y, width, height, width, 0, width, height);
            break;
         case BUTTON_NORM:
            renderer.Drawimage(_img, x, y, width, height, 0, 0, width, height);
            break;
      }
   }

}

