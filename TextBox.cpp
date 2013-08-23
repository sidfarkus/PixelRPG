#include "TextBox.h"

namespace GUI  {
   TextBox::TextBox(const char * image, Font * font, unsigned int borderwidth, int maxLength, int x, int y, unsigned int wide, unsigned int tall) : Control(x,y,wide,tall) {
      _img = ImageLoader::Load(image);
      _border = borderwidth;
      _allowEntry = true;
      _curText = "";
      _cursorDelay = 1;
      _font = font;
      _maxChars = maxLength;
   }

   TextBox::~TextBox()  {
   }

   bool TextBox::Update(const ActionMap & actions, unsigned int tElapsed)  {
      const InputState & input = *actions.GetInputState();

      if (Collide(input.mouseX, input.mouseY))  {
         if (input.mbPressed & MOUSE_B1)
            _allowEntry = true;
      } else if (input.mbPressed & MOUSE_B1)  {
         _allowEntry = false;
         _cursorDelay = 0;
      }

      if (_allowEntry)  {
         char cur = 0;

         for (unsigned int i = 0; i < input.pressed.size(); i++)  {
            cur = input.pressed.at(i).ToChar();

            if (cur)  {
               // backspace
               if (cur == 8)  {
                  if (_curText.length() > 0) _curText.erase(--_curText.end());
               }  else if (cur > 31) {
                  if (_curText.length() < _maxChars) _curText += cur;
               }
            }
         }

         if (_cursorDelay > BLINK_SPEED)
            _cursorDelay = -(_cursorDelay % BLINK_SPEED);
         else if (_cursorDelay < -BLINK_SPEED)
            _cursorDelay = (-_cursorDelay) % BLINK_SPEED;

         if (_cursorDelay > 0)
            _cursorDelay += tElapsed;
         else
            _cursorDelay -= tElapsed;
      }

      return false;
   }

   void TextBox::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      int imgw = 0;

      if (ImageLoader::GetImage(_img))  {
         imgw = ImageLoader::GetImage(_img)->Width();

         renderer.Drawimage(_img, x, y, _border, height, 0, 0, _border, 0);
         renderer.Drawimage(_img, x + _border, y, width - _border - _border, height, _border, 0, imgw - _border - _border, 0, true);
         renderer.Drawimage(_img, x + width - _border, y, _border, height, imgw - _border, 0, _border);
      }

      std::string drawtxt = _curText;
      if (_cursorDelay > 0)  {
         drawtxt += "_";
      }

      renderer.Setclip(x, y, width, height);
      if (_font) _font->Draw(renderer, drawtxt, x + _border, y);
      renderer.Resetclip();

      // debug delay print
      //char * temp = new char[20];
      //sprintf(temp, "delay: %10d", _cursorDelay);
      //_font->Draw(renderer, temp, x, y + 20);
      //delete temp;

   }
}
