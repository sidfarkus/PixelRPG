#include "Texture.h"

Texture::Texture() : Image() {
   _texture = 0;
}

Texture::Texture(const std::string & filename) : Image() {
   _texture = 0;

   Load(filename.c_str());
}

Texture::Texture(const Texture & tex)  {
   _width = tex._width;
   _height = tex._height;
   _refs = _refs;
   _texture = tex._texture;
}

Texture::~Texture()  {
   if(_texture) 
      glDeleteTextures( 1, &_texture );
}

//const Texture& Texture::operator=(const Texture & rhs)  {
//   if (this == &rhs) return *this;
//
//   _texture = rhs._texture;
//   _width = rhs._width;
//   _height = rhs._height;
//   _refs = rhs._refs;
//   
//}

int Texture::Load(const char * filename)  {

   // To simplify things, load to a surface then copy to a texture
   if (Image::Load(filename) < 0) return -1;
   if (_texture)
      Release();

   int newWidth = _width, newHeight = _height;
   if ((Width() & (Width() - 1)) != 0) {
      newWidth = NextPowerofTwo(Width());
   }

   if ((Height() & (Height() - 1)) != 0) {
      newHeight = NextPowerofTwo(Height());
   }

   // Copy to a new surface to process the alpha
   SDL_Surface * temp = _img;

   // ABGR
   SDL_Surface * tempimg = SDL_CreateRGBSurface(SDL_SRCCOLORKEY, newWidth, newHeight, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
   _img = SDL_DisplayFormat(tempimg);

   SDL_FreeSurface(tempimg);
   
   // copy everything over
   int end = temp->h * temp->pitch / temp->format->BytesPerPixel;
   for (unsigned int i = 0; i < end; i++)  {

	   
	   
	   unsigned int val = ((unsigned int *) temp->pixels)[i];

      if (val != 0x00FF00FF)
         ((unsigned int *) _img->pixels)[i] = 0xFF000000 | val;
      else
         ((unsigned int *) _img->pixels)[i] = 0x00FFFFFF & val;
   }

   // free temp
   SDL_FreeSurface(temp);
    
   // build a texture based on the surface
   glGenTextures(1, &_texture);
   glBindTexture(GL_TEXTURE_2D, _texture);

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width(), Height(), 0, 
                GL_BGRA, GL_UNSIGNED_BYTE, _img->pixels);

   return 0;
}

//void Texture::GetPixels(unsigned int colors[], int size, int x, int y)  {
//}

int Texture::FromMemory(const char * buffer)  {
   return 0;
}

void Texture::MakeEmpty(int width, int height)  {
   Image::MakeEmpty(width, height);

   // build a texture based on the surface
   glGenTextures(1, &_texture);
   glBindTexture(GL_TEXTURE_2D, _texture);

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width(), Height(), 0, 
                GL_BGRA, GL_UNSIGNED_BYTE, _img->pixels);
}

void Texture::Release()  {
   glDeleteTextures( 1, &_texture );
   _texture = 0;
}
