#include "Character.h"

Character::Character() : 
_imgs(),
_pos(0, 0)
{
}

Character::~Character()  {
}

void Character::MoveTo(int X, int Y)  {
   SetX(X);
   SetY(Y);
}
