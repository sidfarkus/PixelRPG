#include "Frame.h"

namespace GUI  {
   Frame::Frame() : Control() {
      _img = -1;
      _top = 0;
      _bottom = 0;
      _left = 0;
      _right = 0;
   }

   Frame::Frame(const char * texture, int topborder, int bottomborder, int leftborder, int rightborder, 
      int x, int y, unsigned int wide, unsigned int tall) : 
      Control(x, y, wide + leftborder + rightborder, tall + topborder + bottomborder)
   {
      _img = ImageLoader::Load(texture);
      _top = topborder;
      _bottom = bottomborder;
      _left = leftborder;
      _right = rightborder;
   }

   bool Frame::Update(const ActionMap & actions, unsigned int tElapsed)  {
      return Control::Update(actions, tElapsed);
   }

   bool Frame::Collide(int mx, int my)  {
      if ((mx <= x + width) &&
         (mx >= x) && (my >= y) &&
         (my <= y + height))
         return true;
      return false;
   }

   void Frame::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      if (_img < 0 || ImageLoader::GetImage(_img) == NULL) return;

      int imgw = ImageLoader::GetImage(_img)->Width();
      int imgh= ImageLoader::GetImage(_img)->Height();
      int centerw = width - _left - _right;
      int centerh = height - _top - _bottom;

      // top
      renderer.Drawimage(_img, x, y, 0, 0, 0, 0, _left, _top);
      renderer.Drawimage(_img, x + _left, y, centerw, _top, _left, 0, imgw - (_left + _right), _top, true);
      renderer.Drawimage(_img, x + _left + centerw, y, 0, 0, imgw - _right, 0, _right, _top);

      // middle
      renderer.Drawimage(_img, x, y + _top, _left, centerh, 0, _top, _left, imgh - (_top + _bottom), true);
      renderer.Drawimage(_img, x + _left, y + _top, centerw, centerh, _left, _top, imgw - (_left + _right), imgh - (_top + _bottom), true);
      renderer.Drawimage(_img, x + _left + centerw, y + _top, _right, centerh, imgw - _right, _top, _right, imgh - (_top + _bottom), true);

      // bottom
      renderer.Drawimage(_img, x, y + _top + centerh, 0, 0, 0, imgh - _bottom, _left, _bottom);
      renderer.Drawimage(_img, x + _left, y + _top + centerh, centerw, _bottom, _left, imgh - _bottom, imgw - (_left + _right), _bottom, true);
      renderer.Drawimage(_img, x + _left + centerw, y + _top + centerh, 0, 0, imgw - _right, imgh - _bottom, _right, _bottom);
   }

}
