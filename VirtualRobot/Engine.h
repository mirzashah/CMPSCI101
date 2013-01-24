//Engine.h
//*****************************************************************************
//This class represents a simple 2D graphics engine that sits on top of OpenGL.
//The engine maintains a list of "Layer" objects that it paints one-by-one
//on each redraw.
//*****************************************************************************

#ifndef ENGINE_H_DEFINED
#define ENGINE_H_DEFINED

#include "Layer.h"
#include "DisplayTypes.h"
#include <map>
using std::map;

namespace Beeber
{
typedef map<MouseButton, bool> MouseButtonMap;
typedef map<MouseButton, XYPoint> MouseButtonToPositionMap;
class Engine
{
   public:
      static Engine& Instance();
      virtual ~Engine();

      void            AddLayer(Layer* layer);
      void            Invalidate();

      void            OnDraw();
      void            OnResize(int width, int height);

      //Iterative Timer
      void            OnTimer();
      int             TimerDurationInMilliseconds(){return(15);}

      //Keyboard/Mouse
      bool            IsMouseButtonDown(MouseButton button);
      XYPoint         LastMousePosition();
      DevicePoint     LastMousePositionDevice(){return(_lastMousePositionDevice);}
      void            LastMousePositionDevice(DevicePoint p){_lastMousePositionDevice = p;}
      XYPoint         MousePosition();
      DevicePoint     MousePositionDevice(){return(_mousePositionDevice);}
      void            MousePositionDevice(DevicePoint p){_mousePositionDevice = p;}
      void            OnMouseMove(int x, int y);
      void            OnMouseDoubleClick(MouseButton button);
      void            OnMouseDown(MouseButton button);
      void            OnMouseUp(MouseButton button);
      void            OnKeyDown(unsigned char key, int x, int y);
      void            OnKeyUp();

      //Coordinate Transformation Management
      XYPoint         Center(){return(_center);}
      void            Center(XYPoint p){_center = p;}
      XYExtents       Extents();
      double          ExtentLeft();
      double          ExtentRight();
      double          ExtentTop();
      double          ExtentBottom();
      double          Scale(){return(_scale);} //XY to pixel ratio
      void            Scale(double scale){_scale = scale;}
      int             WidthInPixels(){return(_widthInPixels);}
      void            WidthInPixels(int width){_widthInPixels = width;}
      int             HeightInPixels(){return(_heightInPixels);}
      void            HeightInPixels(int height){_heightInPixels = height;}
      DevicePoint     XY2Device(XYPoint p);
      XYPoint         Device2XY(DevicePoint p);

   private: //Keyboard/Mouse Handling
      void                      IsMouseButtonDown(MouseButton button, bool isIt);
      XYPoint                   PositionOfLastClick(MouseButton button);
      MouseButtonToPositionMap& LastMouseDownPosition(){return(_lastMouseDownPosition);}
      MouseButtonMap&           MouseDownMap(){return(_mouseDownMap);}

   private:
      Engine();
      void            DrawAllLayers();
      void            HandlePanning();
      void            HandleZoomIn();
      void            HandleZoomOut();
      LayerList&      Layers(){return(_layers);}
      void            ReadjustProjectionExtents();

   private: //Simulation and IPC
      bool           IsInSimulationMode();
      int            EngineCyclesSinceLastSimulatorInvocation(){return(_engineCyclesSinceLastSimulatorInvocation);}
      void           EngineCyclesSinceLastSimulatorInvocation(int t){_engineCyclesSinceLastSimulatorInvocation = t;}
      void           CheckForAndProcessIncomingMessages();
   private:
      int                      _engineCyclesSinceLastSimulatorInvocation;
      LayerList                _layers;
      XYPoint                  _center;
      double                   _scale;
      int                      _widthInPixels;
      int                      _heightInPixels;
      MouseButtonMap           _mouseDownMap;
      MouseButtonToPositionMap _lastMouseDownPosition;
      DevicePoint              _lastMousePositionDevice;
      DevicePoint              _mousePositionDevice;
      static Engine*           _instance;
};

Engine& GetEngine();

};


#endif
