#include "ImageLoader.h"
#include "Console.h"
#include "Config.h"

extern Console console;
extern ConfigFile Preferences;

std::vector< std::pair<const char *, Image *> > ImageLoader::_images;
std::deque<int> ImageLoader::_freeIndices;

IMAGEHANDLE ImageLoader::Load(const char * filename, bool fromMemory)  {
   int found = -1;

   if (fromMemory)  {
      Image * newImage = new Image();
      
      if (newImage->FromMemory(filename))  {
      }

      return -1;
   }

   for (unsigned int i = 0; i < _images.size(); i++)
      if (strcmp(_images.at(i).first, filename) == 0) { found = i; break; }

   if (found < 0)  {
      Image * newimage;

      if (Preferences.GetValue<bool>("USE_SDLBLITTER"))
         newimage = new Image();
      else
         newimage = new Texture();

      char * name = new char[strlen(filename)];
      strcpy(name, filename);

      if (newimage->Load(filename) >= 0)  {
         int spot = 0;

         if (!_freeIndices.size())  {
            _images.push_back(std::pair<const char *, Image *>(name, newimage));
            spot = _images.size() - 1;
         }  else  {
            _images[_freeIndices.front()] = std::pair<const char *, Image *>(name, newimage);
            spot = _freeIndices.front();
            _freeIndices.pop_front();
         }

         console.AddLine(std::string("Loaded image <") + filename + ">");
         return spot;

      } else
         return -1;

   } else  {

      _images.at(found).second->_refs++;
      return found;

   }
}

const Image * ImageLoader::GetImage(IMAGEHANDLE hwnd)  {
   if ((hwnd < 0) || (hwnd >= _images.size())) {
      return NULL;
   }

   return _images.at(hwnd).second;
}

void ImageLoader::ReleaseAll()  {
   for (unsigned int i = 0; i < _images.size(); i++)  {
      _images.at(i).second->Release();
      delete _images.at(i).second;
   }
}

void ImageLoader::TryRelease(IMAGEHANDLE & hwnd)  {
   if (hwnd < 0 || hwnd >= _images.size()) return;

   _images[hwnd].second->_refs--;
   
   if (_images.at(hwnd).second->_refs < 1)  {
     
      console.AddLine(std::string("Image <") + _images.at(hwnd).first + "> released.");
      _images[hwnd].second->Release();
      _images[hwnd].first = "";
      _freeIndices.push_back(hwnd);

      hwnd = -1;
   }
      
}
