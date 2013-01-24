#include "EmotionsLayer.h"
#include "BeeberMessage.h"
#include <cassert>
#include <cstdlib>
#include <cstring>

namespace Beeber
{

/*****************************************************************************/
EmotionsLayer::EmotionsLayer()
/*****************************************************************************/
{
   EmotionReport& latest = LatestReport();
   EmotionReport& animate = AnimationTrackerReport();

   memset(&latest, 0x00, sizeof(EmotionReport));
   memset(&animate, 0x00, sizeof(EmotionReport));
   latest.emotionValues[4] = 0.8;
   latest.emotionValues[2] = -0.8;
   latest.emotionValues[3] = -0.8;
   latest.emotionValues[5] =  0.4;
   latest.emotionValues[6] = -0.5;
   latest.emotionValues[7] = -0.2;

}

/*****************************************************************************/
EmotionsLayer::~EmotionsLayer()
/*****************************************************************************/
{
}

/*****************************************************************************/
void EmotionsLayer::AdjustAnimationTracker()
/*****************************************************************************/
{
   //TODO: Adjust animation picture here to converge with latest message
   EmotionReport& latest = LatestReport();
   EmotionReport& animate = AnimationTrackerReport();

   const double adjustRatePerCycle = 0.005;
   for(unsigned int c = 0; c < (int)(EST_LAST); c++)
   {
         double latestVal = latest.emotionValues[(EmotionSpectrumType)(c)];
         double animateVal = animate.emotionValues[(EmotionSpectrumType)(c)];

         //Move slider in the right direction
         if(animateVal < latestVal)
         {
            animateVal = animateVal + adjustRatePerCycle;
            if(animateVal > latestVal) //Prevent jitter
               animateVal = latestVal;
         }
         else if (animateVal > latestVal)
         {
            animateVal = animateVal - adjustRatePerCycle;
            if(animateVal < latestVal) //Prevent jitter
               animateVal = latestVal;
         }

         animate.emotionValues[(EmotionSpectrumType)(c)] = animateVal;
   }


}

/*****************************************************************************/
void EmotionsLayer::OnDraw()
/*****************************************************************************/
{
   DrawEmotionMeters();
}

/*****************************************************************************/
void EmotionsLayer::DrawEmotionMeter(int c, string label, float val)
/*****************************************************************************/
{
   assert(val >= -1.0);
   assert(val <= 1.0);

   SetColor(100,100,4);
   glLineWidth(3);

   const int ySpacingInPixels     = 30;
   const int xRightOffsetInPixels = 200;
   const int yTopOffset           = 10;
   const int sliderWidth          = 180;

   int sliderXVal = WidthInPixels() - xRightOffsetInPixels;
   int sliderYVal = (HeightInPixels() - yTopOffset) - (ySpacingInPixels * c);

   Beeber::Drawing::Slider(DevicePoint(sliderXVal, sliderYVal), label, val, sliderWidth);

}

/*****************************************************************************/
void EmotionsLayer::DrawEmotionMeters()
/*****************************************************************************/
{
   EmotionReport emotions = AnimationTrackerReport();

   for(unsigned int c = 0; c < EST_LAST; c++)
   {
      string label = BeeberEmotionSpectrumToString((EmotionSpectrumType)(c));
      float  val   = emotions.emotionValues[c];
      DrawEmotionMeter(c+1, label, val);
   }
}

/*****************************************************************************/
void EmotionsLayer::OnTimer()
/*****************************************************************************/
{
   AdjustAnimationTracker();
}


};

