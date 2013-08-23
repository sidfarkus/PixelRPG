#include "ConsoleState.h"
#include "Resources.h"
#include <sstream>

#pragma warning(disable : 4482)

extern Console console;
extern ConfigFile Preferences;

ConsoleState::ConsoleState(GUI::Font & font) {
   _font = &font;
   _isOpening = false;
   _height = 0;
   _background = -1;
   _input = NULL;
}

ConsoleState::~ConsoleState()  {
}

void ConsoleState::OnPush()  {
   _isOpening = true;
   _background = ImageLoader::Load((GUI_PATH + "interlace.png").c_str());
   _input = new GUI::TextBox("", _font, 1, 200, 0, 310 - _font->Height() - 1, 800, _font->Height());
}

void ConsoleState::OnPop()  {
   _height = 0;
   delete _input;
   _input = NULL;
}

void ConsoleState::Draw(RenderDevice::Renderer& render, unsigned int tElapsed)  {
   
   if (_isOpening)  {
      if (_height < 310) {
         _height += tElapsed * 5;
      } else if (_height >= 310) {
         _height = 310;
         _isOpening = false;
      }
   }

   render.Fillrect(0, 0, render.ScreenWidth(), _height, Color(0.1f, 0.1f, 0.1f, 0));
   render.Fillrect(0, _height - _font->Height() - 2, render.ScreenWidth(), _font->Height() + 2, Color(0.3f, 0.3f, 0.3f, 0));
   render.Drawimage(_background, 0, _height, render.ScreenWidth(), render.ScreenHeight() - _height); 

   render.Setclip(0, 0, render.ScreenWidth(), _height - _font->Height() - 2);
   console.DrawView(render, _font);
   render.Resetclip();

   _input->Draw(render, tElapsed);

}

void ConsoleState::Update(const ActionMap & actions, unsigned int tElapsed)  {
   const InputState & input = *actions.GetInputState();

   if (input.KeyDown(SDLKey::SDLK_PAGEUP))
      console.ScrollUp(3);

   if (input.KeyDown(SDLKey::SDLK_PAGEDOWN))
      console.ScrollDown(3);

   if (!input.KeyDown(SDLKey::SDLK_BACKQUOTE))
      _input->Update(actions, tElapsed);

   if (input.KeyDown(SDLKey::SDLK_RETURN)) {
      ConsoleCommand c = _parseCommand(_input->GetText());

      if (c.Command == "dumplog")  {

         if (c.Params.size() > 0) 
            console.Write(c.Params.at(0).c_str());
         else
            console.Write("console.log");

         console.AddLine("Successfully wrote console log to file!");

      } else if (c.Command == "showfps")  {

         Preferences.SetValue<bool>("SHOWFPS", !Preferences.GetValue<bool>("SHOWFPS"));
         if (Preferences.GetValue<bool>("SHOWFPS"))
            console.AddLine("Frames per second display on.");
         else
            console.AddLine("Frames per second display off.");

      } else
         console.AddLine(std::string("[echo] ") + _input->GetText());

      _input->SetText(std::string(""));
   }
}

ConsoleCommand ConsoleState::_parseCommand(const std::string & line)  {
   std::istringstream is(line);
   ConsoleCommand temp;

   is >> temp.Command;

   std::string tempstr = "";

   while (!is.eof())  {
      is >> tempstr;
      temp.Params.push_back(tempstr);
   }

   return temp;
}
