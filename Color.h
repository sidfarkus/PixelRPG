#pragma once

struct Color  {
  float R;
  float G;
  float B;
  float A;
  int Bpp;

  Color(float r = 0, float g = 0, float b = 0, float a = 1.0f, int bpp = 32)
  {R=r; B=b; G=g; A=a; Bpp=bpp;}

  static Color Black;
  static Color Blue;
  static Color Green;
  static Color Red;
  static Color Yellow;
  static Color Purple;
  static Color Orange;
  static Color White;
  static Color DarkBlue;
  static Color DarkBrown;

};

const Color operator+(const Color& c1, const Color& c2);
const Color operator-(const Color& c1, const Color& c2);
const Color operator*(const Color& c1, const Color& c2);

inline unsigned char ftob(float x, unsigned char max) {
   return x > 1.0f ? max : (x < 0 ? 0 : (unsigned char)(x * ((float) max)));
}

inline float btof(unsigned char x, unsigned char max)  {
   return x > max ? 1.0f : x / ((float) max);
}

inline unsigned int ColorToLong(const Color& c) {
   if (c.Bpp == 32) {
      return 
       ((unsigned int) ftob(c.B, 255)) |
       ((unsigned int) ftob(c.G, 255) << 8) |
       ((unsigned int) ftob(c.R, 255) << 16) |
       ((unsigned int) ftob(c.A, 255) << 24);
   } else  {
      return 
       ((unsigned int) ftob(c.B, 31)) |
       ((unsigned int) ftob(c.G, 63) << 5) |
       ((unsigned int) ftob(c.R, 31) << 11);
   }
}

inline Color LongToColor(unsigned int c, int bpp = 32)  {
   if (bpp == 32)  {
      return Color(
        btof((c & 0x00FF0000) >> 16, 255),
        btof((c & 0x0000FF00) >> 8, 255),
        btof(c & 0x000000FF, 255),
        btof((c & 0xFF000000) >> 24, 255), 32);
   } else  {
      return Color(
        btof((c & 0xF800) >> 11, 31),
        btof((c & 0x7E0) >> 5, 63),
        btof(c & 0x1F, 31), 16);
   }
}
