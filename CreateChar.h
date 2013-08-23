#pragma once

#include "gamestates.h"
#include "ImageLoader.h"
#include "Layout.h"
#include "Button.h"
#include "ListBox.h"
#include "TextBox.h"
#include "UpDown.h"
#include "Label.h"

class CreateChar : public GameState  {
public:
   CreateChar();
   virtual ~CreateChar();

   virtual void OnPush();
   virtual void OnPop();
   virtual void Update(const ActionMap & actions, unsigned int tElapsed);
   virtual void Draw(RenderDevice::Renderer& render, unsigned int tElapsed);

   static void CreateClick(GUI::Control * sender);
   static void CancelClick(GUI::Control * sender);

private:
   GUI::Font * _font;
   GUI::Button * _create;
   GUI::Button * _cancel;
   GUI::ListBox * _traits;
   GUI::Frame * _stats;
   GUI::Layout * _statslayout;
   GUI::TextBox * _name;
   IMAGEHANDLE _bg;
   IMAGEHANDLE _listIcons;

};
