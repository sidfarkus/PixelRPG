#include "Control.h"

namespace GUI  {

   Control::Control()  {
      x = 0;
      y = 0;
      width = 0;
      height = 0;
      enabled = true;
      visible = true;
   }

   Control::Control(int xpos, int ypos, unsigned int wide, unsigned int tall)  {
      x = xpos;
      y = ypos;
      width = wide;
      height = tall;
      enabled = true;
      visible = true;
   }

   Control::~Control()  {
   }

   bool Control::Update(const ActionMap & actions, unsigned int tElapsed)  {
      return Collide(actions.GetInputState()->mouseX, actions.GetInputState()->mouseY);
   }

   Control * Control::Clone()  {
      return NULL;
   }

   void Control::AlignToRect(ALIGN alignment, int padding, SDL_Rect & rect)  {
      if (alignment == Center)  {
         // center the control in the rect
         SetX((int) (rect.x + rect.w / 2.0f - width / 2.0f));
         SetY((int) (rect.y + rect.h / 2.0f - height / 2.0f));
         return;
      }

      if (alignment & Left)  {
         SetX(rect.x + padding);
      }

      if (alignment & Align::Right)  {
         SetX(rect.x + rect.w - width - padding);
      }

      if (alignment & Top)  {
         SetY(rect.y + padding);
      }

      if (alignment & Align::Bottom)  {
         SetY(rect.y + rect.h - height - padding);
      }

   }

   void Control::AlignToRect(ALIGN alignment, int padding, int xpos, int ypos, unsigned int w, unsigned int h)  {
      if (alignment == Center)  {
         // center the control in the rect
         SetX((int) (xpos + w / 2.0f - width / 2.0f) + padding);
         SetY((int) (ypos + h / 2.0f - height / 2.0f) + padding);
         return;
      }

      if (alignment & Left)  {
         SetX(xpos + padding);
      }

      if (alignment & Align::Right)  {
         SetX(xpos + w - width - padding);
      }

      if (alignment & Top)  {
         SetY(ypos + padding);
      }

      if (alignment & Align::Bottom)  {
         SetY(ypos + h - height - padding);
      }
   }

   void Control::AlignToControl(ALIGN alignment, int padding, const Control & control)  {
      if (alignment == Center)  {
         // center the control in the rect
         SetX((int) (control.x + control.width / 2.0f - width / 2.0f) + padding);
         SetY((int) (control.y + control.height / 2.0f - height / 2.0f) + padding);
         return;
      }

      if (alignment & Left)  {
         SetX(control.x + padding);
      }

      if (alignment & Align::Right)  {
         SetX(control.x + control.width - width - padding);
      }

      if (alignment & Top)  {
         SetY(control.y + padding);
      }

      if (alignment & Align::Bottom)  {
         SetY(control.y + control.height - height - padding);
      }
   }

   void Control::AlignNear(const Control & control, int distance, Align position)   {
      switch (position)  {
         case Top:
            x = (int) (control.x + control.width / 2.0f - width / 2.0f);
            y = control.y - height - distance;
            break;
         case Align::Bottom:
            x = (int) (control.x + (control.width - width) / 2.0f);
            y = control.y + height + distance;
            break;
         case Align::Right:
            x = control.x + control.width + distance;
            y = control.y + (height - control.height) / 2.0f;
            break;
         case Left:
            x = control.x - width - distance;
            y = control.y + (height - control.height) / 2.0f;
            break;
         case Center:
            // No center positioning defined
            break;
      }
   }

   void Control::AlignNear(int xpos, int ypos, unsigned int w, unsigned int h, int distance, Align position)  {
      switch (position)  {
         case Top:
            x = (int) (xpos + w / 2.0f - width / 2.0f);
            y = ypos - height - distance;
            break;
         case Align::Bottom:
            x = (int) (xpos + (w - width) / 2.0f);
            y = ypos + height + distance;
            break;
         case Align::Right:
            x = xpos + w + distance;
            y = ypos + (height - h) / 2.0f;
            break;
         case Left:
            x = xpos - width - distance;
            y = ypos + (height - h) / 2.0f;
            break;
         case Center:
            // No center positioning defined
            break;
      }
   }

   bool Control::Collide(int mx, int my)  {
      if (mx >= x && mx <= x + (int) width &&
          my >= y && my <= y + (int) height) return true;

      return false;
   }

   IContainer::~IContainer()  {
      for (std::vector<Control *>::iterator i = _children.begin(); i != _children.end(); i++)
         delete *i;
   }

   void IContainer::AddChild(Control * control)  {
      if (control) _children.push_back(control);
   }

   void IContainer::UpdateChildren(const ActionMap & actions, unsigned int tElapsed)  {
      for (unsigned int i = 0; i < _children.size(); i++)  {
         if (_children.at(i))
            if (_children.at(i)->Enabled()) _children[i]->Update(actions, tElapsed);
      }
   }

   void IContainer::DrawChildren(RenderDevice::Renderer& renderer, unsigned int tElapsed)  {
      for (unsigned int i = 0; i < _children.size(); i++)  {
         if (_children.at(i))
            if (_children.at(i)->Visible()) _children[i]->Draw(renderer, tElapsed);
      }
   }
}
