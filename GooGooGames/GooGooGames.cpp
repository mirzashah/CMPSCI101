#include "GooGooGames.h"
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <ctime>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

namespace GooGoo
{

void MouseDefault(int x, int y){}
void KeyboardDefault(unsigned char c, int x, int y){}
void ResizeDefault(int x, int y){}
void EmptyDefault(){}


MouseFunctionPointer    g_mouseLeftDown         = MouseDefault;
MouseFunctionPointer    g_mouseLeftUp           = MouseDefault;
MouseFunctionPointer    g_mouseLeftDoubleClick  = MouseDefault;
MouseFunctionPointer    g_mouseRightDown        = MouseDefault;
MouseFunctionPointer    g_mouseRightUp          = MouseDefault;
MouseFunctionPointer    g_mouseRightDoubleClick = MouseDefault;
MouseFunctionPointer    g_mouseMove             = MouseDefault;
KeyboardFunctionPointer g_keyboardDown          = KeyboardDefault;
KeyboardFunctionPointer g_keyboardUp            = KeyboardDefault;
EmptyFunctionPointer    g_draw                  = EmptyDefault;
EmptyFunctionPointer    g_timer                 = EmptyDefault;
ResizeFunctionPointer   g_resize                = ResizeDefault;
EmptyFunctionPointer    g_startup               = EmptyDefault;

/*****************************************************************************/
MouseFunctionPointer GetMouseLeftDownFunction()
/*****************************************************************************/
{
   return g_mouseLeftDown;
}

/*****************************************************************************/
void SetMouseLeftDownFunction(MouseFunctionPointer ptr)
/*****************************************************************************/
{
   g_mouseLeftDown = ptr;
}

/*****************************************************************************/
MouseFunctionPointer GetMouseLeftUpFunction()
/*****************************************************************************/
{
   return g_mouseLeftUp;
}

/*****************************************************************************/
void SetMouseLeftUpFunction(MouseFunctionPointer ptr)
/*****************************************************************************/
{
   g_mouseLeftUp = ptr;
}

/*****************************************************************************/
MouseFunctionPointer GetMouseLeftDoubleClickFunction()
/*****************************************************************************/
{
   return g_mouseLeftDoubleClick;
}

/*****************************************************************************/
EmptyFunctionPointer GetStartupFunction()
/*****************************************************************************/
{
   return g_startup;
}

/*****************************************************************************/
void SetStartupFunction(EmptyFunctionPointer ptr)
/*****************************************************************************/
{
   g_startup = ptr;
}

/*****************************************************************************/
void SetMouseLeftDoubleClickFunction(MouseFunctionPointer ptr)
/*****************************************************************************/
{
   g_mouseLeftDoubleClick = ptr;
}

/*****************************************************************************/
MouseFunctionPointer GetMouseRightDownFunction()
/*****************************************************************************/
{
   return g_mouseRightDown;
}
/*****************************************************************************/
void SetMouseRightDownFunction(MouseFunctionPointer ptr)
/*****************************************************************************/
{
   g_mouseRightDown = ptr;
}

/*****************************************************************************/
MouseFunctionPointer GetMouseRightUpFunction()
/*****************************************************************************/
{
   return g_mouseRightUp;
}

/*****************************************************************************/
void SetMouseRightUpFunction(MouseFunctionPointer ptr)
/*****************************************************************************/
{
   g_mouseRightUp = ptr;
}

/*****************************************************************************/
MouseFunctionPointer GetMouseRightDoubleClickFunction()
/*****************************************************************************/
{
   return g_mouseRightDoubleClick;
}

/*****************************************************************************/
void SetMouseRightDoubleClickFunction(MouseFunctionPointer ptr)
/*****************************************************************************/
{
   g_mouseRightDoubleClick = ptr;
}

/*****************************************************************************/
MouseFunctionPointer GetMouseMoveFunction()
/*****************************************************************************/
{
   return g_mouseMove;
}

/*****************************************************************************/
void  SetMouseMoveFunction(MouseFunctionPointer ptr)
/*****************************************************************************/
{
   g_mouseMove = ptr;
}

/*****************************************************************************/
KeyboardFunctionPointer GetKeyboardDownFunction()
/*****************************************************************************/
{
   return g_keyboardDown;
}

/*****************************************************************************/
void SetKeyboardDownFunction(KeyboardFunctionPointer ptr)
/*****************************************************************************/
{
   g_keyboardDown = ptr;
}

/*****************************************************************************/
KeyboardFunctionPointer GetKeyboardUpFunction()
/*****************************************************************************/
{
   return g_keyboardUp;
}

/*****************************************************************************/
void SetKeyboardUpFunction(KeyboardFunctionPointer ptr)
/*****************************************************************************/
{
   g_keyboardUp = ptr;
}

/*****************************************************************************/
EmptyFunctionPointer GetDrawFunction()
/*****************************************************************************/
{
   return g_draw;
}

/*****************************************************************************/
void SetDrawFunction(EmptyFunctionPointer ptr)
/*****************************************************************************/
{
   g_draw = ptr;
}

/*****************************************************************************/
EmptyFunctionPointer GetTimerFunction()
/*****************************************************************************/
{
   return g_timer;
}

/*****************************************************************************/
void SetTimerFunction(EmptyFunctionPointer ptr)
/*****************************************************************************/
{
   g_timer = ptr;
}

/*****************************************************************************/
ResizeFunctionPointer GetResizeFunction()
/*****************************************************************************/
{
   return g_resize;
}

/*****************************************************************************/
void SetResizeFunction(ResizeFunctionPointer ptr)
/*****************************************************************************/
{
   g_resize = ptr;
}

struct SystemState
{
   SystemState()
   {
      memset(this, 0x00, sizeof(SystemState));
   }

   int  mouseX;
   int  mouseY;
   char lastKeyDown;
   int  screenWidthInPixels;
   int  screenHeightInPixels;
   int  timerDurationInMilliseconds;
   bool isLeftMouseDown;
   bool isRightMouseDown;
};

SystemState g_systemState;

SystemState& State(){return(g_systemState);}

/*****************************************************************************/
void SetTimerDelayInMilliseconds(int milliseconds)
/*****************************************************************************/
{
   State().timerDurationInMilliseconds = milliseconds;
}


bool wasOnStartupCalled = false;

/*****************************************************************************/
void resize(int width, int height)
/*****************************************************************************/
{

   //Adjust viewport and 2d ortho projection
   glViewport(0, 0, width, height);
   State().screenWidthInPixels = width;
   State().screenHeightInPixels = height;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, width, 0,  height);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   if(!wasOnStartupCalled)
   {
      wasOnStartupCalled = true;
      GetStartupFunction()();
   }

   GetResizeFunction()(width, height);
   glutPostRedisplay();
}

/*****************************************************************************/
void ClearScreen()
/*****************************************************************************/
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_LINE_SMOOTH);
   glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*****************************************************************************/
void display()
/*****************************************************************************/
{
   static bool firstTime = true;
   if(firstTime)
   {
      ClearScreen();
      firstTime = false;
   }

   GetDrawFunction()();
   glutSwapBuffers();
}

/*****************************************************************************/
void key(unsigned char key, int x, int y)
/*****************************************************************************/
{
   y = ScreenHeightInPixels() - y;
   State().mouseX = x;
   State().mouseY = y;
   GetKeyboardDownFunction()(key, x, y);
   glutPostRedisplay();
}

/*****************************************************************************/
void keyUp(unsigned char key, int x, int y)
/*****************************************************************************/
{
   y = ScreenHeightInPixels() - y;
   State().mouseX = x;
   State().mouseY = y;
   GetKeyboardUpFunction()(key, x, y);
   glutPostRedisplay();
}

/*****************************************************************************/
void mouseMove(int x, int y)
/*****************************************************************************/
{
   y = ScreenHeightInPixels() - y;
   State().mouseX = x;
   State().mouseY = y;

   GetMouseMoveFunction()(x,y);
}

/*****************************************************************************/
void mouse(int button, int state, int x, int y)
/*****************************************************************************/
{
   y = ScreenHeightInPixels() - y;
   State().mouseX = x;
   State().mouseY = y;

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
               case GLUT_LEFT_BUTTON:   GetMouseLeftDoubleClickFunction()(x,y); break;
               case GLUT_RIGHT_BUTTON:  GetMouseRightDoubleClickFunction()(x,y); break;
               case GLUT_MIDDLE_BUTTON: break;
               default: break;
            };
         }
         lastButtonDown = lastButtonDown + 1; //Little hack to make sure you have to start double click over again
      }
      else
      {
         switch(button)
         {
            case GLUT_LEFT_BUTTON:
               State().isLeftMouseDown = true;
               GetMouseLeftDownFunction()(x,y);
               break;
            case GLUT_RIGHT_BUTTON:
               State().isRightMouseDown = true;
               GetMouseRightDownFunction()(x,y);
               break;
            case GLUT_MIDDLE_BUTTON: break;
            default: break;
         };
         lastButtonDown = button;
      }

      lastTimeDown = timeDown;
   }
   else if(state == GLUT_UP)
   {
      switch(button)
      {
         case GLUT_LEFT_BUTTON:
            State().isLeftMouseDown = false;
            GetMouseLeftUpFunction()(x,y);
            break;
         case GLUT_RIGHT_BUTTON:
            State().isRightMouseDown = false;
            GetMouseRightUpFunction()(x,y);
            break;
         case GLUT_MIDDLE_BUTTON:  break;
         default: break;
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
   if(extra == 1)
   {
      GetTimerFunction()();
      glutTimerFunc(State().timerDurationInMilliseconds,timer,1);
   }
   else if (extra == 0)
   {
      //Hardcoding
      glutPostRedisplay();
      glutTimerFunc(15,timer,0);
   }
}

/*****************************************************************************/
void StartGooGooGameEngine(const char applicationName[], int width, int height, int x, int y)
/*****************************************************************************/
{
   cout << "GooGooGames Engine (v1.1)" << endl;
   cout << "Copyright (c) 2011, Mirza A. Shah" << endl;
   cout << "**********************************\n" << endl;

   SetTimerDelayInMilliseconds(1000); //This is for user game logic
   srand(time(NULL)); //Randomize timer

   cout<<"Initializing GLUT."<<endl;
   int argc = 0;
   char* temp = "hello";
   char* argv[] = {temp};
   glutInit(&argc, argv);
   glutInitWindowSize(width,height);
   cout<<"Initializing window position."<<endl;
   glutInitWindowPosition(x,y);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutCreateWindow(applicationName);
   glutReshapeFunc(resize);
   glutDisplayFunc(display);
   glutKeyboardFunc(key);
   glutKeyboardUpFunc(keyUp);
   glutMouseFunc(mouse);
   glutPassiveMotionFunc(mouseMove);
   glutMotionFunc(mouseMove);
   glutTimerFunc(0, timer, 0); //Draw refresh
   glutTimerFunc(0, timer, 1); //User callback
   glutIdleFunc(idle);
   cout<<"Entering GLUT main loop."<<endl;
   glutMainLoop();
}

/*****************************************************************************/
int GenerateRandomNumber(int lowerBound, int upperBound)
/*****************************************************************************/
{
   return((rand() % (upperBound - lowerBound)) + lowerBound);
}

/*****************************************************************************/
int ScreenHeightInPixels()
/*****************************************************************************/
{
   return(State().screenHeightInPixels);
}

/*****************************************************************************/
int ScreenWidthInPixels()
/*****************************************************************************/
{
   return(State().screenWidthInPixels);
}

/*****************************************************************************/
void CurrentMousePosition(int& x, int& y)
/*****************************************************************************/
{
   x = State().mouseX;
   y = State().mouseY;
}

/*****************************************************************************/
void SetBackgroundColor(int r, int g, int b)
/*****************************************************************************/
{
   glClearColor(r/255.0f, g/255.0f, b/255.0f, 0);
}

/*****************************************************************************/
bool PlaySound(char musicFilename[])
/*****************************************************************************/
{
   //TODO:!!!
   return false;
}

/*****************************************************************************/
void ToggleFullScreenMode()
/*****************************************************************************/
{
   glutFullScreenToggle();
}

/*****************************************************************************/
void SetColor(int r, int g, int b, int transparency)
/*****************************************************************************/
{
   glColor4f(r/255.0f, g/255.0f, b/255.0f, transparency/255.0f);
}

/*****************************************************************************/
void DrawLine(int x1, int y1, int x2, int y2)
/*****************************************************************************/
{
   glBegin(GL_LINES);
      glVertex2d(x1, y1);
      glVertex2d(x2, y2);
   glEnd();
}

/*****************************************************************************/
void DrawPolygon(Point points[], int n, bool fillIt)
/*****************************************************************************/
{
   if(fillIt)
      glBegin(GL_POLYGON);
   else
      glBegin(GL_LINE_LOOP);

   for(int c = 0; c < n; c++)
   {
      glVertex2d(points[c].x, points[c].y);
   }

   glEnd();
}

/*****************************************************************************/
void DrawRectangle(int xLeft, int yTop, int width, int height, bool fillIt)
/*****************************************************************************/
{
   if(fillIt)
      glBegin(GL_POLYGON);
   else
      glBegin(GL_LINE_LOOP);

   glVertex2d(xLeft, yTop);
   glVertex2d(xLeft + width, yTop);
   glVertex2d(xLeft + width, yTop - height);
   glVertex2d(xLeft, yTop - height);
   if (!fillIt)
      glVertex2d(xLeft, yTop); //Loop back to beginning
   glEnd();

}

/*****************************************************************************/
void DrawCircle(int x, int y, int radius, bool filled)
/*****************************************************************************/
{
   int num_segments = 50;
   double cx = x;
   double cy = y;
   double r = radius;

   if(filled)
      glBegin(GL_POLYGON);
   else
      glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}

enum FontName
{
   FN_STROKE_ROMAN,
   FN_STROKE_MONO_ROMAN,
   FN_BITMAP_9_BY_15,
   FN_BITMAP_8_BY_13,
   FN_BITMAP_TIMES_ROMAN_10,
   FN_BITMAP_TIMES_ROMAN_24,
   FN_BITMAP_HELVETICA_10,
   FN_BITMAP_HELVETICA_12,
   FN_BITMAP_HELVETICA_18
};

/*****************************************************************************/
static void* Font2GLUTFont(FontName font)
/*****************************************************************************/
{
   switch(font)
   {
      case FN_STROKE_ROMAN:            return(GLUT_STROKE_ROMAN);
      case FN_STROKE_MONO_ROMAN:       return(GLUT_STROKE_MONO_ROMAN);
      case FN_BITMAP_9_BY_15:          return(GLUT_BITMAP_9_BY_15);
      case FN_BITMAP_8_BY_13:          return(GLUT_BITMAP_8_BY_13);
      case FN_BITMAP_TIMES_ROMAN_10:   return(GLUT_BITMAP_TIMES_ROMAN_10);
      case FN_BITMAP_TIMES_ROMAN_24:   return(GLUT_BITMAP_TIMES_ROMAN_24);
      case FN_BITMAP_HELVETICA_10:     return(GLUT_BITMAP_HELVETICA_10);
      case FN_BITMAP_HELVETICA_12:     return(GLUT_BITMAP_HELVETICA_12);
      case FN_BITMAP_HELVETICA_18:     return(GLUT_BITMAP_HELVETICA_18);
      default:                         return(GLUT_STROKE_ROMAN);
   };
}

/*****************************************************************************/
void DrawString(int x, int y, char text[], int fontType)
/*****************************************************************************/
{
   glRasterPos2d(x, y);
   glutBitmapString(Font2GLUTFont((FontName)(fontType)), (const unsigned char*)(text));
}

/*****************************************************************************/
void SetLineWidth(int widthInPixels)
/*****************************************************************************/
{
   glLineWidth(widthInPixels);
}

/*****************************************************************************/
bool IsLeftMouseButtonDown()
/*****************************************************************************/
{
   return (State().isLeftMouseDown);
}

/*****************************************************************************/
bool IsRightMouseButtonDown()
/*****************************************************************************/
{
   return (State().isRightMouseDown);
}

}
