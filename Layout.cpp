#include "Layout.h"

#pragma warning(disable : 4482)

namespace GUI  {
   Layout::Layout(int x, int y, unsigned int wide, unsigned int tall, int padding, Layouts layout, ALIGN align) : 
                  Control(x, y, wide, tall) 
   {
      SetLayout(layout);
      _align = align;
      _padding = padding;
      _layoutChanged = true;
   }

   Layout::~Layout()  {
      // delete children
   }

   bool Layout::Update(const ActionMap & actions, unsigned int tElapsed)  {
      if (_layoutChanged)  {
         std::vector<Control*>::iterator iter = _children.begin();
         int curWide = _padding, curTall = _padding, maxHeight = 0;

         switch (_layout)  {
            case None:
               // Don't move controls
               _layoutChanged = false;
               break;
            case Grid:
               // Grid of controls
               for (; iter != _children.end(); iter++)  {
                  if (curWide + (*iter)->Width() > width)  {
                     curTall += maxHeight + _padding;
                     curWide = _padding;
                     maxHeight = 0;
                  }

                  if ((*iter)->Height() > static_cast<unsigned int>(maxHeight)) maxHeight = (int) (*iter)->Height();

                  _moveChildRelative(*iter, curWide, curTall);
                  curWide += (*iter)->Width() + _padding;
               }
               
               _layoutChanged = false;
               break;
            case HorizontalLine:
               // Horizontal line of controls
               for (; iter != _children.end(); iter++)  {
                  if (curWide + static_cast<int>((*iter)->Width()) > Right()) break;

                  _moveChildRelative(*iter, curWide, 0);
                  curWide += (*iter)->Width() + _padding;
               }

               _layoutChanged = false;
               break;
            case VerticalLine:
               // Vertical line of controls
               for (; iter != _children.end(); iter++)  {                 
                  if (curTall > Bottom()) break;

                  _moveChildRelative(*iter, 0, curTall);
                  curTall += (*iter)->Height() + _padding;
               }

               _layoutChanged = false;
               break;
         }
      }

      UpdateChildren(actions, tElapsed);

      return Collide(actions.GetInputState()->mouseX, actions.GetInputState()->mouseY);
   }

   void Layout::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      //renderer.Setclip(x, y, width, height);
      DrawChildren(renderer, tElapsed);
      //renderer.Resetclip();
   }

   void Layout::AddSpacer(SpacerType type, int wide, int tall)  {
      switch (type)  {
         case HorizontalSpacer:
            // fill all remaining space on the line if wide = 0, otherwise fill wide space
            if (wide)  {
               AddChild(new layoutSpacer(wide - _padding, 1));
            } else {
               AddChild(new layoutSpacer(this->Right() - _children.back()->Right() - _padding, 1));
            }
            break;
         case VerticalSpacer:
            // if tall is nonzero fill tall many lines
            if (tall)  {
               AddChild(new layoutSpacer(this->Width(), tall));
            }
            break;
         case FixedSpacer:
            // fill exactly wide by tall
            if (wide && tall)  {
               AddChild(new layoutSpacer(wide, tall));
            }
            break;
      }
   }

   void Layout::_moveChildRelative(Control * control, int newX, int newY)  {
      if (_align & Center) {
         control->Move(x + newX - control->Width(), y + newY - control->Height());
      }

      if (_align & Top) {
         control->SetY(y + newY);
      }

      if (_align & Left) {
         control->SetX(x + newX);
      }

      if (_align & Align::Right) {
         control->SetX(Right() - newX - control->Width());
      }

      if (_align & Align::Bottom) {
         control->SetY(Bottom() - newY - control->Height());
      }
   }

   Layout::layoutSpacer::layoutSpacer(unsigned int wide, unsigned int tall) : Control(0, 0, wide, tall) {
   }

   void Layout::layoutSpacer::Draw(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      // Nothing is drawn!
   }

}

