#include "Statics.h"

StaticObject::StaticObject(const std::string & name, const ImageAnimation & image) : 
 _img(image), _name(name)
{
   SetX(0);
   SetY(0);
   SetWidth(image.Width());
   SetHeight(image.Height());
}

 StaticObject::StaticObject(const std::string & name, const ImageAnimation & image, int x, int y, int w, int h) :
 _img(image), _name(name)
{
   SetX(x);
   SetY(y);

   if (w && h)  {
      SetWidth(w);
      SetHeight(h);
   } else {
      SetWidth(image.Width());
      SetHeight(image.Height());      
   }
}

StaticObject::~StaticObject()  {
}

void StaticObject::Draw(RenderDevice::Renderer & render, unsigned int tElapsed, int sX, int sY)  {
   if (_img.IsLoaded())  {

      int x = X() - sX;
      int y = Y() - sY;

      _img.Play(render, tElapsed, x, y, true);
   }
}
