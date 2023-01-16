#include "geotypes-wkb.h"
#include "tinybase-memory.h"

#include <stdio.h>
#include <varargs.h>

bool Error = false;
#define Test(Callback, ...) \
do { \
if (!Test##Callback(__VA_ARGS__)) { \
Error = true; \
printf(" [%3d] %-40s ERRO.\n", __LINE__, #Callback##"()"); } \
} while (0); \

//
// Test data
//

#define GEOM_BUFFER_SIZE 2046

char WkbPoint[] = "0101000000debded539ff13140712b9d04008062c0";
char WkbPointZ[] = "01e9030000debded539ff13140712b9d04008062c0c976be9f7afbe340";
char WkbPointM[] = "01d1070000debded539ff13140712b9d04008062c02d431cebe2363a3f";
char WkbPointZM[] = "01b90b0000debded539ff13140712b9d04008062c0c976be9f7afbe3402d431cebe2363a3f";

char WkbLinestring[] = "010200000003000000000000000000f03f000000000000f03f0000000000000040000000000000f03f00000000000000400000000000000040";
char WkbLinestringZ[] = "01ea03000003000000000000000000f03f000000000000f03f00000000000008400000000000000040000000000000f03f0000000000000840000000000000004000000000000000400000000000000840";
char WkbLinestringM[] = "01d207000003000000000000000000f03f000000000000f03f00000000000008400000000000000040000000000000f03f0000000000000840000000000000004000000000000000400000000000000840";
char WkbLinestringZM[] = "01ba0b000003000000000000000000f03f000000000000f03f000000000000084000000000000010400000000000000040000000000000f03f000000000000084000000000000010400000000000000040000000000000004000000000000008400000000000001040";

char WkbPolygon[] = "01030000000200000004000000000000000000f03f000000000000f03f0000000000000040000000000000f03f00000000000000400000000000000040000000000000f03f000000000000f03f040000009a9999999999f13f9a9999999999f13f666666666666fe3f9a9999999999f13f666666666666fe3f666666666666fe3f9a9999999999f13f9a9999999999f13f";
char WkbPolygonZ[] = "01eb0300000200000004000000000000000000f03f000000000000f03f00000000000008400000000000000040000000000000f03f0000000000000840000000000000004000000000000000400000000000000840000000000000f03f000000000000f03f0000000000000840040000009a9999999999f13f9a9999999999f13f0000000000000840666666666666fe3f9a9999999999f13f0000000000000840666666666666fe3f666666666666fe3f00000000000008409a9999999999f13f9a9999999999f13f0000000000000840";
char WkbPolygonM[] = "01d30700000200000004000000000000000000f03f000000000000f03f00000000000008400000000000000040000000000000f03f0000000000000840000000000000004000000000000000400000000000000840000000000000f03f000000000000f03f0000000000000840040000009a9999999999f13f9a9999999999f13f0000000000000840666666666666fe3f9a9999999999f13f0000000000000840666666666666fe3f666666666666fe3f00000000000008409a9999999999f13f9a9999999999f13f0000000000000840";
char WkbPolygonZM[] = "01bb0b00000200000004000000000000000000f03f000000000000f03f000000000000084000000000000010400000000000000040000000000000f03f000000000000084000000000000010400000000000000040000000000000004000000000000008400000000000001040000000000000f03f000000000000f03f00000000000008400000000000001040040000009a9999999999f13f9a9999999999f13f00000000000008400000000000001040666666666666fe3f9a9999999999f13f00000000000008400000000000001040666666666666fe3f666666666666fe3f000000000000084000000000000010409a9999999999f13f9a9999999999f13f00000000000008400000000000001040";

char WkbTriangle[] = "01110000000100000004000000000000000000f03f000000000000f03f0000000000000040000000000000f03f00000000000000400000000000000040000000000000f03f000000000000f03f";
char WkbTriangleZ[] = "01f90300000100000004000000000000000000f03f000000000000f03f00000000000008400000000000000040000000000000f03f0000000000000840000000000000004000000000000000400000000000000840000000000000f03f000000000000f03f0000000000000840";
char WkbTriangleM[] = "01e10700000100000004000000000000000000f03f000000000000f03f00000000000008400000000000000040000000000000f03f0000000000000840000000000000004000000000000000400000000000000840000000000000f03f000000000000f03f0000000000000840";
char WkbTriangleZM[] = "01c90b00000100000004000000000000000000f03f000000000000f03f000000000000084000000000000010400000000000000040000000000000f03f000000000000084000000000000010400000000000000040000000000000004000000000000008400000000000001040000000000000f03f000000000000f03f00000000000008400000000000001040";

char WkbPolyhedron[] = "010f0000000200000001030000000100000005000000000000000000000000000000000000000000000000000000000000000000f03f000000000000f03f000000000000f03f000000000000f03f000000000000000000000000000000000000000000000000010300000001000000050000000000000000000000000000000000f03f00000000000000000000000000000040000000000000f03f0000000000000040000000000000f03f000000000000f03f0000000000000000000000000000f03f";
char WkbPolyhedronZ[] = "01f70300000600000001eb030000010000000500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000f03f0000000000000000000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000000000000000000000000000000000000000000000000000000001eb03000001000000050000000000000000000000000000000000000000000000000000000000000000000000000000000000f03f0000000000000000000000000000f03f000000000000f03f0000000000000000000000000000f03f0000000000000000000000000000000000000000000000000000000000000000000000000000000001eb0300000100000005000000000000000000000000000000000000000000000000000000000000000000f03f00000000000000000000000000000000000000000000f03f0000000000000000000000000000f03f00000000000000000000000000000000000000000000f03f00000000000000000000000000000000000000000000000001eb0300000100000005000000000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000f03f000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000f03f00000000000000000000000000000000000000000000f03f000000000000f03f000000000000000001eb03000001000000050000000000000000000000000000000000f03f00000000000000000000000000000000000000000000f03f000000000000f03f000000000000f03f000000000000f03f000000000000f03f000000000000f03f000000000000f03f00000000000000000000000000000000000000000000f03f000000000000000001eb030000010000000500000000000000000000000000000000000000000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000f03f000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000f03f00000000000000000000000000000000000000000000f03f";
char WkbPolyhedronM[] = "01df0700000600000001d3070000010000000500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000f03f0000000000000000000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000000000000000000000000000000000000000000000000000000001d307000001000000050000000000000000000000000000000000000000000000000000000000000000000000000000000000f03f0000000000000000000000000000f03f000000000000f03f0000000000000000000000000000f03f0000000000000000000000000000000000000000000000000000000000000000000000000000000001d30700000100000005000000000000000000000000000000000000000000000000000000000000000000f03f00000000000000000000000000000000000000000000f03f0000000000000000000000000000f03f00000000000000000000000000000000000000000000f03f00000000000000000000000000000000000000000000000001d30700000100000005000000000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000f03f000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000f03f00000000000000000000000000000000000000000000f03f000000000000f03f000000000000000001d307000001000000050000000000000000000000000000000000f03f00000000000000000000000000000000000000000000f03f000000000000f03f000000000000f03f000000000000f03f000000000000f03f000000000000f03f000000000000f03f00000000000000000000000000000000000000000000f03f000000000000000001d3070000010000000500000000000000000000000000000000000000000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000f03f000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000f03f00000000000000000000000000000000000000000000f03f";
char WkbPolyhedronZM[] = "01c70b00000600000001bb0b00000100000005000000000000000000000000000000000000000000000000000000000000000000224000000000000000000000000000000000000000000000f03f00000000000022400000000000000000000000000000f03f000000000000f03f00000000000022400000000000000000000000000000f03f00000000000000000000000000002240000000000000000000000000000000000000000000000000000000000000224001bb0b0000010000000500000000000000000000000000000000000000000000000000000000000000000020400000000000000000000000000000f03f00000000000000000000000000002040000000000000f03f000000000000f03f00000000000000000000000000002040000000000000f03f000000000000000000000000000000000000000000002040000000000000000000000000000000000000000000000000000000000000204001bb0b000001000000050000000000000000000000000000000000000000000000000000000000000000001c40000000000000f03f000000000000000000000000000000000000000000001c40000000000000f03f0000000000000000000000000000f03f0000000000001c4000000000000000000000000000000000000000000000f03f0000000000001c400000000000000000000000000000000000000000000000000000000000001c4001bb0b00000100000005000000000000000000f03f000000000000f03f00000000000000000000000000001840000000000000f03f000000000000f03f000000000000f03f0000000000001840000000000000f03f0000000000000000000000000000f03f0000000000001840000000000000f03f000000000000000000000000000000000000000000001840000000000000f03f000000000000f03f0000000000000000000000000000184001bb0b000001000000050000000000000000000000000000000000f03f000000000000000000000000000014400000000000000000000000000000f03f000000000000f03f0000000000001440000000000000f03f000000000000f03f000000000000f03f0000000000001440000000000000f03f000000000000f03f000000000000000000000000000014400000000000000000000000000000f03f0000000000000000000000000000144001bb0b0000010000000500000000000000000000000000000000000000000000000000f03f0000000000001040000000000000f03f0000000000000000000000000000f03f0000000000001040000000000000f03f000000000000f03f000000000000f03f00000000000010400000000000000000000000000000f03f000000000000f03f000000000000104000000000000000000000000000000000000000000000f03f0000000000001040";

char WkbTIN[] = "01100000000200000001110000000100000004000000000000000000000000000000000000000000000000000000000000000000f03f000000000000f03f00000000000000000000000000000000000000000000000001110000000100000004000000000000000000f03f0000000000000000000000000000f03f000000000000f03f0000000000000000000000000000f03f000000000000f03f0000000000000000";
char WkbTINZ[] = "01f80300000200000001f903000001000000040000000000000000000000000000000000000000000000000000400000000000000000000000000000f03f0000000000000040000000000000f03f0000000000000000000000000000004000000000000000000000000000000000000000000000004001f90300000100000004000000000000000000f03f00000000000000000000000000000040000000000000f03f000000000000f03f00000000000000400000000000000000000000000000f03f0000000000000040000000000000f03f00000000000000000000000000000040";
char WkbTINM[] = "01e00700000200000001e107000001000000040000000000000000000000000000000000000000000000000000400000000000000000000000000000f03f0000000000000040000000000000f03f0000000000000000000000000000004000000000000000000000000000000000000000000000004001e10700000100000004000000000000000000f03f00000000000000000000000000000040000000000000f03f000000000000f03f00000000000000400000000000000000000000000000f03f0000000000000040000000000000f03f00000000000000000000000000000040";
char WkbTINZM[] = "01c80b00000200000001c90b0000010000000400000000000000000000000000000000000000000000000000004000000000000022400000000000000000000000000000f03f00000000000000400000000000002040000000000000f03f000000000000000000000000000000400000000000001c40000000000000000000000000000000000000000000000040000000000000184001c90b00000100000004000000000000000000f03f000000000000000000000000000000400000000000001440000000000000f03f000000000000f03f000000000000004000000000000010400000000000000000000000000000f03f00000000000000400000000000000840000000000000f03f000000000000000000000000000000400000000000000040";

char WkbMultiPoint[] = "0104000000020000000101000000000000000000f03f0000000000000040010100000000000000000014400000000000001840";
char WkbMultiPointZ[] = "01ec0300000200000001e9030000000000000000f03f0000000000000040000000000000084001e9030000000000000000144000000000000018400000000000001c40";
char WkbMultiPointM[] = "01d40700000200000001d1070000000000000000f03f0000000000000040000000000000084001d1070000000000000000144000000000000018400000000000001c40";
char WkbMultiPointZM[] = "01bc0b00000200000001b90b0000000000000000f03f00000000000000400000000000000840000000000000104001b90b0000000000000000144000000000000018400000000000001c400000000000002040";

char WkbMultiLinestring[] = "010500000002000000010200000002000000000000000000f03f000000000000004000000000000014400000000000001840010200000002000000000000000000224000000000000024400000000000002a400000000000002c40";
char WkbMultiLinestringZ[] = "01ed0300000200000001ea03000002000000000000000000f03f00000000000000400000000000000840000000000000144000000000000018400000000000001c4001ea030000020000000000000000002240000000000000244000000000000026400000000000002a400000000000002c400000000000002e40";
char WkbMultiLinestringM[] = "01d50700000200000001d207000002000000000000000000f03f00000000000000400000000000000840000000000000144000000000000018400000000000001c4001d2070000020000000000000000002240000000000000244000000000000026400000000000002a400000000000002c400000000000002e40";
char WkbMultiLinestringZM[] = "01bd0b00000200000001ba0b000002000000000000000000f03f000000000000004000000000000008400000000000001040000000000000144000000000000018400000000000001c40000000000000204001ba0b00000200000000000000000022400000000000002440000000000000264000000000000028400000000000002a400000000000002c400000000000002e400000000000003040";

char WkbMultiPolygon[] = "01060000000200000001030000000200000005000000000000000000000000000000000000000000000000001040000000000000000000000000000010400000000000001040000000000000000000000000000010400000000000000000000000000000000005000000000000000000f03f000000000000f03f0000000000000040000000000000f03f00000000000000400000000000000040000000000000f03f0000000000000040000000000000f03f000000000000f03f01030000000100000005000000000000000000f0bf000000000000f0bf000000000000f0bf00000000000000c000000000000000c000000000000000c000000000000000c0000000000000f0bf000000000000f0bf000000000000f0bf";
char WkbMultiPolygonZ[] = "01ee0300000200000001eb030000020000000500000000000000000000000000000000000000000000000000000000000000000010400000000000000000000000000000000000000000000010400000000000001040000000000000000000000000000000000000000000001040000000000000000000000000000000000000000000000000000000000000000005000000000000000000f03f000000000000f03f00000000000000000000000000000040000000000000f03f0000000000000000000000000000004000000000000000400000000000000000000000000000f03f00000000000000400000000000000000000000000000f03f000000000000f03f000000000000000001eb0300000100000005000000000000000000f0bf000000000000f0bf0000000000000000000000000000f0bf00000000000000c0000000000000000000000000000000c000000000000000c0000000000000000000000000000000c0000000000000f0bf0000000000000000000000000000f0bf000000000000f0bf0000000000000000";
char WkbMultiPolygonM[] = "01d60700000200000001d3070000020000000500000000000000000000000000000000000000000000000000000000000000000010400000000000000000000000000000000000000000000010400000000000001040000000000000000000000000000000000000000000001040000000000000000000000000000000000000000000000000000000000000000005000000000000000000f03f000000000000f03f00000000000000000000000000000040000000000000f03f0000000000000000000000000000004000000000000000400000000000000000000000000000f03f00000000000000400000000000000000000000000000f03f000000000000f03f000000000000000001d30700000100000005000000000000000000f0bf000000000000f0bf0000000000000000000000000000f0bf00000000000000c0000000000000000000000000000000c000000000000000c0000000000000000000000000000000c0000000000000f0bf0000000000000000000000000000f0bf000000000000f0bf0000000000000000";
char WkbMultiPolygonZM[] = "01be0b00000200000001bb0b00000200000005000000000000000000000000000000000000000000000000000000000000000000f03f000000000000104000000000000000000000000000000000000000000000004000000000000010400000000000001040000000000000000000000000000008400000000000000000000000000000104000000000000000000000000000001040000000000000000000000000000000000000000000000000000000000000f03f05000000000000000000f03f000000000000f03f000000000000000000000000000018400000000000000040000000000000f03f00000000000000000000000000001c400000000000000040000000000000004000000000000000000000000000002040000000000000f03f000000000000004000000000000000000000000000002240000000000000f03f000000000000f03f0000000000000000000000000000184001bb0b00000100000005000000000000000000f0bf000000000000f0bf00000000000000000000000000002640000000000000f0bf00000000000000c00000000000000000000000000000284000000000000000c000000000000000c000000000000000000000000000002a4000000000000000c0000000000000f0bf00000000000000000000000000002c40000000000000f0bf000000000000f0bf00000000000000000000000000002640";

char WkbCollection[] = "0107000000020000000101000000000000000000004000000000000008400102000000020000000000000000000040000000000000084000000000000008400000000000001040";
char WkbCollectionZ[] = "01ef0300000200000001e903000000000000000000400000000000000840000000000000224001ea03000002000000000000000000004000000000000008400000000000001040000000000000084000000000000010400000000000001440";
char WkbCollectionM[] = "01d70700000200000001d107000000000000000000400000000000000840000000000000224001d207000002000000000000000000004000000000000008400000000000001040000000000000084000000000000010400000000000001440";
char WkbCollectionZM[] = "01bf0b00000200000001b90b0000000000000000004000000000000008400000000000002240000000000000244001ba0b00000200000000000000000000400000000000000840000000000000104000000000000026400000000000000840000000000000104000000000000014400000000000002840";

//
// Test functions
//

internal buffer
LoadWkb(char* In, u8* Out)
{
    usz OutLen = strlen(In) / 2;
    for (usz OutIdx = 0, InIdx = 0; OutIdx < OutLen; OutIdx++)
    {
        char Byte1 = (In[InIdx] >= '0' && In[InIdx] <= '9')
            ? In[InIdx] - '0' : In[InIdx] - 'a' + 10;
        InIdx++;
        char Byte2 = (In[InIdx] >= '0' && In[InIdx] <= '9')
            ? In[InIdx] - '0' : In[InIdx] - 'a' + 10;
        InIdx++;
        Out[OutIdx] = (u8)(Byte1 << 4 | Byte2);
    }
    return Buffer(Out, OutLen, GEOM_BUFFER_SIZE);
}

bool TestReadPoint(buffer WkbRead, void* Expected, usz ExpectedSize)
{
    return EqualBuffers(WkbRead, Buffer((u8*)Expected, ExpectedSize, 0));
}

bool TestReadLinestring(buffer WkbRead, void* Expected, usz ExpectedSize)
{
    return EqualBuffers(WkbRead, Buffer((u8*)Expected, ExpectedSize, 0));
}

bool TestReadPolygon(buffer WkbRead, void* Expected, usz ExpectedSize)
{
    return EqualBuffers(WkbRead, Buffer((u8*)Expected, ExpectedSize, 0));
}

bool TestReadTriangle(buffer WkbRead, void* Expected, usz ExpectedSize)
{
    return EqualBuffers(WkbRead, Buffer((u8*)Expected, ExpectedSize, 0));
}

bool TestReadPolyhedron(buffer WkbRead, void* Expected, usz ExpectedSize)
{
    return EqualBuffers(WkbRead, Buffer((u8*)Expected, ExpectedSize, 0));
}

bool TestReadTIN(buffer WkbRead, void* Expected, usz ExpectedSize)
{
    return EqualBuffers(WkbRead, Buffer((u8*)Expected, ExpectedSize, 0));
}

bool TestReadMultiPoint(buffer WkbRead, void* Expected, usz ExpectedSize)
{
    return EqualBuffers(WkbRead, Buffer((u8*)Expected, ExpectedSize, 0));
}

bool TestReadMultiLinestring(buffer WkbRead, void* Expected, usz ExpectedSize)
{
    return EqualBuffers(WkbRead, Buffer((u8*)Expected, ExpectedSize, 0));
}

bool TestReadMultiPolygon(buffer WkbRead, void* Expected, usz ExpectedSize)
{
    return EqualBuffers(WkbRead, Buffer((u8*)Expected, ExpectedSize, 0));
}

bool TestReadCollection(buffer WkbRead, void* Expected, usz ExpectedSize)
{
    return EqualBuffers(WkbRead, Buffer((u8*)Expected, ExpectedSize, 0));
}

bool TestIterRing2(void** List, usz Size)
{
    wkb_iter2 Iter = { 0, Size, List[0] };
    usz Count = 0;
    ring2* Ring = (ring2*)List[0];
    do
    {
        if (Ring != List[Count++]) return false;
    } while ((Ring = GetNextRing(&Iter)));
    return Count == Size;
}

bool TestIterLinestring2(void** List, usz Size)
{
    wkb_iter2 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_linestring2* Linestring = (wkb_linestring2*)List[0];
    do
    {
        if (Linestring != List[Count++]) return false;
    } while ((Linestring = GetNextLinestring(&Iter)));
    return Count == Size;
}

bool TestIterPolygon2(void** List, usz Size)
{
    wkb_iter2 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_polygon2* Polygon = (wkb_polygon2*)List[0];
    do
    {
        if (Polygon != List[Count++]) return false;
    } while ((Polygon = GetNextPolygon(&Iter)));
    return Count == Size;
}

bool TestIterTriangle2(void** List, usz Size)
{
    wkb_iter2 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_triangle2* Triangle = (wkb_triangle2*)List[0];
    do
    {
        if (Triangle != List[Count++]) return false;
    } while ((Triangle = GetNextTriangle(&Iter)));
    return Count == Size;
}

bool TestIterGeometry2(void** List, usz Size)
{
    wkb_iter2 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_geometry2* Geometry = (wkb_geometry2*)List[0];
    do
    {
        if (Geometry != List[Count++]) return false;
    } while ((Geometry = GetNextGeometry(&Iter)));
    return Count == Size;
}

bool TestIterRing3(void** List, usz Size)
{
    wkb_iter3 Iter = { 0, Size, List[0] };
    usz Count = 0;
    ring3* Ring = (ring3*)List[0];
    do
    {
        if (Ring != List[Count++]) return false;
    } while ((Ring = GetNextRing(&Iter)));
    return Count == Size;
}

bool TestIterLinestring3(void** List, usz Size)
{
    wkb_iter3 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_linestring3* Linestring = (wkb_linestring3*)List[0];
    do
    {
        if (Linestring != List[Count++]) return false;
    } while ((Linestring = GetNextLinestring(&Iter)));
    return Count == Size;
}

bool TestIterPolygon3(void** List, usz Size)
{
    wkb_iter3 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_polygon3* Polygon = (wkb_polygon3*)List[0];
    do
    {
        if (Polygon != List[Count++]) return false;
    } while ((Polygon = GetNextPolygon(&Iter)));
    return Count == Size;
}

bool TestIterTriangle3(void** List, usz Size)
{
    wkb_iter3 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_triangle3* Triangle = (wkb_triangle3*)List[0];
    do
    {
        if (Triangle != List[Count++]) return false;
    } while ((Triangle = GetNextTriangle(&Iter)));
    return Count == Size;
}

bool TestIterGeometry3(void** List, usz Size)
{
    wkb_iter3 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_geometry3* Geometry = (wkb_geometry3*)List[0];
    do
    {
        if (Geometry != List[Count++]) return false;
    } while ((Geometry = GetNextGeometry(&Iter)));
    return Count == Size;
}

bool TestIterRing4(void** List, usz Size)
{
    wkb_iter4 Iter = { 0, Size, List[0] };
    usz Count = 0;
    ring4* Ring = (ring4*)List[0];
    do
    {
        if (Ring != List[Count++]) return false;
    } while ((Ring = GetNextRing(&Iter)));
    return Count == Size;
}

bool TestIterLinestring4(void** List, usz Size)
{
    wkb_iter4 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_linestring4* Linestring = (wkb_linestring4*)List[0];
    do
    {
        if (Linestring != List[Count++]) return false;
    } while ((Linestring = GetNextLinestring(&Iter)));
    return Count == Size;
}

bool TestIterPolygon4(void** List, usz Size)
{
    wkb_iter4 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_polygon4* Polygon = (wkb_polygon4*)List[0];
    do
    {
        if (Polygon != List[Count++]) return false;
    } while ((Polygon = GetNextPolygon(&Iter)));
    return Count == Size;
}

bool TestIterTriangle4(void** List, usz Size)
{
    wkb_iter4 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_triangle4* Triangle = (wkb_triangle4*)List[0];
    do
    {
        if (Triangle != List[Count++]) return false;
    } while ((Triangle = GetNextTriangle(&Iter)));
    return Count == Size;
}

bool TestIterGeometry4(void** List, usz Size)
{
    wkb_iter4 Iter = { 0, Size, List[0] };
    usz Count = 0;
    wkb_geometry4* Geometry = (wkb_geometry4*)List[0];
    do
    {
        if (Geometry != List[Count++]) return false;
    } while ((Geometry = GetNextGeometry(&Iter)));
    return Count == Size;
}

//
// Test program
//

int main()
{
    u8 Geom1[GEOM_BUFFER_SIZE] = {0};
    u8 Geom2[GEOM_BUFFER_SIZE] = {0};
    
    // WkbPoint
    {
        wkb_point2* Point = CreatePoint(&Geom1, V2(17.9438374, -148.0000022001));
        Test(ReadPoint, LoadWkb(WkbPoint, Geom2), Point, sizeof(*Point));
        
        wkb_point3* PointZ = CreatePointZ(&Geom1, V3(17.9438374, -148.0000022001, 40923.832));
        Test(ReadPoint, LoadWkb(WkbPointZ, Geom2), PointZ, sizeof(*PointZ));
        
        wkb_point3* PointM = CreatePointM(&Geom1, V3(17.9438374, -148.0000022001, 0.0004));
        Test(ReadPoint, LoadWkb(WkbPointM, Geom2), PointM, sizeof(*PointM));
        
        wkb_point4* PointZM = CreatePointZM(&Geom1, V4(17.9438374, -148.0000022001, 40923.832, 0.0004));
        Test(ReadPoint, LoadWkb(WkbPointZM, Geom2), PointZM, sizeof(*PointZM));
    }
    
    // WkbLinestring
    {
        usz LinestringSize = 0;
        
        wkb_linestring2* Linestring = CreateLinestring(Geom1);
        AddVertex(Linestring, V2(1, 1));
        AddVertex(Linestring, V2(2, 1));
        AddVertex(Linestring, V2(2, 2));
        LinestringSize = GetLinestringSize(Linestring);
        Test(ReadLinestring, LoadWkb(WkbLinestring, Geom2), Linestring, LinestringSize);
        
        wkb_linestring3* LinestringZ = CreateLinestringZ(Geom1);
        AddVertex(LinestringZ, V3(1, 1, 3));
        AddVertex(LinestringZ, V3(2, 1, 3));
        AddVertex(LinestringZ, V3(2, 2, 3));
        LinestringSize = GetLinestringSize(LinestringZ);
        Test(ReadLinestring, LoadWkb(WkbLinestringZ, Geom2), LinestringZ, LinestringSize);
        
        wkb_linestring3* LinestringM = CreateLinestringM(Geom1);
        AddVertex(LinestringM, V3(1, 1, 3));
        AddVertex(LinestringM, V3(2, 1, 3));
        AddVertex(LinestringM, V3(2, 2, 3));
        LinestringSize = GetLinestringSize(LinestringM);
        Test(ReadLinestring, LoadWkb(WkbLinestringM, Geom2), LinestringM, LinestringSize);
        
        wkb_linestring4* LinestringZM = CreateLinestringZM(Geom1);
        AddVertex(LinestringZM, V4(1, 1, 3, 4));
        AddVertex(LinestringZM, V4(2, 1, 3, 4));
        AddVertex(LinestringZM, V4(2, 2, 3, 4));
        LinestringSize = GetLinestringSize(LinestringZM);
        Test(ReadLinestring, LoadWkb(WkbLinestringZM, Geom2), LinestringZM, LinestringSize);
    }
    
    // WkbPolygon
    {
        usz PolygonSize = 0;
        
        wkb_polygon2* Polygon = CreatePolygon(Geom1);
        {
            ring2* RingA = AddRing(Polygon);
            AddVertex(RingA, V2(1, 1));
            AddVertex(RingA, V2(2, 1));
            AddVertex(RingA, V2(2, 2));
            AddVertex(RingA, V2(1, 1));
            ring2* RingB = AddRing(Polygon);
            AddVertex(RingB, V2(1.1, 1.1));
            AddVertex(RingB, V2(1.9, 1.1));
            AddVertex(RingB, V2(1.9, 1.9));
            AddVertex(RingB, V2(1.1, 1.1));
        }
        PolygonSize = GetPolygonSize(Polygon);
        Test(ReadPolygon, LoadWkb(WkbPolygon, Geom2), Polygon, PolygonSize);
        
        wkb_polygon3* PolygonZ = CreatePolygonZ(Geom1);
        {
            ring3* RingA = AddRing(PolygonZ);
            AddVertex(RingA, V3(1, 1, 3));
            AddVertex(RingA, V3(2, 1, 3));
            AddVertex(RingA, V3(2, 2, 3));
            AddVertex(RingA, V3(1, 1, 3));
            ring3* RingB = AddRing(PolygonZ);
            AddVertex(RingB, V3(1.1, 1.1, 3));
            AddVertex(RingB, V3(1.9, 1.1, 3));
            AddVertex(RingB, V3(1.9, 1.9, 3));
            AddVertex(RingB, V3(1.1, 1.1, 3));
        }
        PolygonSize = GetPolygonSize(PolygonZ);
        Test(ReadPolygon, LoadWkb(WkbPolygonZ, Geom2), PolygonZ, PolygonSize);
        
        wkb_polygon3* PolygonM = CreatePolygonM(Geom1);
        {
            ring3* RingA = AddRing(PolygonM);
            AddVertex(RingA, V3(1, 1, 3));
            AddVertex(RingA, V3(2, 1, 3));
            AddVertex(RingA, V3(2, 2, 3));
            AddVertex(RingA, V3(1, 1, 3));
            ring3* RingB = AddRing(PolygonM);
            AddVertex(RingB, V3(1.1, 1.1, 3));
            AddVertex(RingB, V3(1.9, 1.1, 3));
            AddVertex(RingB, V3(1.9, 1.9, 3));
            AddVertex(RingB, V3(1.1, 1.1, 3));
        }
        PolygonSize = GetPolygonSize(PolygonM);
        Test(ReadPolygon, LoadWkb(WkbPolygonM, Geom2), PolygonM, PolygonSize);
        
        wkb_polygon4* PolygonZM = CreatePolygonZM(Geom1);;
        {
            ring4* RingA = AddRing(PolygonZM);
            AddVertex(RingA, V4(1, 1, 3, 4));
            AddVertex(RingA, V4(2, 1, 3, 4));
            AddVertex(RingA, V4(2, 2, 3, 4));
            AddVertex(RingA, V4(1, 1, 3, 4));
            ring4* RingB = AddRing(PolygonZM);
            AddVertex(RingB, V4(1.1, 1.1, 3, 4));
            AddVertex(RingB, V4(1.9, 1.1, 3, 4));
            AddVertex(RingB, V4(1.9, 1.9, 3, 4));
            AddVertex(RingB, V4(1.1, 1.1, 3, 4));
        }
        PolygonSize = GetPolygonSize(PolygonZM);
        Test(ReadPolygon, LoadWkb(WkbPolygonZM, Geom2), PolygonZM, PolygonSize);
    }
    
    // WkbTriangle
    {
        usz TriangleSize = 0;
        
        wkb_triangle2* Triangle = CreateTriangle(Geom1);
        {
            ring2* RingA = AddRing(Triangle);
            AddVertex(RingA, V2(1, 1));
            AddVertex(RingA, V2(2, 1));
            AddVertex(RingA, V2(2, 2));
            AddVertex(RingA, V2(1, 1));
        }
        TriangleSize = GetTriangleSize(Triangle);
        Test(ReadTriangle, LoadWkb(WkbTriangle, Geom2), Triangle, TriangleSize);
        
        wkb_triangle3* TriangleZ = CreateTriangleZ(Geom1);
        {
            ring3* RingA = AddRing(TriangleZ);
            AddVertex(RingA, V3(1, 1, 3));
            AddVertex(RingA, V3(2, 1, 3));
            AddVertex(RingA, V3(2, 2, 3));
            AddVertex(RingA, V3(1, 1, 3));
        }
        TriangleSize = GetTriangleSize(TriangleZ);
        Test(ReadTriangle, LoadWkb(WkbTriangleZ, Geom2), TriangleZ, TriangleSize);
        
        wkb_triangle3* TriangleM = CreateTriangleM(Geom1);
        {
            ring3* RingA = AddRing(TriangleM);
            AddVertex(RingA, V3(1, 1, 3));
            AddVertex(RingA, V3(2, 1, 3));
            AddVertex(RingA, V3(2, 2, 3));
            AddVertex(RingA, V3(1, 1, 3));
        }
        TriangleSize = GetTriangleSize(TriangleM);
        Test(ReadTriangle, LoadWkb(WkbTriangleM, Geom2), TriangleM, TriangleSize);
        
        wkb_triangle4* TriangleZM = CreateTriangleZM(Geom1);
        {
            ring4* RingA = AddRing(TriangleZM);
            AddVertex(RingA, V4(1, 1, 3, 4));
            AddVertex(RingA, V4(2, 1, 3, 4));
            AddVertex(RingA, V4(2, 2, 3, 4));
            AddVertex(RingA, V4(1, 1, 3, 4));
        }
        TriangleSize = GetTriangleSize(TriangleZM);
        Test(ReadTriangle, LoadWkb(WkbTriangleZM, Geom2), TriangleZM, TriangleSize);
    }
    
    // WkbPolyhedron
    {
        usz PolyhedronSize = 0;
        
        wkb_polyhedron2* Polyhedron = CreatePolyhedron(Geom1);
        {
            wkb_polygon2* PolygonA = AddPolygon(Polyhedron);
            {
                ring2* RingA = AddRing(PolygonA);
                AddVertex(RingA, V2(0, 0));
                AddVertex(RingA, V2(0, 1));
                AddVertex(RingA, V2(1, 1));
                AddVertex(RingA, V2(1, 0));
                AddVertex(RingA, V2(0, 0));
            }
            wkb_polygon2* PolygonB = AddPolygon(Polyhedron);
            {
                ring2* RingA = AddRing(PolygonB);
                AddVertex(RingA, V2(0, 1));
                AddVertex(RingA, V2(0, 2));
                AddVertex(RingA, V2(1, 2));
                AddVertex(RingA, V2(1, 1));
                AddVertex(RingA, V2(0, 1));
            }
        }
        PolyhedronSize = GetPolyhedronSize(Polyhedron);
        Test(ReadPolyhedron, LoadWkb(WkbPolyhedron, Geom2), Polyhedron, PolyhedronSize);
        
        wkb_polyhedron3* PolyhedronZ = CreatePolyhedronZ(Geom1);
        {
            wkb_polygon3* PolygonA = AddPolygon(PolyhedronZ);
            {
                ring3* RingA = AddRing(PolygonA);
                AddVertex(RingA, V3(0, 0, 0));
                AddVertex(RingA, V3(0, 0, 1));
                AddVertex(RingA, V3(0, 1, 1));
                AddVertex(RingA, V3(0, 1, 0));
                AddVertex(RingA, V3(0, 0, 0));
            }
            wkb_polygon3* PolygonB = AddPolygon(PolyhedronZ);
            {
                ring3* RingA = AddRing(PolygonB);
                AddVertex(RingA, V3(0, 0, 0));
                AddVertex(RingA, V3(0, 1, 0));
                AddVertex(RingA, V3(1, 1, 0));
                AddVertex(RingA, V3(1, 0, 0));
                AddVertex(RingA, V3(0, 0, 0));
            }
            wkb_polygon3* PolygonC = AddPolygon(PolyhedronZ);
            {
                ring3* RingA = AddRing(PolygonC);
                AddVertex(RingA, V3(0, 0, 0));
                AddVertex(RingA, V3(1, 0, 0));
                AddVertex(RingA, V3(1, 0, 1));
                AddVertex(RingA, V3(0, 0, 1));
                AddVertex(RingA, V3(0, 0, 0));
            }
            wkb_polygon3* PolygonD = AddPolygon(PolyhedronZ);
            {
                ring3* RingA = AddRing(PolygonD);
                AddVertex(RingA, V3(1, 1, 0));
                AddVertex(RingA, V3(1, 1, 1));
                AddVertex(RingA, V3(1, 0, 1));
                AddVertex(RingA, V3(1, 0, 0));
                AddVertex(RingA, V3(1, 1, 0));
            }
            wkb_polygon3* PolygonE = AddPolygon(PolyhedronZ);
            {
                ring3* RingA = AddRing(PolygonE);
                AddVertex(RingA, V3(0, 1, 0));
                AddVertex(RingA, V3(0, 1, 1));
                AddVertex(RingA, V3(1, 1, 1));
                AddVertex(RingA, V3(1, 1, 0));
                AddVertex(RingA, V3(0, 1, 0));
            }
            wkb_polygon3* PolygonF = AddPolygon(PolyhedronZ);
            {
                ring3* RingA = AddRing(PolygonF);
                AddVertex(RingA, V3(0, 0, 1));
                AddVertex(RingA, V3(1, 0, 1));
                AddVertex(RingA, V3(1, 1, 1));
                AddVertex(RingA, V3(0, 1, 1));
                AddVertex(RingA, V3(0, 0, 1));
            }
        }
        PolyhedronSize = GetPolyhedronSize(PolyhedronZ);
        Test(ReadPolyhedron, LoadWkb(WkbPolyhedronZ, Geom2), PolyhedronZ, PolyhedronSize);
        
        wkb_polyhedron3* PolyhedronM = CreatePolyhedronM(Geom1);
        {
            wkb_polygon3* PolygonA = AddPolygon(PolyhedronM);
            {
                ring3* RingA = AddRing(PolygonA);
                AddVertex(RingA, V3(0, 0, 0));
                AddVertex(RingA, V3(0, 0, 1));
                AddVertex(RingA, V3(0, 1, 1));
                AddVertex(RingA, V3(0, 1, 0));
                AddVertex(RingA, V3(0, 0, 0));
            }
            wkb_polygon3* PolygonB = AddPolygon(PolyhedronM);
            {
                ring3* RingA = AddRing(PolygonB);
                AddVertex(RingA, V3(0, 0, 0));
                AddVertex(RingA, V3(0, 1, 0));
                AddVertex(RingA, V3(1, 1, 0));
                AddVertex(RingA, V3(1, 0, 0));
                AddVertex(RingA, V3(0, 0, 0));
            }
            wkb_polygon3* PolygonC = AddPolygon(PolyhedronM);
            {
                ring3* RingA = AddRing(PolygonC);
                AddVertex(RingA, V3(0, 0, 0));
                AddVertex(RingA, V3(1, 0, 0));
                AddVertex(RingA, V3(1, 0, 1));
                AddVertex(RingA, V3(0, 0, 1));
                AddVertex(RingA, V3(0, 0, 0));
            }
            wkb_polygon3* PolygonD = AddPolygon(PolyhedronM);
            {
                ring3* RingA = AddRing(PolygonD);
                AddVertex(RingA, V3(1, 1, 0));
                AddVertex(RingA, V3(1, 1, 1));
                AddVertex(RingA, V3(1, 0, 1));
                AddVertex(RingA, V3(1, 0, 0));
                AddVertex(RingA, V3(1, 1, 0));
            }
            wkb_polygon3* PolygonE = AddPolygon(PolyhedronM);
            {
                ring3* RingA = AddRing(PolygonE);
                AddVertex(RingA, V3(0, 1, 0));
                AddVertex(RingA, V3(0, 1, 1));
                AddVertex(RingA, V3(1, 1, 1));
                AddVertex(RingA, V3(1, 1, 0));
                AddVertex(RingA, V3(0, 1, 0));
            }
            wkb_polygon3* PolygonF = AddPolygon(PolyhedronM);
            {
                ring3* RingA = AddRing(PolygonF);
                AddVertex(RingA, V3(0, 0, 1));
                AddVertex(RingA, V3(1, 0, 1));
                AddVertex(RingA, V3(1, 1, 1));
                AddVertex(RingA, V3(0, 1, 1));
                AddVertex(RingA, V3(0, 0, 1));
            }
        }
        PolyhedronSize = GetPolyhedronSize(PolyhedronM);
        Test(ReadPolyhedron, LoadWkb(WkbPolyhedronM, Geom2), PolyhedronM, PolyhedronSize);
        
        wkb_polyhedron4* PolyhedronZM = CreatePolyhedronZM(Geom1);
        {
            wkb_polygon4* PolygonA = AddPolygon(PolyhedronZM);
            {
                ring4* RingA = AddRing(PolygonA);
                AddVertex(RingA, V4(0, 0, 0, 9));
                AddVertex(RingA, V4(0, 0, 1, 9));
                AddVertex(RingA, V4(0, 1, 1, 9));
                AddVertex(RingA, V4(0, 1, 0, 9));
                AddVertex(RingA, V4(0, 0, 0, 9));
            }
            wkb_polygon4* PolygonB = AddPolygon(PolyhedronZM);
            {
                ring4* RingA = AddRing(PolygonB);
                AddVertex(RingA, V4(0, 0, 0, 8));
                AddVertex(RingA, V4(0, 1, 0, 8));
                AddVertex(RingA, V4(1, 1, 0, 8));
                AddVertex(RingA, V4(1, 0, 0, 8));
                AddVertex(RingA, V4(0, 0, 0, 8));
            }
            wkb_polygon4* PolygonC = AddPolygon(PolyhedronZM);
            {
                ring4* RingA = AddRing(PolygonC);
                AddVertex(RingA, V4(0, 0, 0, 7));
                AddVertex(RingA, V4(1, 0, 0, 7));
                AddVertex(RingA, V4(1, 0, 1, 7));
                AddVertex(RingA, V4(0, 0, 1, 7));
                AddVertex(RingA, V4(0, 0, 0, 7));
            }
            wkb_polygon4* PolygonD = AddPolygon(PolyhedronZM);
            {
                ring4* RingA = AddRing(PolygonD);
                AddVertex(RingA, V4(1, 1, 0, 6));
                AddVertex(RingA, V4(1, 1, 1, 6));
                AddVertex(RingA, V4(1, 0, 1, 6));
                AddVertex(RingA, V4(1, 0, 0, 6));
                AddVertex(RingA, V4(1, 1, 0, 6));
            }
            wkb_polygon4* PolygonE = AddPolygon(PolyhedronZM);
            {
                ring4* RingA = AddRing(PolygonE);
                AddVertex(RingA, V4(0, 1, 0, 5));
                AddVertex(RingA, V4(0, 1, 1, 5));
                AddVertex(RingA, V4(1, 1, 1, 5));
                AddVertex(RingA, V4(1, 1, 0, 5));
                AddVertex(RingA, V4(0, 1, 0, 5));
            }
            wkb_polygon4* PolygonF = AddPolygon(PolyhedronZM);
            {
                ring4* RingA = AddRing(PolygonF);
                AddVertex(RingA, V4(0, 0, 1, 4));
                AddVertex(RingA, V4(1, 0, 1, 4));
                AddVertex(RingA, V4(1, 1, 1, 4));
                AddVertex(RingA, V4(0, 1, 1, 4));
                AddVertex(RingA, V4(0, 0, 1, 4));
            }
        }
        PolyhedronSize = GetPolyhedronSize(PolyhedronZM);
        Test(ReadPolyhedron, LoadWkb(WkbPolyhedronZM, Geom2), PolyhedronZM, PolyhedronSize);
    }
    
    // TIN
    {
        usz TINSize = 0;
        
        wkb_tin2* TIN = CreateTIN(Geom1);
        {
            wkb_triangle2* TriangleA = AddTriangle(TIN);
            {
                ring2* RingA = AddRing(TriangleA);
                AddVertex(RingA, V2(0, 0));
                AddVertex(RingA, V2(0, 1));
                AddVertex(RingA, V2(1, 0));
                AddVertex(RingA, V2(0, 0));
            }
            wkb_polygon2* TriangleB = AddTriangle(TIN);
            {
                ring2* RingA = AddRing(TriangleB);
                AddVertex(RingA, V2(1, 0));
                AddVertex(RingA, V2(1, 1));
                AddVertex(RingA, V2(0, 1));
                AddVertex(RingA, V2(1, 0));
            }
        }
        TINSize = GetTINSize(TIN);
        Test(ReadTIN, LoadWkb(WkbTIN, Geom2), TIN, TINSize);
        
        wkb_tin3* TINZ = CreateTINZ(Geom1);
        {
            wkb_triangle3* TriangleA = AddTriangle(TINZ);
            {
                ring3* RingA = AddRing(TriangleA);
                AddVertex(RingA, V3(0, 0, 2));
                AddVertex(RingA, V3(0, 1, 2));
                AddVertex(RingA, V3(1, 0, 2));
                AddVertex(RingA, V3(0, 0, 2));
            }
            wkb_polygon3* TriangleB = AddTriangle(TINZ);
            {
                ring3* RingA = AddRing(TriangleB);
                AddVertex(RingA, V3(1, 0, 2));
                AddVertex(RingA, V3(1, 1, 2));
                AddVertex(RingA, V3(0, 1, 2));
                AddVertex(RingA, V3(1, 0, 2));
            }
        }
        TINSize = GetTINSize(TINZ);
        Test(ReadTIN, LoadWkb(WkbTINZ, Geom2), TINZ, TINSize);
        
        wkb_tin3* TINM = CreateTINM(Geom1);
        {
            wkb_triangle3* TriangleA = AddTriangle(TINM);
            {
                ring3* RingA = AddRing(TriangleA);
                AddVertex(RingA, V3(0, 0, 2));
                AddVertex(RingA, V3(0, 1, 2));
                AddVertex(RingA, V3(1, 0, 2));
                AddVertex(RingA, V3(0, 0, 2));
            }
            wkb_polygon3* TriangleB = AddTriangle(TINM);
            {
                ring3* RingA = AddRing(TriangleB);
                AddVertex(RingA, V3(1, 0, 2));
                AddVertex(RingA, V3(1, 1, 2));
                AddVertex(RingA, V3(0, 1, 2));
                AddVertex(RingA, V3(1, 0, 2));
            }
        }
        TINSize = GetTINSize(TINM);
        Test(ReadTIN, LoadWkb(WkbTINM, Geom2), TINM, TINSize);
        
        wkb_tin4* TINZM = CreateTINZM(Geom1);
        {
            wkb_triangle4* TriangleA = AddTriangle(TINZM);
            {
                ring4* RingA = AddRing(TriangleA);
                AddVertex(RingA, V4(0, 0, 2, 9));
                AddVertex(RingA, V4(0, 1, 2, 8));
                AddVertex(RingA, V4(1, 0, 2, 7));
                AddVertex(RingA, V4(0, 0, 2, 6));
            }
            wkb_polygon4* TriangleB = AddTriangle(TINZM);
            {
                ring4* RingA = AddRing(TriangleB);
                AddVertex(RingA, V4(1, 0, 2, 5));
                AddVertex(RingA, V4(1, 1, 2, 4));
                AddVertex(RingA, V4(0, 1, 2, 3));
                AddVertex(RingA, V4(1, 0, 2, 2));
            }
        }
        TINSize = GetTINSize(TINZM);
        Test(ReadTIN, LoadWkb(WkbTINZM, Geom2), TINZM, TINSize);
    }
    
    // MultiPoint
    {
        usz MultiPointSize = 0;
        
        wkb_multipoint2* MultiPoint = CreateMultiPoint(Geom1);
        AddPoint(MultiPoint, V2(1, 2));
        AddPoint(MultiPoint, V2(5, 6));
        MultiPointSize = GetMultiPointSize(MultiPoint);
        Test(ReadMultiPoint, LoadWkb(WkbMultiPoint, Geom2), MultiPoint, MultiPointSize);
        
        wkb_multipoint3* MultiPointZ = CreateMultiPointZ(Geom1);
        AddPoint(MultiPointZ, V3(1, 2, 3));
        AddPoint(MultiPointZ, V3(5, 6, 7));
        MultiPointSize = GetMultiPointSize(MultiPointZ);
        Test(ReadMultiPoint, LoadWkb(WkbMultiPointZ, Geom2), MultiPointZ, MultiPointSize);
        
        wkb_multipoint3* MultiPointM = CreateMultiPointM(Geom1);
        AddPoint(MultiPointM, V3(1, 2, 3));
        AddPoint(MultiPointM, V3(5, 6, 7));
        MultiPointSize = GetMultiPointSize(MultiPointM);
        Test(ReadMultiPoint, LoadWkb(WkbMultiPointM, Geom2), MultiPointM, MultiPointSize);
        
        wkb_multipoint4* MultiPointZM = CreateMultiPointZM(Geom1);
        AddPoint(MultiPointZM, V4(1, 2, 3, 4));
        AddPoint(MultiPointZM, V4(5, 6, 7, 8));
        MultiPointSize = GetMultiPointSize(MultiPointZM);
        Test(ReadMultiPoint, LoadWkb(WkbMultiPointZM, Geom2), MultiPointZM, MultiPointSize);
    }
    
    // MultiLinestring
    {
        usz MultiLinestringSize = 0;
        
        wkb_multilinestring2* MultiLinestring = CreateMultiLinestring(Geom1);
        {
            wkb_linestring2* LinestringA = AddLinestring(MultiLinestring);
            AddVertex(LinestringA, V2(1, 2));
            AddVertex(LinestringA, V2(5, 6));
            wkb_linestring2* LinestringB = AddLinestring(MultiLinestring);
            AddVertex(LinestringB, V2(9, 10));
            AddVertex(LinestringB, V2(13, 14));
        }
        MultiLinestringSize = GetMultiLinestringSize(MultiLinestring);
        Test(ReadMultiLinestring, LoadWkb(WkbMultiLinestring, Geom2), MultiLinestring, MultiLinestringSize);
        
        wkb_multilinestring3* MultiLinestringZ = CreateMultiLinestringZ(Geom1);
        {
            wkb_linestring3* LinestringA = AddLinestring(MultiLinestringZ);
            AddVertex(LinestringA, V3(1, 2, 3));
            AddVertex(LinestringA, V3(5, 6, 7));
            wkb_linestring3* LinestringB = AddLinestring(MultiLinestringZ);
            AddVertex(LinestringB, V3(9, 10, 11));
            AddVertex(LinestringB, V3(13, 14, 15));
        }
        MultiLinestringSize = GetMultiLinestringSize(MultiLinestringZ);
        Test(ReadMultiLinestring, LoadWkb(WkbMultiLinestringZ, Geom2), MultiLinestringZ, MultiLinestringSize);
        
        wkb_multilinestring3* MultiLinestringM = CreateMultiLinestringM(Geom1);
        {
            wkb_linestring3* LinestringA = AddLinestring(MultiLinestringM);
            AddVertex(LinestringA, V3(1, 2, 3));
            AddVertex(LinestringA, V3(5, 6, 7));
            wkb_linestring3* LinestringB = AddLinestring(MultiLinestringM);
            AddVertex(LinestringB, V3(9, 10, 11));
            AddVertex(LinestringB, V3(13, 14, 15));
        }
        MultiLinestringSize = GetMultiLinestringSize(MultiLinestringM);
        Test(ReadMultiLinestring, LoadWkb(WkbMultiLinestringM, Geom2), MultiLinestringM, MultiLinestringSize);
        
        wkb_multilinestring4* MultiLinestringZM = CreateMultiLinestringZM(Geom1);
        {
            wkb_linestring4* LinestringA = AddLinestring(MultiLinestringZM);
            AddVertex(LinestringA, V4(1, 2, 3, 4));
            AddVertex(LinestringA, V4(5, 6, 7, 8));
            wkb_linestring4* LinestringB = AddLinestring(MultiLinestringZM);
            AddVertex(LinestringB, V4(9, 10, 11, 12));
            AddVertex(LinestringB, V4(13, 14, 15, 16));
        }
        MultiLinestringSize = GetMultiLinestringSize(MultiLinestringZM);
        Test(ReadMultiLinestring, LoadWkb(WkbMultiLinestringZM, Geom2), MultiLinestringZM, MultiLinestringSize);
    }
    
    // MultiPolygon
    {
        usz MultiPolygonSize = 0;
        
        wkb_multipolygon2* MultiPolygon = CreateMultiPolygon(Geom1);
        {
            wkb_polygon2* PolygonA = AddPolygon(MultiPolygon);
            {
                ring2* RingA = AddRing(PolygonA);
                AddVertex(RingA, V2(0, 0));
                AddVertex(RingA, V2(4, 0));
                AddVertex(RingA, V2(4, 4));
                AddVertex(RingA, V2(0, 4));
                AddVertex(RingA, V2(0, 0));
                
                ring2* RingB = AddRing(PolygonA);
                AddVertex(RingB, V2(1, 1));
                AddVertex(RingB, V2(2, 1));
                AddVertex(RingB, V2(2, 2));
                AddVertex(RingB, V2(1, 2));
                AddVertex(RingB, V2(1, 1));
            }
            
            wkb_polygon2* PolygonB = AddPolygon(MultiPolygon);
            {
                ring2* RingA = AddRing(PolygonB);
                AddVertex(RingA, V2(-1, -1));
                AddVertex(RingA, V2(-1, -2));
                AddVertex(RingA, V2(-2, -2));
                AddVertex(RingA, V2(-2, -1));
                AddVertex(RingA, V2(-1, -1));
            }
        }
        MultiPolygonSize = GetMultiPolygonSize(MultiPolygon);
        Test(ReadMultiPolygon, LoadWkb(WkbMultiPolygon, Geom2), MultiPolygon, MultiPolygonSize);
        
        wkb_multipolygon3* MultiPolygonZ = CreateMultiPolygonZ(Geom1);
        {
            wkb_polygon3* PolygonA = AddPolygon(MultiPolygonZ);
            {
                ring3* RingA = AddRing(PolygonA);
                AddVertex(RingA, V3(0, 0, 0));
                AddVertex(RingA, V3(4, 0, 0));
                AddVertex(RingA, V3(4, 4, 0));
                AddVertex(RingA, V3(0, 4, 0));
                AddVertex(RingA, V3(0, 0, 0));
                
                ring3* RingB = AddRing(PolygonA);
                AddVertex(RingB, V3(1, 1, 0));
                AddVertex(RingB, V3(2, 1, 0));
                AddVertex(RingB, V3(2, 2, 0));
                AddVertex(RingB, V3(1, 2, 0));
                AddVertex(RingB, V3(1, 1, 0));
            }
            
            wkb_polygon3* PolygonB = AddPolygon(MultiPolygonZ);
            {
                ring3* RingA = AddRing(PolygonB);
                AddVertex(RingA, V3(-1, -1, 0));
                AddVertex(RingA, V3(-1, -2, 0));
                AddVertex(RingA, V3(-2, -2, 0));
                AddVertex(RingA, V3(-2, -1, 0));
                AddVertex(RingA, V3(-1, -1, 0));
            }
        }
        MultiPolygonSize = GetMultiPolygonSize(MultiPolygonZ);
        Test(ReadMultiPolygon, LoadWkb(WkbMultiPolygonZ, Geom2), MultiPolygonZ, MultiPolygonSize);
        
        wkb_multipolygon3* MultiPolygonM = CreateMultiPolygonM(Geom1);
        {
            wkb_polygon3* PolygonA = AddPolygon(MultiPolygonM);
            {
                ring3* RingA = AddRing(PolygonA);
                AddVertex(RingA, V3(0, 0, 0));
                AddVertex(RingA, V3(4, 0, 0));
                AddVertex(RingA, V3(4, 4, 0));
                AddVertex(RingA, V3(0, 4, 0));
                AddVertex(RingA, V3(0, 0, 0));
                
                ring3* RingB = AddRing(PolygonA);
                AddVertex(RingB, V3(1, 1, 0));
                AddVertex(RingB, V3(2, 1, 0));
                AddVertex(RingB, V3(2, 2, 0));
                AddVertex(RingB, V3(1, 2, 0));
                AddVertex(RingB, V3(1, 1, 0));
            }
            
            wkb_polygon3* PolygonB = AddPolygon(MultiPolygonM);
            {
                ring3* RingA = AddRing(PolygonB);
                AddVertex(RingA, V3(-1, -1, 0));
                AddVertex(RingA, V3(-1, -2, 0));
                AddVertex(RingA, V3(-2, -2, 0));
                AddVertex(RingA, V3(-2, -1, 0));
                AddVertex(RingA, V3(-1, -1, 0));
            }
        }
        MultiPolygonSize = GetMultiPolygonSize(MultiPolygonM);
        Test(ReadMultiPolygon, LoadWkb(WkbMultiPolygonM, Geom2), MultiPolygonM, MultiPolygonSize);
        
        wkb_multipolygon4* MultiPolygonZM = CreateMultiPolygonZM(Geom1);
        {
            wkb_polygon4* PolygonA = AddPolygon(MultiPolygonZM);
            {
                ring4* RingA = AddRing(PolygonA);
                AddVertex(RingA, V4(0, 0, 0, 1));
                AddVertex(RingA, V4(4, 0, 0, 2));
                AddVertex(RingA, V4(4, 4, 0, 3));
                AddVertex(RingA, V4(0, 4, 0, 4));
                AddVertex(RingA, V4(0, 0, 0, 1));
                
                ring4* RingB = AddRing(PolygonA);
                AddVertex(RingB, V4(1, 1, 0, 6));
                AddVertex(RingB, V4(2, 1, 0, 7));
                AddVertex(RingB, V4(2, 2, 0, 8));
                AddVertex(RingB, V4(1, 2, 0, 9));
                AddVertex(RingB, V4(1, 1, 0, 6));
            }
            
            wkb_polygon4* PolygonB = AddPolygon(MultiPolygonZM);
            {
                ring4* RingA = AddRing(PolygonB);
                AddVertex(RingA, V4(-1, -1, 0, 11));
                AddVertex(RingA, V4(-1, -2, 0, 12));
                AddVertex(RingA, V4(-2, -2, 0, 13));
                AddVertex(RingA, V4(-2, -1, 0, 14));
                AddVertex(RingA, V4(-1, -1, 0, 11));
            }
        }
        MultiPolygonSize = GetMultiPolygonSize(MultiPolygonZM);
        Test(ReadMultiPolygon, LoadWkb(WkbMultiPolygonZM, Geom2), MultiPolygonZM, MultiPolygonSize);
    }
    
    // Geometry Collection
    {
        usz CollectionSize = 0;
        
        wkb_collection2* Collection = CreateCollection(Geom1);
        {
            wkb_point2* Point = AddPoint(Collection, V2(2, 3));
            wkb_linestring2* Linestring = AddLinestring(Collection);
            {
                AddVertex(Linestring, V2(2, 3));
                AddVertex(Linestring, V2(3, 4));
            }
        }
        CollectionSize = GetCollectionSize(Collection);
        Test(ReadCollection, LoadWkb(WkbCollection, Geom2), Collection, CollectionSize);
        
        wkb_collection3* CollectionZ = CreateCollectionZ(Geom1);
        {
            wkb_point3* Point = AddPoint(CollectionZ, V3(2, 3, 9));
            wkb_linestring3* Linestring = AddLinestring(CollectionZ);
            {
                AddVertex(Linestring, V3(2, 3, 4));
                AddVertex(Linestring, V3(3, 4, 5));
            }
        }
        CollectionSize = GetCollectionSize(CollectionZ);
        Test(ReadCollection, LoadWkb(WkbCollectionZ, Geom2), CollectionZ, CollectionSize);
        
        wkb_collection3* CollectionM = CreateCollectionM(Geom1);
        {
            wkb_point3* Point = AddPoint(CollectionM, V3(2, 3, 9));
            wkb_linestring3* Linestring = AddLinestring(CollectionM);
            {
                AddVertex(Linestring, V3(2, 3, 4));
                AddVertex(Linestring, V3(3, 4, 5));
            }
        }
        CollectionSize = GetCollectionSize(CollectionM);
        Test(ReadCollection, LoadWkb(WkbCollectionM, Geom2), CollectionM, CollectionSize);
        
        wkb_collection4* CollectionZM = CreateCollectionZM(Geom1);
        {
            wkb_point4* Point = AddPoint(CollectionZM, V4(2, 3, 9, 10));
            wkb_linestring4* Linestring = AddLinestring(CollectionZM);
            {
                AddVertex(Linestring, V4(2, 3, 4, 11));
                AddVertex(Linestring, V4(3, 4, 5, 12));
            }
        }
        CollectionSize = GetCollectionSize(CollectionZM);
        Test(ReadCollection, LoadWkb(WkbCollectionZM, Geom2), CollectionZM, CollectionSize);
    }
    
    // Iter
    {
        wkb_collection2* Collection = CreateCollection(Geom1);
        {
            void* GeomList[7];
            // GetNextRing
            {
                wkb_polygon2* Polygon = AddPolygon(Collection);
                
                ring2* RingA = AddRing(Polygon);
                AddVertex(RingA, V2(1, 2));
                AddVertex(RingA, V2(2, 3));
                AddVertex(RingA, V2(3, 4));
                AddVertex(RingA, V2(1, 2));
                
                ring2* RingB = AddRing(Polygon);
                AddVertex(RingB, V2(11, 12));
                AddVertex(RingB, V2(12, 13));
                AddVertex(RingB, V2(13, 14));
                AddVertex(RingB, V2(11, 12));
                
                ring2* RingC = AddRing(Polygon);
                AddVertex(RingC, V2(-1, -2));
                AddVertex(RingC, V2(-2, -3));
                AddVertex(RingC, V2(-3, -4));
                AddVertex(RingC, V2(-1, -2));
                
                void* List[3] = { RingA, RingB, RingC };
                Test(IterRing2, List, 3);
                GeomList[0] = Polygon;
            }
            
            // GetNextLinestring
            {
                wkb_linestring2* LinestringA = AddLinestring(Collection);
                AddVertex(LinestringA, V2(1, 2));
                AddVertex(LinestringA, V2(3, 4));
                
                wkb_linestring2* LinestringB = AddLinestring(Collection);
                AddVertex(LinestringB, V2(5, 6));
                AddVertex(LinestringB, V2(7, 8));
                
                wkb_linestring2* LinestringC = AddLinestring(Collection);
                AddVertex(LinestringC, V2(-1, -2));
                AddVertex(LinestringC, V2(-3, -4));
                
                void* List[3] = { LinestringA, LinestringB, LinestringC };
                Test(IterLinestring2, List, 3);
                GeomList[1] = LinestringA;
                GeomList[2] = LinestringB;
                GeomList[3] = LinestringC;
            }
            
            // GetNextPolygon
            // GetNextTriangle
            {
                wkb_polygon2* PolygonA = AddPolygon(Collection);
                {
                    ring2* RingA = AddRing(PolygonA);
                    AddVertex(RingA, V2(1, 2));
                    AddVertex(RingA, V2(2, 3));
                    AddVertex(RingA, V2(3, 4));
                    AddVertex(RingA, V2(1, 2));
                }
                
                wkb_polygon2* PolygonB = AddPolygon(Collection);
                {
                    ring2* RingB = AddRing(PolygonB);
                    AddVertex(RingB, V2(11, 12));
                    AddVertex(RingB, V2(12, 13));
                    AddVertex(RingB, V2(13, 14));
                    AddVertex(RingB, V2(11, 12));
                }
                
                wkb_polygon2* PolygonC = AddPolygon(Collection);
                {
                    ring2* RingC = AddRing(PolygonC);
                    AddVertex(RingC, V2(-1, -2));
                    AddVertex(RingC, V2(-2, -3));
                    AddVertex(RingC, V2(-3, -4));
                    AddVertex(RingC, V2(-1, -2));
                }
                
                void* List[3] = { PolygonA, PolygonB, PolygonC };
                Test(IterPolygon2, List, 3);
                Test(IterTriangle2, List, 3);
                GeomList[4] = PolygonA;
                GeomList[5] = PolygonB;
                GeomList[6] = PolygonC;
            }
            
            // GetNextGeometry
            Test(IterGeometry2, GeomList, 7);
        }
        
        wkb_collection3* CollectionZ = CreateCollectionZ(Geom1);
        {
            void* GeomList[7];
            // GetNextRing
            {
                wkb_polygon3* Polygon = AddPolygon(CollectionZ);
                
                ring3* RingA = AddRing(Polygon);
                AddVertex(RingA, V3(1, 2, 1));
                AddVertex(RingA, V3(2, 3, 1));
                AddVertex(RingA, V3(3, 4, 1));
                AddVertex(RingA, V3(1, 2, 1));
                
                ring3* RingB = AddRing(Polygon);
                AddVertex(RingB, V3(11, 12, 1));
                AddVertex(RingB, V3(12, 13, 1));
                AddVertex(RingB, V3(13, 14, 1));
                AddVertex(RingB, V3(11, 12, 1));
                
                ring3* RingC = AddRing(Polygon);
                AddVertex(RingC, V3(-1, -2, 1));
                AddVertex(RingC, V3(-2, -3, 1));
                AddVertex(RingC, V3(-3, -4, 1));
                AddVertex(RingC, V3(-1, -2, 1));
                
                void* List[3] = { RingA, RingB, RingC };
                Test(IterRing3, List, 3);
                GeomList[0] = Polygon;
            }
            
            // GetNextLinestring
            {
                wkb_linestring3* LinestringA = AddLinestring(CollectionZ);
                AddVertex(LinestringA, V3(1, 2, 1));
                AddVertex(LinestringA, V3(3, 4, 1));
                
                wkb_linestring3* LinestringB = AddLinestring(CollectionZ);
                AddVertex(LinestringB, V3(5, 6, 1));
                AddVertex(LinestringB, V3(7, 8, 1));
                
                wkb_linestring3* LinestringC = AddLinestring(CollectionZ);
                AddVertex(LinestringC, V3(-1, -2, 1));
                AddVertex(LinestringC, V3(-3, -4, 1));
                
                void* List[3] = { LinestringA, LinestringB, LinestringC };
                Test(IterLinestring3, List, 3);
                GeomList[1] = LinestringA;
                GeomList[2] = LinestringB;
                GeomList[3] = LinestringC;
            }
            
            // GetNextPolygon
            // GetNextTriangle
            {
                wkb_polygon3* PolygonA = AddPolygon(CollectionZ);
                {
                    ring3* RingA = AddRing(PolygonA);
                    AddVertex(RingA, V3(1, 2, 1));
                    AddVertex(RingA, V3(2, 3, 1));
                    AddVertex(RingA, V3(3, 4, 1));
                    AddVertex(RingA, V3(1, 2, 1));
                }
                
                wkb_polygon3* PolygonB = AddPolygon(CollectionZ);
                {
                    ring3* RingB = AddRing(PolygonB);
                    AddVertex(RingB, V3(11, 12, 1));
                    AddVertex(RingB, V3(12, 13, 1));
                    AddVertex(RingB, V3(13, 14, 1));
                    AddVertex(RingB, V3(11, 12, 1));
                }
                
                wkb_polygon3* PolygonC = AddPolygon(CollectionZ);
                {
                    ring3* RingC = AddRing(PolygonC);
                    AddVertex(RingC, V3(-1, -2, 1));
                    AddVertex(RingC, V3(-2, -3, 1));
                    AddVertex(RingC, V3(-3, -4, 1));
                    AddVertex(RingC, V3(-1, -2, 1));
                }
                
                void* List[3] = { PolygonA, PolygonB, PolygonC };
                Test(IterPolygon3, List, 3);
                Test(IterTriangle3, List, 3);
                GeomList[4] = PolygonA;
                GeomList[5] = PolygonB;
                GeomList[6] = PolygonC;
            }
            
            // GetNextGeometry
            Test(IterGeometry3, GeomList, 7);
        }
        
        wkb_collection4* CollectionZM = CreateCollectionZM(Geom1);
        {
            void* GeomList[7];
            // GetNextRing
            {
                wkb_polygon4* Polygon = AddPolygon(CollectionZM);
                
                ring4* RingA = AddRing(Polygon);
                AddVertex(RingA, V4(1, 2, 1, 2));
                AddVertex(RingA, V4(2, 3, 1, 2));
                AddVertex(RingA, V4(3, 4, 1, 2));
                AddVertex(RingA, V4(1, 2, 1, 2));
                
                ring4* RingB = AddRing(Polygon);
                AddVertex(RingB, V4(11, 12, 1, 2));
                AddVertex(RingB, V4(12, 13, 1, 2));
                AddVertex(RingB, V4(13, 14, 1, 2));
                AddVertex(RingB, V4(11, 12, 1, 2));
                
                ring4* RingC = AddRing(Polygon);
                AddVertex(RingC, V4(-1, -2, 1, 2));
                AddVertex(RingC, V4(-2, -3, 1, 2));
                AddVertex(RingC, V4(-3, -4, 1, 2));
                AddVertex(RingC, V4(-1, -2, 1, 2));
                
                void* List[3] = { RingA, RingB, RingC };
                Test(IterRing4, List, 3);
                GeomList[0] = Polygon;
            }
            
            // GetNextLinestring
            {
                wkb_linestring4* LinestringA = AddLinestring(CollectionZM);
                AddVertex(LinestringA, V4(1, 2, 1, 2));
                AddVertex(LinestringA, V4(3, 4, 1, 2));
                
                wkb_linestring4* LinestringB = AddLinestring(CollectionZM);
                AddVertex(LinestringB, V4(5, 6, 1, 2));
                AddVertex(LinestringB, V4(7, 8, 1, 2));
                
                wkb_linestring4* LinestringC = AddLinestring(CollectionZM);
                AddVertex(LinestringC, V4(-1, -2, 1, 2));
                AddVertex(LinestringC, V4(-3, -4, 1, 2));
                
                void* List[3] = { LinestringA, LinestringB, LinestringC };
                Test(IterLinestring4, List, 3);
                GeomList[1] = LinestringA;
                GeomList[2] = LinestringB;
                GeomList[3] = LinestringC;
            }
            
            // GetNextPolygon
            // GetNextTriangle
            {
                wkb_polygon4* PolygonA = AddPolygon(CollectionZM);
                {
                    ring4* RingA = AddRing(PolygonA);
                    AddVertex(RingA, V4(1, 2, 1, 2));
                    AddVertex(RingA, V4(2, 3, 1, 2));
                    AddVertex(RingA, V4(3, 4, 1, 2));
                    AddVertex(RingA, V4(1, 2, 1, 2));
                }
                
                wkb_polygon4* PolygonB = AddPolygon(CollectionZM);
                {
                    ring4* RingB = AddRing(PolygonB);
                    AddVertex(RingB, V4(11, 12, 1, 2));
                    AddVertex(RingB, V4(12, 13, 1, 2));
                    AddVertex(RingB, V4(13, 14, 1, 2));
                    AddVertex(RingB, V4(11, 12, 1, 2));
                }
                
                wkb_polygon4* PolygonC = AddPolygon(CollectionZM);
                {
                    ring4* RingC = AddRing(PolygonC);
                    AddVertex(RingC, V4(-1, -2, 1, 2));
                    AddVertex(RingC, V4(-2, -3, 1, 2));
                    AddVertex(RingC, V4(-3, -4, 1, 2));
                    AddVertex(RingC, V4(-1, -2, 1, 2));
                }
                
                void* List[3] = { PolygonA, PolygonB, PolygonC };
                Test(IterPolygon4, List, 3);
                Test(IterTriangle4, List, 3);
                GeomList[4] = PolygonA;
                GeomList[5] = PolygonB;
                GeomList[6] = PolygonC;
            }
            
            // GetNextGeometry
            Test(IterGeometry4, GeomList, 7);
        }
    }
    
	if (!Error) printf("All tests passed!\n");
    return 0;
}