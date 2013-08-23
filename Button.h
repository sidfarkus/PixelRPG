#pragma once

#include <string>
#include "SoundLoader.h"
#include "Frame.h"
#include "Font.h"

#define BUTTON_NORM 0x01
#define BUTTON_PRESS 0x02
#define BUTTON_HOVER 0x04
typedef unsigned char BUTTONSTATE;

namespace GUI  {

   class Button : public Frame, public IClickable {
   public:
      Button();
      Button(const char * normPic, const char * hoverPic, const char * downPic, Font * font, int topborder, int bottomborder, int leftborder, int rightborder, 
            int x, int y, unsigned int wide, unsigned int tall, const char * caption = "\0");

      ~Button() {
         ImageLoader::TryRelease(_norm);
         ImageLoader::TryRelease(_hover);
         ImageLoader::TryRelease(_down);
      }

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

      inline std::string GetCaption() const {return _caption;}
      inline void SetCaption(std::string text)  {_caption = text;}
      inline void SetClickSound(const std::string & file) {_clicksound = SoundLoader::Load(file);}
      inline void SetHoverSound(const std::string & file) {_hoversound = SoundLoader::Load(file);}

   private:
      SOUNDHANDLE _clicksound, _hoversound;
      IMAGEHANDLE _norm, _hover, _down;
      std::string _caption;
      Font * _font;
      BUTTONSTATE _state;
   };

}
