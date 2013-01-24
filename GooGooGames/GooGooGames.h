#ifndef GOO_GOO_GAMES_H_DEFINED
#define GOO_GOO_GAMES_H_DEFINED

namespace GooGoo
{

typedef void (*KeyboardFunctionPointer)(unsigned char, int, int);  //This is a function pointer that takes key and also gives current mouse position
typedef void (*MouseFunctionPointer)(int, int); //This is a function pointer that takes an x,y
typedef void (*ResizeFunctionPointer)(int, int); //This is function pointer that takes a width, height
typedef void (*EmptyFunctionPointer)();         //This is a function pointer that takes

/*****************************************************************************/
/* SET EVENT CALLBACK FUNCTIONS WITH THESE */
/*****************************************************************************/
void SetDrawFunction(EmptyFunctionPointer ptr);
void SetMouseLeftDownFunction(MouseFunctionPointer ptr);
void SetMouseLeftUpFunction(MouseFunctionPointer ptr);
void SetMouseLeftDoubleClickFunction(MouseFunctionPointer ptr);
void SetMouseRightDownFunction(MouseFunctionPointer ptr);
void SetMouseRightUpFunction(MouseFunctionPointer ptr);
void SetMouseRightDoubleClickFunction(MouseFunctionPointer ptr);
void SetMouseMoveFunction(MouseFunctionPointer ptr);
void SetKeyboardDownFunction(KeyboardFunctionPointer ptr);
void SetKeyboardUpFunction(KeyboardFunctionPointer ptr);
void SetResizeFunction(ResizeFunctionPointer ptr);
void SetTimerFunction(EmptyFunctionPointer ptr);
void SetStartupFunction(EmptyFunctionPointer ptr);

/*****************************************************************************/
/* RELINQUISH CONTROL TO GOOGOOGAMES */
/*****************************************************************************/
//Surrender control to GooGooGames engine and allow it to start event loop.
//MAKE SURE YOU HAVE SET YOUR EVENT CALLBACK FUNCTIONS BEFORE THIS
void StartGooGooGameEngine(const char applicationName[] = "My Application",
                           int width = 640, int height = 480,
                           int offsetX = 10, int offsetY = 10);

/*****************************************************************************/
/* DRAWING CALLS */
/*****************************************************************************/
//Clears the screen, usually first line of display callback
void ClearScreen();

//Draws a line from (x1,y1) to (x2,y2)
void DrawLine(int x1, int y1, int x2, int y2);

//Draw a circle at point (x,y) with radius r
void DrawCircle(int x, int y, int r, bool fillIt);

//Draw text. For font type, try different styles from 0 to 7. On Windows, 0
//and 1 are not available.
void DrawString(int x, int y, char text[], int fontType);

//Draws a rectangle
void DrawRectangle(int xLeft, int yTop, int width, int height, bool fillIt);

//Represents a point
struct Point
{
   int x;
   int y;
};

//Draws a polygon...takes a set of points in clockwise order in form of array.
//Number of points is also passed.
void DrawPolygon(Point points[], int numberOfPoints, bool fillIt);

//Set current draw color as an R,G,B value.
//Each value must be between 0-255. Optional
//"transparency" variable. 255 = opaque, 0 = completely transparent
//inbetween is translucent
void SetColor(int r, int g, int b, int transparency = 255);

//Sets the background color, by default black (r,g,b) = (0,0,0)
void SetBackgroundColor(int r, int g, int b);

//Set line width in pixels
void SetLineWidth(int widthInPixels);

/*****************************************************************************/
/* MOUSE AND KEYBOARD STATE */
/*****************************************************************************/
//Tells you the current mouse position, uses pass-by-reference to pass back
//x,y values
void CurrentMousePosition(int& x, int& y);

//Returns true if the left mouse button is currently depressed, otherwise false
bool IsLeftMouseButtonDown();

//Returns true if the right mouse button is currently depressed, otherwise
//false
bool IsRightMouseButtonDown();

/*****************************************************************************/
/* SCREEN  */
/*****************************************************************************/
//Makes the game go into full screen mode and take over your entire screen
void ToggleFullScreenMode();

//Gets the current screen height in pixels. Note this changes if you resize the window!
int ScreenHeightInPixels();

//Gets the current screen width in pixels. Note this changes if you resize the window!
int ScreenWidthInPixels();

/*****************************************************************************/
/* RANDOM NUMBERS */
/*****************************************************************************/
//Generates a random number between "lowerBound" and "upperBound"
int GenerateRandomNumber(int lowerBound, int upperBound);

/*****************************************************************************/
/* SOUND */
/*****************************************************************************/
//Play .wav or .mp3 sound file. Pass a string to the function with the filename. Returns false if the sound file could not be found or played.
bool PlaySound(char musicFilename[]);

/*****************************************************************************/
/* Timer Delay */
/*****************************************************************************/
void SetTimerDelayInMilliseconds(int milliseconds);



}


#endif
