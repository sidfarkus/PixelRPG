#pragma once

#include "GameStates.h"
#include "Console.h"
#include "Resources.h"
#include "ImageLoader.h"
#include "Frame.h"
#include "Button.h"
#include "Layout.h"
#include "Multibar.h"
#include "CheckBox.h"
#include "Font.h"
#include "Slider.h"
#include "TextBox.h"
#include "ListBox.h"
#include "Label.h"

class OptionsMenuState : public GameState  {
public:
   OptionsMenuState();
   virtual ~OptionsMenuState();

   virtual void OnPush();
   virtual void OnPop();
   virtual void Draw(RenderDevice::Renderer& render, unsigned int tElapsed);
   virtual void Update(const ActionMap & actions, unsigned int tElapsed);

   // callbacks
   static void CancelClick(GUI::Control * sender);
   static void windowedClick(GUI::Control * sender);
   static void soundClick(GUI::Control * sender);
   static void SaveClick(GUI::Control * sender);
   static void SoundVolChanged(GUI::Slider * sender);
   static void MusicVolChanged(GUI::Slider * sender);

private:
   GUI::Frame * frame;
   GUI::Button * saveButton;
   GUI::Button * cancelButton;
   GUI::Layout * controlLayout;
   GUI::Font * font;
   GUI::Font * titlefont;
};
