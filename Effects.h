#pragma once

#include "Effect.h"

class StrengthMod : public Effect  {
public:
   StrengthMod(int value, const std::string & name, const std::string & desc) : Effect(50, name, desc)  {
      _value = value;
   }

   virtual void Apply(Character & character)  {
      character.ModStr
   }

   inline int Value() const { return value; }

private:
   int _value;
};