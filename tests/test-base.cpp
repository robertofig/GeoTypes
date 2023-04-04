#include "geotypes-base.h"
#include <float.h>

#include <stdio.h>
#include <varargs.h>

bool Error = false;
#define Test(Callback, ...) \
do { \
if (!Test##Callback(__VA_ARGS__)) { \
Error = true; \
printf(" [%3d] %-40s ERROR.\n", __LINE__, #Callback##"()"); } \
} while (0); \

global f64 Tolerance = DBL_EPSILON * 2;

bool Within(f64 Value, f64 Expected)
{
    f64 A = Abs(Value - Expected);
    f64 B = Max(Tolerance * Max(Abs(Value), Abs(Expected)), Tolerance);
    return A <= B;
}

bool Within(v2 Value, v2 Expected)
{
    f64 AX = Abs(Value.X - Expected.X);
    f64 AY = Abs(Value.Y - Expected.Y);
    f64 BX = Max(Tolerance * Max(Abs(Value.X), Abs(Expected.X)), Tolerance);
    f64 BY = Max(Tolerance * Max(Abs(Value.Y), Abs(Expected.Y)), Tolerance);
    return AX <= BX && AY <= BY;
}

bool Within(v3 Value, v3 Expected)
{
    f64 AX = Abs(Value.X - Expected.X);
    f64 AY = Abs(Value.Y - Expected.Y);
    f64 AZ = Abs(Value.Z - Expected.Z);
    f64 BX = Max(Tolerance * Max(Abs(Value.X), Abs(Expected.X)), Tolerance);
    f64 BY = Max(Tolerance * Max(Abs(Value.Y), Abs(Expected.Y)), Tolerance);
    f64 BZ = Max(Tolerance * Max(Abs(Value.Z), Abs(Expected.Z)), Tolerance);
    return AX <= BX && AY <= BY && AZ <= BZ;
}

//
// V2 tests.
//

bool TestV2_Dist(v2 A, v2 B, f64 Expected)
{
    return Within(Dist(A, B), Expected);
}

bool TestV2_Dist2(v2 A, v2 B, f64 Expected)
{
    return Within(Dist2(A, B), Expected);
}

bool TestV2_Dot(v2 A, v2 B, f64 Expected)
{
    return Within(Dot(A, B), Expected);
}

bool TestV2_Mag(v2 A, f64 Expected)
{
    return Within(Mag(A), Expected);
}

bool TestV2_Mag2(v2 A, f64 Expected)
{
    return Within(Mag2(A), Expected);
}

bool TestV2_Rotate90CW(v2 A, v2 Expected)
{
    return Rotate90CW(A) == Expected;
}

bool TestV2_Rotate90CCW(v2 A, v2 Expected)
{
    return Rotate90CCW(A) == Expected;
}

bool TestV2_Unit(v2 A, v2 Expected)
{
    return Within(Unit(A), Expected);
}

//
// V3 tests.
//

bool TestV3_Dist(v3 A, v3 B, f64 Expected)
{
    return Within(Dist(A, B), Expected);
}

bool TestV3_Dist2(v3 A, v3 B, f64 Expected)
{
    return Within(Dist2(A, B), Expected);
}

bool TestV3_Dot(v3 A, v3 B, f64 Expected)
{
    return Within(Dot(A, B), Expected);
}

bool TestV3_Mag(v3 A, f64 Expected)
{
    return Within(Mag(A), Expected);
}

bool TestV3_Mag2(v3 A, f64 Expected)
{
    return Within(Mag2(A), Expected);
}

bool TestV3_Rotate90XAxisCW(v3 A, v3 Expected)
{
    return Rotate90XAxisCW(A) == Expected;
}

bool TestV3_Rotate90XAxisCCW(v3 A, v3 Expected)
{
    return Rotate90XAxisCCW(A) == Expected;
}

bool TestV3_Rotate90YAxisCW(v3 A, v3 Expected)
{
    return Rotate90YAxisCW(A) == Expected;
}

bool TestV3_Rotate90YAxisCCW(v3 A, v3 Expected)
{
    return Rotate90YAxisCCW(A) == Expected;
}

bool TestV3_Rotate90ZAxisCW(v3 A, v3 Expected)
{
    return Rotate90ZAxisCW(A) == Expected;
}

bool TestV3_Rotate90ZAxisCCW(v3 A, v3 Expected)
{
    return Rotate90ZAxisCCW(A) == Expected;
}

bool TestV3_Unit(v3 A, v3 Expected)
{
    return Within(Unit(A), Expected);
}

//
// Circle
//

bool TestCircle_Circle(v2 A, v2 B, f64 Radius, circle Expected)
{
    circle Result = Circle(A, B, Radius);
    return Within(Result.Centre, Expected.Centre);
}

bool TestCircle_Area(circle C, f64 Expected)
{
    return Within(Area(C), Expected);
}

bool TestCircle_Length(circle C, f64 Expected)
{
    return Within(Length(C), Expected);
}

bool TestCircle_ArcLengthAngle(f64 Angle, circle C, f64 Expected)
{
    return Within(ArcLength(Angle, C), Expected);
}

bool TestCircle_ArcLengthPoints(v2 A, v2 B, circle C, f64 Expected)
{
    return Within(ArcLength(A, B, C), Expected);
}

bool TestCircle_GetAngleOfPoint(v2 P, circle C, f64 Expected)
{
    return Within(GetAngleOfPoint(P, C), Expected);
}

bool TestCircle_GetPointOfAngle(f64 Angle, circle C, v2 Expected)
{
    return Within(GetPointOfAngle(Angle, C), Expected);
}

bool TestCircle_PointInCircle(v2 P, circle C, bool Expected)
{
    return Within(PointInCircle(P, C), Expected);
}

//
// BBox2
//

bool TestBBox2_IntersectBBox2(bbox2 A, bbox2 B, bool Expected)
{
    return Intersects(A, B) == Expected;
}

bool TestBBox2_IntersectV2(bbox2 A, v2 B, bool Expected)
{
    return Intersects(A, B) == Expected;
}

bool TestBBox2_IntersectCircle(bbox2 A, circle B, bool Expected)
{
    return Within(Intersects(A, B), Expected);
}

//
// Line2
//

bool TestLine2_LocationAlongLine(line2 L, v2 P, f64 Expected)
{
    return Within(LocationAlongLine(L, P), Expected);
}

bool TestLine2_PointAlongLine(line2 L, f64 M, v2 Expected)
{
    return Within(PointAlongLine(L, M), Expected);
}

bool TestLine2_DistV2(line2 L, v2 P, f64 Expected)
{
    return Within(Dist(L, P), Expected);
}

//
// Line3
//

bool TestLine3_LocationAlongLine(line3 L, v3 P, f64 Expected)
{
    return Within(LocationAlongLine(L, P), Expected);
}

bool TestLine3_PointAlongLine(line3 L, f64 M, v3 Expected)
{
    return Within(PointAlongLine(L, M), Expected);
}

bool TestLine3_DistV3(line3 L, v3 P, f64 Expected)
{
    return Within(Dist(L, P), Expected);
}


//
// Main program
//

int main()
{
    Test(V2_Dist, V2(-12, 5), V2(0, -7), 16.97056274847714);
    Test(V2_Dist2, V2(-12, 5), V2(0, -7), 288);
    Test(V2_Dot, V2(-12, 5), V2(0, -7), -35);
    Test(V2_Mag, V2(-12, 5), 13);
    Test(V2_Mag2, V2(-12, 5), 169);
    Test(V2_Rotate90CW, V2(-12, 5), V2(5, 12));
    Test(V2_Rotate90CW, V2(5, 12), V2(12, -5));
    Test(V2_Rotate90CW, V2(12, -5), V2(-5, -12));
    Test(V2_Rotate90CW, V2(-5, -12), V2(-12, 5));
    Test(V2_Rotate90CCW, V2(-12, 5), V2(-5, -12));
    Test(V2_Rotate90CCW, V2(-5, -12), V2(12, -5));
    Test(V2_Rotate90CCW, V2(12, -5), V2(5, 12));
    Test(V2_Rotate90CCW, V2(5, 12), V2(-12, 5));
    Test(V2_Unit, V2(-12, 5), V2(-0.9230769230769231, 0.38461538461538464));
    
    Test(V3_Dist, V3(-12, 5, 31), V3(0, -7, 14), 24.020824298928627);
    Test(V3_Dist2, V3(-12, 5, 31), V3(0, -7, 14), 577);
    Test(V3_Dot, V3(-12, 5, 31), V3(0, -7, 14), 399);
    Test(V3_Mag, V3(-12, 5, 31), 33.61547262794322);
    Test(V3_Mag2, V3(-12, 5, 31), 1130);
    Test(V3_Rotate90XAxisCW, V3(-12, 5, 31), V3(-12, 31, -5));
    Test(V3_Rotate90XAxisCW, V3(-12, 31, -5), V3(-12, -5, -31));
    Test(V3_Rotate90XAxisCW, V3(-12, -5, -31), V3(-12, -31, 5));
    Test(V3_Rotate90XAxisCW, V3(-12, -31, 5), V3(-12, 5, 31));
    Test(V3_Rotate90XAxisCCW, V3(-12, 5, 31), V3(-12, -31, 5));
    Test(V3_Rotate90XAxisCCW, V3(-12, -31, 5), V3(-12, -5, -31));
    Test(V3_Rotate90XAxisCCW, V3(-12, -5, -31), V3(-12, 31, -5));
    Test(V3_Rotate90XAxisCCW, V3(-12, 31, -5), V3(-12, 5, 31));
    Test(V3_Rotate90YAxisCW, V3(-12, 5, 31), V3(-31, 5, -12));
    Test(V3_Rotate90YAxisCW, V3(-31, 5, -12), V3(12, 5, -31));
    Test(V3_Rotate90YAxisCW, V3(12, 5, -31), V3(31, 5, 12));
    Test(V3_Rotate90YAxisCW, V3(31, 5, 12), V3(-12, 5, 31));
    Test(V3_Rotate90YAxisCCW, V3(-12, 5, 31), V3(31, 5, 12));
    Test(V3_Rotate90YAxisCCW, V3(31, 5, 12), V3(12, 5, -31));
    Test(V3_Rotate90YAxisCCW, V3(12, 5, -31), V3(-31, 5, -12));
    Test(V3_Rotate90YAxisCCW, V3(-31, 5, -12), V3(-12, 5, 31));
    Test(V3_Rotate90ZAxisCW, V3(-12, 5, 31), V3(5, 12, 31));
    Test(V3_Rotate90ZAxisCW, V3(5, 12, 31), V3(12, -5, 31));
    Test(V3_Rotate90ZAxisCW, V3(12, -5, 31), V3(-5, -12, 31));
    Test(V3_Rotate90ZAxisCW, V3(-5, -12, 31), V3(-12, 5, 31));
    Test(V3_Rotate90ZAxisCCW, V3(-12, 5, 31), V3(-5, -12, 31));
    Test(V3_Rotate90ZAxisCCW, V3(-5, -12, 31), V3(12, -5, 31));
    Test(V3_Rotate90ZAxisCCW, V3(12, -5, 31), V3(5, 12, 31));
    Test(V3_Rotate90ZAxisCCW, V3(5, 12, 31), V3(-12, 5, 31));
    Test(V3_Unit, V3(-12, 5, 31), V3(-0.3569784703852378, 0.14874102932718242, 0.922194381828531));
    
    Test(Circle_Circle, V2(-0.17452406437283513, 9.998476951563912), V2(7.0710678118654755, 7.0710678118654755), 10, Circle(0, 0, 10));
    Test(Circle_Area, Circle(0, 0, 10), 314.1592653589793);
    Test(Circle_Length, Circle(0, 0, 10), 62.83185307179586);
    Test(Circle_ArcLengthAngle, 0.7853981633974483, Circle(0, 0, 10), 7.853981633974483);
    Test(Circle_ArcLengthPoints, V2(10, 0), V2(7.0710678118654755, 7.0710678118654755), Circle(0, 0, 10), 7.853981633974483);
    Test(Circle_GetAngleOfPoint, V2(7.0710678118654755, 7.0710678118654755), Circle(0, 0, 10), 0.7853981633974483);
    Test(Circle_GetPointOfAngle, 0.7853981633974483, Circle(0, 0, 10), V2(7.0710678118654755, 7.0710678118654755));
    Test(Circle_PointInCircle, V2(-0.17452406437283513, 9.998476951563912), Circle(0, 0, 10), true);
    Test(Circle_PointInCircle, V2(-0.17452406437283513, 9.998476951563914), Circle(0, 0, 10), false);
    Test(Circle_PointInCircle, V2(1.7453292519943295e-8, 0.9999999999999999), Circle(0, 0, 1), true);
    Test(Circle_PointInCircle, V2(1.7453292519943295e-8, 1.0000000000000002), Circle(0, 0, 1), false);
    
    Test(BBox2_IntersectBBox2, BBox2(0, 0, 2, 2), BBox2(2, 2, 3, 3), true);
    Test(BBox2_IntersectBBox2, BBox2(0, 0, 2, 2), BBox2(2, 2.0000000000000004, 3, 3), false);
    Test(BBox2_IntersectBBox2, BBox2(0, 0, 2, 2), BBox2(-1, -1, 0, 0), true);
    Test(BBox2_IntersectBBox2, BBox2(0, 0, 2, 2), BBox2(-1, -1, 0, -2.2250738585072014e-308), false);
    Test(BBox2_IntersectV2, BBox2(0, 0, 2, 2), V2(2, 2), true);
    Test(BBox2_IntersectV2, BBox2(0, 0, 2, 2), V2(2, 2.0000000000000004), false);
    Test(BBox2_IntersectV2, BBox2(0, 0, 2, 2), V2(0, 0), true);
    Test(BBox2_IntersectV2, BBox2(0, 0, 2, 2), V2(0, -2.2250738585072014e-308), false);
    Test(BBox2_IntersectCircle, BBox2(0, 0, 2, 2), Circle(3, 1, 1), true);
    Test(BBox2_IntersectCircle, BBox2(0, 0, 2, 2), Circle(3.0000000000000004, 1, 1), false);
    Test(BBox2_IntersectCircle, BBox2(0, 0, 2, 2), Circle(-1, 1, 1), true);
    Test(BBox2_IntersectCircle, BBox2(0, 0, 2, 2), Circle(-1.0000000000000002, 1, 1), false);
    Test(BBox2_IntersectCircle, BBox2(0, 0, 2, 2), Circle(3, 3, 1.4142135623730951), true);
    Test(BBox2_IntersectCircle, BBox2(0, 0, 2, 2), Circle(3, 3, 1.4142135623730950), false);
    
    Test(Line2_LocationAlongLine, Line2(0, 0, 2, 2), V2(1, 1), 0.5);
    Test(Line2_LocationAlongLine, Line2(0, 0, 2, 2), V2(1.5, 0.5), 0.5);
    Test(Line2_LocationAlongLine, Line2(0, 0, 2, 2), V2(2, 3), 1.25);
    Test(Line2_LocationAlongLine, Line2(0, 0, 2, 2), V2(0, -1), -0.25);
    Test(Line2_PointAlongLine, Line2(0, 0, 2, 2), 0.5, V2(1, 1));
    Test(Line2_PointAlongLine, Line2(0, 0, 2, 2), 0, V2(0, 0));
    Test(Line2_PointAlongLine, Line2(0, 0, 2, 2), 1, V2(2, 2));
    Test(Line2_DistV2, Line2(0, 0, 2, 2), V2(1, 1), 0);
    Test(Line2_DistV2, Line2(0, 0, 2, 2), V2(1.5, 0.5), 0.7071067811865476);
    Test(Line2_DistV2, Line2(0, 0, 2, 2), V2(2, 3), 1);
    Test(Line2_DistV2, Line2(0, 0, 2, 2), V2(0, -1), 1);
    
    Test(Line3_LocationAlongLine, Line3(0, 0, 0, 2, 2, 2), V3(1, 1, 1), 0.5);
    Test(Line3_LocationAlongLine, Line3(0, 0, 0, 2, 2, 2), V3(1.5, 0.5, 1), 0.5);
    Test(Line3_LocationAlongLine, Line3(0, 0, 0, 2, 2, 2), V3(2, 3, 2.5), 1.25);
    Test(Line3_LocationAlongLine, Line3(0, 0, 0, 2, 2, 2), V3(0, -1, -0.5), -0.25);
    Test(Line3_PointAlongLine, Line3(0, 0, 0, 2, 2, 2), 0.5, V3(1, 1, 1));
    Test(Line3_PointAlongLine, Line3(0, 0, 0, 2, 2, 2), 0, V3(0, 0, 0));
    Test(Line3_PointAlongLine, Line3(0, 0, 0, 2, 2, 2), 1, V3(2, 2, 2));
    Test(Line3_DistV3, Line3(0, 0, 0, 2, 2, 2), V3(1, 1, 1), 0);
    Test(Line3_DistV3, Line3(0, 0, 0, 2, 2, 2), V3(2, 2, 0), 1.632993161855452);
    Test(Line3_DistV3, Line3(0, 0, 0, 2, 2, 2), V3(2, 2, 3), 1);
    Test(Line3_DistV3, Line3(0, 0, 0, 2, 2, 2), V3(0, 0, -1), 1);
    
    if (!Error) printf("All tests passed!\n");
    return 0;
}
