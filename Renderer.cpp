
#include "Renderer.h"
#include "Console.h"

extern Console console;

RenderDevice::RenderDevice()  {
   if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
      throw Exception("UNABLE TO INITIALIZE SDL VIDEO");

   _fullScreen = false;
   _showCursor = true;
   _currentMode = NoMode;
   _screen = NULL;
   _clip = SDL_Rect();
   _stride = 0;
}

void RenderDevice::Initialize(const std::string &caption, ScreenMode m, bool isExclusiveInput, bool isFullScreen)  {
   int w, h, d;
   ModeDetails(m, w, h, d);

   // Attempt to get a HW surface
   if (isFullScreen)  {
      _screen = SDL_SetVideoMode(w, h, d, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
      SDL_WM_ToggleFullScreen(_screen);
   }  else 
      _screen = SDL_SetVideoMode(w, h, d, SDL_HWSURFACE | SDL_DOUBLEBUF);

   _currentMode = m;
   console.AddLine(std::string("Video mode set to ") + ModeToString(m));

   if (d == 32) 
      _stride = _screen->pitch / 4; 
   else 
      _stride = _screen->pitch / 2;

   _clip.x = 0; _clip.y = 0;
   _clip.w = w; _clip.h = h;

   _fullScreen = isFullScreen;
   SDL_WM_SetCaption(caption.c_str(), caption.c_str());

   if (isExclusiveInput)
      SDL_WM_GrabInput(SDL_GRAB_ON);

}

void RenderDevice::Release()  {
   SDL_WM_GrabInput(SDL_GRAB_OFF);
}

int RenderDevice::Start(bool clear)  {
   if (clear)
      Clear();

   return 1;
}

int RenderDevice::Display()  {
   return SDL_Flip(_screen);
}

RenderDevice::Renderer RenderDevice::GetRenderer() const  {
   return Renderer((RenderDevice*) this);
}

void RenderDevice::Clear()  {
   if (_screen->format->BitsPerPixel == 32)  {
      for (int i = 0; i < _screen->w * _screen->h; i++)
         ((unsigned int*)_screen->pixels)[i] = 0;
   } else  {
      for (int i = 0; i < _screen->w * _screen->h; i++)
         ((unsigned short*)_screen->pixels)[i] = 0;
   }
}
void RenderDevice::ResetClip()  {
   _clip.x = 0; _clip.y = 0;
   _clip.w = _screen->w; _clip.h = _screen->h;
   SDL_SetClipRect(_screen, NULL);
}

void RenderDevice::SetClip(const SDL_Rect & rect)  {
   _clip = rect;
   SDL_SetClipRect(_screen, &_clip);
}

void RenderDevice::SetClip(int x, int y, int wide, int tall)  {
   _clip.x = x; _clip.y = y;
   _clip.w = wide; _clip.h = tall;
   SDL_SetClipRect(_screen, &_clip);
}

void RenderDevice::DrawImage(const Image& img, int x, int y, int w, int h, int tu, int tv, int tw, int th, bool tile)  {
   if (!img._img) return;

   if (tile)   {
      int xoff, yoff;

      // clip
      if (w < tw) tw = w;
      if (h < th) th = h;

      tw = (tw <= 0) ? img.Width() : tw;
      th = (th <= 0) ? img.Height() : th;

      for (yoff = y; yoff < y + h; yoff += th)  {
         for (xoff = x; xoff < x + w; xoff += tw)  {
            if ((y + h - yoff < th) && (x + w - xoff < tw))
               DrawImage(img, xoff, yoff, 0, 0, tu, tv, x + w - xoff, y + h - yoff);
            else if (y + h - yoff < th)
               DrawImage(img, xoff, yoff, 0, 0, tu, tv, tw, y + h - yoff);
            else if (x + w - xoff < tw)
               DrawImage(img, xoff, yoff, 0, 0, tu, tv, x + w - xoff, th);
            else
               DrawImage(img, xoff, yoff, 0, 0, tu, tv, tw, th);
         }
      }

   } else  {
      SDL_Rect rect, * srcRect = NULL;

      rect.x = x;
      rect.y = y;

      tw = (tw <= 0) ? img.Width() : tw;
      th = (th <= 0) ? img.Height() : th;

      srcRect = new SDL_Rect();
      srcRect->x = tu;
      srcRect->y = tv;
      srcRect->w = tw;
      srcRect->h = th;

      SDL_BlitSurface(img._img, srcRect, _screen, &rect);

      delete srcRect;
   }
}

void RenderDevice::DrawImage(IMAGEHANDLE hwnd, int x, int y, int w, int h, int tu, int tv, int tw, int th, bool tile)  {
   if (hwnd < 0) return;
   const Image * img = ImageLoader::GetImage(hwnd);

   if (tile)   {
      int xoff, yoff;

      // clip
      if (w < tw) tw = w;
      if (h < th) th = h;

      tw = (tw <= 0) ? img->Width() : tw;
      th = (th <= 0) ? img->Height() : th;


      for (yoff = y; yoff < y + h; yoff += th)  {
         for (xoff = x; xoff < x + w; xoff += tw)  {
            if ((y + h - yoff < th) && (x + w - xoff < tw))
               DrawImage(*img, xoff, yoff, 0, 0, tu, tv, x + w - xoff, y + h - yoff);
            else if (y + h - yoff < th)
               DrawImage(*img, xoff, yoff, 0, 0, tu, tv, tw, y + h - yoff);
            else if (x + w - xoff < tw)
               DrawImage(*img, xoff, yoff, 0, 0, tu, tv, x + w - xoff, th);
            else
               DrawImage(*img, xoff, yoff, 0, 0, tu, tv, tw, th);
         }
      }

   } else  {
      SDL_Rect rect, * srcRect = NULL;

      rect.x = x;
      rect.y = y;

      tw = (tw <= 0) ? img->Width() : tw;
      th = (th <= 0) ? img->Height() : th;

      srcRect = new SDL_Rect();
      srcRect->x = tu;
      srcRect->y = tv;
      srcRect->w = tw;
      srcRect->h = th;

      SDL_BlitSurface(img->_img, srcRect, _screen, &rect);

      delete srcRect;
   }
}

void RenderDevice::DrawToImage(IMAGEHANDLE src, IMAGEHANDLE dest, int x, int y, int w, int h, int tu, int tv, int tw, int th, bool tile)  {
   if (src < 0 || dest < 0) return;
   const Image * img = ImageLoader::GetImage(src);
   const Image * dimg = ImageLoader::GetImage(dest);

   if (tile)   {
      int xoff, yoff;

      // clip
      if (w < tw) tw = w;
      if (h < th) th = h;

      tw = (tw <= 0) ? img->Width() : tw;
      th = (th <= 0) ? img->Height() : th;

      for (yoff = y; yoff < y + h; yoff += th)  {
         for (xoff = x; xoff < x + w; xoff += tw)  {
            if ((y + h - yoff < th) && (x + w - xoff < tw))
               DrawToImage(*img, *dimg, xoff, yoff, 0, 0, tu, tv, x + w - xoff, y + h - yoff);
            else if (y + h - yoff < th)
               DrawToImage(*img, *dimg, xoff, yoff, 0, 0, tu, tv, tw, y + h - yoff);
            else if (x + w - xoff < tw)
               DrawToImage(*img, *dimg, xoff, yoff, 0, 0, tu, tv, x + w - xoff, th);
            else
               DrawToImage(*img, *dimg, xoff, yoff, 0, 0, tu, tv, tw, th);
         }
      }


   } else  {
      SDL_Rect rect, * srcRect = NULL;

      rect.x = x;
      rect.y = y;

      tw = (tw <= 0) ? img->Width() : tw;
      th = (th <= 0) ? img->Height() : th;

      srcRect = new SDL_Rect();
      srcRect->x = tu;
      srcRect->y = tv;
      srcRect->w = tw;
      srcRect->h = th;

      SDL_BlitSurface(img->_img, srcRect, dimg->_img, &rect);

      delete srcRect;
   }
}

void RenderDevice::DrawToImage(const Image& src, const Image& dest, int x, int y, int w, int h, int tu, int tv, int tw, int th, bool tile)  {
   if (!src._img) return;

   if (tile)   {
      int xoff, yoff;

      // clip
      if (w < tw) tw = w;
      if (h < th) th = h;

      tw = (tw <= 0) ? src.Width() : tw;
      th = (th <= 0) ? src.Height() : th;

      for (yoff = y; yoff < y + h; yoff += th)  {
         for (xoff = x; xoff < x + w; xoff += tw)  {
            if ((y + h - yoff < th) && (x + w - xoff < tw))
               DrawToImage(src, dest, xoff, yoff, 0, 0, tu, tv, x + w - xoff, y + h - yoff);
            else if (y + h - yoff < th)
               DrawToImage(src, dest, xoff, yoff, 0, 0, tu, tv, tw, y + h - yoff);
            else if (x + w - xoff < tw)
               DrawToImage(src, dest, xoff, yoff, 0, 0, tu, tv, x + w - xoff, th);
            else
               DrawToImage(src, dest, xoff, yoff, 0, 0, tu, tv, tw, th);
         }
      }

   } else  {
      SDL_Rect rect, * srcRect = NULL;

      rect.x = x;
      rect.y = y;

      tw = (tw <= 0) ? src.Width() : tw;
      th = (th <= 0) ? src.Height() : th;

      srcRect = new SDL_Rect();
      srcRect->x = tu;
      srcRect->y = tv;
      srcRect->w = tw;
      srcRect->h = th;

      SDL_BlitSurface(src._img, srcRect, dest._img, &rect);

      delete srcRect;
   }
}

void RenderDevice::DrawLine(int x1, int y1, int x2, int y2, const Color& c)  {
   bool yLong = false;
   int inc, endVal, decInc, j = 0;

   if (SDL_MUSTLOCK(_screen)) 
      if (SDL_LockSurface(_screen) < 0) 
         return;

   if (x1 < 0) x1 = 0; else if (x1 > _screen->w) x1 = _screen->w;
   if (x2 < 0) x2 = 0; else if (x2 > _screen->w) x2 = _screen->w;
   if (y1 < 0) y1 = 0; else if (y1 > _screen->h) y1 = _screen->h;
   if (y2 < 0) y2 = 0; else if (y2 > _screen->h) y2 = _screen->h;

   int shortLen = y2 - y1;
   int longLen = x2 - x1;

   if (abs(shortLen) > abs(longLen)) {
      int swap = shortLen;
      shortLen = longLen;
      longLen = swap;
      yLong = true;
   }

   endVal = longLen;

   if (longLen < 0) {
      inc = -1;
      longLen = -longLen;
   } else 
      inc = 1;

   if (longLen == 0) 
      decInc = 0;
   else 
      decInc = (shortLen << 16) / longLen;

   if (yLong) {	
      for (int i = 0; i != endVal; i += inc) {
         setpix(x1 + (j >> 16), y1 + i, c);	
         j += decInc;
      }
   } else {
      for (int i = 0; i != endVal; i += inc) {
         setpix(x1 + i, y1 + (j >> 16), c);
         j += decInc;
      }
   }

   if (SDL_MUSTLOCK(_screen)) 
      SDL_UnlockSurface(_screen);
}

void RenderDevice::DrawHLine(int x1, int x2, int y, const Color& c)  {
   if (SDL_MUSTLOCK(_screen)) 
      if (SDL_LockSurface(_screen) < 0) 
         return;

   if (x1 > _screen->w) x1 = _screen->w; else if (x1 < 0) x1 = 0;
   if (x2 > _screen->w) x2 = _screen->w; else if (x2 < 0) x2 = 0;
   if (y > _screen->h) y = _screen->h; else if (y < 0) y = 0;

   if (_screen->format->BitsPerPixel == 32)  {
      for (int i = x1; i <= x2; i++)
         setpix(i, y, c);
   }  else  {
      for (int i = x1; i <= x2; i++)
         setpix16(i, y, c);
   }

   if (SDL_MUSTLOCK(_screen)) 
      SDL_UnlockSurface(_screen);
}

void RenderDevice::DrawVLine(int x, int y1, int y2, const Color& c)  {
   if (SDL_MUSTLOCK(_screen)) 
      if (SDL_LockSurface(_screen) < 0) 
         return;

   if (y1 > _screen->h) y1 = _screen->h; else if (y1 < 0) y1 = 0;
   if (y2 > _screen->h) y2 = _screen->h; else if (y2 < 0) y2 = 0;
   if (x > _screen->w) x = _screen->w; else if (x < 0) x = 0;

   if (_screen->format->BitsPerPixel == 32)  {
      for (int i = y1; i <= y2; i++)
         setpix(x, i, c);
   }  else  {
      for (int i = y1; i <= y2; i++)
         setpix16(x, i, c);
   }
   
   if (SDL_MUSTLOCK(_screen)) 
      SDL_UnlockSurface(_screen);
}

void RenderDevice::Fill(int x, int y, int width, int height, const Color& c)  {
   SDL_Rect rect;
   rect.x = x;
   rect.y = y;
   rect.w = width;
   rect.h = height;

   if (_screen->format->BitsPerPixel == 32)
      SDL_FillRect(_screen, &rect, ColorToLong(c));
   else 
      SDL_FillRect(_screen, &rect, (short) ColorToLong(c));
}

void RenderDevice::LoadPicCursor(const char * cursorFile)  {
   if (_cursor.IsLoaded()) _cursor.Release();
   if (_cursor.Load(cursorFile) >= 0)
      SDL_ShowCursor(SDL_DISABLE);
}

void RenderDevice::SetCursorPic(IMAGEHANDLE hwnd, int size, int tu, int tv)  {
   _cursor.Release();

   if (hwnd > -1)  {
      _cursor = *((const Texture *) ImageLoader::GetImage(hwnd));
   }
}
void RenderDevice::DrawCursor(int mx, int my, int tu, int tv, int tw, int th)  {
   if (_showCursor) DrawImage(_cursor, mx, my, 0, 0, tu, tv, tw, th);
}

void RenderDevice::SetCursorVisible(bool toggle)  {
   _showCursor = toggle;
   if (toggle && _cursor.IsLoaded())
       SDL_ShowCursor(SDL_DISABLE);
   else 
       SDL_ShowCursor(SDL_ENABLE);
}

std::string ModeToString(const RenderDevice::ScreenMode mode)  {
   std::string temp;
   switch (mode)  {
    case RenderDevice::a640x480x16:
       temp = "640x480x16";
       break;
    case RenderDevice::a640x480x32:
       temp = "640x480x32";
       break;
    case RenderDevice::a800x600x16:
       temp = "800x600x16";
       break;
    case RenderDevice::a800x600x32:
       temp = "800x600x32";
       break;
    case RenderDevice::a1024x768x16:
       temp = "1024x768x16";
       break;
    case RenderDevice::a1024x768x32:
       temp = "1024x768x32";
       break;
    case RenderDevice::a1280x960x16:
       temp = "1280x960x16";
       break;
    case RenderDevice::a1280x960x32:
       temp = "1280x960x32";
       break;
    case RenderDevice::a1280x1024x16:
       temp = "1280x1024x16";
       break;
    case RenderDevice::a1280x1024x32:
       temp = "1280x1024x32";
       break;
    case RenderDevice::a1600x1200x16:
       temp = "1600x1200x16";
       break;
    case RenderDevice::a1600x1200x32:
       temp = "1600x1200x32";
       break;
    case RenderDevice::NoMode:
       temp = "No Mode";
       break;
   }
   return temp;

}

void ModeDetails(const RenderDevice::ScreenMode mode, int& width, int& height, int& depth)  {
   switch (mode)  {
    case RenderDevice::a640x480x16:
       width = 640;
       height = 480;
       depth = 16;
       break;
    case RenderDevice::a640x480x32:
       width = 640;
       height = 480;
       depth = 32;
       break;
    case RenderDevice::a800x600x16:
       width = 800;
       height = 600;
       depth = 16;
       break;
    case RenderDevice::a800x600x32:
       width = 800;
       height = 600;
       depth = 32;
       break;
    case RenderDevice::a1024x768x16:
       width = 1024;
       height = 768;
       depth = 16;
       break;
    case RenderDevice::a1024x768x32:
       width = 1024;
       height = 768;
       depth = 32;
       break;
    case RenderDevice::a1280x960x16:
       width = 1280;
       height = 960;
       depth = 16;
       break;
    case RenderDevice::a1280x960x32:
       width = 1280;
       height = 960;
       depth = 32;
       break;
    case RenderDevice::a1440x900x16:
       width = 1440;
       height = 900;
       depth = 16;
       break;
    case RenderDevice::a1440x900x32:
       width = 1440;
       height = 900;
       depth = 32;
       break;
    case RenderDevice::a1280x1024x16:
       width = 1280;
       height = 1024;
       depth = 16;
       break;
    case RenderDevice::a1280x1024x32:
       width = 1280;
       height = 1024;
       depth = 32;
       break;
    case RenderDevice::a1680x1050x16:
       width = 1680;
       height = 1050;
       depth = 16;
       break;
    case RenderDevice::a1680x1050x32:
       width = 1680;
       height = 1050;
       depth = 32;
       break;
    case RenderDevice::a1600x1200x16:
       width = 1600;
       height = 1200;
       depth = 16;
       break;
    case RenderDevice::a1600x1200x32:
       width = 1600;
       height = 1200;
       depth = 32;
       break;
    case RenderDevice::a1920x1200x16:
       width = 1920;
       height = 1200;
       depth = 16;
       break;
    case RenderDevice::a1920x1200x32:
       width = 1920;
       height = 1200;
       depth = 32;
       break;
    case RenderDevice::NoMode:
       width = 0;
       height = 0;
       depth = 0;
       break;
   }

}

