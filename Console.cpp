#include "Console.h"

Console console = Console();

Console::Console()  {
  _maxLines = 18;
  _curTop = 0;
}

Console::Console(unsigned int maxLines)  {
  _maxLines = maxLines;
  _curTop = 0;
}

void Console::AddLine(std::string& line)  {
   char * t = new char[10];
   _strtime(t);
   _lines.push_back(t + (": " + line));

   if (_lines.size() > _maxLines)
      _curTop = _lines.size() - _maxLines;

   if (_lines.size() > MAX_LINES)
      _lines.erase(_lines.begin(), _lines.begin() + (_lines.size() - MAX_LINES));

   delete[] t;
}

void Console::AddLine(const char * line)  {
   char * t = new char[10];
   _strtime(t);
   _lines.push_back(t + (": " + std::string(line)));

   if (_lines.size() > _maxLines)
      _curTop = _lines.size() - _maxLines;
}

void Console::DrawView(RenderDevice::Renderer & render, GUI::Font * font) const  {
   if (_lines.size() == 0) return;

   int end = (_curTop + _maxLines >= _lines.size()) ? _lines.size() : _curTop + _maxLines;

   for (unsigned int i = end - 1; i >= _curTop; --i)  {
      font->Draw(render, _lines.at(i), 2, (i - _curTop) * font->Height());
      if (i == 0) break;
   }
}

void Console::ScrollUp(int amount)  {
  if (_curTop > amount) _curTop -= amount; else _curTop = 0;
}

void Console::ScrollDown(int amount)  {
  if ((_lines.size() - _curTop > _maxLines) && (_curTop < _lines.size() - 1)) 
     _curTop += amount;

  if (_curTop > _lines.size() - _maxLines) _curTop = _lines.size() - _maxLines;
}

void Console::Write(const char * file)  {
   std::ofstream outfile(file);

   if (!outfile)  {
      AddLine("Unable to write to file" + std::string(file) + "!");
      return;
   }

   outfile << "PixelRPG Console Log" << std::endl
      << "----------------------------------------------" << std::endl << std::endl;

   for (std::vector<std::string>::iterator i = _lines.begin(); i != _lines.end(); i++)  {
      outfile << *i << std::endl;
   }
   
   outfile << "*** End of log ***" << std::endl;
   outfile.close();
}
