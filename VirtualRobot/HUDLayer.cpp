#include "HUDLayer.h"
#include <sstream>
using std::ostringstream;

namespace Beeber
{

/*****************************************************************************/
HUDLayer::HUDLayer()
/*****************************************************************************/
{
}

/*****************************************************************************/
HUDLayer::~HUDLayer()
/*****************************************************************************/
{
}

/*****************************************************************************/
void HUDLayer::OnDraw()
/*****************************************************************************/
{
   Drawing::SetColor(154, 205, 50);
   ostringstream text1, text2;
   XYPoint mousePos = MousePosition();
   DevicePoint mousePosDev = MousePositionDevice();
   text1<<"Mouse (XY): ("<<mousePos.x<<", "<<mousePos.y<<")";
   text2<<"Mouse (Device): ("<<mousePosDev.x<<", "<<mousePosDev.y<<")";
   const int rightYOffset = 230;
	Text(DevicePoint(WidthInPixels() - rightYOffset, 28), text2.str(), FN_BITMAP_8_BY_13);
	Text(DevicePoint(WidthInPixels() - rightYOffset, 10), text1.str(), FN_BITMAP_8_BY_13);

}

}
