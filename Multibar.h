#pragma once
#include <vector>
#include "ImageLoader.h"
#include "Control.h"
#include "Frame.h"
#include "Button.h"

namespace GUI  {
   // Multibar
   // Holds a bunch of Buttons in a grid arrangement
   class Multibar : public Frame, public IClickable {
   public:
      Multibar(const char * frameimage, 
         const char * gridimage, int gridsize, 
         int rows, int columns, int padding,
         int topborder, int bottomborder, int leftborder, int rightborder, 
         int x, int y, unsigned int wide, unsigned int tall);
      virtual ~Multibar();

      virtual bool Update(const ActionMap & actions, unsigned int tElapsed);
      virtual void Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed);

      bool AddButton(Button * button, unsigned int xcell, unsigned int ycell);
      void RemoveButton(unsigned int xcell, unsigned int ycell);
      Button * GetButton(unsigned int xcell, unsigned int ycell);

   private:
      int _rows, _cols, _padding, _gridsize;
      IMAGEHANDLE _grid;
      std::vector<Button *> _buttons;
   };
}
