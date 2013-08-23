#pragma once

#include "ImageLoader.h"
#include "Map.h"
#include "Vector.h"

#define WORLDOBJ_PROPERTIES(wName) \
   inline int X() {return wName.X();} \
   inline int Y() {return wName.Y();} \
   inline void SetX(int x) {wName.Coords.X = x;} \
   inline void SetY(int y) {wName.Coords.Y = y;}

struct WorldObject  {
   MapCoord Coords;
   
   WorldObject(int cellx = 0, int celly = 0) : Coords(cellx, celly) {
   }

   inline int CellX() const  { return Coords.CellX; }
   inline int CellY() const { return Coords.CellY; }

   inline int X() const {return Coords.X;}
   inline int Y() const {return Coords.Y;}
};
