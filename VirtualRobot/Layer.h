//Layer.h
//*****************************************************************************
//Represents a single drawable layer in the display.
//*****************************************************************************

#ifndef LAYER_H_DEFINED
#define LAYER_H_DEFINED

#include "DisplayTypes.h"
#include "Drawing.h"
#include <vector>
using std::vector;
using namespace Beeber::Drawing;

namespace Beeber
{

class Layer
{
   friend class Engine;

   public:
      Layer();
      virtual ~Layer();

      virtual void   OnDraw() = 0;

   protected: //Coordinate Transformation Management
      XYPoint        Center();
      void           Center(XYPoint p);
      XYExtents      Extents();
      double         ExtentLeft();
      double         ExtentRight();
      double         ExtentTop();
      double         ExtentBottom();
      double         Scale();
      void           Scale(double scale);
      int            WidthInPixels();
      int            HeightInPixels();
      DevicePoint    XY2Device(XYPoint p);
      XYPoint        Device2XY(DevicePoint p);

   protected: //Keyboard/Mouse/Timers
      bool           IsMouseButtonDown(MouseButton button);
      XYPoint        LastMousePosition();
      DevicePoint    LastMousePositionDevice();
      XYPoint        MousePosition();
      DevicePoint    MousePositionDevice();
      virtual void   OnMouseMove(int x, int y){}
      virtual void   OnMouseDoubleClick(MouseButton button){}
      virtual void   OnMouseDown(MouseButton button){}
      virtual void   OnMouseUp(MouseButton button){}
      virtual void   OnKeyDown(unsigned char key, int x, int y){}
      virtual void   OnKeyUp(){}
      virtual void   OnTimer();
      int            TimerDurationInMilliseconds();

   protected:
      bool           IsInSimulationMode();

   private: //Incoming messages
      void           ProcessIncomingMessages(const BeeberMessageList& msgs);
      void           ProcessIncomingMessage(const BeeberMessage& msg);

   protected:
      virtual void   OnIncomingMessage(time_t timestamp, const ObstacleReport& obstacle){}
      virtual void   OnIncomingMessage(time_t timestamp, const SensorReport& sensors){}
      virtual void   OnIncomingMessage(time_t timestamp, const EmotionReport& emotions){}


};

typedef vector<Layer*> LayerList;

};

#endif
