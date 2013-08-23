#include "GLRenderer.h"
#include "Console.h"

extern Console console;

GLRenderDevice::GLRenderDevice()  {
   if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
      throw Exception("UNABLE TO INITIALIZE SDL VIDEO");

   // set opengl to be double buffered
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

GLRenderDevice::~GLRenderDevice()  {
}

void GLRenderDevice::Initialize(const std::string &caption, ScreenMode m, bool isExclusiveInput, bool isFullScreen)  {
   int w, h, d;
   ModeDetails(m, w, h, d);

   if (isFullScreen)  {
      _screen = SDL_SetVideoMode(w, h, d, SDL_OPENGL | SDL_FULLSCREEN);
      SDL_WM_ToggleFullScreen(_screen);
   }  else 
      _screen = SDL_SetVideoMode(w, h, d, SDL_OPENGL);

   _currentMode = m;
   console.AddLine(std::string("Video mode set to ") + ModeToString(m));

   _clip.x = 0; _clip.y = 0;
   _clip.w = w; _clip.h = h;

   _fullScreen = isFullScreen;
   SDL_WM_SetCaption(caption.c_str(), caption.c_str());

   if (isExclusiveInput)
      SDL_WM_GrabInput(SDL_GRAB_ON);

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
   glDisable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);							            
	glEnable(GL_TEXTURE_2D);
   glEnable(GL_SCISSOR_TEST);

   // Set up GL matrices 
   glViewport(0, 0, GetScreenWidth(), GetScreenHeight());
 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
 
   glOrtho(0.0f, GetScreenWidth(), GetScreenHeight(), 0.0f, -1.0f, 1.0f);
	
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

}

void GLRenderDevice::Release()  {
   SDL_WM_GrabInput(SDL_GRAB_OFF);
}

int GLRenderDevice::Start(bool clear)  {
   if (clear) 
      Clear();

   glLoadIdentity();

   return 1;
}

int GLRenderDevice::Display()  {
   SDL_GL_SwapBuffers();
   return 0;
}

RenderDevice::Renderer GLRenderDevice::GetRenderer() const  {
   return RenderDevice::Renderer((RenderDevice *) this);
}

void GLRenderDevice::Clear()  {
   glClear( GL_COLOR_BUFFER_BIT );
}

void GLRenderDevice::ResetClip()  {
   SetClip(_clip.x, _clip.y, _clip.w, _clip.h);
}

void GLRenderDevice::SetClip(const SDL_Rect & rect)  {
   glScissor(rect.x, rect.y, rect.w, rect.h);
}

void GLRenderDevice::SetClip(int x, int y, int wide, int tall)  {
   glScissor(x, y, wide, tall);
}

void GLRenderDevice::DrawLine(int x1, int y1, int x2, int y2, const Color& c)  {					
	glColor4f(c.R, c.G, c.B, c.A);				
	glBegin(GL_LINE_STRIP);				
		glVertex2d((float) x1, (float) y1);						
		glVertex2d((float) x2, (float) y2);													
	glEnd();
   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void GLRenderDevice::DrawHLine(int x1, int x2, int y, const Color& c)  {			
	glColor4f(c.R, c.G, c.B, c.A);				
	glBegin(GL_LINE_STRIP);				
		glVertex2d((float) x1, (float) y);						
		glVertex2d((float) x2, (float) y);													
	glEnd();
   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void GLRenderDevice::DrawVLine(int x, int y1, int y2, const Color& c)  {		
	glColor4f(c.R, c.G, c.B, c.A);				
	glBegin(GL_LINE_STRIP);				
		glVertex2d((float) x, (float) y1);						
		glVertex2d((float) x, (float) y2);													
	glEnd();	
   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void GLRenderDevice::DrawImage(const Image& img, int x, int y, int w, int h, int tu, int tv, int tw, int th, bool tile)  {
   Texture * tex = dynamic_cast<Texture *>(const_cast<Image *>(&img));

   if (tex)  {
      if (tile)  { 
         int yoff, xoff;

         // clip
         if (w < tw) tw = w;
         if (h < th) th = h;

         tw = (tw <= 0) ? tex->Width() : tw;
         th = (th <= 0) ? tex->Height() : th;

         for (yoff = y; yoff < y + h; yoff += th)  {
            for (xoff = x; xoff < x + w; xoff += tw)  {
               if ((y + h - yoff < th) && (x + w - xoff < tw))
                  DrawImage(*tex, xoff, yoff, 0, 0, tu, tv, x + w - xoff, y + h - yoff);
               else if (y + h - yoff < th)
                  DrawImage(*tex, xoff, yoff, 0, 0, tu, tv, tw, y + h - yoff);
               else if (x + w - xoff < tw)
                  DrawImage(*tex, xoff, yoff, 0, 0, tu, tv, x + w - xoff, th);
               else
                  DrawImage(*tex, xoff, yoff, 0, 0, tu, tv, tw, th);
            }
         }

      }  else  {

         float twf, thf;

         if (tw <= 0)  {
            twf = 1.0f;
            tw = tex->Width();
         } else
            twf = tw / (float) img.Width();

         if (th <= 0)  {
            th = tex->Height();
            thf = 1.0f;
         } else
            thf = th / (float) img.Height();

         float tuf = tu / (float) img.Width();
         float tvf = tv / (float) img.Height();

         glBindTexture(GL_TEXTURE_2D, tex->_texture);

         glBegin(GL_QUADS);
            glTexCoord2f(tuf, tvf);
            glVertex2f(x, y);

            glTexCoord2f(tuf + twf, tvf);
            glVertex2f(x + tw, y);

            glTexCoord2f(tuf + twf, tvf + thf);
            glVertex2f(x + tw, y + th);

            glTexCoord2f(tuf, tvf + thf);
            glVertex2f(x, y + th);
         glEnd();
      }
   }
}

void GLRenderDevice::DrawImage(IMAGEHANDLE hwnd, int x, int y, int w, int h, int tu, int tv, int tw, int th, bool tile)  {
   const Image * img = ImageLoader::GetImage(hwnd);
   if (!img) return;

   DrawImage(*img, x, y, w, h, tu, tv, tw, th, tile);
}

void GLRenderDevice::DrawToImage(IMAGEHANDLE src, IMAGEHANDLE dest, int x, int y, int w, int h, int tu, int tv, int tw, int th, bool tile)  {
}

void GLRenderDevice::DrawToImage(const Image& src, const Image& dest, int x, int y, int w, int h, int tu, int tv, int tw, int th, bool tile)  {
}

void GLRenderDevice::Fill(int x, int y, int width, int height, const Color& c)  {
   glBindTexture( GL_TEXTURE_2D, 0);
   glColor3f(c.R, c.G, c.B);
   glBegin( GL_QUADS );
      glVertex2i(x, y);
      glVertex2i(x + width, y);
      glVertex2i(x + width, y + height);
      glVertex2i(x, y + height);
   glEnd();
   glColor3f(1.0f, 1.0f, 1.0f);
}

void GLRenderDevice::DrawCursor(int mx, int my, int tu, int tv, int tw, int th)  {
   if (_showCursor) 
      DrawImage(_cursor, mx, my, _cursor.Width(), _cursor.Height(), tu, tv, tw, th);
}

void GLRenderDevice::LoadPicCursor(const char * cursorFile)  {
   _cursor.Load(cursorFile);
}
