#pragma once
#include <vector>
#include <map>

#include <string>
#include "Exception.h"
#include "Renderer.h"
#include "ActionMap.h"

class GameState  {
public:
   virtual void OnPush() = 0;
   virtual void OnPop() = 0;
   virtual void Draw(RenderDevice::Renderer& render, unsigned int tElapsed) = 0;
   virtual void Update(const ActionMap & actions, unsigned int tElapsed) = 0;
   virtual ~GameState() {};

   inline bool Enabled() const {return _enabled;}
   inline void SetEnabled(bool val) {_enabled = val;}

protected:
   GameState() {_enabled = true;}
   bool _enabled;

};

// Use this as the empty state
class EmptyState : public GameState {
public:
   EmptyState() {_enabled = false;}
   virtual void OnPush() {}
   virtual void OnPop() {}
   virtual void Draw(RenderDevice::Renderer& render, unsigned int tElapsed) {}
   virtual void Update(const ActionMap & actions, unsigned int tElapsed) {}
};

struct ltstr {
   bool operator()(const std::string pair1, 
                   const std::string pair2) const {
    return pair1 < pair2;
  }
};

// Static class holding state management tools
class GameStates  {
public:
   //current state management
   static GameState* Current();
   static void Push(const std::string& name);

   // Not recommended, use QueuePop to pop the top state on the next Update()
   static void Pop();

   // Recommended state switching
   static inline void QueuePop()  {_popNext = true;}
   static inline void QueuePush(const std::string & topush)  {_toPush = topush;}
   static inline void Swap(const std::string & toSwap) {QueuePop(); QueuePush(toSwap);}

   static bool UpdateStates(RenderDevice::Renderer& render, const ActionMap & actions, unsigned int tElapsed);

   // Gamestate registering and monitoring
   static void RegisterState(GameState * g, const std::string & name);
   static void ReleaseStates();

private:
   static bool _popNext;
   static std::string _toPush;
   static std::vector<GameState*> _states;
   static std::map<std::string, GameState*, ltstr> _registered;
};
