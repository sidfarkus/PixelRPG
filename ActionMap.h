#pragma once

#include <string>
#include <map>
#include "InputState.h"
#include "Console.h"

namespace ActionState  {
   enum AState {
      None,
      Pressed,
      Released,
      Default
   };
}

struct Action  {
   std::string Name;
   SDLKey Key;
   MOUSE_BSTATE MouseButtons;

   Action(const std::string & name) : Name(name), Key(), MouseButtons(0) {}
};

struct ActionComparer  {
   bool operator()(const Action & action1, const Action & action2)  {
      return action1.Name < action2.Name;
   }
};

// Maps key/mouse button input to action codes
class ActionMap  {
public:
   ActionMap();

   ActionState::AState GetState(const std::string & name) const;

   void AddActionMapping(Action & action, SDLKey key);
   void AddActionMapping(Action & action, MOUSE_BSTATE mbState);
   void UpdateMapping(const InputState & input);

   inline const InputState * const GetInputState() const {return _input;}

private:
   const InputState * _input;
   std::map<Action, ActionState::AState, ActionComparer> _actionMap;
};
