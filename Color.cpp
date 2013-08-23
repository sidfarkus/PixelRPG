#include "Color.h"

Color Color::Black = Color(0, 0, 0);
Color Color::Blue = Color(0, 0, 1.0f);
Color Color::Green = Color(0, 1.0f, 0);
Color Color::Red = Color(1.0f, 0, 0);
Color Color::Yellow = Color(1.0f, 1.0f, 0.0f);
Color Color::Purple = Color(0.6f, 0, 1.0f);
Color Color::Orange = Color(0.4f, 0.8f, 0.1f);
Color Color::White = Color(1.0f, 1.0f, 1.0f);
Color Color::DarkBlue = Color(0, 0, 0.25f);
Color Color::DarkBrown = Color(0.25f, 0.18f, 0.05f);

const Color operator+(const Color& c1, const Color& c2)  {
  return Color(c1.R + c2.R, c1.G + c2.G, c1.B + c2.B, c1.A + c2.A);
}

const Color operator-(const Color& c1, const Color& c2)  {
  return Color(c1.R - c2.R, c1.G - c2.G, c1.B - c2.B, c1.A - c2.A);
}

const Color operator*(const Color& c1, const Color& c2)  {
  return Color(c1.R * c2.R, c1.G * c2.G, c1.B * c2.B, c1.A * c2.A);
}
