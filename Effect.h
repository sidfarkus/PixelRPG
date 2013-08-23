#pragma once

#include <string>

class Character;

// Effects are applied to characters to buff or debuff them
class Effect  {
public:
   Effect(int priority, const std::string & name, const std::string & desc);
   virtual ~Effect();

   virtual void Apply(Character & character) = 0;

   inline int Priority() const { return _priority; }
   inline const std::string & Name() const { return _name; }
   inline const std::string & Description() const { return _description; }

private:
   std::string _name;
   std::string _description;
   int _priority;
};
