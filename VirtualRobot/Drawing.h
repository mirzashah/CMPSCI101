//Drawing.h
//*****************************************************************************
//A set of convenience calls to be used for drawing rather than directly
//calling OpenGL. Not necessary to use these, but it is encouraged.
//*****************************************************************************

#ifndef DRAWING_H_DEFINED
#define DRAWING_H_DEFINED

#include <GL/gl.h>
#include <GL/glu.h>
#include "DisplayTypes.h"
#include <string>
using std::string;

namespace Beeber
{

namespace Drawing
{

void         SetColor(int r, int g, int b, int a = 255);
void         SetColor(const Color& color);

void         Circle(const XYPoint& center, double diameter, bool filled = false);
void         CircleDevice(const DevicePoint& center, double diameterInPixels, bool filled = false);
void         CircleDevice(const XYPoint& center, double diameterInPixels, bool filled = false);

void         Line(const DevicePoint& p1, const DevicePoint& p2);
void         Line(const XYPoint&  p1,const XYPoint&  p2);

void         Text(const DevicePoint& p, string text, FontName font = FN_BITMAP_HELVETICA_10);
void         Text(const XYPoint&  p, string text, FontName font = FN_BITMAP_HELVETICA_10);

void         Slider(const DevicePoint& p, string label, float val, int widthInPixels);
void         Slider(const XYPoint&  p, string label, float val, int widthInPixels);

double       Scale();
XYPoint      Device2XY(const DevicePoint& p);
DevicePoint  XY2Device(const XYPoint&  p);

}
}

#endif
