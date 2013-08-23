#pragma once

#include <math.h>

// simple 2d vector 
union Vector  {
   struct {
      float x;
      float y;
   };
   float e[2];

   inline operator float *() {
      return e;
   }

   Vector operator-(const Vector & v)  {
      return Vector(x - v.x, y - v.y);
   }

   Vector operator+(const Vector & v)  {
      return Vector(x + v.x, y + v.y);
   }

   Vector(float X = 0, float Y = 0) :
      x(X), y(Y)
   {}
};

static Vector operator*(const Vector & v, float scale)  {
   return Vector(v.x * scale, v.y * scale);
}

namespace VectorMath  {

   inline Vector & Scale(Vector & v, float scale)  {
      v.x *= scale;
      v.y *= scale;
      return v;
   }

   inline float Length(Vector & v)  {
      return sqrt(v.x * v.x + v.y * v.y);
   }

   inline float LengthSq(Vector & v)  {
      return v.x * v.x + v.y * v.y;
   }

   inline Vector & Normalize(Vector & v)  {
      float len = Length(v);
      if (len == 0.0f) return v;

      v.x /= len;
      v.y /= len;
      return v;
   }

   inline float Dot(Vector & v1, Vector & v2)  {
      return v1.x * v2.x + v1.y * v2.y;
   }

   inline float Angle(Vector & a, Vector & b)   {
      float x = Dot(a, b);
      return acos(x / (Length(a) * Length(b)));
   }

}
