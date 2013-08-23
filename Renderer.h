#pragma once

#include <string>
#include <math.h>
#include "SDLInclude\\SDL.h"
#include "ImageLoader.h"
#include "Exception.h"
#include "Color.h"
#include "Image.h"

class RenderDevice  {
public:

   // Supports the following modes
   enum ScreenMode  {
      NoMode,
      a640x480x16,
      a640x480x32,
      a800x600x16,
      a800x600x32,
      a1024x768x16,
      a1024x768x32,
      a1280x960x16,
      a1280x960x32,
      a1440x900x16,
      a1440x900x32,
      a1280x1024x16,
      a1280x1024x32,
      a1680x1050x16,
      a1680x1050x32,
      a1600x1200x16,
      a1600x1200x32,
      a1920x1200x16,
      a1920x1200x32
   };

   // Stub class to allow outside rendering to be done without capability
   // for modifying the main renderer (created by renderdevice)
   class Renderer  {
   public:      
      Renderer(RenderDevice * dev) {_device = dev;}

      inline void Resetclip()  {
         if (_device) _device->ResetClip();
      }

      inline void Setclip(const SDL_Rect & rect)  {
         if (_device) _device->SetClip(rect);
      }

      inline void Setclip(int x, int y, int wide, int tall)  {
         if (_device) _device->SetClip(x, y, wide, tall);
      }

      inline void Changecursor(IMAGEHANDLE newPic)  {
         if (_device) _device->SetCursorPic(newPic);
      }

      inline void Drawline(int x1, int y1, int x2, int y2, const Color& c)  {
         if (_device) _device->DrawLine(x1, y1, x2, y2, c);
      }

      inline void Hline(int x1, int x2, int y, const Color& c)  {
         if (_device) _device->DrawHLine(x1, x2, y, c);
      }

      inline void Vline(int x, int y1, int y2, const Color& c)  {
         if (_device) _device->DrawVLine(x, y1, y2, c);
      }

      inline void Drawimage(const Image& img, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false)  {
         if (_device) _device->DrawImage(img, x, y, w, h, tu, tv, tw, th, tile);
      }

      inline void Drawimage(IMAGEHANDLE hwnd, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false)  {
         if (_device) _device->DrawImage(hwnd, x, y, w, h, tu, tv, tw, th, tile);
      }

      inline void Drawtoimage(IMAGEHANDLE src, IMAGEHANDLE dest, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false)  {
         if (_device) _device->DrawToImage(src, dest, x, y, w, h, tu, tv, tw, th, tile);
      }

      inline void Drawtoimage(const Image& src, const Image& dest, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false)  {
         if (_device) _device->DrawToImage(src, dest, x, y, w, h, tu, tv, tw, th, tile);
      }

      inline void Fillrect(int x, int y, int width, int height, const Color& c)  {
         if (_device) _device->Fill(x, y, width, height, c);
      }

      inline void ClearScreen()  {
         if (_device) _device->Clear();
      }
      
      inline int ScreenWidth() {if (_device) return _device->GetScreenWidth(); return -1;}
      inline int ScreenHeight() {if (_device) return _device->GetScreenHeight(); return -1;}

      friend class RenderDevice;

   protected:      
      RenderDevice * _device;

   };

   RenderDevice();
   virtual ~RenderDevice() {}

   virtual void Initialize(const std::string &caption, ScreenMode m, bool isExclusiveInput = false, bool isFullScreen = false);
   virtual void Release();

   // Performs clearing, setup etc of surfaces
   virtual int Start(bool clear = false);
   virtual int Display();

   // Gets the renderer associated with this device
   virtual Renderer GetRenderer() const;

   virtual void Clear();
   virtual void ResetClip();
   virtual void SetClip(const SDL_Rect & rect);
   virtual void SetClip(int x, int y, int wide, int tall);
   virtual void DrawLine(int x1, int y1, int x2, int y2, const Color& c);
   virtual void DrawHLine(int x1, int x2, int y, const Color& c);
   virtual void DrawVLine(int x, int y1, int y2, const Color& c);
   virtual void DrawImage(const Image& img, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false);
   virtual void DrawImage(IMAGEHANDLE hwnd, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false);
   virtual void DrawToImage(IMAGEHANDLE src, IMAGEHANDLE dest, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false);
   virtual void DrawToImage(const Image& src, const Image& dest, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false);
   virtual void Fill(int x, int y, int width, int height, const Color& c);

   virtual void LoadPicCursor(const char * cursorFile);
   virtual void SetCursorPic(IMAGEHANDLE hwnd, int size = 0, int tu = 0, int tv = 0);
   virtual void DrawCursor(int mx, int my, int tu = 0, int tv = 0, int tw = 0, int th = 0);
   virtual void SetCursorVisible(bool toggle);
   virtual inline bool GetCursorVisible() const {return _showCursor;}
   virtual inline int GetCursorSize() const {return _cursor.Height();}

   virtual int ChangeMode(ScreenMode m) { return 0; }
   virtual int VerifyMode(ScreenMode m) const { return 0; }
   virtual int GetScreenModes(ScreenMode modes[]) const { return 0; }
   virtual inline ScreenMode GetMode() const {return _currentMode;}
   virtual inline int GetScreenWidth() const {if (_screen) return _screen->w;}
   virtual inline int GetScreenHeight() const {if (_screen) return _screen->h;}

protected:
   
   bool _fullScreen;
   bool _showCursor;  
   SDL_Rect _clip;
   ScreenMode _currentMode;
   SDL_Surface * _screen;
   Texture _cursor;

private:
   inline void setpix(int x, int y, Color c) {
      ((unsigned int*)_screen->pixels)[x+y*_stride]=ColorToLong(c);
   }

   inline void setpix16(int x, int y, Color c) {
      ((unsigned short*)_screen->pixels)[x+y*_stride]=(short)ColorToLong(c);
   }

   inline Color getpix(int x, int y) const {
      return LongToColor(((unsigned int*)_screen->pixels)[x+y*_stride]);
   }

   inline Color getpix16(int x, int y) const {
      return LongToColor(((unsigned short*)_screen->pixels)[x+y*_stride], 16);
   }

   unsigned int _stride;

};

std::string ModeToString(const RenderDevice::ScreenMode mode);
void ModeDetails(const RenderDevice::ScreenMode mode, int& width, int& height, int& depth);
