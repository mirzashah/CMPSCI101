#ifndef DISPLAY_TYPES_H_DEFINED
#define DISPLAY_TYPES_H_DEFINED

#include <BeeberIPC.h>

namespace Beeber
{

struct Color
{
   Color(int rIn, int gIn, int bIn){r = rIn; g = gIn; b = bIn;}
   int r,g,b;
};

struct DevicePoint
{
   DevicePoint(int xIn = 0, int yIn = 0){x = xIn; y = yIn;}
   int x;
   int y;
};

#undef MB_LEFT
#undef MB_RIGHT
#undef MB_MIDDLE

enum MouseButton
{
   MB_LEFT,
   MB_MIDDLE ,
   MB_RIGHT
};

enum FontName
{
   FN_STROKE_ROMAN,
   FN_STROKE_MONO_ROMAN,
   FN_BITMAP_9_BY_15,
   FN_BITMAP_8_BY_13,
   FN_BITMAP_TIMES_ROMAN_10,
   FN_BITMAP_TIMES_ROMAN_24,
   FN_BITMAP_HELVETICA_10,
   FN_BITMAP_HELVETICA_12,
   FN_BITMAP_HELVETICA_18
};


};

#endif
