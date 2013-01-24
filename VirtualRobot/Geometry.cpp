#include "Geometry.h"
#include <cmath>
#include <map>
#include <cassert>
using std::pair;

namespace Beeber
{

/*****************************************************************************/
double AngularDistanceInDegrees(double angleInDegrees1, double angleInDegrees2)
/*****************************************************************************/
{
   double bearingIfWeGoLeft  = DeltaDegreesTurningLeft(angleInDegrees1, angleInDegrees2);
   double bearingIfWeGoRight = DeltaDegreesTurningRight(angleInDegrees1, angleInDegrees2);
   assert(bearingIfWeGoLeft >= 0 && bearingIfWeGoRight >= 0); //Want to make sure calls ain't givin screwy angles naw
   return(Min(bearingIfWeGoLeft, bearingIfWeGoRight));
}

/*****************************************************************************/
double Distance(const XYPoint& point1, const XYPoint& point2)
/*****************************************************************************/
{
   return(sqrt(pow(point1.x-point2.x, 2) + pow(point1.y-point2.y,2)));
}

/*****************************************************************************/
const double GetPI()
/*****************************************************************************/
{
   return(3.14159265);
}

/*****************************************************************************/
double Deg2Rad(double deg)
/*****************************************************************************/
{
   return(deg * GetPI()/180.0f);
}

/*****************************************************************************/
double Rad2Deg(double rad)
/*****************************************************************************/
{
   return(rad * 180.0f/GetPI());
}

/*****************************************************************************/
double GetHeadingToPoint(const XYPoint& p1, const XYPoint& p2)
/*****************************************************************************/
{
   double x0 = p1.x;
   double y0 = p1.y;
   double x  = p2.x;
   double y  = p2.y;

   double dx = x - x0;
   double dy = y - y0;

   double toReturn = Rad2Deg(atan2(dy, dx)); //Calculate heading and return

   return(NormalizeHeading(toReturn));
}

//Calculates the angular distance if we turn left from some heading to some desired heading.
//Left is counterclockwise
/*****************************************************************************/
double DeltaDegreesTurningLeft(double fromHeadingInDegrees, double toHeadingInDegrees)
/*****************************************************************************/
{
   assert(fromHeadingInDegrees >= 0);
   assert(toHeadingInDegrees >= 0);

   if (toHeadingInDegrees < fromHeadingInDegrees)
      toHeadingInDegrees = toHeadingInDegrees + 360.0;

   double toReturn = toHeadingInDegrees - fromHeadingInDegrees;

   toReturn = NormalizeHeading(toReturn);

   assert(toReturn >= 0);
   return(toReturn);
}

//Calculates the angular distance if we turn right from some heading to some desired heading
//Right is clockwise
/*****************************************************************************/
double DeltaDegreesTurningRight(double fromHeadingInDegrees, double toHeadingInDegrees)
/*****************************************************************************/
{
   assert(fromHeadingInDegrees >= 0);
   assert(toHeadingInDegrees >= 0);

   if (toHeadingInDegrees > fromHeadingInDegrees)
      fromHeadingInDegrees = fromHeadingInDegrees + 360.0f;

   double toReturn = fromHeadingInDegrees - toHeadingInDegrees;

   toReturn = NormalizeHeading(toReturn);

   assert(toReturn > 0);
   return(toReturn);
}

//Gets the bearing (deg [positive is clockwise]), elevation (deg), and distance (meters) to a point,
//NOTE: THIS IS RELATIVE BEARING (relative to hdg0)!!!

/*****************************************************************************/
double GetBearingToPoint(const XYPoint& pOrigin, double currentHeading, const XYPoint& pTarget)
/*****************************************************************************/
{
   double tgtHeading = GetHeadingToPoint(pOrigin, pTarget);

   //Calculate bearing
   double bearingIfWeGoLeft  = DeltaDegreesTurningLeft(currentHeading, tgtHeading);
   double bearingIfWeGoRight = DeltaDegreesTurningRight(currentHeading, tgtHeading);
   if(bearingIfWeGoLeft < bearingIfWeGoRight)
       return(bearingIfWeGoLeft);
   else
       return(bearingIfWeGoRight);
}

//Extracts the velocity vectorbased on a heading, pitch, and speed
/*****************************************************************************/
pair<double, double> GetVelocityComponents(double headingInDegrees, double speedInUnitLengthPerSec)
/*****************************************************************************/
{
   double hdgRad = Deg2Rad(headingInDegrees);
   double spd    = speedInUnitLengthPerSec;
   double xVel = spd*cos(hdgRad);
   double yVel = spd*sin(hdgRad);
   return(pair<double,double>(xVel,yVel));
}

//Tells us if some heading falls within a range going clockwise from
//some start angle to some end angle.
/*****************************************************************************/
bool IsHeadingWithinBounds(double headingInDegrees, double startAngleAsDegrees, double endAngleAsDegrees)
/*****************************************************************************/
{
   double hdg                  = headingInDegrees;
   double angStart             = startAngleAsDegrees;
   double angEnd               = endAngleAsDegrees;

   double angDisOfRange        = DeltaDegreesTurningLeft(angStart, angEnd);
   double angDisFromStartToHdg = DeltaDegreesTurningRight(angStart, hdg);
   double angDisFromEndToHdg   = DeltaDegreesTurningLeft(angEnd, hdg);

   return((angDisFromStartToHdg <= angDisOfRange) && (angDisFromEndToHdg <= angDisOfRange));
}

/*****************************************************************************/
double NormalizeHeading(double headingInDegrees)
/*****************************************************************************/
{
   while(headingInDegrees < 0)
      headingInDegrees = headingInDegrees + 360.0f;
   while(headingInDegrees >= 360.0f)
      headingInDegrees = headingInDegrees - 360.0f;
   return(headingInDegrees);
}


}
