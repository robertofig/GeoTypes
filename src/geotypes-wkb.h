#ifndef GEOTYPES_WKB_H
//==========================================================================
// geotypes-wkb.h
//
// Module for reading and writing Well-Known Binary (WKB) geometries. Each
// geometry type gets its own structure, to allow for function overloading.
// 
// Reading: 
//   Load the data into a memory buffer, then cast its pointer to the
//   correct geometry. Access vertices and parts of the geometry using the
//   appropriate Get...() function at the "Access members" section, using
//   the index of the vertex/part as described in the geometry struct.
//
//   Parts can also be iterated upon using the wkb_iter struct, that needs
//   to be manually initialized. After that just continuously pass it to
//   the appropriate GetNext...() function at the "Iterate through members"
//   section. Once no more geometries are left, it returns a NULL pointer.
//
//   To get the full size of a geometry in bytes, use the appropriate
//   Get...Size() function at the "Object size in bytes" section.
//
// Writing:
//   Allocate a memory buffer large enough to hold the entire wkb, then
//   call the Create...() function for the specific geometry type desired.
//   The returned pointer will be initialised, and can be repeatedly
//   passed to one of the Add...() functions at the "Agg geom functions"
//   section.
//
//   To add sub-geometries, first add the encompassing geometry and use
//   the pointer returned to pass it to other Add...() functions. These
//   sub-geometries need to be filled entirely before a new sub-geometry
//   can be created.
//
//   Example: given a multipolygon wkb, pass it to AddPolygon() to create
//   an empty polygon. Then pass the returned pointer to AddRing() to add
//   a new ring to it. Then pass the returned ring pointer to AddVertex()
//   repeatedly to add coordinates to it. Once done, a new ring can be
//   added with AddRing(), or a new polygon with AddPolygon().
//==========================================================================
#define GEOTYPES_WKB_H

#include "geotypes-base.h"

typedef enum wkb_geom_type
{
    Wkb_None                 =    0,
    
    // Geoms 2D
    Wkb_Point                =    1,
    Wkb_Linestring           =    2,
    Wkb_Polygon              =    3,
    Wkb_MultiPoint           =    4,
    Wkb_MultiLinestring      =    5,
    Wkb_MultiPolygon         =    6,
    Wkb_GeometryCollection   =    7,
    Wkb_CircularString       =    8,
    Wkb_CompoundCurve        =    9,
    Wkb_CurvePolygon         =   10,
    Wkb_MultiCurve           =   11,
    Wkb_MultiSurface         =   12,
    Wkb_Curve                =   13,
    Wkb_Surface              =   14,
    Wkb_PolyhedralSurface    =   15,
    Wkb_TIN                  =   16,
    Wkb_Triangle             =   17,
    
    // Geoms 3D (Z)
    Wkb_PointZ               = 1001,
    Wkb_LinestringZ          = 1002,
    Wkb_PolygonZ             = 1003,
    Wkb_MultiPointZ          = 1004,
    Wkb_MultiLinestringZ     = 1005,
    Wkb_MultiPolygonZ        = 1006,
    Wkb_GeometryCollectionZ  = 1007,
    Wkb_CircularStringZ      = 1008,
    Wkb_CompoundCurveZ       = 1009,
    Wkb_CurvePolygonZ        = 1010,
    Wkb_MultiCurveZ          = 1011,
    Wkb_MultiSurfaceZ        = 1012,
    Wkb_CurveZ               = 1013,
    Wkb_SurfaceZ             = 1014,
    Wkb_PolyhedralSurfaceZ   = 1015,
    Wkb_TINZ                 = 1016,
    Wkb_TriangleZ            = 1017,
    
    // Geoms 3D (M)
    Wkb_PointM               = 2001,
    Wkb_LinestringM          = 2002,
    Wkb_PolygonM             = 2003,
    Wkb_MultiPointM          = 2004,
    Wkb_MultiLinestringM     = 2005,
    Wkb_MultiPolygonM        = 2006,
    Wkb_GeometryCollectionM  = 2007,
    Wkb_CircularStringM      = 2008,
    Wkb_CompoundCurveM       = 2009,
    Wkb_CurvePolygonM        = 2010,
    Wkb_MultiCurveM          = 2011,
    Wkb_MultiSurfaceM        = 2012,
    Wkb_CurveM               = 2013,
    Wkb_SurfaceM             = 2014,
    Wkb_PolyhedralSurfaceM   = 2015,
    Wkb_TINM                 = 2016,
    Wkb_TriangleM            = 2017,
    
    // Geoms 4D (ZM)
    Wkb_PointZM              = 3001,
    Wkb_LinestringZM         = 3002,
    Wkb_PolygonZM            = 3003,
    Wkb_MultiPointZM         = 3004,
    Wkb_MultiLinestringZM    = 3005,
    Wkb_MultiPolygonZM       = 3006,
    Wkb_GeometryCollectionZM = 3007,
    Wkb_CircularStringZM     = 3008,
    Wkb_CompoundCurveZM      = 3009,
    Wkb_CurvePolygonZM       = 3010,
    Wkb_MultiCurveZM         = 3011,
    Wkb_MultiSurfaceZM       = 3012,
    Wkb_CurveZM              = 3013,
    Wkb_SurfaceZM            = 3014,
    Wkb_PolyhedralSurfaceZM  = 3015,
    Wkb_TINZM                = 3016,
    Wkb_TriangleZM           = 3017,
} wkb_geom_type;

enum wkb_byte_order : u8
{
    Wkb_BigEndian    = 0,
    Wkb_LittleEndian = 1
};

//=================================
// Geom structs (Base)
//=================================

#pragma pack(push, 1)

struct wkb_header
{
    u8 ByteOrder;
    u32 WkbType;
};

struct ring2
{
    u32 NumPoints;
    //v2 Points[NumPoints];
};

struct ring3
{
    u32 NumPoints;
    //v3 Points[NumPoints];
};

struct ring4
{
    u32 NumPoints;
    //v4 Points[NumPoints];
};

//=================================
// Geom structs (WKB Simple)
//=================================

struct wkb_point2
{
    wkb_header Header;
    v2 Point;
};

struct wkb_point3
{
    wkb_header Header;
    v3 Point;
};

struct wkb_point4
{
    wkb_header Header;
    v4 Point;
};

struct wkb_linestring2
{
    wkb_header Header;
    u32 NumPoints;
    //v2 Points[NumPoints];
};

struct wkb_linestring3
{
    wkb_header Header;
    u32 NumPoints;
    //v3 Points[NumPoints];
};

struct wkb_linestring4
{
    wkb_header Header;
    u32 NumPoints;
    //v4 Points[NumPoints];
};

struct wkb_polygon2
{
    wkb_header Header;
    u32 NumRings;
    //ring2 Rings[NumRings];
};
typedef wkb_polygon2 wkb_triangle2;

struct wkb_polygon3
{
    wkb_header Header;
    u32 NumRings;
    //ring3 Rings[NumRings];
};
typedef wkb_polygon3 wkb_triangle3;

struct wkb_polygon4
{
    wkb_header Header;
    u32 NumRings;
    //ring4 Rings[NumRings];
};
typedef wkb_polygon4 wkb_triangle4;

struct wkb_polyhedron2
{
    wkb_header Header;
    u32 NumPolygons;
    //wkb_polygon2 Polygons[NumPolygons];
};
typedef wkb_polyhedron2 wkb_tin2;

struct wkb_polyhedron3
{
    wkb_header Header;
    u32 NumPolygons;
    //wkb_polygon3 Polygons[NumPolygons];
};
typedef wkb_polyhedron3 wkb_tin3;

struct wkb_polyhedron4
{
    wkb_header Header;
    u32 NumPolygons;
    //wkb_polygon4 Polygons[NumPolygons];
};
typedef wkb_polyhedron4 wkb_tin4;

//=================================
// Geom structs (WKB Multipart)
//=================================

struct wkb_multipoint2
{
    wkb_header Header;
    u32 NumPoints;
    //wkb_point2 Points[NumPoints];
};

struct wkb_multipoint3
{
    wkb_header Header;
    u32 NumPoints;
    //wkb_point3 Points[NumPoints];
};

struct wkb_multipoint4
{
    wkb_header Header;
    u32 NumPoints;
    //wkb_point4 Points[NumPoints];
};

struct wkb_multilinestring2
{
    wkb_header Header;
    u32 NumLinestrings;
    //wkb_linestring2 Linestrings[NumLinestrings];
};

struct wkb_multilinestring3
{
    wkb_header Header;
    u32 NumLinestrings;
    //wkb_linestring3 Linestrings[NumLinestrings];
};

struct wkb_multilinestring4
{
    wkb_header Header;
    u32 NumLinestrings;
    //wkb_linestring4 Linestrings[NumLinestrings];
};

struct wkb_multipolygon2
{
    wkb_header Header;
    u32 NumPolygons;
    //wkb_polygon2 Polygons[NumPolygons];
};

struct wkb_multipolygon3
{
    wkb_header Header;
    u32 NumPolygons;
    //wkb_polygon3 Polygons[NumPolygons];
};

struct wkb_multipolygon4
{
    wkb_header Header;
    u32 NumPolygons;
    //wkb_polygon4 Polygons[NumPolygons];
};

struct wkb_collection2
{
    wkb_header Header;
    u32 NumGeometries;
    //wkb_geometry2 Geometries[NumGeometries];
};

struct wkb_collection3
{
    wkb_header Header;
    u32 NumGeometries;
    //wkb_geometry3 Geometries[NumGeometries];
};

struct wkb_collection4
{
    wkb_header Header;
    u32 NumGeometries;
    //wkb_geometry4 Geometries[NumGeometries];
};

struct wkb_geometry2
{
    union
    {
        wkb_point2 Point;
        wkb_linestring2 Linestring;
        wkb_polygon2 Polygon;
        wkb_triangle2 Triangle;
        wkb_polyhedron2 Polyhedron;
        wkb_tin2 TIN;
        wkb_multipoint2 MultiPoint;
        wkb_multilinestring2 MultiLinestring;
        wkb_multipolygon2 MultiPolygon;
        wkb_collection2 Collection;
        wkb_header Header;
    };
};

struct wkb_geometry3
{
    union
    {
        wkb_point3 Point;
        wkb_linestring3 Linestring;
        wkb_polygon3 Polygon;
        wkb_triangle3 Triangle;
        wkb_polyhedron3 Polyhedron;
        wkb_tin3 TIN;
        wkb_multipoint3 MultiPoint;
        wkb_multilinestring3 MultiLinestring;
        wkb_multipolygon3 MultiPolygon;
        wkb_collection3 Collection;
        wkb_header Header;
    };
};

struct wkb_geometry4
{
    union
    {
        wkb_point4 Point;
        wkb_linestring4 Linestring;
        wkb_polygon4 Polygon;
        wkb_triangle4 Triangle;
        wkb_polyhedron4 Polyhedron;
        wkb_tin4 TIN;
        wkb_multipoint4 MultiPoint;
        wkb_multilinestring4 MultiLinestring;
        wkb_multipolygon4 MultiPolygon;
        wkb_collection4 Collection;
        wkb_header Header;
    };
};

#pragma pack(pop)

//=================================
// Creation functions
//=================================

wkb_point2*           CreatePoint(void* Wkb, v2 _Point);
wkb_point3*           CreatePointZ(void* Wkb, v3 _Point);
wkb_point3*           CreatePointM(void* Wkb, v3 _Point);
wkb_point4*           CreatePointZM(void* Wkb, v4 _Point);

wkb_linestring2*      CreateLinestring(void* Wkb);
wkb_linestring3*      CreateLinestringZ(void* Wkb);
wkb_linestring3*      CreateLinestringM(void* Wkb);
wkb_linestring4*      CreateLinestringZM(void* Wkb);

wkb_polygon2*         CreatePolygon(void* Wkb);
wkb_polygon3*         CreatePolygonZ(void* Wkb);
wkb_polygon3*         CreatePolygonM(void* Wkb);
wkb_polygon4*         CreatePolygonZM(void* Wkb);

wkb_triangle2*        CreateTriangle(void* Wkb);
wkb_triangle3*        CreateTriangleZ(void* Wkb);
wkb_triangle3*        CreateTriangleM(void* Wkb);
wkb_triangle4*        CreateTriangleZM(void* Wkb);

wkb_polyhedron2*      CreatePolyhedron(void* Wkb);
wkb_polyhedron3*      CreatePolyhedronZ(void* Wkb);
wkb_polyhedron3*      CreatePolyhedronM(void* Wkb);
wkb_polyhedron4*      CreatePolyhedronZM(void* Wkb);

wkb_tin2*             CreateTIN(void* Wkb);
wkb_tin3*             CreateTINZ(void* Wkb);
wkb_tin3*             CreateTINM(void* Wkb);
wkb_tin4*             CreateTINZM(void* Wkb);

wkb_multipoint2*      CreateMultiPoint(void* Wkt);
wkb_multipoint3*      CreateMultiPointZ(void* Wkt);
wkb_multipoint3*      CreateMultiPointM(void* Wkt);
wkb_multipoint4*      CreateMultiPointZM(void* Wkt);

wkb_multilinestring2* CreateMultiLinestring(void* Wkt);
wkb_multilinestring3* CreateMultiLinestringZ(void* Wkt);
wkb_multilinestring3* CreateMultiLinestringM(void* Wkt);
wkb_multilinestring4* CreateMultiLinestringZM(void* Wkt);

wkb_multipolygon2*    CreateMultiPolygon(void* Wkt);
wkb_multipolygon3*    CreateMultiPolygonZ(void* Wkt);
wkb_multipolygon3*    CreateMultiPolygonM(void* Wkt);
wkb_multipolygon4*    CreateMultiPolygonZM(void* Wkt);

wkb_collection2*      CreateCollection(void* Wkt);
wkb_collection3*      CreateCollectionZ(void* Wkt);
wkb_collection3*      CreateCollectionM(void* Wkt);
wkb_collection4*      CreateCollectionZM(void* Wkt);

//=================================
// Access members
//=================================

v2*              GetVertex(wkb_linestring2* Linestring, usz TargetIdx);
v3*              GetVertex(wkb_linestring3* Linestring, usz TargetIdx);
v4*              GetVertex(wkb_linestring4* Linestring, usz TargetIdx);

v2*              GetVertex(ring2* Ring, usz TargetIdx);
v3*              GetVertex(ring3* Ring, usz TargetIdx);
v4*              GetVertex(ring4* Ring, usz TargetIdx);

ring2*           GetRing(wkb_polygon2* Polygon, usz TargetIdx);
ring3*           GetRing(wkb_polygon3* Polygon, usz TargetIdx);
ring4*           GetRing(wkb_polygon4* Polygon, usz TargetIdx);

wkb_polygon2*    GetPolygon(wkb_polyhedron2* Mesh, usz TargetIdx);
wkb_polygon3*    GetPolygon(wkb_polyhedron3* Mesh, usz TargetIdx);
wkb_polygon4*    GetPolygon(wkb_polyhedron4* Mesh, usz TargetIdx);

wkb_triangle2*   GetTriangle(wkb_tin2* TIN, usz TargetIdx);
wkb_triangle3*   GetTriangle(wkb_tin3* TIN, usz TargetIdx);
wkb_triangle4*   GetTriangle(wkb_tin4* TIN, usz TargetIdx);

wkb_point2*      GetPoint(wkb_multipoint2* MultiPoint, usz TargetIdx);
wkb_point3*      GetPoint(wkb_multipoint3* MultiPoint, usz TargetIdx);
wkb_point4*      GetPoint(wkb_multipoint4* MultiPoint, usz TargetIdx);

wkb_linestring2* GetLinestring(wkb_multilinestring2* MultiLinestring, usz TargetIdx);
wkb_linestring3* GetLinestring(wkb_multilinestring3* MultiLinestring, usz TargetIdx);
wkb_linestring4* GetLinestring(wkb_multilinestring4* MultiLinestring, usz TargetIdx);

wkb_polygon2*    GetPolygon(wkb_multipolygon2* MultiPolygon, usz TargetIdx);
wkb_polygon3*    GetPolygon(wkb_multipolygon3* MultiPolygon, usz TargetIdx);
wkb_polygon4*    GetPolygon(wkb_multipolygon4* MultiPolygon, usz TargetIdx);

wkb_geometry2*   GetGeometry(wkb_collection2* Collection, usz TargetIdx);
wkb_geometry3*   GetGeometry(wkb_collection3* Collection, usz TargetIdx);
wkb_geometry4*   GetGeometry(wkb_collection4* Collection, usz TargetIdx);

//=================================
// Object size in bytes
//=================================

usz GetRingSize(ring2* Ring);
usz GetRingSize(ring3* Ring);
usz GetRingSize(ring4* Ring);

usz GetLinestringSize(wkb_linestring2* Linestring);
usz GetLinestringSize(wkb_linestring3* Linestring);
usz GetLinestringSize(wkb_linestring4* Linestring);

usz GetPolygonSize(wkb_polygon2* Polygon);
usz GetPolygonSize(wkb_polygon3* Polygon);
usz GetPolygonSize(wkb_polygon4* Polygon);

usz GetTriangleSize(wkb_triangle2* Triangle);
usz GetTriangleSize(wkb_triangle3* Triangle);
usz GetTriangleSize(wkb_triangle4* Triangle);

usz GetPolyhedronSize(wkb_polyhedron2* Mesh);
usz GetPolyhedronSize(wkb_polyhedron3* Mesh);
usz GetPolyhedronSize(wkb_polyhedron4* Mesh);

usz GetTINSize(wkb_tin2* TIN);
usz GetTINSize(wkb_tin3* TIN);
usz GetTINSize(wkb_tin4* TIN);

usz GetMultiPointSize(wkb_multipoint2* MultiPoint);
usz GetMultiPointSize(wkb_multipoint3* MultiPoint);
usz GetMultiPointSize(wkb_multipoint4* MultiPoint);

usz GetMultiLinestringSize(wkb_multilinestring2* MultiLinestring);
usz GetMultiLinestringSize(wkb_multilinestring3* MultiLinestring);
usz GetMultiLinestringSize(wkb_multilinestring4* MultiLinestring);

usz GetMultiPolygonSize(wkb_multipolygon2* MultiPolygon);
usz GetMultiPolygonSize(wkb_multipolygon3* MultiPolygon);
usz GetMultiPolygonSize(wkb_multipolygon4* MultiPolygon);

usz GetGeometrySize(wkb_geometry2* Geometry);
usz GetGeometrySize(wkb_geometry3* Geometry);
usz GetGeometrySize(wkb_geometry4* Geometry);

usz GetCollectionSize(wkb_collection2* Collection);
usz GetCollectionSize(wkb_collection3* Collection);
usz GetCollectionSize(wkb_collection4* Collection);

//=================================
// Iterate through members
//=================================

struct wkb_iter2
{
    usz CurrentIdx;
    usz NumElements;
    void* Geom;
};

struct wkb_iter3
{
    usz CurrentIdx;
    usz NumElements;
    void* Geom;
};

struct wkb_iter4
{
    usz CurrentIdx;
    usz NumElements;
    void* Geom;
};

wkb_iter2        WkbIter(wkb_polygon2* Polygon);
wkb_iter3        WkbIter(wkb_polygon3* Polygon);
wkb_iter4        WkbIter(wkb_polygon4* Polygon);

wkb_iter2        WkbIter(wkb_multilinestring2* MultiLinestring);
wkb_iter3        WkbIter(wkb_multilinestring3* MultiLinestring);
wkb_iter4        WkbIter(wkb_multilinestring4* MultiLinestring);

wkb_iter2        WkbIter(wkb_multipolygon2* MultiPolygon);
wkb_iter3        WkbIter(wkb_multipolygon3* MultiPolygon);
wkb_iter4        WkbIter(wkb_multipolygon4* MultiPolygon);

wkb_iter2        WkbIter(wkb_polyhedron2* Polyhedron);
wkb_iter3        WkbIter(wkb_polyhedron3* Polyhedron);
wkb_iter4        WkbIter(wkb_polyhedron4* Polyhedron);

wkb_iter2        WkbIter(wkb_collection2* Collection);
wkb_iter3        WkbIter(wkb_collection3* Collection);
wkb_iter4        WkbIter(wkb_collection4* Collection);

ring2*           GetNextRing(wkb_iter2* Iter);
ring3*           GetNextRing(wkb_iter3* Iter);
ring4*           GetNextRing(wkb_iter4* Iter);

wkb_linestring2* GetNextLinestring(wkb_iter2* Iter);
wkb_linestring3* GetNextLinestring(wkb_iter3* Iter);
wkb_linestring4* GetNextLinestring(wkb_iter4* Iter);

wkb_polygon2*    GetNextPolygon(wkb_iter2* Iter);
wkb_polygon3*    GetNextPolygon(wkb_iter3* Iter);
wkb_polygon4*    GetNextPolygon(wkb_iter4* Iter);

wkb_triangle2*   GetNextTriangle(wkb_iter2* Iter);
wkb_triangle3*   GetNextTriangle(wkb_iter3* Iter);
wkb_triangle4*   GetNextTriangle(wkb_iter4* Iter);

wkb_geometry2*   GetNextGeometry(wkb_iter2* Iter);
wkb_geometry3*   GetNextGeometry(wkb_iter3* Iter);
wkb_geometry4*   GetNextGeometry(wkb_iter4* Iter);

//=================================
// Get BBox functions
//=================================

bbox2 GetBBox(wkb_point2* Point);
bbox3 GetBBox(wkb_point3* Point);
bbox4 GetBBox(wkb_point4* Point);

bbox2 GetBBox(wkb_linestring2* Linestring);
bbox3 GetBBox(wkb_linestring3* Linestring);
bbox4 GetBBox(wkb_linestring4* Linestring);

bbox2 GetBBox(wkb_polygon2* Polygon);
bbox3 GetBBox(wkb_polygon3* Polygon);
bbox4 GetBBox(wkb_polygon4* Polygon);

bbox2 GetBBox(wkb_polyhedron2* Polyhedron);
bbox3 GetBBox(wkb_polyhedron3* Polyhedron);
bbox4 GetBBox(wkb_polyhedron4* Polyhedron);

bbox2 GetBBox(wkb_multipoint2* MultiPoint);
bbox3 GetBBox(wkb_multipoint3* MultiPoint);
bbox4 GetBBox(wkb_multipoint4* MultiPoint);

bbox2 GetBBox(wkb_multilinestring2* MultiLinestring);
bbox3 GetBBox(wkb_multilinestring3* MultiLinestring);
bbox4 GetBBox(wkb_multilinestring4* MultiLinestring);

bbox2 GetBBox(wkb_multipolygon2* MultiPolygon);
bbox3 GetBBox(wkb_multipolygon3* MultiPolygon);
bbox4 GetBBox(wkb_multipolygon4* MultiPolygon);

bbox2 GetBBox(wkb_collection2* Collection);
bbox3 GetBBox(wkb_collection3* Collection);
bbox4 GetBBox(wkb_collection4* Collection);

//=================================
// Add geom functions
//=================================

void                  AddVertex(ring2* Ring, v2 Point);
void                  AddVertex(ring3* Ring, v3 Point);
void                  AddVertex(ring4* Ring, v4 Point);

void                  AddVertex(wkb_linestring2* Linestring, v2 Point);
void                  AddVertex(wkb_linestring3* Linestring, v3 Point);
void                  AddVertex(wkb_linestring4* Linestring, v4 Point);

ring2*                AddRing(wkb_polygon2* Polygon);
ring3*                AddRing(wkb_polygon3* Polygon);
ring4*                AddRing(wkb_polygon4* Polygon);

wkb_polygon2*         AddPolygon(wkb_polyhedron2* Mesh);
wkb_polygon3*         AddPolygon(wkb_polyhedron3* Mesh);
wkb_polygon4*         AddPolygon(wkb_polyhedron4* Mesh);

wkb_triangle2*        AddTriangle(wkb_tin2* TIN);
wkb_triangle3*        AddTriangle(wkb_tin3* TIN);
wkb_triangle4*        AddTriangle(wkb_tin4* TIN);

wkb_point2*           AddPoint(wkb_multipoint2* MultiPoint, v2 Vertex);
wkb_point3*           AddPoint(wkb_multipoint3* MultiPoint, v3 Vertex);
wkb_point4*           AddPoint(wkb_multipoint4* MultiPoint, v4 Vertex);

wkb_linestring2*      AddLinestring(wkb_multilinestring2* MultiLinestring);
wkb_linestring3*      AddLinestring(wkb_multilinestring3* MultiLinestring);
wkb_linestring4*      AddLinestring(wkb_multilinestring4* MultiLinestring);

wkb_polygon2*         AddPolygon(wkb_multipolygon2* MultiPolygon);
wkb_polygon3*         AddPolygon(wkb_multipolygon3* MultiPolygon);
wkb_polygon4*         AddPolygon(wkb_multipolygon4* MultiPolygon);

wkb_point2*           AddPoint(wkb_collection2* Collection, v2 Vertex);
wkb_point3*           AddPoint(wkb_collection3* Collection, v3 Vertex);
wkb_point4*           AddPoint(wkb_collection4* Collection, v4 Vertex);

wkb_linestring2*      AddLinestring(wkb_collection2* Collection);
wkb_linestring3*      AddLinestring(wkb_collection3* Collection);
wkb_linestring4*      AddLinestring(wkb_collection4* Collection);

wkb_polygon2*         AddPolygon(wkb_collection2* Collection);
wkb_polygon3*         AddPolygon(wkb_collection3* Collection);
wkb_polygon4*         AddPolygon(wkb_collection4* Collection);

wkb_triangle2*        AddTriangle(wkb_collection2* Collection);
wkb_triangle3*        AddTriangle(wkb_collection3* Collection);
wkb_triangle4*        AddTriangle(wkb_collection4* Collection);

wkb_polyhedron2*      AddPolyhedron(wkb_collection2* Collection);
wkb_polyhedron3*      AddPolyhedron(wkb_collection3* Collection);
wkb_polyhedron4*      AddPolyhedron(wkb_collection4* Collection);

wkb_tin2*             AddTIN(wkb_collection2* Collection);
wkb_tin3*             AddTIN(wkb_collection3* Collection);
wkb_tin4*             AddTIN(wkb_collection4* Collection);

wkb_multipoint2*      AddMultiPoint(wkb_collection2* Collection, v2 Vertex);
wkb_multipoint3*      AddMultiPoint(wkb_collection3* Collection, v3 Vertex);
wkb_multipoint4*      AddMultiPoint(wkb_collection4* Collection, v4 Vertex);

wkb_multilinestring2* AddMultiLinestring(wkb_collection2* Collection);
wkb_multilinestring3* AddMultiLinestring(wkb_collection3* Collection);
wkb_multilinestring4* AddMultiLinestring(wkb_collection4* Collection);

wkb_multipolygon2*    AddMultiPolygon(wkb_collection2* Collection);
wkb_multipolygon3*    AddMultiPolygon(wkb_collection3* Collection);
wkb_multipolygon4*    AddMultiPolygon(wkb_collection4* Collection);

wkb_collection2*      AddCollection(wkb_collection2* Collection);
wkb_collection3*      AddCollection(wkb_collection3* Collection);
wkb_collection4*      AddCollection(wkb_collection4* Collection);


#if !defined(GEOTYPES_STATIC_LINKING)
#include "geotypes-wkb.cpp"
#endif

#endif //GEOTYPES_WKB_H
