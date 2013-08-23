#pragma once

#include "SDLInclude\\SDL_opengl.h"
#include "Image.h"
#include <string>

class Texture : public Image  {
public:
   Texture();
   Texture(const std::string & filename);
   Texture(const Texture & tex);
   virtual ~Texture();
   //const Texture& operator=(const Texture & rhs);

   virtual int Load(const char * filename);
   virtual int FromMemory(const char * buffer);
   virtual void MakeEmpty(int width, int height);
   virtual void Release();

   //virtual void GetPixels(unsigned int colors[], int size, int x, int y);
   virtual inline bool IsLoaded() const {return _texture != 0;}

   friend class GLRenderDevice;

private:
   // assume 32 bit integer >:D
   inline int NextPowerofTwo(int n)  {
      n = n - 1;
      n = n | (n >> 1);
      n = n | (n >> 2);
      n = n | (n >> 4);
      n = n | (n >> 8);
      n = n | (n >> 16);
      return n + 1;
   }

   GLuint _texture;
};
