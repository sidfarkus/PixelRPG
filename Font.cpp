#include "Font.h"
#include "Resources.h"
#include "Console.h"

extern Console console;

namespace GUI  {

   Font::Font()  {
      _minChar = 0;
      _maxChar = 0;
      _img = -1;

      for (int i = 0; i < 256; i++)
         _wMap[i] = 0;

      _isloaded = false;
   }

   Font::Font(const char * filename)  {
      _img = -1;
      _minChar = 0;
      _maxChar = 0;

      for (int i = 0; i < 256; i++)
         _wMap[i] = 0;

      _isloaded = false;
      Load(filename);
   }

   Font::~Font()  {
      ImageLoader::TryRelease(_img);
   }

   int Font::Load(const char * filename)  {
      // file is structured:
      //  <filename of font texture>
      //  <minChar as byte> <maxChar as byte>
      //  <byte string of length maxChar - minChar with the width in pixels of each letter>

      std::ifstream inFile;
      inFile.open(filename);
      if (!inFile) return -1;

      // load font
      std::string temp;
      std::getline(inFile, temp);

      _img = ImageLoader::Load((std::string(FONTS_PATH) + temp).c_str());
      if (_img < 0)
         return -2;

      // load min/max char
      unsigned char tempByte = 0;
      inFile >> tempByte;
      _minChar = tempByte;

      inFile >> tempByte;
      _maxChar = tempByte;

      // character widths
      char s[256];
      inFile.ignore();
      int n = inFile.readsome(s, 256);

      for (int i = 0; i <= n; i++)
         _wMap[_minChar + i] = s[i];

      inFile.close();

      _isloaded = true;
      console.AddLine(std::string("Font ") + filename + " loaded.");
      return 1;

   }

   void Font::Draw(RenderDevice::Renderer& renderer, unsigned char letter, int x, int y)  {
      if (_img < 0) return;
      const Image * temp = ImageLoader::GetImage(_img);

      if ((letter <= _maxChar) && (letter >= _minChar))  {
         int pos = 0;

         // get x offset
         for (unsigned char i = _minChar; i < letter; i++)
            pos += _wMap[i];

         renderer.Drawimage(*temp, x, y, _wMap[letter], temp->Height(), pos, 0, _wMap[letter], temp->Height());
      }
   }

   void Font::Draw(RenderDevice::Renderer& renderer, const char * str, int x, int y)  {
      if (_img < 0) return;
      const Image * temp = ImageLoader::GetImage(_img);

      unsigned int len = (unsigned int) strlen(str);
      int offset = 0;

      for (unsigned int i = 0; i < len; i++)  {
         if ((str[i] <= _maxChar) && (str[i] >= _minChar))  {
            int pos = 0;

            for (unsigned char j = _minChar; j < str[i]; j++)
               pos += _wMap[j];

            renderer.Drawimage(*temp, x + offset, y, _wMap[str[i]], temp->Height(), pos, 0, _wMap[str[i]], temp->Height());

            offset += _wMap[str[i]];
         } else
            offset += _wMap[_maxChar - 1];
      }
   }

   void Font::Draw(RenderDevice::Renderer& renderer, const std::string& str, int x, int y)  {
      if (_img < 0) return;
      const Image * temp = ImageLoader::GetImage(_img);

      int offset = 0;

      for (unsigned int i = 0; i < str.length(); i++)  {
         if ((str[i] <= _maxChar) && (str[i] >= _minChar))  {
            int pos = 0;

            for (unsigned char j = _minChar; j < str[i]; j++)
               pos += _wMap[j];

            renderer.Drawimage(*temp, x + offset, y, _wMap[str[i]], temp->Height(), pos, 0, _wMap[str[i]], temp->Height());

            offset += _wMap[str[i]];
         } else
            offset += _wMap[_maxChar - 1];
      }
   }

   void Font::DrawBounded(RenderDevice::Renderer & renderer, const std::string & str, int x, int y, int width, int height)  {
      if (_img < 0) return;
      const Image * temp = ImageLoader::GetImage(_img);

      int xoffset = 0;
      int yoffset = 0;
      int lastSpace = 0;

      renderer.Setclip(x, y, width, height);

      for (unsigned int i = 0; i < str.length(); i++)  {
         if ((str[i] <= _maxChar) && (str[i] >= _minChar))  {
            int pos = 0;

            for (unsigned char j = _minChar; j < str[i]; j++)
               pos += _wMap[j];

            if (xoffset + _wMap[str[i]] > width)  {
               yoffset += Height();
               renderer.Drawimage(*temp, x + xoffset, y + yoffset, _wMap[str[i]], temp->Height(), pos, 0, _wMap[str[i]], temp->Height());
            }

            xoffset += _wMap[str[i]];

         } else  {
            xoffset += _wMap[_maxChar - 1];

            if (str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
               lastSpace = i;
         }
      }

      renderer.Resetclip();
   }

   int Font::Measure(const std::string& str) const  {
      if (_img < 0) return -1;
      int total = 0;

      for (unsigned int i = 0; i < str.length(); i++)  {
         if ((str[i] <= _maxChar) && (str[i] >= _minChar))  {
            total += _wMap[str[i]];
         } else
            total += _wMap[_maxChar - 1];
      }

      return total;

   }

}
