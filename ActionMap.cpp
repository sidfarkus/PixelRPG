#include "ActionMap.h"

extern Console console;

ActionMap::ActionMap()  {
   _input = NULL;
}

ActionState::AState ActionMap::GetState(const std::string & name) const  {
   std::map<Action, ActionState::AState, ActionComparer>::const_iterator found = _actionMap.find(Action(name));

   if (found != _actionMap.end())  {
      return found->second;
   }
   return ActionState::None;
}

void ActionMap::AddActionMapping(Action & action, SDLKey key)  {
   action.Key = key;
   _actionMap[action] = ActionState::Default;
}

void ActionMap::AddActionMapping(Action & action, MOUSE_BSTATE mbState)  {
   action.MouseButtons = mbState;
   _actionMap[action] = ActionState::Default;
}

void ActionMap::UpdateMapping(const InputState & input)  {
   std::map<Action, ActionState::AState, ActionComparer>::iterator i = _actionMap.begin();
   _input = &input;

   for (;i != _actionMap.end(); i++)  {
      if (input.KeyDown(i->first.Key))  {
         i->second = ActionState::Pressed;
      } else if (input.KeyUp(i->first.Key))  {
         i->second = ActionState::Released;
      } else {
         i->second = ActionState::None;
      }
      
      if (i->first.MouseButtons)  {
         if (i->first.MouseButtons & input.mbPressed)  {
            i->second = ActionState::Pressed;
         } else if (i->first.MouseButtons & input.mbReleased)  {
            i->second = ActionState::Released;
         }
      }
   }
}
