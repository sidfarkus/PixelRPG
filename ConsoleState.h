#pragma once

#include <vector>
#include <string>
#include "ImageLoader.h"
#include "Renderer.h"
#include "Console.h"
#include "GameStates.h"
#include "Font.h"
#include "TextBox.h"
#include "Config.h"

struct ConsoleCommand  {
   std::string Command;
   std::vector<std::string> Params;

   ConsoleCommand()  {
      Command = std::string();
      Params = std::vector<std::string>();
   }
};

class ConsoleState : public GameState  {
public:
   ConsoleState(GUI::Font & font);
   virtual ~ConsoleState();

   virtual void OnPush();
   virtual void OnPop();
   virtual void Draw(RenderDevice::Renderer& render, unsigned int tElapsed);
   virtual void Update(const ActionMap & actions, unsigned int tElapsed);

private:
   ConsoleCommand _parseCommand(const std::string & line);

   int _height;
   bool _isOpening;
   GUI::Font * _font;
   GUI::TextBox * _input;
   IMAGEHANDLE _background;
};
