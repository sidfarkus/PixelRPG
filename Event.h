#ifndef EVENT_H
#define EVENT_H


// T is object type, U is the parameter type
template <class T, class U>
class Event  {
public:
   Event(T* objPtr, void (T::*fPtr) (const U)) {_objPtr = objPtr; _fPtr = fPtr;};
   void operator()(const U param);
   void Call(const U param);

private:
   T* _objPtr;
   void(T::*_fPtr)(const U);
};

#include "./Event.cpp"
#endif