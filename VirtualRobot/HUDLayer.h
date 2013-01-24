//HUDLayer.h
//*****************************************************************************
//The heads-up-display (HUD) layer
//*****************************************************************************

#ifndef HUD_LAYER_H_DEFINED
#define HUD_LAYER_H_DEFINED

#include "Layer.h"

namespace Beeber
{

class HUDLayer : public Layer
{
   public:
      HUDLayer();
      virtual ~HUDLayer();

      virtual void OnDraw();
};

};

#endif
