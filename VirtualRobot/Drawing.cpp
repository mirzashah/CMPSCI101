#include "Drawing.h"
#include "Engine.h"
#include <GL/freeglut.h>
#include <cmath>

namespace Beeber
{

namespace Drawing
{

/*****************************************************************************/
void Circle(const XYPoint& center, double diameter, bool filled)
/*****************************************************************************/
{
   int num_segments = 50;
   double cx = center.x;
   double cy = center.y;
   double r = diameter / 2;

   if(filled)
      glBegin(GL_POLYGON);
   else
      glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}

/*****************************************************************************/
void CircleDevice(const DevicePoint& center, double diameterInPixels, bool filled)
/*****************************************************************************/
{
   Circle(Device2XY(center), diameterInPixels * Scale(), filled);
}

/*****************************************************************************/
void CircleDevice(const XYPoint& center, double diameterInPixels, bool filled)
/*****************************************************************************/
{
   CircleDevice(XY2Device(center), diameterInPixels, filled);
}

/*****************************************************************************/
void SetColor(int r, int g, int b, int a)
/*****************************************************************************/
{
   glColor4f(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
}

/*****************************************************************************/
void SetColor(const Color& c)
/*****************************************************************************/
{
   SetColor(c.r, c.g, c.b);
}

/*****************************************************************************/
void Line(const XYPoint& p1, const XYPoint& p2)
/*****************************************************************************/
{
   glBegin(GL_LINES);
      glVertex2d(p1.x, p1.y);
      glVertex2d(p2.x, p2.y);
   glEnd();
}

/*****************************************************************************/
void Line(const DevicePoint& p1, const DevicePoint& p2)
/*****************************************************************************/
{
   Line(Device2XY(p1), Device2XY(p2));
}

/*****************************************************************************/
static void* Font2GLUTFont(FontName font)
/*****************************************************************************/
{
   switch(font)
   {
      case FN_STROKE_ROMAN:            return(GLUT_STROKE_ROMAN);
      case FN_STROKE_MONO_ROMAN:       return(GLUT_STROKE_MONO_ROMAN);
      case FN_BITMAP_9_BY_15:          return(GLUT_BITMAP_9_BY_15);
      case FN_BITMAP_8_BY_13:          return(GLUT_BITMAP_8_BY_13);
      case FN_BITMAP_TIMES_ROMAN_10:   return(GLUT_BITMAP_TIMES_ROMAN_10);
      case FN_BITMAP_TIMES_ROMAN_24:   return(GLUT_BITMAP_TIMES_ROMAN_24);
      case FN_BITMAP_HELVETICA_10:     return(GLUT_BITMAP_HELVETICA_10);
      case FN_BITMAP_HELVETICA_12:     return(GLUT_BITMAP_HELVETICA_12);
      case FN_BITMAP_HELVETICA_18:     return(GLUT_BITMAP_HELVETICA_18);
      default:                         return(GLUT_STROKE_ROMAN);
   };
}

/*****************************************************************************/
void Text(const DevicePoint& p, string text, FontName font)
/*****************************************************************************/
{
   Text(Device2XY(p), text, font);
}

/*****************************************************************************/
void Text(const XYPoint& p, string text, FontName font)
/*****************************************************************************/
{
   glRasterPos2d(p.x, p.y);
   glutBitmapString(Font2GLUTFont(font), (unsigned char*)(text.c_str()));
}

/*****************************************************************************/
void Slider(const DevicePoint& p, string label, float val, int widthInPixels)
/*****************************************************************************/
{
   //Draw spectrum bar from red to blue
   XYPoint pXY1 = Device2XY(p);
   XYPoint pXY2 = Device2XY(DevicePoint(p.x + widthInPixels, p.y));
   glLineWidth(5);
   glBegin(GL_LINES);
      SetColor(255,0,0,125);
      glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
      glVertex2d(pXY1.x, pXY1.y);
      SetColor(65,105,225,125);
      glVertex2d(pXY2.x, pXY2.y);
   glEnd();

   //Normalize val, should be between -1 and 1. 0 is the exact center
   if(val < -1) val = -1;
   else if (val > 1) val = 1;

   //Calculate where pointer should be drawn on X axis
   int offsetX = val * (widthInPixels / 2);
   int centerX = p.x + (widthInPixels / 2);
   int pointerX = centerX + offsetX;

   //Set label and pointer color
   glColor4f(0.7, 0.7, 0.7, 0.5);

   //Draw pointer
   const int pointerDiameterInPixels = 10;
   CircleDevice(DevicePoint(pointerX, p.y), pointerDiameterInPixels, true);

   //Draw Label
   const int labelOffset = 13;
   Text(DevicePoint(p.x, p.y + labelOffset), label, FN_BITMAP_8_BY_13);
}

/*****************************************************************************/
void Slider(const XYPoint& p, string label, float val, int widthInPixels)
/*****************************************************************************/
{
   Slider(XY2Device(p), label, val, widthInPixels);
}

/*****************************************************************************/
XYPoint Device2XY(const DevicePoint& p)
/*****************************************************************************/
{
   return(GetEngine().Device2XY(p));
}

/*****************************************************************************/
DevicePoint XY2Device(const XYPoint& p)
/*****************************************************************************/
{
   return(GetEngine().XY2Device(p));
}

/*****************************************************************************/
double Scale()
/*****************************************************************************/
{
   return(GetEngine().Scale());
}

}
}
