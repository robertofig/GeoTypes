#ifndef GEOTYPES_BASE_H
//=========================================================================
// geotypes-base.h
//
// Module with basic geometric objects and functions to manipulate them.
// All calculations done here are only as precise as the limited mantissa
// in 64-bits floating points allow for.
//=========================================================================
#define GEOTYPES_BASE_H

#include "tinybase-types.h"

#define PI  3.141592653589793
#define TAU 6.283185307179586

//==================================
// 2D Vector
//==================================

struct v2
{
    f64 X, Y;
};

inline v2 V2(f64 X, f64 Y) { v2 Result = { X, Y }; return Result; }

inline v2   operator+(v2 A, v2 B) { return V2(A.X+B.X, A.Y+B.Y); }
inline v2&  operator+=(v2& A, v2 B) { A = A + B; return A; }
inline v2   operator-(v2 A, v2 B) { return V2(A.X-B.X, A.Y-B.Y); }
inline v2&  operator-=(v2& A, v2 B) { A = A - B; return A; }
inline v2   operator*(v2 A, f64 Scalar) { return V2(A.X*Scalar, A.Y*Scalar); }
inline v2   operator*(f64 Scalar, v2 A) { return A * Scalar; }
inline v2&  operator*=(v2& A, f64 Scalar) { A = A * Scalar; return A; }
inline v2   operator/(v2 A, f64 Scalar) { return V2(A.X/Scalar, A.Y/Scalar); }
inline v2   operator/(f64 Scalar, v2 A) { return A / Scalar; }
inline v2&  operator/=(v2& A, f64 Scalar) { A = A / Scalar; return A; }
inline bool operator==(v2 A, v2 B) { return A.X == B.X && A.Y == B.Y; }

f64 Dist(v2 A, v2 B);  // Euclidean distance.
f64 Dist2(v2 A, v2 B); // Euclidean distance squared (no sqrt).
f64 Dot(v2 A, v2 B);   // Dot product.
f64 Cross(v2 A, v2 B); // Cross product of [A] over [B].
f64 Mag(v2 A);         // Magnitude.
f64 Mag2(v2 A);        // Magnitude squared (no sqrt).
v2  Rotate90CW(v2 A);  // Rotates 90 degrees Clockwise.
v2  Rotate90CCW(v2 A); // Rotates 90 degrees Counter-Clockwise.
v2  Unit(v2 A);        // Unit vector.

#define INVALID_V2 V2(INF, INF)

//==================================
// 3D Vector
//==================================

union v3
{
    struct 
    {
        f64 X, Y;
        union { f64 Z, M; };
    };
    struct
    {
        v2 XY;
        union { f64 Z, M; };
    };
};

inline v3 V3(f64 X, f64 Y, f64 Z) { v3 Result = { X, Y, Z }; return Result; }
inline v3 V3(v2 XY, f64 Z) { return V3(XY.X, XY.Y, Z); }

inline v3   operator+(v3 A, v3 B) { return V3(A.X+B.X, A.Y+B.Y, A.Z+B.Z); }
inline v3&  operator+=(v3& A, v3 B) { A = A + B; return A; }
inline v3   operator-(v3 A, v3 B) { return V3(A.X-B.X, A.Y-B.Y, A.Z-B.Z); }
inline v3&  operator-=(v3& A, v3 B) { A = A - B; return A; }
inline v3   operator*(v3 A, f64 Scalar) { return V3(A.X*Scalar, A.Y*Scalar, A.Z*Scalar); }
inline v3   operator*(f64 Scalar, v3 A) { return A * Scalar; }
inline v3&  operator*=(v3& A, f64 Scalar) { A = A * Scalar; return A; }
inline v3   operator/(v3 A, f64 Scalar) { return V3(A.X/Scalar, A.Y/Scalar, A.Z/Scalar); }
inline v3   operator/(f64 Scalar, v3 A) { return A / Scalar; }
inline v3&  operator/=(v3& A, f64 Scalar) { A = A / Scalar; return A; }
inline bool operator==(v3 A, v3 B) { return A.X == B.X && A.Y == B.Y && A.Z == B.Z; }

f64 Dist(v3 A, v3 B);       // 3D euclidean distance.
f64 Dist2(v3 A, v3 B);      // 3D euclidean distance squared (no sqrt).
f64 Dot(v3 A, v3 B);        // Dot product.
f64 Mag(v3 A);              // Magnitude.
f64 Mag2(v3 A);             // Magnitude squared (no sqrt).
v3  Rotate90XAxisCW(v3 A);  // Rotates 90 degrees around X-axis Clockwise.
v3  Rotate90XAxisCCW(v3 A); // Rotates 90 degrees around X-axis Counter-Clockwise.
v3  Rotate90YAxisCW(v3 A);  // Rotates 90 degrees around Y-axis Clockwise.
v3  Rotate90YAxisCCW(v3 A); // Rotates 90 degrees around Y-axis Counter-Clockwise.
v3  Rotate90ZAxisCW(v3 A);  // Rotates 90 degrees around Z-axis Clockwise.
v3  Rotate90ZAxisCCW(v3 A); // Rotates 90 degrees around Z-axis Counter-Clockwise.
v3  Unit(v3 A);             // Unit vector.

#define INVALID_V3 V3(INF, INF, INF)

//==================================
// 4D Vector
//==================================

union v4
{
    struct
    {
        f64 X, Y, Z, M;
    };
    struct
    {
        v3 XYZ;
        f64 M;
    };
    struct
    {
        v2 XY;
        f64 Z, M;
    };
};

inline v4 V4(f64 X, f64 Y, f64 Z, f64 M) { v4 Result = { X, Y, Z, M }; return Result; }
inline v4 V4(v2 XY, f64 Z, f64 M) { return V4(XY.X, XY.Y, Z, M); }
inline v4 V4(v3 XYZ, f64 M) { return V4(XYZ.X, XYZ.Y, XYZ.Z, M); }

#define INVALID_V4 V4(INF, INF, INF, INF)

//==================================
// Circle
//==================================

struct circle
{
    v2 Centre;
    f64 Radius;
};

inline circle Circle(f64 X, f64 Y, f64 Radius) { circle Result = { V2(X, Y), Radius }; return Result; }
inline circle Circle(v2 Centre, f64 Radius) { circle Result = { Centre, Radius }; return Result; }
circle Circle(v2 A, v2 B, f64 Radius); // [A] and [B] are points on the circle.

f64  Area(circle A);                       // Area of circle.
f64  Length(circle C);                     // Length of circle's perimetre.
f64  ArcLength(f64 Angle, circle C);       // Length of arc formed by [Angle].
f64  ArcLength(v2 A, v2 B, circle C);      // Length of arc between points [A] and [B] (on the circle).
f64  GetAngleOfPoint(v2 A, circle C);      // Angle in radians between point [A] and the right-most point of [C].
v2   GetPointOfAngle(f64 Angle, circle C); // Point on circle from right-most point of [C], angle in radians.
bool PointInCircle(v2 P, circle C);        // Checks if [P] lies inside or on the circle.

//==================================
// BBox 2D
//==================================

struct bbox2
{
    v2 Min, Max;
};

inline bbox2 BBox2(v2 Min, v2 Max) { bbox2 Result = { Min, Max }; return Result; }
inline bbox2 BBox2(f64 XMin, f64 YMin, f64 XMax, f64 YMax) { return BBox2(V2(XMin, YMin), V2(XMax, YMax)); }
inline bbox2 BBox2(v2 Min, f64 Width, f64 Height) { return BBox2(Min, Min + V2(Width, Height)); }

f64   Area(bbox2 A);                 // Area of bbox2.
bbox2 Merge(bbox2 A, bbox2 B);       // Creates new bbox2 from the mins and maxs of two bbox2.
bool  Intersects(bbox2 A, bbox2 B);  // Check if two bbox2 overlap.
bool  Intersects(v2 P, bbox2 B);     // Check if point is inside or on bbox2.
bool  Intersects(bbox2 B, v2 P);     // Same as above.
bool  Intersects(circle C, bbox2 B); // Check if circle and bbox2 overlap.
bool  Intersects(bbox2 B, circle C); // Same as above.

//==================================
// Line 2D
//==================================

struct line2
{
    v2 P0, P1;
};

inline line2 Line2(v2 P0, v2 P1) { line2 Result = { P0, P1 }; return Result; }
inline line2 Line2(f64 X0, f64 Y0, f64 X1, f64 Y1) { return Line2(V2(X0, Y0), V2(X1, Y1)); }

f64 Dist(v2 P, line2 L); // Distance of [P] to closest point in [L].
f64 Dist(line2 L, v2 P); // Same as above.

f64 LocationAlongLine(line2 L, v2 Target);

/* Percentage between 0 and 1 where [Target] lies along [L]. If [Target] does not lie over [L],
 |  it is projected over it (closest point). Return value is not clamped, so < 0 means [Target]
 |  is before [L], and > 1 means it's after. */

v2 PointAlongLine(line2 L, f64 LineLocation);

/* Given a [LineLocation] percentage between 0 and 1 along [L], returns the point on it.
|  Percentagens outside the [0,1] interval are clamped to it. */

bool IsPointLeftOfLine(v2 P, line2 L);

/* Returns true if [P] is to the left of [L], and false if not. Also returns false if point
|  is on the line. */

//==================================
// Line 3D
//==================================

struct line3
{
    v3 P0, P1;
};

inline line3 Line3(v3 P0, v3 P1) { line3 Result = { P0, P1 }; return Result; }
inline line3 Line3(f64 X0, f64 Y0, f64 Z0, f64 X1, f64 Y1, f64 Z1) { return Line3(V3(X0, Y0, Z0), V3(X1, Y1, Z1)); }

f64 Dist(v3 P, line3 L); // 3D distance of [P] to closest point in [L].
f64 Dist(line3 L, v3 P); // Same as above.

f64 LocationAlongLine(line3 L, v3 Target);

/* Percentage between 0 and 1 where [Target] lies along [L]. If [Target] does not lie over [L],
 |  it is projected over it (closest point). Return value is not clamped, so < 0 means [Target]
 |  is before [L], and > 1 means it's after. */

v3 PointAlongLine(line3 L, f64 LineLocation);

/* Given a [LineLocation] percentage between 0 and 1 along [L], returns the point on it.
|  Percentagens outside the [0,1] interval are clamped to it. */


#if !defined(GEOTYPES_STATIC_LINKING)
#include "geotypes-base.cpp"
#endif

#endif //GEOTYPES_BASE_H
