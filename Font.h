#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <fstream>
#include <string>
#include "Renderer.h"
#include "ImageLoader.h"
#include "Image.h"

namespace GUI  {

   // Provides font rendering with custom font loader
   class Font  {
   public:
      Font();
      Font(const char * filename);
      ~Font();

      int Load(const char * filename);
      void Draw(RenderDevice::Renderer & renderer, unsigned char letter, int x, int y);
      void Draw(RenderDevice::Renderer & renderer, const char * str, int x, int y);
      void Draw(RenderDevice::Renderer & renderer, const std::string& str, int x, int y);
      void DrawBounded(RenderDevice::Renderer & renderer, const std::string & str, int x, int y, int width, int height);
      
      int Measure(const std::string& str) const;
      inline const int Height() const {
         const Image * img = ImageLoader::GetImage(_img);
         if (img) {
            return img->Height();
         }
         return -1;
      }
      inline bool IsLoaded() const {return _isloaded;}

   private:
      IMAGEHANDLE _img;
      unsigned char _minChar;
      unsigned char _maxChar;
      unsigned char _wMap[256];
      bool _isloaded;
   };
}

#endif
