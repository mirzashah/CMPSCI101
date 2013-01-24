#include "RubberBandLayer.h"
#include <sstream>
using std::ostringstream;

namespace Beeber
{

/*****************************************************************************/
RubberBandLayer::RubberBandLayer()
/*****************************************************************************/
{
}

/*****************************************************************************/
RubberBandLayer::~RubberBandLayer()
/*****************************************************************************/
{
}

/*****************************************************************************/
void RubberBandLayer::OnDraw()
/*****************************************************************************/
{
   if(IsMouseButtonDown(MB_RIGHT))
   {
      glLineWidth(2.0);
      SetColor(218, 165, 32, 200);
      Line(StartPoint(), MousePosition());
      ostringstream disStr;
      disStr << "Distance (mm): " << Distance(StartPoint(), MousePosition());
      Text(MousePosition(), disStr.str());
   }
}

/*****************************************************************************/
void RubberBandLayer::OnMouseDown(MouseButton button)
/*****************************************************************************/
{
   switch(button)
   {
      case MB_RIGHT: _start = MousePosition(); break;
      default: break;
   };
}


}
