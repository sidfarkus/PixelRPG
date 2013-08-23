#include "Multibar.h"

namespace GUI {
   Multibar::Multibar(
      const char * frameimage, 
      const char * gridimage, int gridsize,
      int rows, int columns, int padding, 
      int topborder, int bottomborder, int leftborder, int rightborder, 
      int x, int y, unsigned int wide, unsigned int tall
      ) : Frame(frameimage, topborder, bottomborder, leftborder, rightborder, x, y, wide, tall)
   {
      _rows = rows;
      _cols = columns;
      _padding = padding;
      _gridsize = gridsize;
      _grid = ImageLoader::Load(gridimage);
      _buttons = std::vector<Button *>(rows * columns, NULL);
   }

   Multibar::~Multibar()  {
      for (std::vector<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); i++)
         delete *i;
   }

   bool Multibar::Update(const ActionMap & actions, unsigned int tElapsed)  {
      for (unsigned int i = 0; i < _buttons.size(); i++)  {
         if (_buttons.at(i)) _buttons.at(i)->Update(actions, tElapsed);
      }

      return Collide(actions.GetInputState()->mouseX, actions.GetInputState()->mouseY);
   }

   void Multibar::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      Frame::Draw(renderer, tElapsed);

      renderer.Setclip(x + _right, y + _top, width - _right - _left, height - _top - _bottom);
      renderer.Drawimage(_grid, x + _right + 1, y + _top, width - _right - _left, height - _top - _bottom, 0, 0, 0, 0, true);
      
      for (unsigned int i = 0; i < _buttons.size(); i++)  {
         if (_buttons.at(i)) _buttons.at(i)->Draw(renderer, tElapsed);
      }

      renderer.Resetclip();
   }

   bool Multibar::AddButton(Button * button, unsigned int xcell, unsigned int ycell)  {
      if (xcell < _rows && ycell < _cols && _buttons.at(xcell + ycell * _cols) == NULL)  {
         button->Move(x + (xcell * _gridsize + _padding), y + (ycell * _gridsize + _padding));
         _buttons.insert(_buttons.begin() + (xcell + ycell * _cols), button);
         return false;
      }
      return true;
   }

   void Multibar::RemoveButton(unsigned int xcell, unsigned int ycell)  {
      if (xcell < _rows && ycell < _cols && _buttons.at(xcell + ycell * _cols) == NULL)  {
         _buttons.erase(_buttons.begin() + (xcell + ycell * _cols));
      }
   }

   Button * Multibar::GetButton(unsigned int xcell, unsigned int ycell)  {
      if (xcell < _rows && ycell < _cols && _buttons.at(xcell + ycell * _cols) == NULL)  {
         return _buttons.at(xcell + ycell * _cols);
      }
      return NULL;
   }
}
