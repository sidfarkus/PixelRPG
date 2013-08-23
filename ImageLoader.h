#pragma once

#include <vector>
#include <deque>
#include "Image.h"
#include "Texture.h"

typedef int IMAGEHANDLE;

class ImageLoader  {
public:
   static IMAGEHANDLE Load(const char * filename, bool fromMemory = false);
   static const Image * GetImage(IMAGEHANDLE hwnd);
   static void ReleaseAll();
   static void TryRelease(IMAGEHANDLE & hwnd);

   static unsigned int MaxHandle() {return (unsigned int) _images.size();}

private:
   ImageLoader() {}
   static std::vector< std::pair<const char *, Image *> > _images;
   static std::deque<int> _freeIndices;

};
