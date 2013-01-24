//Emotions Layer
//*****************************************************************************
//Shows how the Beebz is feeling!
//*****************************************************************************

#ifndef EMOTIONS_LAYER_H_DEFINED
#define EMOTIONS_LAYER_H_DEFINED

#include "Layer.h"
#include <BeeberIPC.h>

namespace Beeber
{

class EmotionsLayer : public Layer
{
   public:
      EmotionsLayer();
      virtual ~EmotionsLayer();

      virtual void   OnDraw();
      virtual void   OnTimer();
      void           OnIncomingMessage(time_t timestamp, const EmotionReport& msg){LatestReport(msg);}

   private:
      void           AdjustAnimationTracker();
      void           DrawEmotionMeter(int c, string label, float val);
      void           DrawEmotionMeters();
      //This is the latest emotions message we received from the Beeber brain
      EmotionReport& LatestReport(){return(_latestReport);}
      void           LatestReport(const EmotionReport& report){_latestReport = report;}

      //This is the report we use for tracking animation of
      EmotionReport& AnimationTrackerReport(){return(_animationTrackerReport);}

   private:
      EmotionReport _animationTrackerReport;
      EmotionReport _latestReport;
};

};


#endif
