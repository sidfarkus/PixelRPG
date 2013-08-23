#pragma once

#include <list>
#include "Statics.h"

class StaticsCollection  {
public:
   StaticsCollection();
   ~StaticsCollection();

   void DrawStatics(RenderDevice::Renderer& render, unsigned int tElapsed, int screenX, int screenY);

   void AddStatic(StaticObject * object);
   void RemoveStatic(const std::string & objName);

   StaticObject * GetStatic(const std::string & objName) const;

private:
   std::list<StaticObject *> _objs;

};
