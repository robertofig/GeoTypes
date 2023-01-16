
//==================================
// 2D Vector
//==================================

f64
Dot(v2 A, v2 B)
{ 
    f64 Result = A.X*B.X + A.Y*B.Y;
    return Result;
}

f64
Cross(v2 A, v2 B)
{
    f64 Result = A.X*B.Y - A.Y*B.X;
    return Result;
}

f64
Mag(v2 A)
{
    f64 Result = sqrt(A.X*A.X + A.Y*A.Y);
    return Result;
}

f64
Mag2(v2 A)
{
    f64 Result = A.X*A.X + A.Y*A.Y;
    return Result;
}

v2
Unit(v2 A)
{
    v2 Result = A / Mag(A);
    return Result;
}

v2
Rotate90CW(v2 A)
{
    v2 Result = V2(A.Y, -A.X);
    return Result;
}

v2
Rotate90CCW(v2 A)
{
    v2 Result = V2(-A.Y, A.X);
    return Result;
}

f64
Dist(v2 A, v2 B)
{
    f64 Result = Mag(A - B);
    return Result;
}

f64
Dist2(v2 A, v2 B)
{
    f64 Result = Mag2(A - B);
    return Result;
}

//==================================
// 3D Vector
//==================================

f64
Dot(v3 A, v3 B)
{ 
    f64 Result = A.X*B.X + A.Y*B.Y + A.Z*B.Z;
    return Result;
}

f64
Mag(v3 A)
{
    f64 Result = sqrt(A.X*A.X + A.Y*A.Y + A.Z*A.Z);
    return Result;
}

f64
Mag2(v3 A)
{
    f64 Result = A.X*A.X + A.Y*A.Y + A.Z*A.Z;
    return Result;
}

v3
Unit(v3 A)
{
    v3 Result = A / Mag(A);
    return Result;
}

v3
Rotate90XAxisCW(v3 A)
{
    v3 Result = V3(A.X, A.Z, -A.Y);
    return Result;
}

v3
Rotate90XAxisCCW(v3 A)
{
    v3 Result = V3(A.X, -A.Z, A.Y);
    return Result;
}

v3
Rotate90YAxisCW(v3 A)
{
    v3 Result = V3(-A.Z, A.Y, A.X);
    return Result;
}

v3
Rotate90YAxisCCW(v3 A)
{
    v3 Result = V3(A.Z, A.Y, -A.X);
    return Result;
}

v3
Rotate90ZAxisCW(v3 A)
{
    v3 Result = V3(A.Y, -A.X, A.Z);
    return Result;
}

v3
Rotate90ZAxisCCW(v3 A)
{
    v3 Result = V3(-A.Y, A.X, A.Z);
    return Result;
}

f64
Dist(v3 A, v3 B)
{
    f64 Result = Mag(A - B);
    return Result;
}

f64
Dist2(v3 A, v3 B)
{
    f64 Result = Mag2(A - B);
    return Result;
}

//==================================
// Circle
//==================================

circle
Circle(v2 A, v2 B, f64 Radius)
{
    v2 MidPoint = A + ((B-A) * 0.5);
    v2 HalfBaseUnit = Unit(B - MidPoint);
    v2 HeightUnit = Radius > 0 ? Rotate90CCW(HalfBaseUnit) : Rotate90CW(HalfBaseUnit);
    f64 HalfBaseLen = Dist(A, B) / 2;
    f64 HeightLen = sqrt(Radius*Radius - HalfBaseLen*HalfBaseLen);
    v2 Height = HeightUnit * HeightLen;
    v2 Centre = MidPoint + Height;
    
    return Circle(Centre, Abs(Radius));
}

f64
Length(circle C)
{
    f64 Result = TAU * C.Radius;
    return Result;
}

f64
Area(circle C)
{
    f64 Result = PI * C.Radius * C.Radius;
    return Result;
}

f64
ArcLength(f64 Angle, circle C)
{
    f64 Result = Angle * C.Radius;
    return Result;
}

f64
ArcLength(v2 A, v2 B, circle C)
{
    f64 Base = Dist(A, B);
    f64 Circ2 = 2 * C.Radius * C.Radius;
    f64 Angle = acos((Circ2 - Base*Base) / Circ2); // Law of cosines.
    f64 Result = ArcLength(Angle, C);
    return Result;
}

v2
GetPointOfAngle(f64 Angle, circle C)
{
    v2 Result = C.Centre + (C.Radius * V2(cos(Angle), sin(Angle)));
    return Result;
}

f64
GetAngleOfPoint(v2 A, circle C)
{
    v2 CAUnit = Unit(A - C.Centre);
    f64 Result = acos(CAUnit.X) * (CAUnit.Y > 0 ? 1 : -1);
    return Result;
}

bool
PointInCircle(v2 P, circle C)
{
    v2 Delta = C.Centre - P;
    f64 A = Dot(Delta, Delta);
    f64 B = C.Radius * C.Radius;
    bool Result = A <= B;
    return Result;
}

//==================================
// BBox 2D
//==================================

bool
Intersect(bbox2 A, bbox2 B)
{
    bool Result = !(A.Max.X < B.Min.X || A.Min.X > B.Max.X || A.Max.Y < B.Min.Y || A.Min.Y > B.Max.Y);
    return Result;
}

bool
Intersect(v2 P, bbox2 B)
{
    bool Result = !(P.X < B.Min.X || P.X > B.Max.X || P.Y < B.Min.Y || P.Y > B.Max.Y);
    return Result;
}

bool
Intersect(bbox2 B, v2 P) 
{
    return Intersect(P, B);
}

bool
Intersect(circle C, bbox2 B)
{
    f64 NearestX = Max(B.Min.X, Min(C.Centre.X, B.Max.X));
    f64 NearestY = Max(B.Min.Y, Min(C.Centre.Y, B.Max.Y));
    bool Result = PointInCircle(V2(NearestX, NearestY), C);
    return Result;
}

bool
Intersect(bbox2 B, circle C)
{
    return Intersect(C, B);
}

//==================================
// Line 2D
//==================================

bool
IsPointLeftOfLine(v2 P, line2 L)
{
    f64 Result = (L.P1.X-L.P0.X)*(P.Y-L.P0.Y) - (L.P1.Y-L.P0.Y)*(P.X-L.P0.X);
    return Result > 0;
}

f64
LocationAlongLine(line2 L, v2 Target)
{
    v2 LineDir = L.P1 - L.P0;
    v2 TargetDir = Target - L.P0;
    v2 LineDirUnit = Unit(LineDir);
    
    f64 Result = Dot(LineDirUnit, TargetDir) / Mag(LineDir);
    return Result;
}

v2
PointAlongLine(line2 L, f64 LineLocation)
{
    v2 Result = ((L.P1 - L.P0) * LineLocation) + L.P0;
    return Result;    
}

f64
Dist(v2 P, line2 L)
{
    f64 LineLocation = Clamp01(LocationAlongLine(L, P));
    v2 Projection = PointAlongLine(L, LineLocation);
    f64 Result = Dist(P, Projection);
    return Result;
}

f64
Dist(line2 L, v2 P)
{
    return Dist(P, L);
}

//==================================
// Line 3D
//==================================

f64
LocationAlongLine(line3 L, v3 Target)
{
    v3 LineDir = L.P1 - L.P0;
    v3 TargetDir = Target - L.P0;
    v3 LineDirUnit = Unit(LineDir);
    
    f64 Result = Dot(LineDirUnit, TargetDir) / Mag(LineDir);
    return Result;
}

v3
PointAlongLine(line3 L, f64 LineLocation)
{
    v3 Result = ((L.P1 - L.P0) * LineLocation) + L.P0;
    return Result;    
}

f64
Dist(v3 P, line3 L)
{
    f64 LineLocation = Clamp01(LocationAlongLine(L, P));
    v3 Projection = PointAlongLine(L, LineLocation);
    f64 Result = Dist(P, Projection);
    return Result;
}

f64
Dist(line3 L, v3 P)
{
    return Dist(P, L);
}
