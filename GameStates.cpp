#include "GameStates.h"
#include "Console.h"

bool GameStates::_popNext = false;
std::string GameStates::_toPush = "";
std::vector<GameState*> GameStates::_states = std::vector<GameState*>();
std::map<std::string, GameState*, ltstr> GameStates::_registered = std::map<std::string, GameState*, ltstr>();

extern Console console;

//current state management
GameState* GameStates::Current() {
   if (_states.size() > 0) return _states.at(_states.size() - 1); 
   return NULL;
}

void GameStates::Push(const std::string& name) {
   if (_registered.find(name) != _registered.end())  {
      console.AddLine(std::string("Pushing gamestate ") + name + ".");
      _registered[name]->OnPush(); 
      _states.push_back(_registered[name]);
   } else
      console.AddLine(std::string("Attempt to push nonexistant state ") + name + ".");
}

// Not recommended, use QueuePop to pop the top state on the next Update()
void GameStates::Pop() {
   console.AddLine(std::string("Popping current gamestate."));
   (*(--_states.end()))->OnPop(); 
   _states.pop_back();
}

bool GameStates::UpdateStates(RenderDevice::Renderer& render, const ActionMap & actions, unsigned int tElapsed) {
   if (_states.size() == 0) return true;

   if (_popNext)  {
      Pop();
      _popNext = false;
   }

   if (_toPush != "")  {
      Push(_toPush);
      _toPush = "";
   }

   if (_states.size() == 0) return true;

   if ((*(--_states.end()))->Enabled()) (*(--_states.end()))->Update(actions, tElapsed);

   for (unsigned int i = 0; i < _states.size(); i++)  {
      if (_states.at(i)->Enabled()) _states.at(i)->Draw(render, tElapsed);
   }

   return false;
}


// Gamestate registering and monitoring
void GameStates::RegisterState(GameState * g, const std::string & name) {
   if (_registered.find(name) == _registered.end())  {
      console.AddLine(std::string("Registering gamestate ") + name + ".");
      _registered[name] = g;
   }  else
      console.AddLine(std::string("State ") + name + " already exists!");
}

void GameStates::ReleaseStates() {
   for (std::map<std::string, GameState*, ltstr>::iterator i = _registered.begin();
        i != _registered.end(); i++)  {

      i->second->OnPop();
      delete i->second;
      
   }
}