#include "CheckBox.h"

#pragma warning(disable : 4482)

namespace GUI  {
   Align CheckBox::CaptionAlign = Align::Left;

   CheckBox::CheckBox(const char * boxfile, Font * font, const char * text, unsigned int boxwide, int x, int y, unsigned int w, unsigned int h) 
      : Control(x, y, w, h) {
      _checked = false;
      _boximage = ImageLoader::Load(boxfile);
      _font = font;
      _boxwidth = boxwide;
      _caption = text;
      width = boxwide + 2 + _font->Measure(_caption);
   }

   CheckBox::CheckBox(const CheckBox & box) : Control(box.X(), box.Y(), box.Width(), box.Height())  {
      _checked = box.Checked();
      _boximage = box._boximage;
      _font = box._font;
      _boxwidth = box._boxwidth;
      _caption = std::string(box._caption);
   }

   CheckBox::~CheckBox()  {
   }

   bool CheckBox::Update(const ActionMap & actions, unsigned int tElapsed)  {
      const InputState & input = *actions.GetInputState();

      if ((input.mouseX >= x) && (input.mouseX <= x + _boxwidth) &&
          (input.mouseY >= y) && (input.mouseY <= y + (int) height))  {
         
          if (input.mbPressed & MOUSE_B1)  {
             _checked = !_checked;

             if (_onClick) _onClick(this);
          }

          if (_onHover) _onHover(this);
          return true;
      }

      return false;
   }
    
   void CheckBox::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      int capWide = _font->Measure(_caption);

      if (_checked)  {
         renderer.Drawimage(_boximage, x, y, _boxwidth, height, _boxwidth, 0, _boxwidth, 0);
      } else
         renderer.Drawimage(_boximage, x, y, _boxwidth, height, 0, 0, _boxwidth, 0);

      // maybe switch to use a label or something
      switch (CaptionAlign)  {
         case Align::Right:
            _font->Draw(renderer, _caption, x + _boxwidth + 2, static_cast<int>(y + (height - _font->Height()) / 2.0f));
            break;
         case Left:
            _font->Draw(renderer, _caption, x - capWide - 2, static_cast<int>(y + (height - _font->Height()) / 2.0f));
            break;
         case Align::Bottom:
            _font->Draw(renderer, _caption, static_cast<int>(x - (int) (capWide / 2.0f) + (_boxwidth / 2.0f)), y + _boxwidth);
            break;
         case Top:
            _font->Draw(renderer, _caption, static_cast<int>(x - (int) (capWide / 2.0f) + (_boxwidth / 2.0f)), y - _font->Height());
            break;
         case Center:
            // No center alignment available
            break;
      }

   }

}
