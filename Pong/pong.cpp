//Pong for GooGooGames
//Author: mas
//----------------------------------------------------------------------------
//Dear students,
//Notice in this version of Pong a few distinctions from the one in class.
//1) Structures replace the scalar variables we had before making the code
//a lot cleaner and shorter
//
//2) Instead of typing "using namespace GooGoo" at the top of the page,
//I omit this. Instead whereever I use a GooGooGames function, I prefix
//the function with "GooGoo::". We didn't talk about namespaces, but
//essentially it's an organization tool in C++ to group functions.
//If you type the namespace followed by "::" followed by the function
//name, this is acceptable. I did this to make it clear which functions
//are ones I wrote for this game, and which are part of the GooGoo library.
//
//3) This game is complete with scoring, randomized ball, divider line,
//and autospeed up.

#include "GooGooGames.h" //Needed for GooGoo functions
#include <iostream>      //Needed for cout
#include <cstdio>
#include <ctime>

using namespace std;

//New types (i.e. structs) we want to use to build the game.
/*****************************************************************************/
struct Paddle
{
   int x;
   int y;
   int speed;
   int width;
   int height;
   int score;
};

struct Ball
{
   int x;
   int y;
   int speedX;
   int speedY;
   int width;
};

//Global variables: Note that the structures above are useless until we actually
//declare variables of their type as follows:
/*****************************************************************************/
Paddle leftPaddle;    //Models the left paddle
Paddle rightPaddle;   //Models the right paddle
Ball   theBall;       //Models the ball
int    numberOfTimerCalls; //Models time elapsed in terms of OnTimer calls


//Function prototypes - These are promises to the C++ compiler that we will
//implement the functions somewhere else
/*****************************************************************************/
void CheckIfBallHasHitAPaddleAndNeedsToChangeVelocity(Ball& b);
void CheckIfBallHasHitTopOrBottomWallsAndNeedsToChangeVelocity(Ball& b);
void CheckIfBallHasGonePastLeftOrRightWallsAndIncrementScoreIfNecessary(Ball b);
void DrawPaddle(Paddle p);
void DrawBall(Ball b);
void DrawDividerLine();
void DrawScores();
void InitializePaddleAndBallPositions(bool resetScores);
void MoveBall(Ball& b);
void MovePaddleDown(Paddle& p);
void MovePaddleUp(Paddle& p);
void OnDraw();
void OnKeyDown(unsigned char c, int x, int y);
void OnResize(int width, int height);
void OnStartup();
void OnTimer();
void RecalculatePaddlePositions();
void SpeedUpBallIfNecessary(Ball& b);


//Main Function - All C and C++ programs start at function int main()!!!
/*****************************************************************************/

/*****************************************************************************/
int main()
/*****************************************************************************/
{
   //Set event callback functions.
   GooGoo::SetDrawFunction(OnDraw);
   GooGoo::SetKeyboardDownFunction(OnKeyDown);
   GooGoo::SetResizeFunction(OnResize);
   GooGoo::SetTimerFunction(OnTimer);
   GooGoo::SetStartupFunction(OnStartup);

   //Start up GooGooGames Engine. This gives control over to GooGooGames
   //and starts the "event loop". The event callback functions set above
   //(OnDraw, OnKeyDown, etc) will be called as the events occur.
   int screenWidth = 640;
   int screenHeight = 480;
   GooGoo::StartGooGooGameEngine("Pong!", screenWidth, screenHeight, 100, 100);

   return 0;
}

//Function definitions - These are the implementations of the functions we
//promised to implement above in our function prototypes section
/*****************************************************************************/

/*****************************************************************************/
void CheckIfBallHasHitAPaddleAndNeedsToChangeVelocity(Ball& b)
/*****************************************************************************/
{
   bool didItHitLeftPaddle  = (b.x <= leftPaddle.x + leftPaddle.width) && (b.y <= leftPaddle.y) && (b.y >= leftPaddle.y - leftPaddle.height); //Yes, a hit!
   bool didItHitRightPaddle = (b.x + b.width >= rightPaddle.x) && (b.y <= rightPaddle.y) && (b.y >= rightPaddle.y - rightPaddle.height); //Yes, a hit!

   if((didItHitLeftPaddle && b.speedX < 0) || (didItHitRightPaddle && b.speedX > 0))
   {
      b.speedX = -b.speedX;
   }
}

/*****************************************************************************/
void CheckIfBallHasHitTopOrBottomWallsAndNeedsToChangeVelocity(Ball& b)
/*****************************************************************************/
{
   //Check top and bottom edges
   if(b.y >= GooGoo::ScreenHeightInPixels() || (b.y - b.width) <= 0)
   {
      b.speedY = -b.speedY;
   }
}

/*****************************************************************************/
void CheckIfBallHasGonePastLeftOrRightWallsAndIncrementScoreIfNecessary(Ball b)
/*****************************************************************************/
{
   if (b.x <= 0) //Check left edge
   {
      rightPaddle.score = rightPaddle.score + 1;
      InitializePaddleAndBallPositions(false); //Reset ball and paddles
   }
   else if (b.x + b.width >= GooGoo::ScreenWidthInPixels()) //Check right edge
   {
      leftPaddle.score = leftPaddle.score + 1;
      InitializePaddleAndBallPositions(false); //Reset ball and paddles
   }
}

/*****************************************************************************/
void DrawPaddle(Paddle p)
/*****************************************************************************/
{
   GooGoo::SetColor(0, 255, 0);
   GooGoo::DrawRectangle(p.x, p.y, p.width, p.height, true);
}

/*****************************************************************************/
void DrawBall(Ball b)
/*****************************************************************************/
{
   GooGoo::SetColor(0, 255, 0, 255);
   GooGoo::DrawRectangle(b.x, b.y, b.width, b.width, true);
}

/*****************************************************************************/
void DrawDividerLine()
/*****************************************************************************/
{
   const int LINE_SPACING = 3;
   const int LINE_HEIGHT  = 8;
   int       screenWidth  = GooGoo::ScreenWidthInPixels();
   int       screenHeight = GooGoo::ScreenHeightInPixels();

   GooGoo::SetLineWidth(4);
   GooGoo::SetColor(0, 255, 0);

   for (int y = screenHeight; y > 0; y = y - (LINE_HEIGHT + LINE_SPACING))
   {
      GooGoo::DrawLine(screenWidth / 2, y, screenWidth / 2, y - LINE_HEIGHT);
   }
}

/*****************************************************************************/
void DrawScores()
/*****************************************************************************/
{
   //Convert the scores which are integers into strings.
   char leftScore[32];
   char rightScore[32];
   sprintf(leftScore, "%i", leftPaddle.score);
   sprintf(rightScore, "%i", rightPaddle.score);

   //Draw the scores to the left and right of the divider line
   GooGoo::SetColor(0, 255, 0);
   const int X_OFFSET = 60;
   const int Y_OFFSET = 40;
   int       screenWidth  = GooGoo::ScreenWidthInPixels();
   int       screenHeight = GooGoo::ScreenHeightInPixels();
   GooGoo::DrawString(screenWidth / 2 - X_OFFSET, screenHeight - Y_OFFSET, leftScore, 2);
   GooGoo::DrawString(screenWidth / 2 + X_OFFSET, screenHeight - Y_OFFSET, rightScore, 2);
}

/*****************************************************************************/
void InitializePaddleAndBallPositions(bool resetScores)
/*****************************************************************************/
{
   int screenWidth         = GooGoo::ScreenWidthInPixels();
   int screenHeight        = GooGoo::ScreenHeightInPixels();
   const int PADDLE_HEIGHT = 90;
   const int PADDLE_WIDTH  = 20;
   const int PADDLE_SPEED  = 9;
   const int BALL_WIDTH    = 15;

   //Initialize round start time
   numberOfTimerCalls = 0;

   //Initialize left paddle
   leftPaddle.x      = 0;
   leftPaddle.y      = (screenHeight / 2) + (PADDLE_HEIGHT / 2);
   leftPaddle.width  = PADDLE_WIDTH;
   leftPaddle.height = PADDLE_HEIGHT;
   leftPaddle.speed  = PADDLE_SPEED;

   //Initialize right paddle
   rightPaddle.x      = screenWidth - PADDLE_WIDTH;
   rightPaddle.y      = (screenHeight / 2) + (PADDLE_HEIGHT / 2);
   rightPaddle.width  = PADDLE_WIDTH;
   rightPaddle.height = PADDLE_HEIGHT;
   rightPaddle.speed  = PADDLE_SPEED;

   //Reset scores
   if(resetScores)
   {
      leftPaddle.score  = 0;
      rightPaddle.score = 0;
   }

   //Initialize ball
   theBall.x      = (screenWidth / 2) - (BALL_WIDTH / 2);
   theBall.y      = (screenHeight / 2) - (BALL_WIDTH / 2);
   theBall.width  = BALL_WIDTH;
   theBall.speedX = 1;
   theBall.speedY = 1;

   //Randomize direction of ball
   int directionX = GooGoo::GenerateRandomNumber(0,1);
   int directionY = GooGoo::GenerateRandomNumber(0,1);
   if(directionX == 0)
   {
      theBall.speedX = -theBall.speedX;
   }
   if(directionY == 0)
   {
      theBall.speedY = -theBall.speedY;
   }
}

/*****************************************************************************/
void MoveBall(Ball& b)
/*****************************************************************************/
{
   b.x = b.x + b.speedX;
   b.y = b.y + b.speedY;
}

/*****************************************************************************/
void MovePaddleDown(Paddle& p)
/*****************************************************************************/
{
   p.y = p.y - p.speed;
   RecalculatePaddlePositions();
}

/*****************************************************************************/
void MovePaddleUp(Paddle& p)
/*****************************************************************************/
{
   p.y = p.y + p.speed;
   RecalculatePaddlePositions();
}

/*****************************************************************************/
void OnDraw()
/*****************************************************************************/
{
   //The "draw" event is used to "repaint" the screens. Graphical applications
   //work like any other animation (e.g. South Park) by constantly redrwaing
   //the current frame. You do that fast enough, you get smooth animation.
   //This is where you want to draw your scene based on your model utilizing
   //the GooGoo drawing primitives (DrawLine, DrawPolygon, DrawCircle, etc).

   GooGoo::ClearScreen();
   GooGoo::SetLineWidth(1);
   DrawPaddle(leftPaddle);
   DrawPaddle(rightPaddle);
   DrawBall(theBall);
   DrawDividerLine();
   DrawScores();
}

/*****************************************************************************/
void OnKeyDown(unsigned char c, int x, int y)
/*****************************************************************************/
{
   //The "key down" event is triggered whenever you press the key. The
   //arguments to this function are the key that is pressed, the current
   //mouse x position, and current mouse y position
   if (c == 'f' || c == 'F')
   {
      GooGoo::ToggleFullScreenMode();
   }
   else if (c == 'q' || c == 'Q')
   {
      MovePaddleUp(leftPaddle);
   }
   else if (c == 'a' || c == 'A')
   {
      MovePaddleDown(leftPaddle);
   }
   else if (c == 'p' || c == 'P')
   {
      MovePaddleUp(rightPaddle);
   }
   else if (c == 'l' || c == 'L')
   {
      MovePaddleDown(rightPaddle);
   }
}

/*****************************************************************************/
void OnResize(int width, int height)
/*****************************************************************************/
{
   //The "resize" event occurs whenever you resize the window in which the
   //game is running. Well-designed games should resize and move game
   //objects.
   RecalculatePaddlePositions();
}

/*****************************************************************************/
void OnStartup()
/*****************************************************************************/
{
   //The "startup" event is where you get a chance to initalize your game
   //model (i.e the variables that constitute your game, in this case the
   //paddles and ball.
   InitializePaddleAndBallPositions(true);
}

/*****************************************************************************/
void OnTimer()
/*****************************************************************************/
{
   //The "timer" event is called every X milliseconds. Use this as a place
   //to drive the logic of the game as time elapses.

   numberOfTimerCalls = numberOfTimerCalls + 1; //We use this to track time elapsed

   MoveBall(theBall);
   CheckIfBallHasHitTopOrBottomWallsAndNeedsToChangeVelocity(theBall);
   CheckIfBallHasHitAPaddleAndNeedsToChangeVelocity(theBall);
   CheckIfBallHasGonePastLeftOrRightWallsAndIncrementScoreIfNecessary(theBall);
   SpeedUpBallIfNecessary(theBall);
   GooGoo::SetTimerDelayInMilliseconds(15); //Change this to make the timer change
}


/*****************************************************************************/
void RecalculatePaddlePositions()
/*****************************************************************************/
{
   //Adjust right paddle to be at correct x
   rightPaddle.x = GooGoo::ScreenWidthInPixels() - rightPaddle.width;

   //Make sure both paddles stay on screen...
   //Paddle 1
   if(leftPaddle.y - leftPaddle.height <= 0)
      leftPaddle.y = leftPaddle.height;

   if(leftPaddle.y >= GooGoo::ScreenHeightInPixels())
      leftPaddle.y = GooGoo::ScreenHeightInPixels();

   //Paddle 2
   if(rightPaddle.y - rightPaddle.height <= 0)
      rightPaddle.y = rightPaddle.height;

   if(rightPaddle.y >= GooGoo::ScreenHeightInPixels())
      rightPaddle.y = GooGoo::ScreenHeightInPixels();
}


/*****************************************************************************/
void SpeedUpBallIfNecessary(Ball& b)
/*****************************************************************************/
{
   const int NUMBER_OF_TIMER_CALLS_BEFORE_SPEEDUP = 1000;
   const int AMOUNT_TO_SPEED_UP_BY              = 1;

   if (numberOfTimerCalls % NUMBER_OF_TIMER_CALLS_BEFORE_SPEEDUP == 0)
   {

      //Save direction ball is moving in both up and down
      int xDirection, yDirection;
      if(b.speedX < 0)
      {
         xDirection = -1;
      }
      else
      {
         xDirection = 1;
      }

      if(b.speedY < 0)
      {
         yDirection = -1;
      }
      else
      {
         yDirection = 1;
      }

      b.speedX = b.speedX + (xDirection * AMOUNT_TO_SPEED_UP_BY);
      b.speedY = b.speedY + (yDirection * AMOUNT_TO_SPEED_UP_BY);

      numberOfTimerCalls = 0;
   }

}

