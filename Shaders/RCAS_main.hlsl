// LICENSE
// =======
// Copyright (c) 2021 Advanced Micro Devices, Inc. All rights reserved.
// -------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
// -------
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
// -------
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

cbuffer cb : register(b0)
{
	uint4 const0;
};

Texture2D InputTexture : register(t0);
RWTexture2D<float4> OutputTexture : register(u0);

#define A_GPU 1
#define A_HLSL 1
#include "FidelityFX-FSR\ffx-fsr\ffx_a.h"

#define FSR_RCAS_F 1

AF4 FsrRcasLoadF(ASU2 p)
{
	return InputTexture.Load(int3(p, 0));
}

void FsrRcasInputF(inout AF1 r,inout AF1 g,inout AF1 b)
{
	if(LINEAR)
	{
		r = AToSrgbF1(r);
		g = AToSrgbF1(g);
		b = AToSrgbF1(b);
	}
}

#include "FidelityFX-FSR\ffx-fsr\ffx_fsr1.h"

[numthreads(64, 1, 1)]
void mainCS(uint3 LocalThreadId : SV_GroupThreadID, uint3 WorkGroupId : SV_GroupID)
{
	// Remapped local xy in workgroup.
	AU2 gxy=ARmp8x8(LocalThreadId.x)+AU2(WorkGroupId.x<<3u,WorkGroupId.y<<3u);
	// Fetch the constant from some constant buffer.
	// Run the filter.
	AF3 c;
	FsrRcasF(c.r,c.g,c.b,gxy,const0);
	if(LINEAR)
	{
		c = AFromSrgbF3(c);
	}
	OutputTexture[gxy] = AF4(c, 1);
}
