#pragma once

#include <vector>
#include "SDLInclude\\SDL.h"

typedef unsigned char MOUSE_BSTATE;
const MOUSE_BSTATE MOUSE_NONE = 0x00;
const MOUSE_BSTATE MOUSE_B1 = 0x01;
const MOUSE_BSTATE MOUSE_B2 = 0x02;
const MOUSE_BSTATE MOUSE_B3 = 0x04;

struct Key  {
   SDLKey KeyVal;
   Uint16 UnicodeVal;

   Key(SDLKey k, Uint16 u) : KeyVal(k), UnicodeVal(u) {}

   char ToChar() const {
      if (UnicodeVal && UnicodeVal < 0x80)
         return (char) UnicodeVal;
      else
         return 0;
   }
};

struct InputState  {
   int mouseX;
   int mouseY;
   MOUSE_BSTATE mbPressed;
   MOUSE_BSTATE mbReleased;
   std::vector<Key> pressed;
   std::vector<Key> released;
   SDLMod keymod;

   InputState() {mouseX = 0; mouseY = 0; mbPressed = 0; mbReleased = 0;}
   bool KeyDown(SDLKey key) const {
      for (std::vector<Key>::const_iterator i = pressed.begin();
           i != pressed.end(); i++)
           if (i->KeyVal == key) return true;
      return false;
   }

   bool KeyUp(SDLKey key) const {
      for (std::vector<Key>::const_iterator i = released.begin();
           i != released.end(); i++)
           if (i->KeyVal == key) return true;
      return false;
   }
};