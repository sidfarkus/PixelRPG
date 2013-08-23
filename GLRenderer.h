#pragma once

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "SDLInclude\\SDL_opengl.h"
#include "Renderer.h"
#include "Exception.h"
#include "Texture.h"

class GLRenderDevice : public RenderDevice {
public:
   GLRenderDevice();
   virtual ~GLRenderDevice();

   virtual void Initialize(const std::string &caption, ScreenMode m, bool isExclusiveInput = false, bool isFullScreen = false);
   virtual void Release();

   // Performs clearing, setup etc of surfaces
   virtual int Start(bool clear = false);
   virtual int Display();

   // Gets the renderer associated with this device
   virtual Renderer GetRenderer() const;

   virtual void ResetClip();
   virtual void SetClip(const SDL_Rect & rect);
   virtual void SetClip(int x, int y, int wide, int tall);

   virtual void Clear();
   virtual void DrawLine(int x1, int y1, int x2, int y2, const Color& c);
   virtual void DrawHLine(int x1, int x2, int y, const Color& c);
   virtual void DrawVLine(int x, int y1, int y2, const Color& c);
   virtual void DrawImage(const Image& img, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false);
   virtual void DrawImage(IMAGEHANDLE hwnd, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false);
   virtual void DrawToImage(IMAGEHANDLE src, IMAGEHANDLE dest, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false);
   virtual void DrawToImage(const Image& src, const Image& dest, int x, int y, int w, int h, int tu = 0, int tv = 0, int tw = 0, int th = 0, bool tile = false);

   virtual void Fill(int x, int y, int width, int height, const Color& c);
   virtual void DrawCursor(int mx, int my, int tu = 0, int tv = 0, int tw = 0, int th = 0);
   virtual void LoadPicCursor(const char * cursorFile);

   virtual int ChangeMode(ScreenMode m) { return 0; }
   virtual int VerifyMode(ScreenMode m) const { return 0; }
   virtual int GetScreenModes(ScreenMode modes[]) const { return 0; }

private:

};
