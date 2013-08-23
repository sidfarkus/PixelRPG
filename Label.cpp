#include "Label.h"

namespace GUI  {

   Label::Label(const char * text, Font * font, int x, int y) : Control(x, y, 0, 0)  {
      _font = font;
      _text = std::string(text);

      if (_font)  {
         width = _font->Measure(text);
         height = _font->Height();
         _cache.MakeEmpty(width, height);
      }
   }

   bool Label::Update(const ActionMap & actions, unsigned int tElapsed)  {
      // Don't process events
      return Control::Update(actions, tElapsed);
   }

   void Label::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      if (_font)  {
         if (_cache.IsLoaded())
            _font->Draw(renderer, _text, x, y);
         else
            _font->Draw(renderer, _text, x, y);
      }
   }

}
