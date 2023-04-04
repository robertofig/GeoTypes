global wkb_byte_order gByteOrder = Wkb_LittleEndian;
global wkb_header gNullHeader = { Wkb_BigEndian, Wkb_None };

//=================================
// Creation functions
//=================================

inline wkb_point2*
CreatePoint(void* Wkb, v2 _Point)
{
    wkb_point2* Result = (wkb_point2*)Wkb;
    *Result = { { gByteOrder, Wkb_Point }, _Point };
    return Result;
}

inline wkb_point3*
CreatePointZ(void* Wkb, v3 _Point)
{
    wkb_point3* Result = (wkb_point3*)Wkb;
    *Result = { { gByteOrder, Wkb_PointZ }, _Point };
    return Result;
}

inline wkb_point3*
CreatePointM(void* Wkb, v3 _Point)
{
    wkb_point3* Result = (wkb_point3*)Wkb;
    *Result = { { gByteOrder, Wkb_PointM }, _Point };
    return Result;
}

inline wkb_point4*
CreatePointZM(void* Wkb, v4 _Point)
{
    wkb_point4* Result = (wkb_point4*)Wkb;
    *Result = { { gByteOrder, Wkb_PointZM }, _Point };
    return Result;
}

inline wkb_linestring2*
CreateLinestring(void* Wkb)
{
    wkb_linestring2* Result = (wkb_linestring2*)Wkb;
    *Result = { { gByteOrder, Wkb_Linestring }, 0 };
    return Result;
}

inline wkb_linestring3*
CreateLinestringZ(void* Wkb)
{
    wkb_linestring3* Result = (wkb_linestring3*)Wkb;
    *Result = { { gByteOrder, Wkb_LinestringZ }, 0 };
    return Result;
}

inline wkb_linestring3*
CreateLinestringM(void* Wkb)
{
    wkb_linestring3* Result = (wkb_linestring3*)Wkb;
    *Result = { { gByteOrder, Wkb_LinestringM }, 0 };
    return Result;
}

inline wkb_linestring4*
CreateLinestringZM(void* Wkb)
{
    wkb_linestring4* Result = (wkb_linestring4*)Wkb;
    *Result = { { gByteOrder, Wkb_LinestringZM }, 0 };
    return Result;
}

inline wkb_polygon2*
CreatePolygon(void* Wkb)
{
    wkb_polygon2* Result = (wkb_polygon2*)Wkb;
    *Result = { { gByteOrder, Wkb_Polygon }, 0 };
    return Result;
}

inline wkb_polygon3*
CreatePolygonZ(void* Wkb)
{
    wkb_polygon3* Result = (wkb_polygon3*)Wkb;
    *Result = { { gByteOrder, Wkb_PolygonZ }, 0 };
    return Result;
}

inline wkb_polygon3*
CreatePolygonM(void* Wkb)
{
    wkb_polygon3* Result = (wkb_polygon3*)Wkb;
    *Result = { { gByteOrder, Wkb_PolygonM }, 0 };
    return Result;
}

inline wkb_polygon4*
CreatePolygonZM(void* Wkb)
{
    wkb_polygon4* Result = (wkb_polygon4*)Wkb;
    *Result = { { gByteOrder, Wkb_PolygonZM }, 0 };
    return Result;
}

inline wkb_triangle2*
CreateTriangle(void* Wkb)
{
    wkb_triangle2* Result = (wkb_triangle2*)Wkb;
    *Result = { { gByteOrder, Wkb_Triangle }, 0 };
    return Result;
}

inline wkb_triangle3*
CreateTriangleZ(void* Wkb)
{
    wkb_triangle3* Result = (wkb_triangle3*)Wkb;
    *Result = { { gByteOrder, Wkb_TriangleZ }, 0 };
    return Result;
}

inline wkb_triangle3*
CreateTriangleM(void* Wkb)
{
    wkb_triangle3* Result = (wkb_triangle3*)Wkb;
    *Result = { { gByteOrder, Wkb_TriangleM }, 0 };
    return Result;
}

inline wkb_triangle4*
CreateTriangleZM(void* Wkb)
{
    wkb_triangle4* Result = (wkb_triangle4*)Wkb;
    *Result = { { gByteOrder, Wkb_TriangleZM }, 0 };
    return Result;
}

inline wkb_polyhedron2*
CreatePolyhedron(void* Wkb)
{
    wkb_polyhedron2* Result = (wkb_polyhedron2*)Wkb;
    *Result = { { gByteOrder, Wkb_PolyhedralSurface }, 0 };
    return Result;
}

inline wkb_polyhedron3*
CreatePolyhedronZ(void* Wkb)
{
    wkb_polyhedron3* Result = (wkb_polyhedron3*)Wkb;
    *Result = { { gByteOrder, Wkb_PolyhedralSurfaceZ }, 0 };
    return Result;
}

inline wkb_polyhedron3*
CreatePolyhedronM(void* Wkb)
{
    wkb_polyhedron3* Result = (wkb_polyhedron3*)Wkb;
    *Result = { { gByteOrder, Wkb_PolyhedralSurfaceM }, 0 };
    return Result;
}

inline wkb_polyhedron4*
CreatePolyhedronZM(void* Wkb)
{
    wkb_polyhedron4* Result = (wkb_polyhedron4*)Wkb;
    *Result = { { gByteOrder, Wkb_PolyhedralSurfaceZM }, 0 };
    return Result;
}

inline wkb_tin2*
CreateTIN(void* Wkb)
{
    wkb_tin2* Result = (wkb_tin2*)Wkb;
    *Result = { { gByteOrder, Wkb_TIN }, 0 };
    return Result;
}

inline wkb_tin3*
CreateTINZ(void* Wkb)
{
    wkb_tin3* Result = (wkb_tin3*)Wkb;
    *Result = { { gByteOrder, Wkb_TINZ }, 0 };
    return Result;
}

inline wkb_tin3*
CreateTINM(void* Wkb)
{
    wkb_tin3* Result = (wkb_tin3*)Wkb;
    *Result = { { gByteOrder, Wkb_TINM }, 0 };
    return Result;
}

inline wkb_tin4*
CreateTINZM(void* Wkb)
{
    wkb_tin4* Result = (wkb_tin4*)Wkb;
    *Result = { { gByteOrder, Wkb_TINZM }, 0 };
    return Result;
}

inline wkb_multipoint2*
CreateMultiPoint(void* Wkb)
{
    wkb_multipoint2* Result = (wkb_multipoint2*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiPoint }, 0 };
    return Result;
}

inline wkb_multipoint3*
CreateMultiPointZ(void* Wkb)
{
    wkb_multipoint3* Result = (wkb_multipoint3*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiPointZ }, 0 };
    return Result;
}

inline wkb_multipoint3*
CreateMultiPointM(void* Wkb)
{
    wkb_multipoint3* Result = (wkb_multipoint3*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiPointM }, 0 };
    return Result;
}

inline wkb_multipoint4*
CreateMultiPointZM(void* Wkb)
{
    wkb_multipoint4* Result = (wkb_multipoint4*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiPointZM }, 0 };
    return Result;
}

inline wkb_multilinestring2*
CreateMultiLinestring(void* Wkb)
{
    wkb_multilinestring2* Result = (wkb_multilinestring2*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiLinestring }, 0 };
    return Result;
}

inline wkb_multilinestring3*
CreateMultiLinestringZ(void* Wkb)
{
    wkb_multilinestring3* Result = (wkb_multilinestring3*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiLinestringZ }, 0 };
    return Result;
}

inline wkb_multilinestring3*
CreateMultiLinestringM(void* Wkb)
{
    wkb_multilinestring3* Result = (wkb_multilinestring3*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiLinestringM }, 0 };
    return Result;
}

inline wkb_multilinestring4*
CreateMultiLinestringZM(void* Wkb)
{
    wkb_multilinestring4* Result = (wkb_multilinestring4*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiLinestringZM }, 0 };
    return Result;
}

inline wkb_multipolygon2*
CreateMultiPolygon(void* Wkb)
{
    wkb_multipolygon2* Result = (wkb_multipolygon2*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiPolygon }, 0 };
    return Result;
}

inline wkb_multipolygon3*
CreateMultiPolygonZ(void* Wkb)
{
    wkb_multipolygon3* Result = (wkb_multipolygon3*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiPolygonZ }, 0 };
    return Result;
}

inline wkb_multipolygon3*
CreateMultiPolygonM(void* Wkb)
{
    wkb_multipolygon3* Result = (wkb_multipolygon3*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiPolygonM }, 0 };
    return Result;
}

inline wkb_multipolygon4*
CreateMultiPolygonZM(void* Wkb)
{
    wkb_multipolygon4* Result = (wkb_multipolygon4*)Wkb;
    *Result = { { gByteOrder, Wkb_MultiPolygonZM }, 0 };
    return Result;
}

inline wkb_collection2*
CreateCollection(void* Wkb)
{
    wkb_collection2* Result = (wkb_collection2*)Wkb;
    *Result = { { gByteOrder, Wkb_GeometryCollection }, 0 };
    return Result;
}

inline wkb_collection3*
CreateCollectionZ(void* Wkb)
{
    wkb_collection3* Result = (wkb_collection3*)Wkb;
    *Result = { { gByteOrder, Wkb_GeometryCollectionZ }, 0 };
    return Result;
}

inline wkb_collection3*
CreateCollectionM(void* Wkb)
{
    wkb_collection3* Result = (wkb_collection3*)Wkb;
    *Result = { { gByteOrder, Wkb_GeometryCollectionM }, 0 };
    return Result;
}

inline wkb_collection4*
CreateCollectionZM(void* Wkb)
{
    wkb_collection4* Result = (wkb_collection4*)Wkb;
    *Result = { { gByteOrder, Wkb_GeometryCollectionZM }, 0 };
    return Result;
}

//=================================
// Access members
//=================================

inline v2*
GetVertex(wkb_linestring2* Linestring, usz TargetIdx)
{
    v2* Points = (v2*)&Linestring[1];
    return Points + TargetIdx;
}

inline v3*
GetVertex(wkb_linestring3* Linestring, usz TargetIdx)
{
    v3* Points = (v3*)&Linestring[1];
    return Points + TargetIdx;
}

inline v4*
GetVertex(wkb_linestring4* Linestring, usz TargetIdx)
{
    v4* Points = (v4*)&Linestring[1];
    return Points + TargetIdx;
}

inline v2*
GetVertex(ring2* Ring, usz TargetIdx)
{
    v2* Points = (v2*)&Ring[1];
    return Points + TargetIdx;
}

inline v3*
GetVertex(ring3* Ring, usz TargetIdx)
{
    v3* Points = (v3*)&Ring[1];
    return Points + TargetIdx;
}

inline v4*
GetVertex(ring4* Ring, usz TargetIdx)
{
    v4* Points = (v4*)&Ring[1];
    return Points + TargetIdx;
}

inline ring2*
GetRing(wkb_polygon2* Polygon, usz TargetIdx)
{
    ring2* Ring = (ring2*)&Polygon[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Ring = (ring2*)((u8*)Ring + sizeof(ring2) + (sizeof(v2) * Ring->NumPoints));
    }
    return Ring;
}

inline ring3*
GetRing(wkb_polygon3* Polygon, usz TargetIdx)
{
    ring3* Ring = (ring3*)&Polygon[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Ring = (ring3*)((u8*)Ring + sizeof(ring3) + (sizeof(v3) * Ring->NumPoints));
    }
    return Ring;
}

inline ring4*
GetRing(wkb_polygon4* Polygon, usz TargetIdx)
{
    ring4* Ring = (ring4*)&Polygon[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Ring = (ring4*)((u8*)Ring + sizeof(ring4) + (sizeof(v4) * Ring->NumPoints));
    }
    return Ring;
}

inline wkb_polygon2*
GetPolygon(wkb_polyhedron2* Mesh, usz TargetIdx)
{
    wkb_polygon2* Polygon = (wkb_polygon2*)&Mesh[1];
	for (usz Count = 0; Count < TargetIdx; Count++)
	{
        Polygon = (wkb_polygon2*)GetRing(Polygon, Polygon->NumRings);
	}
    return Polygon;
}

inline wkb_polygon3*
GetPolygon(wkb_polyhedron3* Mesh, usz TargetIdx)
{
    wkb_polygon3* Polygon = (wkb_polygon3*)&Mesh[1];
	for (usz Count = 0; Count < TargetIdx; Count++)
	{
        Polygon = (wkb_polygon3*)GetRing(Polygon, Polygon->NumRings);
	}
    return Polygon;
}

inline wkb_polygon4*
GetPolygon(wkb_polyhedron4* Mesh, usz TargetIdx)
{
    wkb_polygon4* Polygon = (wkb_polygon4*)&Mesh[1];
	for (usz Count = 0; Count < TargetIdx; Count++)
	{
        Polygon = (wkb_polygon4*)GetRing(Polygon, Polygon->NumRings);
	}
    return Polygon;
}

inline wkb_triangle2*
GetTriangle(wkb_tin2* TIN, usz TargetIdx)
{
    wkb_triangle2* Triangle = (wkb_triangle2*)&TIN[1];
    usz TriangleSize = sizeof(wkb_triangle2) + sizeof(ring2) + (sizeof(v2) * 4);
    return (wkb_triangle2*)((u8*)Triangle + (TriangleSize * TargetIdx));
}

inline wkb_triangle3*
GetTriangle(wkb_tin3* TIN, usz TargetIdx)
{
    wkb_triangle3* Triangle = (wkb_triangle3*)&TIN[1];
    usz TriangleSize = sizeof(wkb_triangle3) + sizeof(ring3) + (sizeof(v3) * 4);
    return (wkb_triangle3*)((u8*)Triangle + (TriangleSize * TargetIdx));
}

inline wkb_triangle4*
GetTriangle(wkb_tin4* TIN, usz TargetIdx)
{
    wkb_triangle4* Triangle = (wkb_triangle4*)&TIN[1];
    usz TriangleSize = sizeof(wkb_triangle4) + sizeof(ring4) + (sizeof(v4) * 4);
    return (wkb_triangle4*)((u8*)Triangle + (TriangleSize * TargetIdx));
}

inline wkb_point2*
GetPoint(wkb_multipoint2* MultiPoint, usz TargetIdx)
{
    wkb_point2* Point = (wkb_point2*)&MultiPoint[1];
    return Point + TargetIdx;
}

inline wkb_point3*
GetPoint(wkb_multipoint3* MultiPoint, usz TargetIdx)
{
    wkb_point3* Point = (wkb_point3*)&MultiPoint[1];
    return Point + TargetIdx;
}

inline wkb_point4*
GetPoint(wkb_multipoint4* MultiPoint, usz TargetIdx)
{
    wkb_point4* Point = (wkb_point4*)&MultiPoint[1];
    return Point + TargetIdx;
}

inline wkb_linestring2*
GetLinestring(wkb_multilinestring2* MultiLinestring, usz TargetIdx)
{
    wkb_linestring2* Linestring = (wkb_linestring2*)&MultiLinestring[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Linestring = (wkb_linestring2*)GetVertex(Linestring, Linestring->NumPoints);
    }
    return Linestring;
}

inline wkb_linestring3*
GetLinestring(wkb_multilinestring3* MultiLinestring, usz TargetIdx)
{
    wkb_linestring3* Linestring = (wkb_linestring3*)&MultiLinestring[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Linestring = (wkb_linestring3*)GetVertex(Linestring, Linestring->NumPoints);
    }
    return Linestring;
}

inline wkb_linestring4*
GetLinestring(wkb_multilinestring4* MultiLinestring, usz TargetIdx)
{
    wkb_linestring4* Linestring = (wkb_linestring4*)&MultiLinestring[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Linestring = (wkb_linestring4*)GetVertex(Linestring, Linestring->NumPoints);
    }
    return Linestring;
}

inline wkb_polygon2*
GetPolygon(wkb_multipolygon2* MultiPolygon, usz TargetIdx)
{
    wkb_polygon2* Polygon = (wkb_polygon2*)&MultiPolygon[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Polygon = (wkb_polygon2*)GetRing(Polygon, Polygon->NumRings);
    }
    return Polygon;
}

inline wkb_polygon3*
GetPolygon(wkb_multipolygon3* MultiPolygon, usz TargetIdx)
{
    wkb_polygon3* Polygon = (wkb_polygon3*)&MultiPolygon[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Polygon = (wkb_polygon3*)GetRing(Polygon, Polygon->NumRings);
    }
    return Polygon;
}

inline wkb_polygon4*
GetPolygon(wkb_multipolygon4* MultiPolygon, usz TargetIdx)
{
    wkb_polygon4* Polygon = (wkb_polygon4*)&MultiPolygon[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Polygon = (wkb_polygon4*)GetRing(Polygon, Polygon->NumRings);
    }
    return Polygon;
}

// OBS(roberto): Internal function that get used in multiple places in the code.

internal void*
_AdvanceToNextGeometry2(void* Geometry)
{
    switch (((wkb_geometry2*)Geometry)->Header.WkbType)
    {
        case Wkb_Point:
        {
            Geometry = (u8*)Geometry + sizeof(wkb_geometry2);
        } break;
        
        case Wkb_Linestring:
        {
            wkb_linestring2* Linestring = (wkb_linestring2*)Geometry; 
            Geometry = GetVertex(Linestring, Linestring->NumPoints);
        } break;
        
        case Wkb_Polygon:
        {
            wkb_polygon2* Polygon = (wkb_polygon2*)Geometry;
            Geometry = GetRing(Polygon, Polygon->NumRings);
        } break;
        
        case Wkb_Triangle:
        {
            Geometry = (u8*)Geometry + sizeof(wkb_triangle2) + sizeof(ring2) + (sizeof(v2) * 4);
        } break;
        
        case Wkb_PolyhedralSurface:
        {
            wkb_polyhedron2* Mesh = (wkb_polyhedron2*)Geometry;
            Geometry = GetPolygon(Mesh, Mesh->NumPolygons);
        } break;
        
        case Wkb_TIN:
        {
            wkb_tin2* TIN = (wkb_tin2*)Geometry;
            Geometry = GetTriangle(TIN, TIN->NumPolygons);
        } break;
        
        case Wkb_MultiPoint:
        {
            wkb_multipoint2* MultiPoint = (wkb_multipoint2*)Geometry;
            Geometry = GetPoint(MultiPoint, MultiPoint->NumPoints);
        } break;
        
        case Wkb_MultiLinestring:
        {
            wkb_multilinestring2* MultiLinestring = (wkb_multilinestring2*)Geometry;
            Geometry = GetLinestring(MultiLinestring, MultiLinestring->NumLinestrings);
        } break;
        
        case Wkb_MultiPolygon:
        {
            wkb_multipolygon2* MultiPolygon = (wkb_multipolygon2*)Geometry;
            Geometry = GetPolygon(MultiPolygon, MultiPolygon->NumPolygons);
        } break;
        
        case Wkb_GeometryCollection:
        {
            wkb_collection2* Collection = (wkb_collection2*)Geometry;
            Geometry = GetGeometry(Collection, Collection->NumGeometries);
        } break;
        
        default:
        {
            Geometry = &gNullHeader;
        }
    }
    return Geometry;
}

inline wkb_geometry2*
GetGeometry(wkb_collection2* Collection, usz TargetIdx)
{
    void* Geometry = (void*)&Collection[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Geometry = _AdvanceToNextGeometry2(Geometry);
    }
    return (wkb_geometry2*)Geometry;
}

// OBS(roberto): Internal function that get used in multiple places in the code.

internal void*
_AdvanceToNextGeometry3(void* Geometry)
{
    switch (((wkb_geometry3*)Geometry)->Header.WkbType)
    {
        case Wkb_PointZ:
        case Wkb_PointM:
        {
            Geometry = (u8*)Geometry + sizeof(wkb_geometry3);
        } break;
        
        case Wkb_LinestringZ:
        case Wkb_LinestringM:
        {
            wkb_linestring3* Linestring = (wkb_linestring3*)Geometry; 
            Geometry = GetVertex(Linestring, Linestring->NumPoints);
        } break;
        
        case Wkb_PolygonZ:
        case Wkb_PolygonM:
        {
            wkb_polygon3* Polygon = (wkb_polygon3*)Geometry;
            Geometry = GetRing(Polygon, Polygon->NumRings);
        } break;
        
        case Wkb_TriangleZ:
        case Wkb_TriangleM:
        {
            Geometry = (u8*)Geometry + sizeof(wkb_triangle3) + sizeof(ring3) + (sizeof(v3) * 4);
        } break;
        
        case Wkb_PolyhedralSurfaceZ:
        case Wkb_PolyhedralSurfaceM:
        {
            wkb_polyhedron3* Mesh = (wkb_polyhedron3*)Geometry;
            Geometry = GetPolygon(Mesh, Mesh->NumPolygons);
        } break;
        
        case Wkb_TINZ:
        case Wkb_TINM:
        {
            wkb_tin3* TIN = (wkb_tin3*)Geometry;
            Geometry = GetTriangle(TIN, TIN->NumPolygons);
        } break;
        
        case Wkb_MultiPointZ:
        case Wkb_MultiPointM:
        {
            wkb_multipoint3* MultiPoint = (wkb_multipoint3*)Geometry;
            Geometry = GetPoint(MultiPoint, MultiPoint->NumPoints);
        } break;
        
        case Wkb_MultiLinestringZ:
        case Wkb_MultiLinestringM:
        {
            wkb_multilinestring3* MultiLinestring = (wkb_multilinestring3*)Geometry;
            Geometry = GetLinestring(MultiLinestring, MultiLinestring->NumLinestrings);
        } break;
        
        case Wkb_MultiPolygonZ:
        case Wkb_MultiPolygonM:
        {
            wkb_multipolygon3* MultiPolygon = (wkb_multipolygon3*)Geometry;
            Geometry = GetPolygon(MultiPolygon, MultiPolygon->NumPolygons);
        } break;
        
        case Wkb_GeometryCollectionZ:
        case Wkb_GeometryCollectionM:
        {
            wkb_collection3* Collection = (wkb_collection3*)Geometry;
            Geometry = GetGeometry(Collection, Collection->NumGeometries);
        } break;
        
        default:
        {
            Geometry = &gNullHeader;
        }
    }
    return Geometry;
}

inline wkb_geometry3*
GetGeometry(wkb_collection3* Collection, usz TargetIdx)
{
    void* Geometry = (void*)&Collection[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Geometry = _AdvanceToNextGeometry3(Geometry);
    }
    return (wkb_geometry3*)Geometry;
}

internal void*
_AdvanceToNextGeometry4(void* Geometry)
{
    switch (((wkb_geometry4*)Geometry)->Header.WkbType)
    {
        case Wkb_PointZM:
        {
            Geometry = (u8*)Geometry + sizeof(wkb_geometry4);
        } break;
        
        case Wkb_LinestringZM:
        {
            wkb_linestring4* Linestring = (wkb_linestring4*)Geometry; 
            Geometry = GetVertex(Linestring, Linestring->NumPoints);
        } break;
        
        case Wkb_PolygonZM:
        {
            wkb_polygon4* Polygon = (wkb_polygon4*)Geometry;
            Geometry = GetRing(Polygon, Polygon->NumRings);
        } break;
        
        case Wkb_TriangleZM:
        {
            Geometry = (u8*)Geometry + sizeof(wkb_triangle4) + sizeof(ring4) + (sizeof(v4) * 4);
        } break;
        
        case Wkb_PolyhedralSurfaceZM:
        {
            wkb_polyhedron4* Mesh = (wkb_polyhedron4*)Geometry;
            Geometry = GetPolygon(Mesh, Mesh->NumPolygons);
        } break;
        
        case Wkb_TINZM:
        {
            wkb_tin4* TIN = (wkb_tin4*)Geometry;
            Geometry = GetTriangle(TIN, TIN->NumPolygons);
        } break;
        
        case Wkb_MultiPointZM:
        {
            wkb_multipoint4* MultiPoint = (wkb_multipoint4*)Geometry;
            Geometry = GetPoint(MultiPoint, MultiPoint->NumPoints);
        } break;
        
        case Wkb_MultiLinestringZM:
        {
            wkb_multilinestring4* MultiLinestring = (wkb_multilinestring4*)Geometry;
            Geometry = GetLinestring(MultiLinestring, MultiLinestring->NumLinestrings);
        } break;
        
        case Wkb_MultiPolygonZM:
        {
            wkb_multipolygon4* MultiPolygon = (wkb_multipolygon4*)Geometry;
            Geometry = GetPolygon(MultiPolygon, MultiPolygon->NumPolygons);
        } break;
        
        case Wkb_GeometryCollectionZM:
        {
            wkb_collection4* Collection = (wkb_collection4*)Geometry;
            Geometry = GetGeometry(Collection, Collection->NumGeometries);
        } break;
        
        default:
        {
            Geometry = &gNullHeader;
        }
    }
    return Geometry;
}

inline wkb_geometry4*
GetGeometry(wkb_collection4* Collection, usz TargetIdx)
{
    void* Geometry = (void*)&Collection[1];
    for (usz Count = 0; Count < TargetIdx; Count++)
    {
        Geometry = _AdvanceToNextGeometry4(Geometry);
    }
    return (wkb_geometry4*)Geometry;
}

//=================================
// Object size in bytes
//=================================

inline usz
GetRingSize(ring2* Ring)
{
    return sizeof(ring2) + (sizeof(v2) * Ring->NumPoints);
}

inline usz
GetRingSize(ring3* Ring)
{
    return sizeof(ring3) + (sizeof(v3) * Ring->NumPoints);
}

inline usz
GetRingSize(ring4* Ring)
{
    return sizeof(ring4) + (sizeof(v4) * Ring->NumPoints);
}

inline usz
GetLinestringSize(wkb_linestring2* Linestring)
{
    return sizeof(wkb_linestring2) + (sizeof(v2) * Linestring->NumPoints);
}

inline usz
GetLinestringSize(wkb_linestring3* Linestring)
{
    return sizeof(wkb_linestring3) + (sizeof(v3) * Linestring->NumPoints);
}

inline usz
GetLinestringSize(wkb_linestring4* Linestring)
{
    return sizeof(wkb_linestring4) + (sizeof(v4) * Linestring->NumPoints);
}

inline usz
GetPolygonSize(wkb_polygon2* Polygon)
{
    ring2* Ring = GetRing(Polygon, Polygon->NumRings);
    return (usz)Ring - (usz)Polygon;
}

inline usz
GetPolygonSize(wkb_polygon3* Polygon)
{
    ring3* Ring = GetRing(Polygon, Polygon->NumRings);
    return (usz)Ring - (usz)Polygon;
}

inline usz
GetPolygonSize(wkb_polygon4* Polygon)
{
    ring4* Ring = GetRing(Polygon, Polygon->NumRings);
    return (usz)Ring - (usz)Polygon;
}

inline usz
GetTriangleSize(wkb_triangle2* Triangle)
{
    return sizeof(wkb_triangle2) + sizeof(ring2) + (sizeof(v2) * 4);
}

inline usz
GetTriangleSize(wkb_triangle3* Triangle)
{
    return sizeof(wkb_triangle3) + sizeof(ring3) + (sizeof(v3) * 4);
}

inline usz
GetTriangleSize(wkb_triangle4* Triangle)
{
    return sizeof(wkb_triangle4) + sizeof(ring4) + (sizeof(v4) * 4);
}

inline usz
GetPolyhedronSize(wkb_polyhedron2* Mesh)
{
    wkb_polygon2* Polygon = GetPolygon(Mesh, Mesh->NumPolygons);
    return (usz)Polygon - (usz)Mesh;
}

inline usz
GetPolyhedronSize(wkb_polyhedron3* Mesh)
{
    wkb_polygon3* Polygon = GetPolygon(Mesh, Mesh->NumPolygons);
    return (usz)Polygon - (usz)Mesh;
}

inline usz
GetPolyhedronSize(wkb_polyhedron4* Mesh)
{
    wkb_polygon4* Polygon = GetPolygon(Mesh, Mesh->NumPolygons);
    return (usz)Polygon - (usz)Mesh;
}

inline usz
GetTINSize(wkb_tin2* TIN)
{
    wkb_triangle2* Triangle = GetTriangle(TIN, TIN->NumPolygons);
    return (usz)Triangle - (usz)TIN;
}

inline usz
GetTINSize(wkb_tin3* TIN)
{
    wkb_triangle3* Triangle = GetTriangle(TIN, TIN->NumPolygons);
    return (usz)Triangle - (usz)TIN;
}

inline usz
GetTINSize(wkb_tin4* TIN)
{
    wkb_triangle4* Triangle = GetTriangle(TIN, TIN->NumPolygons);
    return (usz)Triangle - (usz)TIN;
}

inline usz
GetMultiPointSize(wkb_multipoint2* MultiPoint)
{
    return sizeof(wkb_multipoint2) + (sizeof(wkb_point2) * MultiPoint->NumPoints);
}

inline usz
GetMultiPointSize(wkb_multipoint3* MultiPoint)
{
    return sizeof(wkb_multipoint3) + (sizeof(wkb_point3) * MultiPoint->NumPoints);
}

inline usz
GetMultiPointSize(wkb_multipoint4* MultiPoint)
{
    return sizeof(wkb_multipoint4) + (sizeof(wkb_point4) * MultiPoint->NumPoints);
}

inline usz
GetMultiLinestringSize(wkb_multilinestring2* MultiLinestring)
{
    wkb_linestring2* Linestring = GetLinestring(MultiLinestring, MultiLinestring->NumLinestrings);
    return (usz)Linestring - (usz)MultiLinestring;
}

inline usz
GetMultiLinestringSize(wkb_multilinestring3* MultiLinestring)
{
    wkb_linestring3* Linestring = GetLinestring(MultiLinestring, MultiLinestring->NumLinestrings);
    return (usz)Linestring - (usz)MultiLinestring;
}

inline usz
GetMultiLinestringSize(wkb_multilinestring4* MultiLinestring)
{
    wkb_linestring4* Linestring = GetLinestring(MultiLinestring, MultiLinestring->NumLinestrings);
    return (usz)Linestring - (usz)MultiLinestring;
}

inline usz
GetMultiPolygonSize(wkb_multipolygon2* MultiPolygon)
{
    wkb_polygon2* Polygon = GetPolygon(MultiPolygon, MultiPolygon->NumPolygons);
    return (usz)Polygon - (usz)MultiPolygon;
}

inline usz
GetMultiPolygonSize(wkb_multipolygon3* MultiPolygon)
{
    wkb_polygon3* Polygon = GetPolygon(MultiPolygon, MultiPolygon->NumPolygons);
    return (usz)Polygon - (usz)MultiPolygon;
}

inline usz
GetMultiPolygonSize(wkb_multipolygon4* MultiPolygon)
{
    wkb_polygon4* Polygon = GetPolygon(MultiPolygon, MultiPolygon->NumPolygons);
    return (usz)Polygon - (usz)MultiPolygon;
}

inline usz
GetGeometrySize(wkb_geometry2* Geometry)
{
    wkb_geometry2* NextGeometry = (wkb_geometry2*)_AdvanceToNextGeometry2(Geometry);
    return (usz)NextGeometry - (usz)Geometry;
}

inline usz
GetGeometrySize(wkb_geometry3* Geometry)
{
    wkb_geometry3* NextGeometry = (wkb_geometry3*)_AdvanceToNextGeometry3(Geometry);
    return (usz)NextGeometry - (usz)Geometry;
}

inline usz
GetGeometrySize(wkb_geometry4* Geometry)
{
    wkb_geometry4* NextGeometry = (wkb_geometry4*)_AdvanceToNextGeometry4(Geometry);
    return (usz)NextGeometry - (usz)Geometry;
}

inline usz
GetCollectionSize(wkb_collection2* Collection)
{
    wkb_geometry2* Geometry = GetGeometry(Collection, Collection->NumGeometries);
    return (usz)Geometry - (usz)Collection;
}

inline usz
GetCollectionSize(wkb_collection3* Collection)
{
    wkb_geometry3* Geometry = GetGeometry(Collection, Collection->NumGeometries);
    return (usz)Geometry - (usz)Collection;
}

inline usz
GetCollectionSize(wkb_collection4* Collection)
{
    wkb_geometry4* Geometry = GetGeometry(Collection, Collection->NumGeometries);
    return (usz)Geometry - (usz)Collection;
}

//=================================
// Iterate through members
//=================================

inline wkb_iter2
WkbIter(wkb_polygon2* Polygon)
{
    wkb_iter2 Result = { 0, Polygon->NumRings, GetRing(Polygon, 0) };
    return Result;
}

inline wkb_iter3
WkbIter(wkb_polygon3* Polygon)
{
    wkb_iter3 Result = { 0, Polygon->NumRings, GetRing(Polygon, 0) };
    return Result;
}

inline wkb_iter4
WkbIter(wkb_polygon4* Polygon)
{
    wkb_iter4 Result = { 0, Polygon->NumRings, GetRing(Polygon, 0) };
    return Result;
}

inline wkb_iter2
WkbIter(wkb_multilinestring2* MultiLinestring)
{
    wkb_iter2 Result = { 0, MultiLinestring->NumLinestrings, GetLinestring(MultiLinestring, 0) };
    return Result;
}

inline wkb_iter3
WkbIter(wkb_multilinestring3* MultiLinestring)
{
    wkb_iter3 Result = { 0, MultiLinestring->NumLinestrings, GetLinestring(MultiLinestring, 0) };
    return Result;
}

inline wkb_iter4
WkbIter(wkb_multilinestring4* MultiLinestring)
{
    wkb_iter4 Result = { 0, MultiLinestring->NumLinestrings, GetLinestring(MultiLinestring, 0) };
    return Result;
}

inline wkb_iter2
WkbIter(wkb_multipolygon2* MultiPolygon)
{
    wkb_iter2 Result = { 0, MultiPolygon->NumPolygons, GetPolygon(MultiPolygon, 0) };
    return Result;
}

inline wkb_iter3
WkbIter(wkb_multipolygon3* MultiPolygon)
{
    wkb_iter3 Result = { 0, MultiPolygon->NumPolygons, GetPolygon(MultiPolygon, 0) };
    return Result;
}

inline wkb_iter4
WkbIter(wkb_multipolygon4* MultiPolygon)
{
    wkb_iter4 Result = { 0, MultiPolygon->NumPolygons, GetPolygon(MultiPolygon, 0) };
    return Result;
}

inline wkb_iter2
WkbIter(wkb_polyhedron2* Polyhedron)
{
    wkb_iter2 Result = { 0, Polyhedron->NumPolygons, GetPolygon(Polyhedron, 0) };
    return Result;
}

inline wkb_iter3
WkbIter(wkb_polyhedron3* Polyhedron)
{
    wkb_iter3 Result = { 0, Polyhedron->NumPolygons, GetPolygon(Polyhedron, 0) };
    return Result;
}

inline wkb_iter4
WkbIter(wkb_polyhedron4* Polyhedron)
{
    wkb_iter4 Result = { 0, Polyhedron->NumPolygons, GetPolygon(Polyhedron, 0) };
    return Result;
}

inline wkb_iter2
WkbIter(wkb_collection2* Collection)
{
    wkb_iter2 Result = { 0, Collection->NumGeometries, GetGeometry(Collection, 0) };
    return Result;
}

inline wkb_iter3
WkbIter(wkb_collection3* Collection)
{
    wkb_iter3 Result = { 0, Collection->NumGeometries, GetGeometry(Collection, 0) };
    return Result;
}

inline wkb_iter4
WkbIter(wkb_collection4* Collection)
{
    wkb_iter4 Result = { 0, Collection->NumGeometries, GetGeometry(Collection, 0) };
    return Result;
}

inline ring2*
GetNextRing(wkb_iter2* Iter)
{
    ring2* Ring = (ring2*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Ring + GetRingSize(Ring)) * IsLastElement);
    return (ring2*)Iter->Geom;
}

inline ring3*
GetNextRing(wkb_iter3* Iter)
{
    ring3* Ring = (ring3*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Ring + GetRingSize(Ring)) * IsLastElement);
    return (ring3*)Iter->Geom;
}

inline ring4*
GetNextRing(wkb_iter4* Iter)
{
    ring4* Ring = (ring4*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Ring + GetRingSize(Ring)) * IsLastElement);
    return (ring4*)Iter->Geom;
}

inline wkb_linestring2*
GetNextLinestring(wkb_iter2* Iter)
{
    wkb_linestring2* Linestring = (wkb_linestring2*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Linestring + GetLinestringSize(Linestring)) * IsLastElement);
    return (wkb_linestring2*)Iter->Geom;
}

inline wkb_linestring3*
GetNextLinestring(wkb_iter3* Iter)
{
    wkb_linestring3* Linestring = (wkb_linestring3*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Linestring + GetLinestringSize(Linestring)) * IsLastElement);
    return (wkb_linestring3*)Iter->Geom;
}

inline wkb_linestring4*
GetNextLinestring(wkb_iter4* Iter)
{
    wkb_linestring4* Linestring = (wkb_linestring4*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Linestring + GetLinestringSize(Linestring)) * IsLastElement);
    return (wkb_linestring4*)Iter->Geom;
}

inline wkb_polygon2*
GetNextPolygon(wkb_iter2* Iter)
{
    wkb_polygon2* Polygon = (wkb_polygon2*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Polygon + GetPolygonSize(Polygon)) * IsLastElement);
    return (wkb_polygon2*)Iter->Geom;
}

inline wkb_polygon3*
GetNextPolygon(wkb_iter3* Iter)
{
    wkb_polygon3* Polygon = (wkb_polygon3*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Polygon + GetPolygonSize(Polygon)) * IsLastElement);
    return (wkb_polygon3*)Iter->Geom;
}

inline wkb_polygon4*
GetNextPolygon(wkb_iter4* Iter)
{
    wkb_polygon4* Polygon = (wkb_polygon4*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Polygon + GetPolygonSize(Polygon)) * IsLastElement);
    return (wkb_polygon4*)Iter->Geom;
}

inline wkb_triangle2*
GetNextTriangle(wkb_iter2* Iter)
{
    wkb_triangle2* Triangle = (wkb_triangle2*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Triangle + GetTriangleSize(Triangle)) * IsLastElement);
    return (wkb_triangle2*)Iter->Geom;
}

inline wkb_triangle3*
GetNextTriangle(wkb_iter3* Iter)
{
    wkb_triangle3* Triangle = (wkb_triangle3*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Triangle + GetTriangleSize(Triangle)) * IsLastElement);
    return (wkb_triangle3*)Iter->Geom;
}

inline wkb_triangle4*
GetNextTriangle(wkb_iter4* Iter)
{
    wkb_triangle4* Triangle = (wkb_triangle4*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Triangle + GetTriangleSize(Triangle)) * IsLastElement);
    return (wkb_triangle4*)Iter->Geom;
}

inline wkb_geometry2*
GetNextGeometry(wkb_iter2* Iter)
{
    wkb_geometry2* Geometry = (wkb_geometry2*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Geometry + GetGeometrySize(Geometry)) * IsLastElement);
    return (wkb_geometry2*)Iter->Geom;
}

inline wkb_geometry3*
GetNextGeometry(wkb_iter3* Iter)
{
    wkb_geometry3* Geometry = (wkb_geometry3*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Geometry + GetGeometrySize(Geometry)) * IsLastElement);
    return (wkb_geometry3*)Iter->Geom;
}

inline wkb_geometry4*
GetNextGeometry(wkb_iter4* Iter)
{
    wkb_geometry4* Geometry = (wkb_geometry4*)(Iter->Geom);
    i32 IsLastElement = (++Iter->CurrentIdx < Iter->NumElements);
    Iter->Geom = (void*)(((isz)Geometry + GetGeometrySize(Geometry)) * IsLastElement);
    return (wkb_geometry4*)Iter->Geom;
}

//=================================
// Get BBox functions
//=================================

inline bbox2
GetBBox(wkb_point2* Point)
{
    bbox2 Result = BBox2(Point->Point, Point->Point);
    return Result;
}

inline bbox3
GetBBox(wkb_point3* Point)
{
    bbox3 Result = BBox3(Point->Point, Point->Point);
    return Result;
}

inline bbox4
GetBBox(wkb_point4* Point)
{
    bbox4 Result = BBox4(Point->Point, Point->Point);
    return Result;
}

inline bbox2
GetBBox(wkb_linestring2* Linestring)
{
    bbox2 Result = BBox2(DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX);
    for (v2* Vertex = GetVertex(Linestring, 0), *EndOfGeom = GetVertex(Linestring, Linestring->NumPoints)
         ; Vertex < EndOfGeom
         ; Vertex++)
    {
        Result = Merge(Result, BBox2(*Vertex, *Vertex));
    }
    return Result;
}

inline bbox3
GetBBox(wkb_linestring3* Linestring)
{
    bbox3 Result = BBox3(DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    for (v3* Vertex = GetVertex(Linestring, 0), *EndOfGeom = GetVertex(Linestring, Linestring->NumPoints)
         ; Vertex < EndOfGeom
         ; Vertex++)
    {
        Result = Merge(Result, BBox3(*Vertex, *Vertex));
    }
    return Result;
}

inline bbox4
GetBBox(wkb_linestring4* Linestring)
{
    bbox4 Result = BBox4(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    for (v4* Vertex = GetVertex(Linestring, 0), *EndOfGeom = GetVertex(Linestring, Linestring->NumPoints)
         ; Vertex < EndOfGeom
         ; Vertex++)
    {
        Result = Merge(Result, BBox4(*Vertex, *Vertex));
    }
    return Result;
}

inline bbox2
GetBBox(wkb_polygon2* Polygon)
{
    bbox2 Result = BBox2(DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX);
    ring2* Ring = (ring2*)&Polygon[1];
    for (v2* Vertex = GetVertex(Ring, 0), *EndOfGeom = GetVertex(Ring, Ring->NumPoints)
         ; Vertex < EndOfGeom
         ; Vertex++)
    {
        Result = Merge(Result, BBox2(*Vertex, *Vertex));
    }
    return Result;
}

inline bbox3
GetBBox(wkb_polygon3* Polygon)
{
    bbox3 Result = BBox3(DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    ring3* Ring = (ring3*)&Polygon[1];
    for (v3* Vertex = GetVertex(Ring, 0), *EndOfGeom = GetVertex(Ring, Ring->NumPoints)
         ; Vertex < EndOfGeom
         ; Vertex++)
    {
        Result = Merge(Result, BBox3(*Vertex, *Vertex));
    }
    return Result;
}

inline bbox4
GetBBox(wkb_polygon4* Polygon)
{
    bbox4 Result = BBox4(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    ring4* Ring = (ring4*)&Polygon[1];
    for (v4* Vertex = GetVertex(Ring, 0), *EndOfGeom = GetVertex(Ring, Ring->NumPoints)
         ; Vertex < EndOfGeom
         ; Vertex++)
    {
        Result = Merge(Result, BBox4(*Vertex, *Vertex));
    }
    return Result;
}

inline bbox2
GetBBox(wkb_polyhedron2* Polyhedron)
{
    bbox2 Result = BBox2(DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter2 Iter = WkbIter(Polyhedron);
    for (wkb_polygon2* Polygon = (wkb_polygon2*)Iter.Geom; Polygon; Polygon = GetNextPolygon(&Iter))
    {
        Result = Merge(Result, GetBBox(Polygon));
    }
    return Result;
}

inline bbox3
GetBBox(wkb_polyhedron3* Polyhedron)
{
    bbox3 Result = BBox3(DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter3 Iter = WkbIter(Polyhedron);
    for (wkb_polygon3* Polygon = (wkb_polygon3*)Iter.Geom; Polygon; Polygon = GetNextPolygon(&Iter))
    {
        Result = Merge(Result, GetBBox(Polygon));
    }
    return Result;
}

inline bbox4
GetBBox(wkb_polyhedron4* Polyhedron)
{
    bbox4 Result = BBox4(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter4 Iter = WkbIter(Polyhedron);
    for (wkb_polygon4* Polygon = (wkb_polygon4*)Iter.Geom; Polygon; Polygon = GetNextPolygon(&Iter))
    {
        Result = Merge(Result, GetBBox(Polygon));
    }
    return Result;
}

inline bbox2
GetBBox(wkb_multipoint2* MultiPoint)
{
    bbox2 Result = BBox2(DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX);
    for (wkb_point2* Point = GetPoint(MultiPoint, 0), *EndOfGeom = GetPoint(MultiPoint, MultiPoint->NumPoints)
         ; Point < EndOfGeom
         ; Point++)
    {
        Result = Merge(Result, BBox2(Point->Point, Point->Point));
    }
    return Result;
}

inline bbox3
GetBBox(wkb_multipoint3* MultiPoint)
{
    bbox3 Result = BBox3(DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    for (wkb_point3* Point = GetPoint(MultiPoint, 0), *EndOfGeom = GetPoint(MultiPoint, MultiPoint->NumPoints)
         ; Point < EndOfGeom
         ; Point++)
    {
        Result = Merge(Result, BBox3(Point->Point, Point->Point));
    }
    return Result;
}

inline bbox4
GetBBox(wkb_multipoint4* MultiPoint)
{
    bbox4 Result = BBox4(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    for (wkb_point4* Point = GetPoint(MultiPoint, 0), *EndOfGeom = GetPoint(MultiPoint, MultiPoint->NumPoints)
         ; Point < EndOfGeom
         ; Point++)
    {
        Result = Merge(Result, BBox4(Point->Point, Point->Point));
    }
    return Result;
}

inline bbox2
GetBBox(wkb_multilinestring2* MultiLinestring)
{
    bbox2 Result = BBox2(DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter2 Iter = WkbIter(MultiLinestring);
    for (wkb_linestring2* Linestring = (wkb_linestring2*)Iter.Geom; Linestring; Linestring = GetNextLinestring(&Iter))
    {
        Result = Merge(Result, GetBBox(Linestring));
    }
    return Result;
}

inline bbox3
GetBBox(wkb_multilinestring3* MultiLinestring)
{
    bbox3 Result = BBox3(DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter3 Iter = WkbIter(MultiLinestring);
    for (wkb_linestring3* Linestring = (wkb_linestring3*)Iter.Geom; Linestring; Linestring = GetNextLinestring(&Iter))
    {
        Result = Merge(Result, GetBBox(Linestring));
    }
    return Result;
}

inline bbox4
GetBBox(wkb_multilinestring4* MultiLinestring)
{
    bbox4 Result = BBox4(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter4 Iter = WkbIter(MultiLinestring);
    for (wkb_linestring4* Linestring = (wkb_linestring4*)Iter.Geom; Linestring; Linestring = GetNextLinestring(&Iter))
    {
        Result = Merge(Result, GetBBox(Linestring));
    }
    return Result;
}

inline bbox2
GetBBox(wkb_multipolygon2* MultiPolygon)
{
    bbox2 Result = BBox2(DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter2 Iter = WkbIter(MultiPolygon);
    for (wkb_polygon2* Polygon = (wkb_polygon2*)Iter.Geom; Polygon; Polygon = GetNextPolygon(&Iter))
    {
        Result = Merge(Result, GetBBox(Polygon));
    }
    return Result;
}

inline bbox3
GetBBox(wkb_multipolygon3* MultiPolygon)
{
    bbox3 Result = BBox3(DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter3 Iter = WkbIter(MultiPolygon);
    for (wkb_polygon3* Polygon = (wkb_polygon3*)Iter.Geom; Polygon; Polygon = GetNextPolygon(&Iter))
    {
        Result = Merge(Result, GetBBox(Polygon));
    }
    return Result;
}

inline bbox4
GetBBox(wkb_multipolygon4* MultiPolygon)
{
    bbox4 Result = BBox4(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter4 Iter = WkbIter(MultiPolygon);
    for (wkb_polygon4* Polygon = (wkb_polygon4*)Iter.Geom; Polygon; Polygon = GetNextPolygon(&Iter))
    {
        Result = Merge(Result, GetBBox(Polygon));
    }
    return Result;
}

inline bbox2
GetBBox(wkb_collection2* Collection)
{
    bbox2 Result = BBox2(DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter2 Iter = WkbIter(Collection);
    for (wkb_geometry2* Geometry = (wkb_geometry2*)Iter.Geom; Geometry; Geometry = GetNextGeometry(&Iter))
    {
        bbox2 BBox = {0};
        switch (Geometry->Header.WkbType)
        {
            case Wkb_Point: BBox = GetBBox(&Geometry->Point); break;
            case Wkb_Linestring: BBox = GetBBox(&Geometry->Linestring); break;
            case Wkb_Polygon:
            case Wkb_Triangle: BBox = GetBBox(&Geometry->Polygon); break;
            case Wkb_PolyhedralSurface:
            case Wkb_TIN: BBox = GetBBox(&Geometry->Polyhedron); break;
            case Wkb_MultiPoint: BBox = GetBBox(&Geometry->MultiPoint); break;
            case Wkb_MultiLinestring: BBox = GetBBox(&Geometry->MultiLinestring); break;
            case Wkb_MultiPolygon: BBox = GetBBox(&Geometry->MultiPolygon); break;
            case Wkb_GeometryCollection: BBox = GetBBox(&Geometry->Collection); break;
        }
        Result = Merge(Result, BBox);
    }
    return Result;
}

inline bbox3
GetBBox(wkb_collection3* Collection)
{
    bbox3 Result = BBox3(DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter3 Iter = WkbIter(Collection);
    for (wkb_geometry3* Geometry = (wkb_geometry3*)Iter.Geom; Geometry; Geometry = GetNextGeometry(&Iter))
    {
        bbox3 BBox = {0};
        switch (Geometry->Header.WkbType)
        {
            case Wkb_PointZ:
            case Wkb_PointM: BBox = GetBBox(&Geometry->Point); break;
            case Wkb_LinestringZ:
            case Wkb_LinestringM: BBox = GetBBox(&Geometry->Linestring); break;
            case Wkb_PolygonZ:
            case Wkb_PolygonM:
            case Wkb_TriangleZ:
            case Wkb_TriangleM: BBox = GetBBox(&Geometry->Polygon); break;
            case Wkb_PolyhedralSurfaceZ:
            case Wkb_PolyhedralSurfaceM:
            case Wkb_TINZ:
            case Wkb_TINM: BBox = GetBBox(&Geometry->Polyhedron); break;
            case Wkb_MultiPointZ:
            case Wkb_MultiPointM: BBox = GetBBox(&Geometry->MultiPoint); break;
            case Wkb_MultiLinestringZ:
            case Wkb_MultiLinestringM: BBox = GetBBox(&Geometry->MultiLinestring); break;
            case Wkb_MultiPolygonZ:
            case Wkb_MultiPolygonM: BBox = GetBBox(&Geometry->MultiPolygon); break;
            case Wkb_GeometryCollectionZ:
            case Wkb_GeometryCollectionM: BBox = GetBBox(&Geometry->Collection); break;
        }
        Result = Merge(Result, BBox);
    }
    return Result;
}

inline bbox4
GetBBox(wkb_collection4* Collection)
{
    bbox4 Result = BBox4(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX);
    wkb_iter4 Iter = WkbIter(Collection);
    for (wkb_geometry4* Geometry = (wkb_geometry4*)Iter.Geom; Geometry; Geometry = GetNextGeometry(&Iter))
    {
        bbox4 BBox = {0};
        switch (Geometry->Header.WkbType)
        {
            case Wkb_PointZM: BBox = GetBBox(&Geometry->Point); break;
            case Wkb_LinestringZM: BBox = GetBBox(&Geometry->Linestring); break;
            case Wkb_PolygonZM:
            case Wkb_TriangleZM: BBox = GetBBox(&Geometry->Polygon); break;
            case Wkb_PolyhedralSurfaceZM:
            case Wkb_TINZM: BBox = GetBBox(&Geometry->Polyhedron); break;
            case Wkb_MultiPointZM: BBox = GetBBox(&Geometry->MultiPoint); break;
            case Wkb_MultiLinestringZM: BBox = GetBBox(&Geometry->MultiLinestring); break;
            case Wkb_MultiPolygonZM: BBox = GetBBox(&Geometry->MultiPolygon); break;
            case Wkb_GeometryCollectionZM: BBox = GetBBox(&Geometry->Collection); break;
        }
        Result = Merge(Result, BBox);
    }
    return Result;
}

//=================================
// Add geom functions
//=================================

inline void
AddVertex(ring2* Ring, v2 Point)
{
    v2* Points = (v2*)&Ring[1];
    Points[Ring->NumPoints++] = Point;
}

inline void
AddVertex(ring3* Ring, v3 Point)
{
    v3* Points = (v3*)&Ring[1];
    Points[Ring->NumPoints++] = Point;
}

inline void
AddVertex(ring4* Ring, v4 Point)
{
    v4* Points = (v4*)&Ring[1];
    Points[Ring->NumPoints++] = Point;
}

inline void
AddVertex(wkb_linestring2* Linestring, v2 Point)
{
    v2* Points = (v2*)&Linestring[1];
    Points[Linestring->NumPoints++] = Point;
}

inline void
AddVertex(wkb_linestring3* Linestring, v3 Point)
{
    v3* Points = (v3*)&Linestring[1];
    Points[Linestring->NumPoints++] = Point;
}

inline void
AddVertex(wkb_linestring4* Linestring, v4 Point)
{
    v4* Points = (v4*)&Linestring[1];
    Points[Linestring->NumPoints++] = Point;
}

inline ring2*
AddRing(wkb_polygon2* Polygon)
{
    ring2* Ring = GetRing(Polygon, Polygon->NumRings++);
    Ring->NumPoints = 0;
    return Ring;
}

inline ring3*
AddRing(wkb_polygon3* Polygon)
{
    ring3* Ring = GetRing(Polygon, Polygon->NumRings++);
    Ring->NumPoints = 0;
    return Ring;
}

inline ring4*
AddRing(wkb_polygon4* Polygon)
{
    ring4* Ring = GetRing(Polygon, Polygon->NumRings++);
    Ring->NumPoints = 0;
    return Ring;
}

inline wkb_polygon2*
AddPolygon(wkb_polyhedron2* Mesh)
{
    void* Ptr = GetPolygon(Mesh, Mesh->NumPolygons++);
    return CreatePolygon(Ptr);
}

inline wkb_polygon3*
AddPolygon(wkb_polyhedron3* Mesh)
{
    void* Ptr = GetPolygon(Mesh, Mesh->NumPolygons++);
    return Mesh->Header.WkbType == Wkb_PolyhedralSurfaceZ
        ? CreatePolygonZ(Ptr) : CreatePolygonM(Ptr);
}

inline wkb_polygon4*
AddPolygon(wkb_polyhedron4* Mesh)
{
    void* Ptr = GetPolygon(Mesh, Mesh->NumPolygons++);
    return CreatePolygonZM(Ptr);
}

inline wkb_triangle2*
AddTriangle(wkb_tin2* TIN)
{
    void* Ptr = GetTriangle(TIN, TIN->NumPolygons++);
    return CreateTriangle(Ptr);
}

inline wkb_triangle3*
AddTriangle(wkb_tin3* TIN)
{
    void* Ptr = GetTriangle(TIN, TIN->NumPolygons++);
    return TIN->Header.WkbType == Wkb_TINZ
        ? CreateTriangleZ(Ptr) : CreateTriangleM(Ptr);
}

inline wkb_triangle4*
AddTriangle(wkb_tin4* TIN)
{
    void* Ptr = GetTriangle(TIN, TIN->NumPolygons++);
    return CreateTriangleZM(Ptr);
}

inline wkb_point2*
AddPoint(wkb_multipoint2* MultiPoint, v2 Vertex)
{
    void* Ptr = GetPoint(MultiPoint, MultiPoint->NumPoints++);
    return CreatePoint(Ptr, Vertex);
}

inline wkb_point3*
AddPoint(wkb_multipoint3* MultiPoint, v3 Vertex)
{
    void* Ptr = GetPoint(MultiPoint, MultiPoint->NumPoints++);
    return MultiPoint->Header.WkbType == Wkb_MultiPointZ
        ? CreatePointZ(Ptr, Vertex) : CreatePointM(Ptr, Vertex);
}

inline wkb_point4*
AddPoint(wkb_multipoint4* MultiPoint, v4 Vertex)
{
    void* Ptr = GetPoint(MultiPoint, MultiPoint->NumPoints++);
    return CreatePointZM(Ptr, Vertex);
}

inline wkb_linestring2*
AddLinestring(wkb_multilinestring2* MultiLinestring)
{
    void* Ptr = GetLinestring(MultiLinestring, MultiLinestring->NumLinestrings++);
    return CreateLinestring(Ptr);
}

inline wkb_linestring3*
AddLinestring(wkb_multilinestring3* MultiLinestring)
{
    void* Ptr = GetLinestring(MultiLinestring, MultiLinestring->NumLinestrings++);
    return MultiLinestring->Header.WkbType == Wkb_MultiLinestringZ
        ? CreateLinestringZ(Ptr) : CreateLinestringM(Ptr);
}

inline wkb_linestring4*
AddLinestring(wkb_multilinestring4* MultiLinestring)
{
    void* Ptr = GetLinestring(MultiLinestring, MultiLinestring->NumLinestrings++);
    return CreateLinestringZM(Ptr);
}

inline wkb_polygon2*
AddPolygon(wkb_multipolygon2* MultiPolygon)
{
    void* Ptr = GetPolygon(MultiPolygon, MultiPolygon->NumPolygons++);
    return CreatePolygon(Ptr);
}

inline wkb_polygon3*
AddPolygon(wkb_multipolygon3* MultiPolygon)
{
    void* Ptr = GetPolygon(MultiPolygon, MultiPolygon->NumPolygons++);
    return MultiPolygon->Header.WkbType == Wkb_MultiPolygonZ
        ? CreatePolygonZ(Ptr) : CreatePolygonM(Ptr);
}

inline wkb_polygon4*
AddPolygon(wkb_multipolygon4* MultiPolygon)
{
    void* Ptr = GetPolygon(MultiPolygon, MultiPolygon->NumPolygons++);
    return CreatePolygonZM(Ptr);
}

inline wkb_point2*
AddPoint(wkb_collection2* Collection, v2 Vertex)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreatePoint(Ptr, Vertex);
}

inline wkb_point3*
AddPoint(wkb_collection3* Collection, v3 Vertex)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return Collection->Header.WkbType == Wkb_GeometryCollectionZ
        ? CreatePointZ(Ptr, Vertex) : CreatePointM(Ptr, Vertex);
}

inline wkb_point4*
AddPoint(wkb_collection4* Collection, v4 Vertex)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreatePointZM(Ptr, Vertex);
}

inline wkb_linestring2*
AddLinestring(wkb_collection2* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateLinestring(Ptr);
}

inline wkb_linestring3*
AddLinestring(wkb_collection3* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return Collection->Header.WkbType == Wkb_GeometryCollectionZ
        ? CreateLinestringZ(Ptr) : CreateLinestringM(Ptr);
}

inline wkb_linestring4*
AddLinestring(wkb_collection4* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateLinestringZM(Ptr);
}

inline wkb_polygon2*
AddPolygon(wkb_collection2* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreatePolygon(Ptr);
}

inline wkb_polygon3*
AddPolygon(wkb_collection3* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return Collection->Header.WkbType == Wkb_GeometryCollectionZ
        ? CreatePolygonZ(Ptr) : CreatePolygonM(Ptr);
}

inline wkb_polygon4*
AddPolygon(wkb_collection4* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreatePolygonZM(Ptr);
}

inline wkb_triangle2*
AddTriangle(wkb_collection2* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateTriangle(Ptr);
}

inline wkb_triangle3*
AddTriangle(wkb_collection3* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return Collection->Header.WkbType == Wkb_GeometryCollectionZ
        ? CreateTriangleZ(Ptr) : CreateTriangleM(Ptr);
}

inline wkb_triangle4*
AddTriangle(wkb_collection4* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateTriangleZM(Ptr);
}

inline wkb_polyhedron2*
AddPolyhedron(wkb_collection2* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreatePolyhedron(Ptr);
}

inline wkb_polyhedron3*
AddPolyhedron(wkb_collection3* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return Collection->Header.WkbType == Wkb_GeometryCollectionZ
        ? CreatePolyhedronZ(Ptr) : CreatePolyhedronM(Ptr);
}

inline wkb_polyhedron4*
AddPolyhedron(wkb_collection4* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreatePolyhedronZM(Ptr);
}

inline wkb_tin2*
AddTIN(wkb_collection2* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateTIN(Ptr);
}

inline wkb_tin3*
AddTIN(wkb_collection3* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return Collection->Header.WkbType == Wkb_GeometryCollectionZ
        ? CreateTINZ(Ptr) : CreateTINM(Ptr);
}

inline wkb_tin4*
AddTIN(wkb_collection4* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateTINZM(Ptr);
}

inline wkb_multipoint2*
AddMultiPoint(wkb_collection2* Collection, v2 Vertex)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateMultiPoint(Ptr);
}

inline wkb_multipoint3*
AddMultiPoint(wkb_collection3* Collection, v3 Vertex)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return Collection->Header.WkbType == Wkb_GeometryCollectionZ
        ? CreateMultiPointZ(Ptr) : CreateMultiPointM(Ptr);
}

inline wkb_multipoint4*
AddMultiPoint(wkb_collection4* Collection, v4 Vertex)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateMultiPointZM(Ptr);
}

inline wkb_multilinestring2*
AddMultiLinestring(wkb_collection2* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateMultiLinestring(Ptr);
}

inline wkb_multilinestring3*
AddMultiLinestring(wkb_collection3* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return Collection->Header.WkbType == Wkb_GeometryCollectionZ
        ? CreateMultiLinestringZ(Ptr) : CreateMultiLinestringM(Ptr);
}

inline wkb_multilinestring4*
AddMultiLinestring(wkb_collection4* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateMultiLinestringZM(Ptr);
}

inline wkb_multipolygon2*
AddMultiPolygon(wkb_collection2* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateMultiPolygon(Ptr);
}

inline wkb_multipolygon3*
AddMultiPolygon(wkb_collection3* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return Collection->Header.WkbType == Wkb_GeometryCollectionZ
        ? CreateMultiPolygonZ(Ptr) : CreateMultiPolygonM(Ptr);
}

inline wkb_multipolygon4*
AddMultiPolygon(wkb_collection4* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateMultiPolygonZM(Ptr);
}

inline wkb_collection2*
AddCollection(wkb_collection2* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateCollection(Ptr);
}

inline wkb_collection3*
AddCollection(wkb_collection3* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return Collection->Header.WkbType == Wkb_GeometryCollectionZ
        ? CreateCollectionZ(Ptr) : CreateCollectionM(Ptr);
}

inline wkb_collection4*
AddCollection(wkb_collection4* Collection)
{
    void* Ptr = GetGeometry(Collection, Collection->NumGeometries++);
    return CreateCollectionZM(Ptr);
}

