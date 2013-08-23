#include "ImageAnimation.h"

ImageAnimation::ImageAnimation()  {
   _img = -1;
   _width = 0;
   _height = 0;
   _yOffset = 0;
   _frameSize = 0;
   _numFrames = 0;
   _frameTime = 0;
   _position = 0;
}

ImageAnimation::ImageAnimation(const char * filename, int yOffset, int frameWide, int numFrames, unsigned int frameTime)  {
   _img = Load(filename, yOffset, frameWide, numFrames, frameTime);
   const Image * temp = ImageLoader::GetImage(_img);

   if (temp)  {
      _width = temp->Width();
      _height = temp->Height();
   } else {
      _width = 0;
      _height = 0;
   }
}

int ImageAnimation::Load(const char * filename, int yOffset, int frameWide, int numFrames, unsigned int frameTime)  {
   _yOffset = yOffset;
   _frameSize = frameWide;
   _numFrames = numFrames;
   _frameTime = frameTime;
   _position = 0;

   _img = ImageLoader::Load(filename);

   return _img;
}

void ImageAnimation::Play(RenderDevice::Renderer & render, unsigned int tElapsed, int x, int y, bool loop, bool reverse)  {
   if (!_numFrames || !_frameTime) return;

   if (_numFrames == 1)  {
      
      render.Drawimage(_img, x, y, 0, 0, 0, _yOffset, _frameSize, _frameSize);

   } else {

      _position += tElapsed;

      if ((_position >= _frameTime * _numFrames) && loop)  {
         if (reverse) 
            _position -= _frameTime * _numFrames;
         else
            _position -= _frameTime * _numFrames - (_position - _frameTime * _numFrames);
      }

      int xoff = (_position / _frameTime) * _frameSize;
      xoff = (xoff <= _numFrames * _frameSize) ? xoff : (_numFrames - 1) * _frameSize;

      render.Drawimage(_img, x, y, 0, 0, xoff, _yOffset, _frameSize, _frameSize);
   }

}
