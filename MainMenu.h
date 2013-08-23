#pragma once

#include <sstream>
#include "GameStates.h"
#include "InputState.h"
#include "Renderer.h"
#include "Resources.h"
#include "Button.h"
#include "Layout.h"
#include "SoundLoader.h"

class MainMenuState : public GameState {
public:
   MainMenuState();
   virtual ~MainMenuState();
   virtual void OnPush();
   virtual void OnPop();
   virtual void Update(const ActionMap & actions, unsigned int tElapsed);
   virtual void Draw(RenderDevice::Renderer& render, unsigned int tElapsed);

   static void PlayClick(GUI::Control * sender);
   static void ExitClick(GUI::Control * sender);
   static void OptionsClick(GUI::Control * sender);
   static void LoadClick(GUI::Control * sender);

private:
   // Main menu items
   GUI::Layout * menu;
   GUI::Font * mainfont;
   GUI::Frame * mainFrame;
   int mx, my;
   float curx;
   IMAGEHANDLE bgImage;
   IMAGEHANDLE bgSky;
};
