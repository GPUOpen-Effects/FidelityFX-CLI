#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer cb
// {
//
//   uint4 const0;                      // Offset:    0 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// InputTexture                      texture  float4          2d             t0      1 
// OutputTexture                         UAV  float4          2d             u0      1 
// cb                                cbuffer      NA          NA            cb0      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// no Input
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// no Output
cs_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[1], immediateIndexed
dcl_resource_texture2d (float,float,float,float) t0
dcl_uav_typed_texture2d (float,float,float,float) u0
dcl_input vThreadGroupID.xy
dcl_input vThreadIDInGroup.x
dcl_temps 9
dcl_thread_group 64, 1, 1
mov r0.zw, l(0,0,0,0)
ushr r1.x, vThreadIDInGroup.x, l(3)
bfi r1.y, l(1), l(0), vThreadIDInGroup.x, r1.x
ubfe r1.x, l(3), l(1), vThreadIDInGroup.x
imad r1.xy, vThreadGroupID.xyxx, l(8, 8, 0, 0), r1.xyxx
iadd r2.xyzw, r1.xyxy, l(0, -1, -1, 0)
mov r0.xy, r2.zwzz
ld_indexable(texture2d)(float,float,float,float) r0.xyz, r0.xyzw, t0.xyzw
log r3.xyz, r0.xyzx
mul r0.xyz, r0.xyzx, l(12.920000, 12.920000, 12.920000, 0.000000)
max r0.xyz, r0.xyzx, l(0.040450, 0.040450, 0.040450, 0.000000)
mul r3.xyz, r3.xyzx, l(0.416667, 0.416667, 0.416667, 0.000000)
exp r3.xyz, r3.xyzx
mad r3.xyz, r3.xyzx, l(1.055000, 1.055000, 1.055000, 0.000000), l(-0.055000, -0.055000, -0.055000, 0.000000)
min r0.xyz, r0.xyzx, r3.xyzx
iadd r3.xyzw, r1.xyxy, l(0, 1, 1, 0)
mov r4.xy, r3.zwzz
mov r4.zw, l(0,0,0,0)
ld_indexable(texture2d)(float,float,float,float) r4.xyz, r4.xyzw, t0.xyzw
log r5.xyz, r4.xyzx
mul r4.xyz, r4.xyzx, l(12.920000, 12.920000, 12.920000, 0.000000)
max r4.xyz, r4.xyzx, l(0.040450, 0.040450, 0.040450, 0.000000)
mul r5.xyz, r5.xyzx, l(0.416667, 0.416667, 0.416667, 0.000000)
exp r5.xyz, r5.xyzx
mad r5.xyz, r5.xyzx, l(1.055000, 1.055000, 1.055000, 0.000000), l(-0.055000, -0.055000, -0.055000, 0.000000)
min r4.xyz, r4.xyzx, r5.xyzx
min r5.xyz, r0.xyzx, r4.xyzx
mov r2.zw, l(0,0,0,0)
ld_indexable(texture2d)(float,float,float,float) r2.xyz, r2.xyzw, t0.xyzw
log r6.xyz, r2.xyzx
mul r2.xyz, r2.xyzx, l(12.920000, 12.920000, 12.920000, 0.000000)
max r2.xyz, r2.xyzx, l(0.040450, 0.040450, 0.040450, 0.000000)
mul r6.xyz, r6.xyzx, l(0.416667, 0.416667, 0.416667, 0.000000)
exp r6.xyz, r6.xyzx
mad r6.xyz, r6.xyzx, l(1.055000, 1.055000, 1.055000, 0.000000), l(-0.055000, -0.055000, -0.055000, 0.000000)
min r2.xyz, r2.xyzx, r6.xyzx
min r5.xyz, r5.xyzx, r2.xyzx
mov r3.zw, l(0,0,0,0)
ld_indexable(texture2d)(float,float,float,float) r3.xyz, r3.xyzw, t0.xyzw
log r6.xyz, r3.xyzx
mul r3.xyz, r3.xyzx, l(12.920000, 12.920000, 12.920000, 0.000000)
max r3.xyz, r3.xyzx, l(0.040450, 0.040450, 0.040450, 0.000000)
mul r6.xyz, r6.xyzx, l(0.416667, 0.416667, 0.416667, 0.000000)
exp r6.xyz, r6.xyzx
mad r6.xyz, r6.xyzx, l(1.055000, 1.055000, 1.055000, 0.000000), l(-0.055000, -0.055000, -0.055000, 0.000000)
min r3.xyz, r3.xyzx, r6.xyzx
min r5.xyz, r3.xyzx, r5.xyzx
mad r6.xyz, r5.xyzx, l(4.000000, 4.000000, 4.000000, 0.000000), l(-4.000000, -4.000000, -4.000000, 0.000000)
rcp r6.xyz, r6.xyzx
max r7.xyz, r0.xyzx, r4.xyzx
max r7.xyz, r2.xyzx, r7.xyzx
max r7.xyz, r3.xyzx, r7.xyzx
add r8.xyz, -r7.xyzx, l(1.000000, 1.000000, 1.000000, 0.000000)
mul r7.xyz, r7.xyzx, l(4.000000, 4.000000, 4.000000, 0.000000)
rcp r7.xyz, r7.xyzx
mul r5.xyz, r5.xyzx, r7.xyzx
mul r6.xyz, r6.xyzx, r8.xyzx
max r5.xyz, -r5.xyzx, r6.xyzx
max r0.w, r5.z, r5.y
max r0.w, r0.w, r5.x
min r0.w, r0.w, l(0.000000)
max r0.w, r0.w, l(-0.187500)
mul r0.w, r0.w, cb0[0].x
mul r0.xyz, r0.xyzx, r0.wwww
mad r0.xyz, r0.wwww, r2.xyzx, r0.xyzx
mad r0.xyz, r0.wwww, r3.xyzx, r0.xyzx
mad r0.xyz, r0.wwww, r4.xyzx, r0.xyzx
mad r0.w, r0.w, l(4.000000), l(1.000000)
mov r1.zw, l(0,0,0,0)
ld_indexable(texture2d)(float,float,float,float) r2.xyz, r1.xyzw, t0.xyzw
log r3.xyz, r2.xyzx
mul r2.xyz, r2.xyzx, l(12.920000, 12.920000, 12.920000, 0.000000)
max r2.xyz, r2.xyzx, l(0.040450, 0.040450, 0.040450, 0.000000)
mul r3.xyz, r3.xyzx, l(0.416667, 0.416667, 0.416667, 0.000000)
exp r3.xyz, r3.xyzx
mad r3.xyz, r3.xyzx, l(1.055000, 1.055000, 1.055000, 0.000000), l(-0.055000, -0.055000, -0.055000, 0.000000)
min r2.xyz, r2.xyzx, r3.xyzx
add r0.xyz, r0.xyzx, r2.xyzx
iadd r1.z, -r0.w, l(0x7ef19fff)
mad r0.w, -r1.z, r0.w, l(2.000000)
mul r0.w, r0.w, r1.z
mul r2.xyz, r0.wwww, r0.xyzx
mad r0.xyz, r0.xyzx, r0.wwww, l(-0.003131, -0.003131, -0.003131, 0.000000)
mul_sat r0.xyz, r0.xyzx, l(-1.#INF00, -1.#INF00, -1.#INF00, 0.000000)
mad r3.xyz, r2.xyzx, l(0.947867, 0.947867, 0.947867, 0.000000), l(0.052133, 0.052133, 0.052133, 0.000000)
mul r2.xyz, r0.xyzx, r2.xyzx
log r3.xyz, r3.xyzx
mul r3.xyz, r3.xyzx, l(2.400000, 2.400000, 2.400000, 0.000000)
exp r3.xyz, r3.xyzx
mad r0.xyz, -r0.xyzx, r3.xyzx, r3.xyzx
mad r0.xyz, r2.xyzx, l(0.077399, 0.077399, 0.077399, 0.000000), r0.xyzx
mov r0.w, l(1.000000)
store_uav_typed u0.xyzw, r1.xyyy, r0.xyzw
ret 
// Approximately 94 instruction slots used
#endif

const BYTE g_mainCS[] =
{
     68,  88,  66,  67,  61, 228, 
    183, 114, 169,  43,   8, 102, 
    214, 132, 181,  91,  10, 230, 
    199,  70,   1,   0,   0,   0, 
      8,  15,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    148,   1,   0,   0, 164,   1, 
      0,   0, 180,   1,   0,   0, 
    108,  14,   0,   0,  82,  68, 
     69,  70,  88,   1,   0,   0, 
      1,   0,   0,   0, 188,   0, 
      0,   0,   3,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
     83,  67,   0, 129,   0,   0, 
     48,   1,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
    156,   0,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0, 169,   0,   0,   0, 
      4,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 183,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     73, 110, 112, 117, 116,  84, 
    101, 120, 116, 117, 114, 101, 
      0,  79, 117, 116, 112, 117, 
    116,  84, 101, 120, 116, 117, 
    114, 101,   0,  99,  98,   0, 
    171, 171, 183,   0,   0,   0, 
      1,   0,   0,   0, 212,   0, 
      0,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 252,   0,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     12,   1,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     99, 111, 110, 115, 116,  48, 
      0, 117, 105, 110, 116,  52, 
      0, 171, 171, 171,   1,   0, 
     19,   0,   1,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   1,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  49,  48,  46, 
     49,   0,  73,  83,  71,  78, 
      8,   0,   0,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     79,  83,  71,  78,   8,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  83,  72, 
     69,  88, 176,  12,   0,   0, 
     80,   0,   5,   0,  44,   3, 
      0,   0, 106,   8,   0,   1, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      0,   0,   0,   0,  85,  85, 
      0,   0, 156,  24,   0,   4, 
      0, 224,  17,   0,   0,   0, 
      0,   0,  85,  85,   0,   0, 
     95,   0,   0,   2,  50,  16, 
      2,   0,  95,   0,   0,   2, 
     18,  32,   2,   0, 104,   0, 
      0,   2,   9,   0,   0,   0, 
    155,   0,   0,   4,  64,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   8, 194,   0,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     85,   0,   0,   6,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,  32,   2,   0,   1,  64, 
      0,   0,   3,   0,   0,   0, 
    140,   0,   0,  10,  34,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  10,  32, 
      2,   0,  10,   0,  16,   0, 
      1,   0,   0,   0, 138,   0, 
      0,   8,  18,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   3,   0,   0,   0, 
      1,  64,   0,   0,   1,   0, 
      0,   0,  10,  32,   2,   0, 
     35,   0,   0,  11,  50,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  16,   2,   0,   2,  64, 
      0,   0,   8,   0,   0,   0, 
      8,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     70,   0,  16,   0,   1,   0, 
      0,   0,  30,   0,   0,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  70,   4,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     54,   0,   0,   5,  50,   0, 
     16,   0,   0,   0,   0,   0, 
    230,  10,  16,   0,   2,   0, 
      0,   0,  45,   0,   0, 137, 
    194,   0,   0, 128,  67,  85, 
     21,   0, 114,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,  47,   0,   0,   5, 
    114,   0,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,  10, 114,   0,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
      2,  64,   0,   0,  82, 184, 
     78,  65,  82, 184,  78,  65, 
     82, 184,  78,  65,   0,   0, 
      0,   0,  52,   0,   0,  10, 
    114,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0, 213, 174,  37,  61, 
    213, 174,  37,  61, 213, 174, 
     37,  61,   0,   0,   0,   0, 
     56,   0,   0,  10, 114,   0, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,   2,  64,   0,   0, 
     85,  85, 213,  62,  85,  85, 
    213,  62,  85,  85, 213,  62, 
      0,   0,   0,   0,  25,   0, 
      0,   5, 114,   0,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     50,   0,   0,  15, 114,   0, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,   2,  64,   0,   0, 
     61,  10, 135,  63,  61,  10, 
    135,  63,  61,  10, 135,  63, 
      0,   0,   0,   0,   2,  64, 
      0,   0, 174,  71,  97, 189, 
    174,  71,  97, 189, 174,  71, 
     97, 189,   0,   0,   0,   0, 
     51,   0,   0,   7, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  30,   0, 
      0,  10, 242,   0,  16,   0, 
      3,   0,   0,   0,  70,   4, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
     50,   0,  16,   0,   4,   0, 
      0,   0, 230,  10,  16,   0, 
      3,   0,   0,   0,  54,   0, 
      0,   8, 194,   0,  16,   0, 
      4,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     45,   0,   0, 137, 194,   0, 
      0, 128,  67,  85,  21,   0, 
    114,   0,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,  70, 126, 
     16,   0,   0,   0,   0,   0, 
     47,   0,   0,   5, 114,   0, 
     16,   0,   5,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,  56,   0,   0,  10, 
    114,   0,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      4,   0,   0,   0,   2,  64, 
      0,   0,  82, 184,  78,  65, 
     82, 184,  78,  65,  82, 184, 
     78,  65,   0,   0,   0,   0, 
     52,   0,   0,  10, 114,   0, 
     16,   0,   4,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,   2,  64,   0,   0, 
    213, 174,  37,  61, 213, 174, 
     37,  61, 213, 174,  37,  61, 
      0,   0,   0,   0,  56,   0, 
      0,  10, 114,   0,  16,   0, 
      5,   0,   0,   0,  70,   2, 
     16,   0,   5,   0,   0,   0, 
      2,  64,   0,   0,  85,  85, 
    213,  62,  85,  85, 213,  62, 
     85,  85, 213,  62,   0,   0, 
      0,   0,  25,   0,   0,   5, 
    114,   0,  16,   0,   5,   0, 
      0,   0,  70,   2,  16,   0, 
      5,   0,   0,   0,  50,   0, 
      0,  15, 114,   0,  16,   0, 
      5,   0,   0,   0,  70,   2, 
     16,   0,   5,   0,   0,   0, 
      2,  64,   0,   0,  61,  10, 
    135,  63,  61,  10, 135,  63, 
     61,  10, 135,  63,   0,   0, 
      0,   0,   2,  64,   0,   0, 
    174,  71,  97, 189, 174,  71, 
     97, 189, 174,  71,  97, 189, 
      0,   0,   0,   0,  51,   0, 
      0,   7, 114,   0,  16,   0, 
      4,   0,   0,   0,  70,   2, 
     16,   0,   4,   0,   0,   0, 
     70,   2,  16,   0,   5,   0, 
      0,   0,  51,   0,   0,   7, 
    114,   0,  16,   0,   5,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   4,   0,   0,   0, 
     54,   0,   0,   8, 194,   0, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  45,   0,   0, 137, 
    194,   0,   0, 128,  67,  85, 
     21,   0, 114,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,  47,   0,   0,   5, 
    114,   0,  16,   0,   6,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  56,   0, 
      0,  10, 114,   0,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,  82, 184, 
     78,  65,  82, 184,  78,  65, 
     82, 184,  78,  65,   0,   0, 
      0,   0,  52,   0,   0,  10, 
    114,   0,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,   2,  64, 
      0,   0, 213, 174,  37,  61, 
    213, 174,  37,  61, 213, 174, 
     37,  61,   0,   0,   0,   0, 
     56,   0,   0,  10, 114,   0, 
     16,   0,   6,   0,   0,   0, 
     70,   2,  16,   0,   6,   0, 
      0,   0,   2,  64,   0,   0, 
     85,  85, 213,  62,  85,  85, 
    213,  62,  85,  85, 213,  62, 
      0,   0,   0,   0,  25,   0, 
      0,   5, 114,   0,  16,   0, 
      6,   0,   0,   0,  70,   2, 
     16,   0,   6,   0,   0,   0, 
     50,   0,   0,  15, 114,   0, 
     16,   0,   6,   0,   0,   0, 
     70,   2,  16,   0,   6,   0, 
      0,   0,   2,  64,   0,   0, 
     61,  10, 135,  63,  61,  10, 
    135,  63,  61,  10, 135,  63, 
      0,   0,   0,   0,   2,  64, 
      0,   0, 174,  71,  97, 189, 
    174,  71,  97, 189, 174,  71, 
     97, 189,   0,   0,   0,   0, 
     51,   0,   0,   7, 114,   0, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      6,   0,   0,   0,  51,   0, 
      0,   7, 114,   0,  16,   0, 
      5,   0,   0,   0,  70,   2, 
     16,   0,   5,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   8, 
    194,   0,  16,   0,   3,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  45,   0, 
      0, 137, 194,   0,   0, 128, 
     67,  85,  21,   0, 114,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      0,   0,   0,   0,  47,   0, 
      0,   5, 114,   0,  16,   0, 
      6,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     56,   0,   0,  10, 114,   0, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,   2,  64,   0,   0, 
     82, 184,  78,  65,  82, 184, 
     78,  65,  82, 184,  78,  65, 
      0,   0,   0,   0,  52,   0, 
      0,  10, 114,   0,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
      2,  64,   0,   0, 213, 174, 
     37,  61, 213, 174,  37,  61, 
    213, 174,  37,  61,   0,   0, 
      0,   0,  56,   0,   0,  10, 
    114,   0,  16,   0,   6,   0, 
      0,   0,  70,   2,  16,   0, 
      6,   0,   0,   0,   2,  64, 
      0,   0,  85,  85, 213,  62, 
     85,  85, 213,  62,  85,  85, 
    213,  62,   0,   0,   0,   0, 
     25,   0,   0,   5, 114,   0, 
     16,   0,   6,   0,   0,   0, 
     70,   2,  16,   0,   6,   0, 
      0,   0,  50,   0,   0,  15, 
    114,   0,  16,   0,   6,   0, 
      0,   0,  70,   2,  16,   0, 
      6,   0,   0,   0,   2,  64, 
      0,   0,  61,  10, 135,  63, 
     61,  10, 135,  63,  61,  10, 
    135,  63,   0,   0,   0,   0, 
      2,  64,   0,   0, 174,  71, 
     97, 189, 174,  71,  97, 189, 
    174,  71,  97, 189,   0,   0, 
      0,   0,  51,   0,   0,   7, 
    114,   0,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   6,   0,   0,   0, 
     51,   0,   0,   7, 114,   0, 
     16,   0,   5,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      5,   0,   0,   0,  50,   0, 
      0,  15, 114,   0,  16,   0, 
      6,   0,   0,   0,  70,   2, 
     16,   0,   5,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
    128,  64,   0,   0, 128,  64, 
      0,   0, 128,  64,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0, 128, 192,   0,   0, 
    128, 192,   0,   0, 128, 192, 
      0,   0,   0,   0, 129,   0, 
      0,   5, 114,   0,  16,   0, 
      6,   0,   0,   0,  70,   2, 
     16,   0,   6,   0,   0,   0, 
     52,   0,   0,   7, 114,   0, 
     16,   0,   7,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      4,   0,   0,   0,  52,   0, 
      0,   7, 114,   0,  16,   0, 
      7,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   7,   0, 
      0,   0,  52,   0,   0,   7, 
    114,   0,  16,   0,   7,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   7,   0,   0,   0, 
      0,   0,   0,  11, 114,   0, 
     16,   0,   8,   0,   0,   0, 
     70,   2,  16, 128,  65,   0, 
      0,   0,   7,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
    128,  63,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
      0,   0,  56,   0,   0,  10, 
    114,   0,  16,   0,   7,   0, 
      0,   0,  70,   2,  16,   0, 
      7,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128,  64, 
      0,   0, 128,  64,   0,   0, 
    128,  64,   0,   0,   0,   0, 
    129,   0,   0,   5, 114,   0, 
     16,   0,   7,   0,   0,   0, 
     70,   2,  16,   0,   7,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   5,   0, 
      0,   0,  70,   2,  16,   0, 
      5,   0,   0,   0,  70,   2, 
     16,   0,   7,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   6,   0,   0,   0, 
     70,   2,  16,   0,   6,   0, 
      0,   0,  70,   2,  16,   0, 
      8,   0,   0,   0,  52,   0, 
      0,   8, 114,   0,  16,   0, 
      5,   0,   0,   0,  70,   2, 
     16, 128,  65,   0,   0,   0, 
      5,   0,   0,   0,  70,   2, 
     16,   0,   6,   0,   0,   0, 
     52,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     42,   0,  16,   0,   5,   0, 
      0,   0,  26,   0,  16,   0, 
      5,   0,   0,   0,  52,   0, 
      0,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   5,   0, 
      0,   0,  51,   0,   0,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     52,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,  64, 190,  56,   0, 
      0,   8, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     10, 128,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,   9, 114,   0,  16,   0, 
      0,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,   9, 114,   0,  16,   0, 
      0,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,   9, 114,   0,  16,   0, 
      0,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,   9, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128,  64,   1,  64,   0,   0, 
      0,   0, 128,  63,  54,   0, 
      0,   8, 194,   0,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     45,   0,   0, 137, 194,   0, 
      0, 128,  67,  85,  21,   0, 
    114,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  70, 126, 
     16,   0,   0,   0,   0,   0, 
     47,   0,   0,   5, 114,   0, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  56,   0,   0,  10, 
    114,   0,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,   2,  64, 
      0,   0,  82, 184,  78,  65, 
     82, 184,  78,  65,  82, 184, 
     78,  65,   0,   0,   0,   0, 
     52,   0,   0,  10, 114,   0, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,   2,  64,   0,   0, 
    213, 174,  37,  61, 213, 174, 
     37,  61, 213, 174,  37,  61, 
      0,   0,   0,   0,  56,   0, 
      0,  10, 114,   0,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
      2,  64,   0,   0,  85,  85, 
    213,  62,  85,  85, 213,  62, 
     85,  85, 213,  62,   0,   0, 
      0,   0,  25,   0,   0,   5, 
    114,   0,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,  15, 114,   0,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
      2,  64,   0,   0,  61,  10, 
    135,  63,  61,  10, 135,  63, 
     61,  10, 135,  63,   0,   0, 
      0,   0,   2,  64,   0,   0, 
    174,  71,  97, 189, 174,  71, 
     97, 189, 174,  71,  97, 189, 
      0,   0,   0,   0,  51,   0, 
      0,   7, 114,   0,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,   0,   0,   0,   7, 
    114,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     30,   0,   0,   8,  66,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
      1,  64,   0,   0, 255, 159, 
    241, 126,  50,   0,   0,  10, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16, 128, 
     65,   0,   0,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  64, 
     56,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      2,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  50,   0,   0,  12, 
    114,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
      2,  64,   0,   0,  49,  46, 
     77, 187,  49,  46,  77, 187, 
     49,  46,  77, 187,   0,   0, 
      0,   0,  56,  32,   0,  10, 
    114,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128, 255, 
      0,   0, 128, 255,   0,   0, 
    128, 255,   0,   0,   0,   0, 
     50,   0,   0,  15, 114,   0, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,   2,  64,   0,   0, 
    110, 167, 114,  63, 110, 167, 
    114,  63, 110, 167, 114,  63, 
      0,   0,   0,   0,   2,  64, 
      0,   0,  25, 137,  85,  61, 
     25, 137,  85,  61,  25, 137, 
     85,  61,   0,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  47,   0, 
      0,   5, 114,   0,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     56,   0,   0,  10, 114,   0, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,   2,  64,   0,   0, 
    154, 153,  25,  64, 154, 153, 
     25,  64, 154, 153,  25,  64, 
      0,   0,   0,   0,  25,   0, 
      0,   5, 114,   0,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     50,   0,   0,  10, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,  12, 114,   0,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0, 145, 131, 
    158,  61, 145, 131, 158,  61, 
    145, 131, 158,  61,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 130,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
    164,   0,   0,   7, 242, 224, 
     17,   0,   0,   0,   0,   0, 
     70,   5,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    148,   0,   0,   0,  94,   0, 
      0,   0,   9,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,  70,   0,   0,   0, 
      4,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   5,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0
};
