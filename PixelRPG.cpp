// we don't care about enum scope
#pragma warning(disable : 4482)

#pragma comment (lib, "sdl.lib")
#pragma comment (lib, "sdl_image.lib")
#pragma comment (lib, "sdl_mixer.lib")
#pragma comment (lib, "lua5.1.lib")

#define WIN32_LEAN_AND_MEAN

#include "windows.h"
#include "SDLInclude\\SDL.h"
#include "Console.h"
extern Console console;

#ifdef TIME4DEBUG
   #include <map>
   #include <string>
   // debug tracking

   std::map<int, std::string> memorymap;
   inline void * __cdecl operator new(unsigned int size, const char *file, int line)  {
      void *ptr = (void *)malloc(size);
      memorymap[(int) ptr] = std::string(file);
      return(ptr);
   };

   inline void __cdecl operator delete(void *p)  {
      std::map<int, std::string>::iterator x = memorymap.find((int) p);
      if (x != memorymap.end()) memorymap.erase(x);
	   free(p);
   };

   #define DEBUG_NEW new(__FILE__, __LINE__)
#endif

// game code
#include "GameStates.h"
#include "Exception.h"
#include "Renderer.h"
#include "GLRenderer.h"
#include "Config.h"
#include "ActionMap.h"

// resources
#include "Resources.h"
#include "Font.h"
#include "SoundLoader.h"
#include "ImageLoader.h"

// gamestates
#include "MainMenu.h"
#include "ConsoleState.h"
#include "OptionsMenu.h"
#include "CreateChar.h"
#include "MapView.h"
#include "WorldMap.h"

extern ConfigFile Preferences;

RenderDevice * render = NULL;

int APIENTRY WinMain(HINSTANCE hInstance, 
                     HINSTANCE hPrevInstance, 
                     LPSTR lpCmdLine, 
                     int nCmdShow)  
{

   if (SDL_Init(SDL_INIT_TIMER) < 0)  {
      return -1;
   }

   console.AddLine("Initialized SDL Timer.");
   atexit(SDL_Quit);

   try  {

      console.AddLine("Starting RenderDevice...");
      if (Preferences.GetValue<bool>("USE_SDLBLITTER"))  {
         render = new RenderDevice();
      }  else  {
         render = new GLRenderDevice();
      }

      render->Initialize(std::string("PixelRPG"), RenderDevice::a800x600x32, !Preferences.GetValue<bool>("WINDOWED"), !Preferences.GetValue<bool>("WINDOWED"));
      console.AddLine("RenderDevice initialized.");

   } catch (Exception &e)  {

      console.AddLine(std::string("Error!") + e.GetMessage());
      console.Write("console.log");

      return -1;
   }

   SDL_EnableUNICODE(true);
   SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
   if (SoundLoader::Init(Preferences.GetValue<int>("CHANNELS")))  {
      console.AddLine("SoundLoader initilization failed!");
   } else
      console.AddLine("Initialized sound/music playback.");

   SoundLoader::MusicVolume(Preferences.GetValue<int>("MUSICVOL"));
   SoundLoader::SoundVolume(Preferences.GetValue<int>("SOUNDVOL"));

   int mx = 0, my = 0;
   unsigned int oldt = 0, telapsed = 1;
   bool leave = false, showconsole = false;
   bool clearflag = Preferences.GetValue<bool>("CLEAR_BUFFER");
   bool allsleep = false, inputsleep = false;

   SDL_Event event;
   atexit(SoundLoader::Close);
   atexit(ImageLoader::ReleaseAll);

   GUI::Font mainfont = GUI::Font((FONTS_PATH + "vera.fnt").c_str());

   // Register all game states
   GameStates::RegisterState(new MainMenuState(), "Main Menu");
   GameStates::RegisterState(new ConsoleState(mainfont), "Console");
   GameStates::RegisterState(new OptionsMenuState(), "Options Menu");
   GameStates::RegisterState(new MapView(), "Map View");
   GameStates::RegisterState(new CreateChar(), "Create Character");
   GameStates::RegisterState(new WorldMap(), "World Map");

   RenderDevice::Renderer stub = render->GetRenderer();
   render->LoadPicCursor((CURSORS_PATH + "default.png").c_str());
   render->SetCursorVisible(true);

   // start up to main menu
   GameStates::Push("Main Menu");

   // start music
   if (!SoundLoader::PlayMusic(MUSIC_PATH + Preferences.GetValue<std::string>("MAINMENU_MUSIC"), true))
      console.AddLine("Could not load main menu music!");

   // Register key bindings
   ActionMap actionMap;
   actionMap.AddActionMapping(Action("click"), MOUSE_B1);
   actionMap.AddActionMapping(Action("up"), SDLKey::SDLK_UP);
   actionMap.AddActionMapping(Action("down"), SDLKey::SDLK_UP);
   actionMap.AddActionMapping(Action("left"), SDLKey::SDLK_UP);
   actionMap.AddActionMapping(Action("right"), SDLKey::SDLK_UP);

   while (render->Start(clearflag) && !leave)  {
     
      InputState curInput = InputState();
      oldt = SDL_GetTicks();

      // Input
      while (SDL_PollEvent(&event))  {
         switch (event.type)  {
         case SDL_KEYDOWN:
            if (inputsleep) break;

            curInput.pressed.push_back(Key((SDLKey) event.key.keysym.sym, event.key.keysym.unicode));
            curInput.keymod = event.key.keysym.mod;
            break;
         case SDL_KEYUP:
            if (inputsleep) break;

            curInput.released.push_back(Key((SDLKey) event.key.keysym.sym, event.key.keysym.unicode));
            curInput.keymod = event.key.keysym.mod;
            break;
         case SDL_MOUSEMOTION:
            if (inputsleep) break;

            mx = event.motion.x;
            my = event.motion.y;
            break;
         case SDL_MOUSEBUTTONDOWN:
            if (inputsleep) break;

            if (event.button.button == SDL_BUTTON_LEFT)
               curInput.mbPressed = curInput.mbPressed | MOUSE_B1;
            else if (event.button.button == SDL_BUTTON_RIGHT)
               curInput.mbPressed = curInput.mbPressed | MOUSE_B2;
            else if (event.button.button == SDL_BUTTON_MIDDLE)
               curInput.mbPressed = curInput.mbPressed | MOUSE_B3;
            break;
         case SDL_MOUSEBUTTONUP:
            if (inputsleep) break;

            if (event.button.button == SDL_BUTTON_LEFT)
               curInput.mbReleased = curInput.mbReleased | MOUSE_B1;
            else if (event.button.button == SDL_BUTTON_RIGHT)
               curInput.mbReleased = curInput.mbReleased | MOUSE_B2;
            else if (event.button.button == SDL_BUTTON_MIDDLE)
               curInput.mbReleased = curInput.mbReleased | MOUSE_B3;
            break;
         case SDL_ACTIVEEVENT:

            switch (event.active.state)  {
            case SDL_APPACTIVE:
               if (event.active.gain)
                  allsleep = false;
               else
                  allsleep = true;
               break;

            case SDL_APPINPUTFOCUS:
               if (event.active.gain)
                  inputsleep = true;
               else
                  inputsleep = false;
               break;
            }

            break;
         }
      }
      curInput.mouseX = mx;
      curInput.mouseY = my;
      // --

      if (allsleep)  {
         SDL_Delay(1);
         continue;
      }

      actionMap.UpdateMapping(curInput);

      // Console
      if (curInput.KeyDown(SDLKey::SDLK_BACKQUOTE))  {
         showconsole = !showconsole;
         
         if (!showconsole)  {
            GameStates::Pop();
         }  else  {
            GameStates::Push("Console");
         }
      }
     
      // update and draw all game states
      if (GameStates::UpdateStates(stub, actionMap, telapsed))
         break;

      if (Preferences.GetValue<bool>("SHOWFPS"))  {
         std::ostringstream os;
         os << "FPS: " << (1000 / (telapsed > 0 ? telapsed : 1));

         mainfont.Draw(stub, os.str(), 720, 580);
      }

      render->DrawCursor(mx, my);

      render->Display();
      telapsed = SDL_GetTicks() - oldt;
   }

   GameStates::ReleaseStates();
   delete render;

   console.Write("console.log");
   return 0;
}
