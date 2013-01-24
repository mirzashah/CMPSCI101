//RubberBandLayer
//*****************************************************************************
//Interactive layer for drawing distance measuring rubber band via right click
//*****************************************************************************

#ifndef RUBBER_BAND_LAYER_H
#define RUBBER_BAND_LAYER_H

#include "Layer.h"

namespace Beeber
{

class RubberBandLayer : public Layer
{
   public:
      RubberBandLayer();
      virtual ~RubberBandLayer();

   protected:
      virtual void OnDraw();
      virtual void OnMouseDown(MouseButton button);

   private:
      XYPoint  StartPoint(){return _start;}

   private:
      XYPoint _start;
};

}

#endif
