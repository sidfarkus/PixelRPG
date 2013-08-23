#ifndef EVENT_CPP
#define EVENT_CPP

#include "./Event.h"

template <class T, class U>
void Event<T, U>::operator()(const U param)  {
   (*_objPtr.*_fPtr)(param);
}

template <class T, class U>
void Event<T, U>::Call(const U param)  {
   (*_objPtr.*_fPtr)(param);
}

#endif