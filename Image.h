#ifndef IMAGE_H
#define IMAGE_H

#include "SDLInclude\\SDL.h"
#include "SDLInclude\\SDL_image.h"
#include "Color.h"
#include "Exception.h"

const unsigned int DEFAULT_COLORKEY = 0xFFFF00FF;

class Image  {
public:
   Image();
   Image(const char * filename);
   Image(const Image& image);
   virtual ~Image() {}
   const Image& operator=(const Image& rhs);

   virtual int Load(const char * filename);
   virtual int FromMemory(const char * buffer);
   virtual void MakeEmpty(int width, int height);
   virtual void Release();

   virtual void GetPixels(unsigned int colors[], int size, int x, int y);
   inline SDL_Surface * const GetSurface() const { return _img; }

   virtual inline bool IsLoaded() const {return _img != NULL;}
   inline int Width() const {return _width;}
   inline int Height() const {return _height;}

   friend class RenderDevice;
   friend class ImageLoader;

protected:
   int _refs;
   int _width;
   int _height;
   SDL_Surface * _img;

};

#endif
