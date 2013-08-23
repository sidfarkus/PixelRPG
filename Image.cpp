
#include "Image.h"

Image::Image()  {
   _img = NULL;
   _width = 0;
   _height = 0;
   _refs = 0;
}

Image::Image(const char * filename)  {
   _img = NULL;
   _refs = 0;

   Load(filename);
}

Image::Image(const Image& image)  {
   _width = image._width;
   _height = image._height;
   _img = image._img;
   _refs = image._refs;
}

const Image& Image::operator=(const Image& rhs)  {
   if (this == &rhs) return *this;

   _width = rhs._width;
   _height = rhs._height;
   _refs = rhs._refs;

   if (_img != NULL)
      SDL_FreeSurface(_img);

   _img = rhs._img;
   return *this;
}

int Image::Load(const char * filename)  {
   SDL_Surface * tempimg;

   if (_img)
      SDL_FreeSurface(_img);

   tempimg = IMG_Load(filename);
   if (tempimg == NULL ) return -1;

   SDL_SetColorKey(tempimg, SDL_SRCCOLORKEY | SDL_RLEACCEL, DEFAULT_COLORKEY);
   _img = SDL_DisplayFormat(tempimg);

   if (_img)  {
      _width = _img->w;
      _height = _img->h;
      _refs = 1;
   } else
      return -1;

   SDL_FreeSurface(tempimg);
   return 1;
}

void Image::GetPixels(unsigned int colors[], int size, int x, int y)  {
   // colors better be size * size big
   if (SDL_MUSTLOCK(_img))
      if (SDL_LockSurface(_img) < 0) return;

   int _stride = 0, xsize = 0, ysize = 0;
   x = (x < 0) ? 0 : (x > _img->w) ? _img->w : x;
   y = (y < 0) ? 0 : (y > _img->h) ? _img->h : y;
   xsize = (x + size > _img->w) ? _img->w : (x + size < 0) ? 0 : x + size;
   ysize = (y + size > _img->h) ? _img->h : (y + size < 0) ? 0 : y + size;

   if (_img->format->BitsPerPixel == 32)  {
      
      _stride = _img->pitch / 4;

      for (int i = y; i < ysize; i++)  {
         for (int j = x; j < xsize; j++)  {
            colors[(j - x) + (i - y) * size] = ((unsigned int*) _img->pixels)[j + i * _stride];
         }
      }

   }  else  {

      _stride = _img->pitch / 2;

      for (int i = y; i < ysize; i++)  {
         for (int j = x; j < xsize; j++)  {
            colors[(j - x) + (i - y) * size] = ((unsigned short*) _img->pixels)[j + i * _stride];
         }
      }
   }

   SDL_UnlockSurface(_img);
}

int Image::FromMemory(const char * buffer)  {

   return 1;
}

void Image::MakeEmpty(int width, int height)  {
   if (_img)
      Release();

   SDL_Surface * tempimg = SDL_CreateRGBSurface(SDL_SRCCOLORKEY, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
   _img = SDL_DisplayFormat(tempimg);

   SDL_FreeSurface(tempimg);
}

void Image::Release()  {
   if (_img)
      SDL_FreeSurface(_img);
   _img = NULL;
}
