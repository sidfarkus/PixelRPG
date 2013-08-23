#pragma once

#include "Renderer.h"
#include "ImageLoader.h"

class ImageAnimation  {
public:
   ImageAnimation();
   ImageAnimation(const char * filename, int yOffset, int frameWide, int numFrames, unsigned int frameTime);

   int Load(const char * filename, int yOffset, int frameWide, int numFrames, unsigned int frameTime);
   void Play(RenderDevice::Renderer & render, unsigned int tElapsed, int x, int y, bool loop = false, bool reverse = false);

   inline bool IsLoaded() const {return _img > -1 && _img < static_cast<int>(ImageLoader::MaxHandle());}
   inline int Width() const {return _width;}
   inline int Height() const {return _height;}

private:
   int _position;
   int _yOffset;
   int _frameSize;
   int _numFrames;
   int _width, _height;
   unsigned int _frameTime;
   IMAGEHANDLE _img;
};
