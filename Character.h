#pragma once

#include <list>
#include <vector>
#include <string>
#include "ImageAnimation.h"
#include "WorldObject.h"
#include "Effect.h"

namespace Animations  {
   // Defines standard animations -- numbers greater than Num_Animations are non-standard
   enum Animation  {
      None,
      Idle,
      Walk_Up,
      Walk_Down,
      Walk_Left,
      Walk_Right,
      Walk_UpLeft,
      Walk_UpRight,
      Walk_DownLeft,
      Walk_DownRight,
      Basic_Attack,
      Basic_Cast,
      Special_Attack,
      Long_Cast,
      Short_Cast,
      Channeled_Cast,
      Custom1,
      Custom2,
      Custom3,
      Custom4,
      Custom5,
      Custom6,
      Custom7,
      Custom8,
      Custom9,
      Custom10,
      Num_Animations
   };
}

class Character  {
public:

   Character();
   virtual ~Character();

   void MoveTo(int X, int Y);
   void Update(unsigned int tElapsed);
   void Draw(RenderDevice::Renderer & render);

   inline int Level() const { return _level; }
   inline int XP() const { return _xp; }
   inline int Health() const { return _curHealth; }
   inline int MaxHealth() const { return _maxHealth; }
   inline int ActionPoints() const { return _actionPoints; }
   inline int MaxActionPoints() const { return _maxActionPoints; }

   inline int Strength() const { return _strength; }
   inline int Agility() const { return _agility; }
   inline int Precision() const { return _precision; }
   inline int Focus() const { return _focus; }
   inline int Charisma() const { return _charisma; }

   inline void ModLevel(int lvl) { _level += lvl; }
   inline void ModXP(int xp) { _xp += xp; }
   inline void ModHealth(int health) { _curHealth += health; }
   inline void ModMaxHealth(int maxHealth) { _maxHealth += maxHealth; if (_curHealth > _maxHealth) _curHealth = _maxHealth;}
   inline void ModAP(int ap)  { _actionPoints += ap; }
   inline void ModMaxAP(int maxAP)  { _maxActionPoints += maxAP; if (_maxActionPoints > _actionPoints) _actionPoints = _maxActionPoints; }

   inline void ModStr(int str)  { _strength += str; }
   inline void ModAgi(int agi)  { _agility += agi; }
   inline void ModPre(int pre)  { _precision += pre; }
   inline void ModFoc(int foc)  { _focus += foc; }
   inline void ModCha(int cha)  { _charisma += cha; }

   WORLDOBJ_PROPERTIES(_pos);

private:
   std::list<Effect *> _effects;
   std::vector<ImageAnimation> _imgs;
   WorldObject _pos;
   Animations::Animation _curAnim;

   int _level;             // Current level
   int _xp;                // Current XP
   int _curHealth;         // Current health value
   int _maxHealth;         // Maximum health
   int _actionPoints;      // Current action points
   int _maxActionPoints;   // Maximum action points

   int _strength;          // Strength modifies melee attack power
   int _agility;           // Agility modifies action point regen rate
   int _precision;         // Precision modifies chance to hit with all attacks
   int _focus;             // Focus modifies damage of spells
   int _charisma;          // Charisma modifies how inclined enemies are to attack
   
};
