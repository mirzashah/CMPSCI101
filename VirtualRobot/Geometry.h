// Geometry
//*****************************************************************************
// Data types and functions for geometrical calculations
//*****************************************************************************

#ifndef GEOMETRY_H_DEFINED
#define GEOMETRY_H_DEFINED

#include <vector>
#include <map>
using std::pair;
using std::vector;

namespace Beeber
{

struct XYPoint
{
   XYPoint(double xIn = 0, double yIn = 0){x = xIn; y = yIn;}
   double x;
   double y;
};

typedef vector<XYPoint> XYPointList;

struct XYExtents
{
   XYExtents(double leftIn, double rightIn, double topIn, double bottomIn)
   {
      left = leftIn;
      right = rightIn;
      top = topIn;
      bottom = bottomIn;
   }
   double left;
   double right;
   double top;
   double bottom;
};

template <typename T> T Min(const T& v1, const T& v2)
{
   if(v1 <= v2) return v1;
   else         return v2;
}

template <typename T> T Max(const T& v1, const T& v2)
{
   if(v1 >= v2) return v1;
   else         return v2;
}

double               NormalizeHeading(double headingInDegrees);

const double         GetPI();
double               Deg2Rad(double degrees);
double               Rad2Deg(double radians);
double               Distance(const XYPoint& point1, const XYPoint& point2);
double               AngularDistanceInDegrees(double angleInDegrees1, double angleInDegrees2);
double               DeltaDegreesTurningLeft(double fromHeadingInDegrees, double toHeadingInDegrees);
double               DeltaDegreesTurningRight(double fromHeadingInDegrees, double toHeadingInDegrees);
double               GetBearingToPoint(const XYPoint& pOrigin, double currentHeading, const XYPoint& pTarget);
double               GetHeadingToPoint(const XYPoint& p1, const XYPoint& p2);
pair<double, double> GetVelocityComponents(double headingInDegrees, double speedInUnitLengthPerSec);
bool                 IsHeadingWithinBounds(double headingInDegrees, double startAngleAsDegrees, double endAngleAsDegrees);


//TODO: Other geometry calls here, CPA, time to CPA, etc
}
#endif
