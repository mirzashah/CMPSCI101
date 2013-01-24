//Notes: This file contains modified version of code created by
//"softSurfer.com". See bottom of file for copyright notice.
#include "CollisionAvoidance.h"
#include "BeeberConfigurationManager.h"
#include "Geometry.h"
#include <map>
#include <cmath>
#include <iostream>
using std::pair;
using std::cout;
using std::endl;

namespace Beeber
{

namespace CollisionAvoidance
{


struct Vector;; //Forward declaration
struct Point
{
   Point(double xIn = 0, double yIn = 0, double zIn = 0)
   {
      x = xIn; y = yIn; z = zIn;
   }
   double x,y,z;
   Point operator+ (const Vector& v); //Point = Point + Vector
   Point operator- (const Vector& v); //Point = Point - Vector
   Vector operator- (const Point& p); //Vector = Point - Point
};

struct Vector
{
   Vector(double xIn = 0, double yIn = 0, double zIn = 0)
   {
      x = xIn; y = yIn; z = zIn;
   }
   double x,y,z;
   Vector operator+ (const Vector& v); //Vector = Vector + Vector
   Vector operator- (const Vector& v); //Vector = Vector - Vector
   Vector operator* (double v);        //Vector = Scalar * Vector
};

struct Line
{
   Line(Point P0In, Point P1In){P0 = P0In; P1 = P1In;}
   Point P0;
   Point P1;
};

struct Segment
{
   Segment(Point P0In, Point P1In){P0 = P0In; P1 = P1In;}
   Point P0;
   Point P1;
};

struct Track
{
   Track(Point P0In, Vector vIn){P0 = P0In; v = vIn;}
   Point P0;
   Vector v;
};

// dist3D_Line_to_Line():
//    Input:  two 3D lines L1 and L2
//    Return: the shortest distance between L1 and L2
double dist3D_Line_to_Line(Line L1, Line L2);

// dist3D_Segment_to_Segment():
//    Input:  two 3D line segments S1 and S2
//    Return: the shortest distance between S1 and S2
double dist3D_Segment_to_Segment(Segment S1, Segment S2);

// cpa_time(): compute the time of CPA for two tracks
//    Input:  two tracks Tr1 and Tr2
//    Return: the time at which the two tracks are closest
double cpa_time(Track Tr1, Track Tr2);

// cpa_distance(): compute the distance at CPA for two tracks
//    Input:  two tracks Tr1 and Tr2
//    Return: the distance for which the two tracks are closest
double cpa_distance(Track Tr1, Track Tr2);

/*****************************************************************************/
bool WillPathYieldCollision(const XYPoint& currentPosition, double pathHeadingInDegrees, double currentSpeedInMillimetersPerSecond, const ObstacleReportList& obstacles)
/*****************************************************************************/
{
   const double MIN_TIME_TO_CPA_IN_SECONDS = BeeberConfig().MinimumTimeTOCPAInSecondsBeforeChangingCourse();

   Point               origin(currentPosition.x, currentPosition.y);
   pair<double,double> vel = GetVelocityComponents(pathHeadingInDegrees, currentSpeedInMillimetersPerSecond);
   Track               self(origin, Vector(vel.first, vel.second, 0));

   unsigned int numObstacles = obstacles.size();
   for(unsigned int c = 0; c < numObstacles; c++)
   {
      ObstacleReport current     = obstacles.at(c);
      Point          obstaclePos(current.xInMillimeters, current.yInMillimeters);
      Track          obstacle(obstaclePos, Vector(0,0,0));
      double         timeToCPA   = cpa_time(self, obstacle);
      double         cpaDistance = cpa_distance(self, obstacle);

      if(cpaDistance <= current.radiusInMillimeters) //Ok, the obstacle is a threat...but time to CPA may be fine
         if(timeToCPA > 0 && timeToCPA <= MIN_TIME_TO_CPA_IN_SECONDS) //but if it ain't...
            return(true); //bad path
   }

   return(false);
}



/*****************************************************************************/
double GetClosestNonCollisionHeadingInDegrees(const XYPoint& currentPosition,
                                              double currentSpeedInMillimetersPerSecond,
                                              double desiredHeadingInDegrees,
                                              const ObstacleReportList& obstacles)
/*****************************************************************************/
{
   /*
   cout << "Trying to find closest not collision heading: " << endl;
   cout << "Current position: " << currentPosition.x << " " << currentPosition.y << endl;
   cout << "Desired Heading: " << desiredHeadingInDegrees << endl;
   cout << "Num obstacles " << obstacles.size() << endl;
   */
   //If there are no obstacles in the way, use the desired heading
   if(!(WillPathYieldCollision(currentPosition, desiredHeadingInDegrees, currentSpeedInMillimetersPerSecond, obstacles)))
      return(desiredHeadingInDegrees);

   for(int offsetInDegrees = 0; offsetInDegrees <= 180; offsetInDegrees = offsetInDegrees + 1)
   {
      double headingLeft = desiredHeadingInDegrees + offsetInDegrees;
      double headingRight = desiredHeadingInDegrees - offsetInDegrees;

      //cout << "Heading Left = " << headingLeft << " Heading Right = " << headingRight << endl;
      if(!WillPathYieldCollision(currentPosition, headingLeft, currentSpeedInMillimetersPerSecond, obstacles))
      {
         //cout << "Found left " << headingLeft << endl;
         return(NormalizeHeading(headingLeft));
      }
      if(!WillPathYieldCollision(currentPosition, headingRight, currentSpeedInMillimetersPerSecond, obstacles))
      {
         //cout << "Found right " << headingRight << endl;
         return(NormalizeHeading(headingRight));
      }
   }

   throw (NoObstacleFreePathsException());
}

/*****************************************************************************/
Point Point::operator+ (const Vector& v)
/*****************************************************************************/
{
   return(Point(x+v.x, y+v.y, z+v.z));
}

/*****************************************************************************/
Point Point::operator- (const Vector& v)
/*****************************************************************************/
{
   return(Point(x-v.x, y-v.y, z-v.z));
}

/*****************************************************************************/
Vector Point::operator- (const Point& p)
/*****************************************************************************/
{
   return(Vector(x - p.x, y-p.y, z-p.z));
}

/*****************************************************************************/
Vector Vector::operator+ (const Vector& v)
/*****************************************************************************/
{
   return(Vector(x+v.x, y+v.y, z+v.z));
}

/*****************************************************************************/
Vector Vector::operator- (const Vector& v)
/*****************************************************************************/
{
   return(Vector(x-v.x, y-v.y, z-v.z));
}

/*****************************************************************************/
Vector Vector::operator* (double v)
/*****************************************************************************/
{
   return(Vector(x*v,y*v,z*v));
}

#define SMALL_NUM  0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)
#define norm(v)    sqrt(dot(v,v))  // norm = length of vector
#define d(u,v)     norm(u-v)       // distance = norm of difference
#define abs(x)     ((x) >= 0 ? (x) : -(x))   // absolute value

// dist3D_Line_to_Line():
//    Input:  two 3D lines L1 and L2
//    Return: the shortest distance between L1 and L2
/*****************************************************************************/
double dist3D_Line_to_Line( Line L1, Line L2)
/*****************************************************************************/
{
    Vector   u = L1.P1 - L1.P0;
    Vector   v = L2.P1 - L2.P0;
    Vector   w = L1.P0 - L2.P0;
    double    a = dot(u,u);        // always >= 0
    double    b = dot(u,v);
    double    c = dot(v,v);        // always >= 0
    double    d = dot(u,w);
    double    e = dot(v,w);
    double    D = a*c - b*b;       // always >= 0
    double    sc, tc;

    // compute the line parameters of the two closest points
    if (D < SMALL_NUM) {         // the lines are almost parallel
        sc = 0.0;
        tc = (b>c ? d/b : e/c);   // use the largest denominator
    }
    else {
        sc = (b*e - c*d) / D;
        tc = (a*e - b*d) / D;
    }

    // get the difference of the two closest points (MAS - I reversed sc 8 u and tc * v)
    Vector   dP = w + (u * sc) - (v * tc);  // = L1(sc) - L2(tc)

    return norm(dP);   // return the closest distance
}
//===================================================================

// dist3D_Segment_to_Segment():
//    Input:  two 3D line segments S1 and S2
//    Return: the shortest distance between S1 and S2
/*****************************************************************************/
double dist3D_Segment_to_Segment( Segment S1, Segment S2)
/*****************************************************************************/
{
    Vector   u = S1.P1 - S1.P0;
    Vector   v = S2.P1 - S2.P0;
    Vector   w = S1.P0 - S2.P0;
    double    a = dot(u,u);        // always >= 0
    double    b = dot(u,v);
    double    c = dot(v,v);        // always >= 0
    double    d = dot(u,w);
    double    e = dot(v,w);
    double    D = a*c - b*b;       // always >= 0
    double    sc, sN, sD = D;      // sc = sN / sD, default sD = D >= 0
    double    tc, tN, tD = D;      // tc = tN / tD, default tD = D >= 0

    // compute the line parameters of the two closest points
    if (D < SMALL_NUM) { // the lines are almost parallel
        sN = 0.0;        // force using point P0 on segment S1
        sD = 1.0;        // to prevent possible division by 0.0 later
        tN = e;
        tD = c;
    }
    else {                // get the closest points on the infinite lines
        sN = (b*e - c*d);
        tN = (a*e - b*d);
        if (sN < 0.0) {       // sc < 0 => the s=0 edge is visible
            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if (sN > sD) {  // sc > 1 => the s=1 edge is visible
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }

    if (tN < 0.0) {           // tc < 0 => the t=0 edge is visible
        tN = 0.0;
        // recompute sc for this edge
        if (-d < 0.0)
            sN = 0.0;
        else if (-d > a)
            sN = sD;
        else {
            sN = -d;
            sD = a;
        }
    }
    else if (tN > tD) {      // tc > 1 => the t=1 edge is visible
        tN = tD;
        // recompute sc for this edge
        if ((-d + b) < 0.0)
            sN = 0;
        else if ((-d + b) > a)
            sN = sD;
        else {
            sN = (-d + b);
            sD = a;
        }
    }
    // finally do the division to get sc and tc
    sc = (abs(sN) < SMALL_NUM ? 0.0 : sN / sD);
    tc = (abs(tN) < SMALL_NUM ? 0.0 : tN / tD);

    // get the difference of the two closest points - (MAS - reversing sc * u and tc * v
    Vector   dP = w + (u * sc) - (v * tc);  // = S1(sc) - S2(tc)

    return norm(dP);   // return the closest distance
}
//===================================================================

// cpa_time(): compute the time of CPA for two tracks
//    Input:  two tracks Tr1 and Tr2
//    Return: the time at which the two tracks are closest
/*****************************************************************************/
double cpa_time( Track Tr1, Track Tr2 )
/*****************************************************************************/
{
    Vector   dv = Tr1.v - Tr2.v;

    double    dv2 = dot(dv,dv);
    if (dv2 < SMALL_NUM)      // the tracks are almost parallel
        return 0.0;            // any time is ok.  Use time 0.

    Vector   w0 = Tr1.P0 - Tr2.P0;
    double    cpatime = -dot(w0,dv) / dv2;

    return cpatime;            // time of CPA
}
//===================================================================

// cpa_distance(): compute the distance at CPA for two tracks
//    Input:  two tracks Tr1 and Tr2
//    Return: the distance for which the two tracks are closest
/*****************************************************************************/
double cpa_distance( Track Tr1, Track Tr2 )
/*****************************************************************************/
{
    double   ctime = cpa_time( Tr1, Tr2);
    Point    P1 = Tr1.P0 + (Tr1.v * ctime); //MAS - Reversing scalar/vector multiplations
    Point    P2 = Tr2.P0 + (Tr2.v * ctime); //MAS - Reversing scalar/vector multiplations

    return d(P1,P2);           // distance at CPA
}

}
}

//NOTE: This file contains code from softsurfer.com, see copyright notice below:
// Copyright 2001, softSurfer (www.softsurfer.com)
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.

// Assume that classes are already given for the objects:
//    Point and Vector with
//        coordinates {float x, y, z;}
//        operators for:
//            Point  = Point ± Vector
//            Vector = Point - Point
//            Vector = Vector ± Vector
//            Vector = Scalar * Vector
//    Line and Segment with defining points {Point P0, P1;}
//    Track with initial position and velocity vector
//            {Point P0; Vector v;}
//===================================================================
