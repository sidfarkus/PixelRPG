#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "Renderer.h"
#include "Font.h"
#include <time.h>

class Console  {
public:
   Console();
   Console(unsigned int maxLines);

   void AddLine(std::string& line);
   void AddLine(const char * line);
   void DrawView(RenderDevice::Renderer & render, GUI::Font * font) const;
   void ScrollUp(int amount = 1);
   void ScrollDown(int amount = 1);

   void Write(const char * file);

   static const unsigned int MAX_LINES = 2000;

private:
   std::vector<std::string> _lines;
   unsigned int _maxLines;       // Maximum displayable lines
   unsigned int _curTop;         // Index of the top of the console

};

