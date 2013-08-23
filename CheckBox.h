#pragma once

#include <string>
#include "ImageLoader.h"
#include "Control.h"
#include "Font.h"

namespace GUI  {
   class CheckBox : public Control, public IClickable {
   public:
      CheckBox(const char * boxfile, Font * font, const char * text, unsigned int boxwide, int x, int y, unsigned int w, unsigned int h);
      CheckBox(const CheckBox & box);
      virtual ~CheckBox();

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

      inline std::string GetCaption() const {return _caption;}
      inline void SetCaption(std::string & caption) {_caption = caption;}
      inline bool Checked() const {return _checked;}
      inline void SetChecked(bool val) {_checked = val;}

      static Align CaptionAlign;

   private:

      int _boxwidth;
      bool _checked;
      IMAGEHANDLE _boximage;
      Font * _font;
      std::string _caption;

   };

}