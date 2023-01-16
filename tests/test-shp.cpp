#include "geotypes-shp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <varargs.h>

bool Error = false;
#define Test(Callback, ...) \
do { \
if (!Test##Callback(__VA_ARGS__)) { \
Error = true; \
printf(" [%3d] %-40s ERRO.\n", __LINE__, #Callback##"()"); } \
} while (0); \

struct file_read
{
    u8* Ptr[3]; // Shp, Shx, Dbf.
    i32 Size[3];
};

internal file_read
LoadSHP(char* BasePath)
{
    file_read Result = {0};
    usz BasePathSize = strlen(BasePath);
    
    char* Ext[3] = { ".shp", ".shx", ".dbf" };
    for (usz Idx = 0; Idx < ArrayCount(Ext); Idx++)
    {
        char FilePathBuf[MAX_PATH_SIZE] = {0};
        buffer FilePath = Buffer(FilePathBuf, 0, sizeof(FilePathBuf));
        AppendDataToBuffer(BasePath, BasePathSize, &FilePath);
        AppendDataToBuffer(Ext[Idx], 4, &FilePath);
        
        FILE* File = fopen(FilePathBuf, "rb");
        fseek(File, 0, SEEK_END);
        Result.Size[Idx] = ftell(File);
        fseek(File, 0, SEEK_SET);
        Result.Ptr[Idx] = (u8*)malloc(Result.Size[Idx]);
        fread(Result.Ptr[Idx], Result.Size[Idx], 1, File);
        fclose(File);
    }
    return Result;
}

internal void
PrintHex(char* Name, u8* Ptr, usz Size)
{
    fprintf(stdout, "%s:", Name);
    for (usz Count = 0; Count < Size; Count++)
    {
        if (Count % 8 == 0) fprintf(stdout, "\n");
        fprintf(stdout, "%2x", *Ptr++);
    }
    fprintf(stdout, "\n");
}

//
// Geom creation tests.
//

bool TestAddPoint(shapefile* Shape, v2 P1, v2 P2, file_read Expected)
{
    shp_feature Feat = AddFeature(Shape, 0, 1);
    AddPoint(&Feat, P1, 0);
    Feat = AddFeature(Shape, 0, 1);
    AddPoint(&Feat, P2, 0);
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddPointM(shapefile* Shape, v3 P1, v3 P2, file_read Expected)
{
    shp_feature Feat = AddFeature(Shape, 0, 1);
    AddPoint(&Feat, P1.XY, 0, P1.M);
    Feat = AddFeature(Shape, 0, 1);
    AddPoint(&Feat, P2.XY, 0, P2.M);
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddPointZM(shapefile* Shape, v4 P1, v4 P2, file_read Expected)
{
    shp_feature Feat = AddFeature(Shape, 0, 1);
    AddPoint(&Feat, P1.XY, P1.Z, P1.M);
    Feat = AddFeature(Shape, 0, 1);
    AddPoint(&Feat, P2.XY, P2.Z, P2.M);
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddMultiPoint(shapefile* Shape, v4* Points, i32 NumPoints, i32 NumFeats, i32 Offset, file_read Expected)
{
    i32 PointsPerRecord = NumPoints / NumFeats;
    for (i32 Count = 0; Count < NumFeats; Count++)
    {
        shp_feature Feat = AddFeature(Shape, 0, PointsPerRecord);
        AddPoints(&Feat, PointsPerRecord, &Points->XY, 0, 0, Offset);
        Points = (v4*)((u8*)Points + (Offset * PointsPerRecord));
    }
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddMultiPointM(shapefile* Shape, v4* Points, i32 NumPoints, i32 NumFeats, i32 Offset, file_read Expected)
{
    i32 PointsPerRecord = NumPoints / NumFeats;
    for (i32 Count = 0; Count < NumFeats; Count++)
    {
        shp_feature Feat = AddFeature(Shape, 0, PointsPerRecord);
        AddPoints(&Feat, PointsPerRecord, &Points->XY, 0, &Points->M, Offset);
        Points = (v4*)((u8*)Points + (Offset * PointsPerRecord));
    }
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddMultiPointZM(shapefile* Shape, v4* Points, i32 NumPoints, i32 NumFeats, i32 Offset, file_read Expected)
{
    i32 PointsPerRecord = NumPoints / NumFeats;
    for (i32 Count = 0; Count < NumFeats; Count++)
    {
        shp_feature Feat = AddFeature(Shape, 0, PointsPerRecord);
        AddPoints(&Feat, PointsPerRecord, &Points->XY, &Points->Z, &Points->M, Offset);
        Points = (v4*)((u8*)Points + (Offset * PointsPerRecord));
    }
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddPolyline(shapefile* Shape, v4* Points, i32 NumPoints, i32 NumParts, i32 NumFeats, i32 Offset, file_read Expected)
{
    i32 PointsPerRecord = NumPoints / NumFeats;
    i32 PointsPerPart = PointsPerRecord / NumParts;
    for (i32 FeatCount = 0; FeatCount < NumFeats; FeatCount++)
    {
        shp_feature Feat = AddFeature(Shape, NumParts, PointsPerRecord);
        for (i32 PartCount = 0; PartCount < NumParts; PartCount++)
        {
            AddLinestring(&Feat, PointsPerPart, &Points->XY, 0, 0, Offset);
            Points = (v4*)((u8*)Points + (Offset * PointsPerPart));
        }
    }
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddPolylineM(shapefile* Shape, v4* Points, i32 NumPoints, i32 NumParts, i32 NumFeats, i32 Offset, file_read Expected)
{
    i32 PointsPerRecord = NumPoints / NumFeats;
    i32 PointsPerPart = PointsPerRecord / NumParts;
    for (i32 FeatCount = 0; FeatCount < NumFeats; FeatCount++)
    {
        shp_feature Feat = AddFeature(Shape, NumParts, PointsPerRecord);
        for (i32 PartCount = 0; PartCount < NumParts; PartCount++)
        {
            AddLinestring(&Feat, PointsPerPart, &Points->XY, 0, &Points->M, Offset);
            Points = (v4*)((u8*)Points + (Offset * PointsPerPart));
        }
    }
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddPolylineZM(shapefile* Shape, v4* Points, i32 NumPoints, i32 NumParts, i32 NumFeats, i32 Offset, file_read Expected)
{
    i32 PointsPerRecord = NumPoints / NumFeats;
    i32 PointsPerPart = PointsPerRecord / NumParts;
    for (i32 FeatCount = 0; FeatCount < NumFeats; FeatCount++)
    {
        shp_feature Feat = AddFeature(Shape, NumParts, PointsPerRecord);
        for (i32 PartCount = 0; PartCount < NumParts; PartCount++)
        {
            AddLinestring(&Feat, PointsPerPart, &Points->XY, &Points->Z, &Points->M, Offset);
            Points = (v4*)((u8*)Points + (Offset * PointsPerPart));
        }
    }
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddPolygon(shapefile* Shape, v4* Points, i32 NumPoints, shp_ring_type* Rings, i32 NumRings, i32 NumFeats, i32 Offset, file_read Expected)
{
    i32 PointsPerRecord = NumPoints / NumFeats;
    i32 PointsPerRing = PointsPerRecord / NumRings;
    for (i32 FeatCount = 0; FeatCount < NumFeats; FeatCount++)
    {
        shp_feature Feat = AddFeature(Shape, NumRings, PointsPerRecord);
        for (i32 PartCount = 0; PartCount < NumRings; PartCount++)
        {
            AddRing(&Feat, *Rings++, PointsPerRing, &Points->XY, 0, 0, Offset);
            Points = (v4*)((u8*)Points + (Offset * PointsPerRing));
        }
    }
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddPolygonM(shapefile* Shape, v4* Points, i32 NumPoints, shp_ring_type* Rings, i32 NumRings, i32 NumFeats, i32 Offset, file_read Expected)
{
    i32 PointsPerRecord = NumPoints / NumFeats;
    i32 PointsPerRing = PointsPerRecord / NumRings;
    for (i32 FeatCount = 0; FeatCount < NumFeats; FeatCount++)
    {
        shp_feature Feat = AddFeature(Shape, NumRings, PointsPerRecord);
        for (i32 PartCount = 0; PartCount < NumRings; PartCount++)
        {
            AddRing(&Feat, *Rings++, PointsPerRing, &Points->XY, 0, &Points->M, Offset);
            Points = (v4*)((u8*)Points + (Offset * PointsPerRing));
        }
    }
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

bool TestAddPolygonZM(shapefile* Shape, v4* Points, i32 NumPoints, shp_ring_type* Rings, i32 NumRings, i32 NumFeats, i32 Offset, file_read Expected)
{
    i32 PointsPerRecord = NumPoints / NumFeats;
    i32 PointsPerRing = PointsPerRecord / NumRings;
    for (i32 FeatCount = 0; FeatCount < NumFeats; FeatCount++)
    {
        shp_feature Feat = AddFeature(Shape, NumRings, PointsPerRecord);
        for (i32 PartCount = 0; PartCount < NumRings; PartCount++)
        {
            AddRing(&Feat, *Rings++, PointsPerRing, &Points->XY, &Points->Z, &Points->M, Offset);
            Points = (v4*)((u8*)Points + (Offset * PointsPerRing));
        }
    }
    return !memcmp(Shape->ShpFilePtr, Expected.Ptr[0], Expected.Size[0]);
}

//
// Main test program.
//

int main()
{
    file_read InPoint = LoadSHP("../tests/data/point");
    file_read InPointM = LoadSHP("../tests/data/point_m");
    file_read InPointZM = LoadSHP("../tests/data/point_zm");
    {
        void* Mem[9] = { calloc(1, InPoint.Size[0]), calloc(1, InPoint.Size[1]), calloc(1, InPoint.Size[2]),
            calloc(1, InPointM.Size[0]), calloc(1, InPointM.Size[1]), calloc(1, InPointM.Size[2]),
            calloc(1, InPointZM.Size[0]), calloc(1, InPointZM.Size[1]), calloc(1, InPointZM.Size[2]) };
        
        shapefile OutGeom = CreatePoint(Mem[0], Mem[1], Mem[2]);
        shapefile OutGeomM = CreatePointM(Mem[3], Mem[4], Mem[5]);
        shapefile OutGeomZM = CreatePointZM(Mem[6], Mem[7], Mem[8]);
        
        Test(AddPoint, &OutGeom, V2(-0.5, 0.5), V2(0.5, -0.5), InPoint);
        Test(AddPointM, &OutGeomM, V3(-0.5, 0.5, 1), V3(0.5, -0.5, 2), InPointM);
        Test(AddPointZM, &OutGeomZM, V4(-0.5, 0.5, 1, -1), V4(0.5, -0.5, 2, -2), InPointZM);
    }
    
    file_read InMultiPoint = LoadSHP("../tests/data/multipoint");
    file_read InMultiPointM = LoadSHP("../tests/data/multipoint_m");
    file_read InMultiPointZM = LoadSHP("../tests/data/multipoint_zm");
    {
        void* Mem[9] = { calloc(1, InMultiPoint.Size[0]), calloc(1, InMultiPoint.Size[1]), calloc(1, InMultiPoint.Size[2]),
            calloc(1, InMultiPointM.Size[0]), calloc(1, InMultiPointM.Size[1]), calloc(1, InMultiPointM.Size[2]),
            calloc(1, InMultiPointZM.Size[0]), calloc(1, InMultiPointZM.Size[1]), calloc(1, InMultiPointZM.Size[2]) };
        
        shapefile OutGeom = CreateMultiPoint(Mem[0], Mem[1], Mem[2]);
        shapefile OutGeomM = CreateMultiPointM(Mem[3], Mem[4], Mem[5]);
        shapefile OutGeomZM = CreateMultiPointZM(Mem[6], Mem[7], Mem[8]);
        
        v4 Points[] = { V4(-0.5, 0.5, 1, -2), V4(0.5, -0.5, 2, -1), V4(-1, 1, 3, 1), V4(1, -1, 4, 2) };
        Test(AddMultiPoint, &OutGeom, Points, 4, 2, sizeof(v4), InMultiPoint);
        Test(AddMultiPointM, &OutGeomM, Points, 4, 2, sizeof(v4), InMultiPointM);
        Test(AddMultiPointZM, &OutGeomZM, Points, 4, 2, sizeof(v4), InMultiPointZM);
    }
    
    file_read InPolyline = LoadSHP("../tests/data/polyline");
    file_read InPolylineM = LoadSHP("../tests/data/polyline_m");
    file_read InPolylineZM = LoadSHP("../tests/data/polyline_zm");
    {
        void* Mem[9] = { calloc(1, InPolyline.Size[0]), calloc(1, InPolyline.Size[1]), calloc(1, InPolyline.Size[2]),
            calloc(1, InPolylineM.Size[0]), calloc(1, InPolylineM.Size[1]), calloc(1, InPolylineM.Size[2]),
            calloc(1, InPolylineZM.Size[0]), calloc(1, InPolylineZM.Size[1]), calloc(1, InPolylineZM.Size[2]) };
        
        shapefile OutGeom = CreatePolyline(Mem[0], Mem[1], Mem[2]);
        shapefile OutGeomM = CreatePolylineM(Mem[3], Mem[4], Mem[5]);
        shapefile OutGeomZM = CreatePolylineZM(Mem[6], Mem[7], Mem[8]);
        
        v4 Points[] = { V4(-0.5, 0.5, 5, -3), V4(-0.5, -0.5, 6, -2), V4(0.5, -0.5, 7, -1),
            V4(-1, 1, 8, 1), V4(-1, -1, 9, 2), V4(1, -1, 10, 3),
            V4(-0.5, 0.5, -5, 3), V4(0.5, 0.5, -6, 2), V4(0.5, -0.5, -7, 1),
            V4(-1, 1, -8, -1), V4(1, 1, -9, -2), V4(1, -1, -10, -3)};
        Test(AddPolyline, &OutGeom, Points, 12, 2, 2, sizeof(v4), InPolyline);
        Test(AddPolylineM, &OutGeomM, Points, 12, 2, 2, sizeof(v4), InPolylineM);
        Test(AddPolylineZM, &OutGeomZM, Points, 12, 2, 2, sizeof(v4), InPolylineZM);
    }
    
    file_read InPolygon = LoadSHP("../tests/data/polygon");
    file_read InPolygonM = LoadSHP("../tests/data/polygon_m");
    file_read InPolygonZM = LoadSHP("../tests/data/polygon_zm");
    {
        void* Mem[9] = { calloc(1, InPolygon.Size[0]), calloc(1, InPolygon.Size[1]), calloc(1, InPolygon.Size[2]),
            calloc(1, InPolygonM.Size[0]), calloc(1, InPolygonM.Size[1]), calloc(1, InPolygonM.Size[2]),
            calloc(1, InPolygonZM.Size[0]), calloc(1, InPolygonZM.Size[1]), calloc(1, InPolygonZM.Size[2]) };
        
        shapefile OutGeom = CreatePolygon(Mem[0], Mem[1], Mem[2]);
        shapefile OutGeomM = CreatePolygonM(Mem[3], Mem[4], Mem[5]);
        shapefile OutGeomZM = CreatePolygonZM(Mem[6], Mem[7], Mem[8]);
        
        v4 Points[] = { V4(-1, 1, -1, 1), V4(-1, -1, -1, 2), V4(1, -1, -1, 3), V4(1, 1, -1, 4), V4(-1, 1, -1, 1),
            V4(-0.9, -0.9, -1, 5), V4(-0.9, 0, -1, 6), V4(0, 0, -1, 7), V4(0, -0.9, -1, 8), V4(-0.9, -0.9, -1, 5),
            V4(0.9, 0.9, -1, 9), V4(0, 0.9, -1, 10), V4(0, 0, -1, 11), V4(0.9, 0, -1, 12), V4(0.9, 0.9, -1, 9),
            V4(2, 4, -4, 13), V4(2, 2, -4, 14), V4(4, 2, -4, 15), V4(4, 4, -4, 16), V4(2, 4, -4, 13),
            V4(2.1, 2.1, -4, 17), V4(2.1, 3, -4, 18), V4(3, 3, -4, 19), V4(3, 2.1, -4, 20), V4(2.1, 2.1, -4, 17),
            V4(3.9, 3.9, -4, 21), V4(3, 3.9, -4, 22), V4(3, 3, -4, 23), V4(3.9, 3, -4, 24), V4(3.9, 3.9, -4, 21) };
        shp_ring_type Rings[] = { ShpRing_Outer, ShpRing_Inner, ShpRing_Inner, ShpRing_Outer, ShpRing_Inner, ShpRing_Inner };
        Test(AddPolygon, &OutGeom, Points, 30, Rings, 6, 1, sizeof(v4), InPolygon);
        Test(AddPolygonM, &OutGeomM, Points, 30, Rings, 6, 1, sizeof(v4), InPolygonM);
        Test(AddPolygonZM, &OutGeomZM, Points, 30, Rings, 6, 1, sizeof(v4), InPolygonZM);
    }
    
    if (!Error) printf("All tests passed!\n");
    return 0;
}