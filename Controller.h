#pragma once

#include "Renderer.h"
#include "Control.h"
#include "InputState.h"
#include "Frame.h"
#include <string>
#include <map>

namespace GUI  {
   struct ControlEntry  {
      Control * Item;
      std::string ToolTip;

      ControlEntry() {Item = NULL; ToolTip = std::string();}
   };

   // Holds a collection of controls
   //  enables tooltips on hovering and loading from a definition file
   class Controller  {
   public:
      Controller()   {
         _tipframe = NULL;
      }

      Controller(const std::string & toolTipImage, int borderSize)   {
         _tipframe = new GUI::Frame(toolTipImage.c_str(), borderSize, borderSize, borderSize, borderSize, 0, 0, 1, 1);
      }

      ~Controller()   {
         std::map<std::string, ControlEntry *>::iterator i = _items.begin();

         for (;i != _items.end(); i++)  {
            delete i->second;
         }

         delete _tipframe;
      }

      // Loads a GUI from a definition file
      inline void LoadGUI(const std::string & filename)  {
      }

      // Add a control pointer to this controller
      // the controller assumes control of the pointer, this should not be used elsewhere
      inline void AddControl(const std::string & name, Control * control, const std::string & toolTip)  {
         if (_items.find(name) != _items.end())  {
            ControlEntry * temp = new ControlEntry();
            temp->Item = control;
            temp->ToolTip = toolTip;
            
            _items[name] = temp;
         }
      }

      // Get a pointer to a specified type of control
      inline T * GetControl<T>(const std::string & name)  {
         std::map<std::string, ControlEntry *>::iterator found = _items.find(name);

         if (found != _items.end())
            return dynamic_cast<T *>(found->second->Item);
      }

      // Removes a control from the controller
      inline void RemoveControl(const std::string & name)  {
         std::map<std::string, ControlEntry *>::iterator found = _items.find(name);

         if (found != _items.end())  {
            delete found->second->Item;
            delete found->second;
            _items.erase(found);
         }
      }

      inline void Clear()  {
         _items.clear();
      }

      // Processes each control, only re-drawing those that are invalidated
      // additionally, draws a tooltip if the associated control has a tooltip
      inline void ProcessControls(RenderDevice::Renderer & render, const ActionMap & actions, unsigned int tElapsed)  {
         std::map<std::string, ControlEntry *>::iterator i = _items.begin();

         for (;i != _items.end(); i++)  {
            if (i->second->Item->Update(actions, tElapsed))  {

               i->second->Item->Draw(render, tElapsed);
               
               if (i->second->ToolTip != "") 
                  DrawToolTip(render, i->second->ToolTip, actions.GetInputState()->mouseX, actions.GetInputState()->mouseY);
            }
         }
      }

      inline void DrawToolTip(RenderDevice::Renderer & render, const std::string & caption, int mx, int my)  {
         int w, h;

         if (_tipframe)  {
            _tipframe->Draw(render, 0);
         } else  {
            render.Fillrect(mx, my, w, h, Color::Blue);
         }
      }

   private:
      GUI::Frame * _tipframe;
      std::map<std::string, ControlEntry *> _items;

   };
}
