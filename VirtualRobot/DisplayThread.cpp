#include "DisplayThread.h"
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <BeeberDisplayCore.h>

using namespace Beeber;

namespace VirtualRobot
{


/*****************************************************************************/
void resize(int width, int height)
/*****************************************************************************/
{
   GetEngine().OnResize(width, height);
}

/*****************************************************************************/
void display()
/*****************************************************************************/
{
   GetEngine().OnDraw();
   glutSwapBuffers();
}

/*****************************************************************************/
void key(unsigned char key, int x, int y)
/*****************************************************************************/
{
   GetEngine().OnKeyDown(key, x, y);
   glutPostRedisplay();
}

/*****************************************************************************/
void mouseMove(int x, int y)
/*****************************************************************************/
{
   GetEngine().OnMouseMove(x,(GetEngine().HeightInPixels() - y));
}

/*****************************************************************************/
void mouse(int button, int state, int x, int y)
/*****************************************************************************/
{
   Engine&    engine         = GetEngine();
   static int lastX = x;
   static int lastY = y;

   if(state == GLUT_DOWN)
   {
      static int lastButtonDown     = -1;
      static clock_t lastTimeDown   = clock();
      clock_t timeDown = clock();

      if(lastButtonDown == button && lastX == x && lastY == y) //GLUT doesn't have double click support so I mimic it here
      {

         if(timeDown - lastTimeDown < (CLOCKS_PER_SEC/2))
         {
            switch(button)
            {
               case GLUT_LEFT_BUTTON:   engine.OnMouseDoubleClick(MB_LEFT); break;
               case GLUT_MIDDLE_BUTTON: engine.OnMouseDoubleClick(MB_MIDDLE); break;
               case GLUT_RIGHT_BUTTON:  engine.OnMouseDoubleClick(MB_RIGHT); break;
            };
         }
         lastButtonDown = lastButtonDown + 1; //Little hack to make sure you have to start double click over again
      }
      else
      {
         switch(button)
         {
            case GLUT_LEFT_BUTTON:   engine.OnMouseDown(MB_LEFT); break;
            case GLUT_MIDDLE_BUTTON: engine.OnMouseDown(MB_MIDDLE); break;
            case GLUT_RIGHT_BUTTON:  engine.OnMouseDown(MB_RIGHT); break;
         };
         lastButtonDown = button;
      }

      lastTimeDown = timeDown;
   }
   else if(state == GLUT_UP)
   {
      switch(button)
      {
         case GLUT_LEFT_BUTTON:   engine.OnMouseUp(MB_LEFT); break;
         case GLUT_MIDDLE_BUTTON: engine.OnMouseUp(MB_MIDDLE); break;
         case GLUT_RIGHT_BUTTON:  engine.OnMouseUp(MB_RIGHT); break;
      };
   }

   lastX = x;
   lastY = y;
}

/*****************************************************************************/
void idle()

/*****************************************************************************/
{
    glutPostRedisplay();
}

/*****************************************************************************/
void timer(int extra)
/*****************************************************************************/
{
   GetEngine().OnTimer();
   glutTimerFunc(GetEngine().TimerDurationInMilliseconds(),timer,0);
}

/*****************************************************************************/
void CreateAndAddAllLayersToEngine()
/*****************************************************************************/
{
   GetEngine().AddLayer(new GridLayer());
   GetEngine().AddLayer(new ObstacleLayer());
   GetEngine().AddLayer(new BotLayer());
   GetEngine().AddLayer(new RubberBandLayer());
   GetEngine().AddLayer(new HUDLayer());
}

/*****************************************************************************/
void InitializeDisplay()
/*****************************************************************************/
{
   CreateAndAddAllLayersToEngine();

   int argc = 0;
   char* temp = "hello";
   char* argv[] = {temp};
   glutInit(&argc, argv);
   glutInitWindowSize(640,480);
   glutInitWindowPosition(50,50);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutCreateWindow("VirtualRobot Display");
   glutReshapeFunc(resize);
   glutDisplayFunc(display);
   glutKeyboardFunc(key);
   glutMouseFunc(mouse);
   glutPassiveMotionFunc(mouseMove);
   glutMotionFunc(mouseMove);
   glutTimerFunc(0, timer,0);
   glutIdleFunc(idle);

}

/*****************************************************************************/
void StartDisplayLoop()
/*****************************************************************************/
{
   glutMainLoop();
}


/*****************************************************************************/
void DisplayThread::Run()
/*****************************************************************************/
{

   InitializeDisplay();
   IsDone().Unlock(); //Was locked in constructor
   StartDisplayLoop();
}

};
