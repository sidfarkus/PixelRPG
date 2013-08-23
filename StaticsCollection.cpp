#include "StaticsCollection.h"

StaticsCollection::StaticsCollection()  {
}

StaticsCollection::~StaticsCollection()  {   
   for (std::list<StaticObject *>::iterator i = _objs.begin(); i != _objs.end(); i++)  {
      delete *i;
   }
}

void StaticsCollection::DrawStatics(RenderDevice::Renderer& render, unsigned int tElapsed, int screenX, int screenY)  {
   // naively draw everything on the screen
   StaticObject * temp = NULL;

   for (std::list<StaticObject *>::iterator i = _objs.begin(); i != _objs.end(); i++)  {
      temp = *i;

      if ((temp->X() + temp->Width() >= screenX) && (temp->X() <= screenX + render.ScreenWidth()) &&
         (temp->Y() + temp->Height() >= screenY) && (temp->Y() <= screenY + render.ScreenHeight()))  {
         
         temp->Draw(render, tElapsed, screenX, screenY);
      }
   }
}

void StaticsCollection::AddStatic(StaticObject * object)   {
   if (object)  {
      _objs.push_back(object);
   }
}

void StaticsCollection::RemoveStatic(const std::string & objName)  {
   for (std::list<StaticObject *>::iterator i = _objs.begin(); i != _objs.end(); i++)  {
      if ((*i)->Name() == objName)  {
         delete *i;
         _objs.erase(i);
         break;
      }
   }
}

StaticObject * StaticsCollection::GetStatic(const std::string & objName) const  {
   for (std::list<StaticObject *>::const_iterator i = _objs.begin(); i != _objs.end(); i++)  {
      if ((*i)->Name() == objName)
         return (*i);
   }

   return NULL;
}
