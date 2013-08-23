#include "Effect.h"

Effect::Effect(int priority, const std::string & name, const std::string & desc) : _name(name), _description(desc), _priority(priority) {
}

Effect::~Effect()  {
}
