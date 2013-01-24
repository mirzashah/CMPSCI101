#include "GridLayer.h"
#include <cmath>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::ostringstream;

namespace Beeber
{

/****************************************************/
const double        SPACING_FACTOR = 100; //Spaced every 100 pixels
const unsigned char DEGREES_SYMBOL = 186;
/****************************************************/

/*****************************************************************************/
GridLayer::GridLayer()
/*****************************************************************************/
{
   InitialCenter(XYPoint(0,0));
   LastKnownScale(0);
}

/*****************************************************************************/
GridLayer::~GridLayer()
/*****************************************************************************/
{
}

/****************************************************/
void GridLayer::DrawGrid()
/****************************************************/
{
   glColor3f(0,1,0);
   glLineWidth(1);
   DrawHorizontals();
   DrawVerticals();
}

/*****************************************************************************/
void GridLayer::OnDraw()
/*****************************************************************************/
{
    UpdateDataNeededByRenderingAlgorithm();
    DrawGrid();
}

/****************************************************/
void GridLayer::DrawVerticalTicLabel(XYPoint p)
/****************************************************/
{
    ostringstream label;
    label << p.x;

    DevicePoint pAdjusted = XY2Device(p);
    pAdjusted.x = pAdjusted.x + 3;
    pAdjusted.y = pAdjusted.y - 8;
    DrawLabel(pAdjusted,label.str());
}

/****************************************************/
void GridLayer::DrawHorizontalTicLabel(XYPoint p)
/****************************************************/
{
    ostringstream label;
    label << p.y;

    DevicePoint pAdjusted = XY2Device(p);
    pAdjusted.x = pAdjusted.x + 3;
    pAdjusted.y = pAdjusted.y + 3;
    DrawLabel(pAdjusted,label.str());
}

/****************************************************/
void GridLayer::DrawLabel(DevicePoint p, string label)
/****************************************************/
{
    Text(p, label);
}

/****************************************************/
void GridLayer::DrawVerticals()
/****************************************************/
{
   double xCenter = InitialCenter().x;

   //Draw verticals right of center and center
   for(double x = xCenter; x<=ExtentRight(); x = x + SpacingOfTicMarksInXYUnits())
      DrawVerticalAt(x);

   //Draw verticals left of center
   for(double x = xCenter - SpacingOfTicMarksInXYUnits(); x>=ExtentLeft(); x = x - SpacingOfTicMarksInXYUnits())
      DrawVerticalAt(x);
}

/****************************************************/
void GridLayer::DrawHorizontals()
/****************************************************/
{
   double yCenter = InitialCenter().y;

   //Draw parallels above center and center
   for(double y = yCenter; y <= ExtentTop(); y = y + SpacingOfTicMarksInXYUnits())
      DrawHorizontalAt(y);

   //Draw parallels below center
   for(double y = yCenter - SpacingOfTicMarksInXYUnits(); y >= ExtentBottom(); y = y - SpacingOfTicMarksInXYUnits())
      DrawHorizontalAt(y);
}

/****************************************************/
void GridLayer::DrawVerticalAt(double x)
/****************************************************/
{
    XYPoint top(x, ExtentTop());
    XYPoint bottom(x, ExtentBottom());
    Line(top,bottom); //Nothin to it ;)
    DrawVerticalTicLabel(top);
}

/****************************************************/
void GridLayer::DrawHorizontalAt(double y)
/****************************************************/
{
    XYPoint left(ExtentLeft(), y);
    XYPoint right(ExtentRight(), y);
    Line(left, right);
    DrawHorizontalTicLabel(left);
}

/****************************************************/
bool GridLayer::HasScaleChangedSinceLastRender()
/****************************************************/
{
    return((LastKnownScale() - Scale()) != 0);
}

/****************************************************/
double GridLayer::SpacingOfTicMarksInXYUnits()
/****************************************************/
{
    return(LastKnownScale() * SPACING_FACTOR);
}

/****************************************************/
void GridLayer::UpdateDataNeededByRenderingAlgorithm()
/****************************************************/
{
    if(HasScaleChangedSinceLastRender())
    {
        LastKnownScale(Scale());
        InitialCenter(Center());
    }
}


}
