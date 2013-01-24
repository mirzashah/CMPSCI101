#include "Engine.h"
#include <cstdlib>
#include <GL/freeglut.h>
#include <BeeberSim.h>

namespace Beeber
{

/*****************************************************************************/
Engine* Engine::_instance = NULL;
/*****************************************************************************/

const double SIMULATOR_TIMESTEP_GRANULARITY_IN_SECONDS = 0.1;

/*****************************************************************************/
Engine::Engine()
/*****************************************************************************/
{
   Scale(1);
   Center(XYPoint(0,0));
   WidthInPixels(0);
   HeightInPixels(0);
   LastMousePositionDevice(DevicePoint(0,0));
   MousePositionDevice(DevicePoint(0,0));

   //Needed for simulator
   EngineCyclesSinceLastSimulatorInvocation(99999);
   Beeber::Simulator::SetSimulatorTimestepGranularityInSeconds(SIMULATOR_TIMESTEP_GRANULARITY_IN_SECONDS);

}

/*****************************************************************************/
Engine::~Engine()
/*****************************************************************************/
{
}

/*****************************************************************************/
void Engine::AddLayer(Layer* layer)
/*****************************************************************************/
{
   Layers().push_back(layer);
}

/*****************************************************************************/
XYPoint Engine::Device2XY(DevicePoint p)
/*****************************************************************************/
{
    double xCart, yCart, zCart;
    GLdouble modelMatrix[16];
    GLdouble projMatrix[16];
    GLint viewport[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);

    gluUnProject(p.x, p.y, 0, modelMatrix, projMatrix, viewport, &xCart, &yCart, &zCart);
    return(XYPoint(xCart,yCart));
}

/*****************************************************************************/
void Engine::DrawAllLayers()
/*****************************************************************************/
{
   LayerList& layers = Layers();
   for(unsigned int c = 0; c < layers.size(); c++)
      layers.at(c)->OnDraw();
}

/*****************************************************************************/
XYExtents Engine::Extents()
/*****************************************************************************/
{

   double  scale      = Scale();
   XYPoint center     = Center();
   int     widthPix   = WidthInPixels();
   int     heightPix  = HeightInPixels();

   double  left       = center.x - ((((double)widthPix) / 2.0) * scale);
   double  right      = center.x + ((((double)widthPix) / 2.0) * scale);

   double  top        = center.y + ((((double)heightPix) / 2.0) * scale);
   double  bottom     = center.y - ((((double)heightPix) / 2.0) * scale);

   return(XYExtents(left, right, top, bottom));
}

/*****************************************************************************/
double Engine::ExtentLeft()
/*****************************************************************************/
{
   return(Extents().left);
}

/*****************************************************************************/
double Engine::ExtentRight()
/*****************************************************************************/
{
   return(Extents().right);
}

/*****************************************************************************/
double Engine::ExtentTop()
/*****************************************************************************/
{
   return(Extents().top);
}

/*****************************************************************************/
double Engine::ExtentBottom()
/*****************************************************************************/
{
   return(Extents().bottom);
}

/****************************************/
void Engine::HandlePanning()
/****************************************/
{
   if(IsMouseButtonDown(MB_LEFT))
   {
      XYPoint currentMousePoint    = MousePosition();
      XYPoint pointOfLastLeftClick = LastMousePosition();
      double deltaX = pointOfLastLeftClick.x - currentMousePoint.x;
      double deltaY = pointOfLastLeftClick.y - currentMousePoint.y ;
      XYPoint center = Center();
      XYPoint newCenter(center.x+deltaX, center.y+deltaY);
      Center(newCenter);
      ReadjustProjectionExtents();
   }
}

/****************************************/
void Engine::ReadjustProjectionExtents()
/****************************************/
{
   XYExtents extents = Extents();
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(extents.left, extents.right, extents.bottom, extents.top);
   glMatrixMode(GL_MODELVIEW);
   glutPostRedisplay();
}

/****************************************/
void Engine::HandleZoomIn()
/****************************************/
{
    Center(PositionOfLastClick(MB_LEFT));
    Scale(Scale()*0.60);
    ReadjustProjectionExtents();
}

/****************************************/
void Engine::HandleZoomOut()
/****************************************/
{
    Scale(Scale()*4);
    ReadjustProjectionExtents();
}

/*****************************************************************************/
Engine& Engine::Instance()
/*****************************************************************************/
{
   if(_instance == NULL)
      _instance = new Engine();
   return(*_instance);
}

/*****************************************************************************/
void Engine::Invalidate()
/*****************************************************************************/
{
   glutPostRedisplay();
}

/*****************************************************************************/
bool Engine::IsMouseButtonDown(MouseButton button)
/*****************************************************************************/
{
   return(MouseDownMap()[button]);
}

/*****************************************************************************/
void Engine::IsMouseButtonDown(MouseButton button, bool isIt)
/*****************************************************************************/
{
   MouseDownMap()[button] = isIt;
}

/*****************************************************************************/
void Engine::OnDraw()
/*****************************************************************************/
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_LINE_SMOOTH);
   glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
   DrawAllLayers();
}

/*****************************************************************************/
void Engine::OnKeyDown(unsigned char key, int x, int y)
/*****************************************************************************/
{
   switch (key)
   {
      case 27 :
         exit(0);
         break;
      default:
         break;
   };
}

/*****************************************************************************/
XYPoint Engine::LastMousePosition()
/*****************************************************************************/
{
   return(Device2XY(LastMousePositionDevice()));
}

/*****************************************************************************/
XYPoint Engine::MousePosition()
/*****************************************************************************/
{
   return(Device2XY(MousePositionDevice()));
}

/*****************************************************************************/
void Engine::OnMouseMove(int x, int y)
/*****************************************************************************/
{
   LastMousePositionDevice(MousePositionDevice());
   MousePositionDevice(DevicePoint(x,y));
   HandlePanning();

   //Invoke for all layers
   LayerList& layers = Layers();
   for(unsigned int c = 0; c < layers.size(); c++)
      layers.at(c)->OnMouseMove(x,y);
}

/*****************************************************************************/
void Engine::OnMouseDoubleClick(MouseButton button)
/*****************************************************************************/
{
   switch(button)
   {
      case MB_LEFT: HandleZoomIn(); break;
      case MB_RIGHT: HandleZoomOut(); break;
      default: break;
   };

   //Invoke for all layers
   LayerList& layers = Layers();
   for(unsigned int c = 0; c < layers.size(); c++)
      layers.at(c)->OnMouseDoubleClick(button);
}

/*****************************************************************************/
void Engine::OnMouseDown(MouseButton button)
/*****************************************************************************/
{
   MouseDownMap()[button] = true;
   LastMouseDownPosition()[button] = MousePosition();

   //Invoke for all layers
   LayerList& layers = Layers();
   for(unsigned int c = 0; c < layers.size(); c++)
      layers.at(c)->OnMouseDown(button);
}

/*****************************************************************************/
void Engine::OnMouseUp(MouseButton button)
/*****************************************************************************/
{
   MouseDownMap()[button] = false;

   //Invoke for all layers
   LayerList& layers = Layers();
   for(unsigned int c = 0; c < layers.size(); c++)
      layers.at(c)->OnMouseUp(button);

}

/*****************************************************************************/
void Engine::OnResize(int width, int height)
/*****************************************************************************/
{
   glViewport(0, 0, width, height);
   WidthInPixels(width);
   HeightInPixels(height);
   XYExtents extents = Extents();

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(extents.left, extents.right, extents.bottom, extents.top);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

/*****************************************************************************/
bool Engine::IsInSimulationMode()
/*****************************************************************************/
{
   return(BeeberConfig().IsSimulationInDisplayEnabled());
}

/*****************************************************************************/
void Engine::CheckForAndProcessIncomingMessages()
/*****************************************************************************/
{
   //Handle Simulation and IPC shiat
   BeeberMessageList msgs;

   msgs = Beeber::Simulator::RunSingleSimulatorEngineCycle();

   if(msgs.size() > 0)
   {
      LayerList& layers = Layers();
      for(unsigned int c = 0; c < layers.size(); c++)
         layers.at(c)->ProcessIncomingMessages(msgs);
   }


}

/*****************************************************************************/
void Engine::OnTimer()
/*****************************************************************************/
{
   CheckForAndProcessIncomingMessages(); //IPC or sim

   //Invoke on time callback in all layers
   LayerList& layers = Layers();
   for(unsigned int c = 0; c < layers.size(); c++)
      layers.at(c)->OnTimer();
}

/*****************************************************************************/
XYPoint Engine::PositionOfLastClick(MouseButton button)
/*****************************************************************************/
{
   return(LastMouseDownPosition()[button]);
}

/*****************************************************************************/
DevicePoint Engine::XY2Device(XYPoint p)
/*****************************************************************************/
{
    double xDev, yDev, zDev;
    GLdouble modelMatrix[16];
    GLdouble projMatrix[16];
    GLint viewport[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);

    gluProject(p.x, p.y, 0, modelMatrix, projMatrix, viewport, &xDev, &yDev, &zDev);
    return(DevicePoint((int)xDev,(int)yDev));
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

/*****************************************************************************/
Engine& GetEngine()
/*****************************************************************************/
{
   return(Engine::Instance());
}

}
