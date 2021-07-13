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
    uint4 const1;
    uint4 const2;
    uint4 const3;
};

SamplerState InputSampler : register(s0); // Not set from the code, but default LINEAR + CLAMP is fine.
Texture2D InputTexture : register(t0);
RWTexture2D<float4> OutputTexture : register(u0);

#define A_GPU 1
#define A_HLSL 1
#include "FidelityFX-FSR\ffx-fsr\ffx_a.h"

#define FSR_EASU_F 1

AF4 FsrEasuRF(AF2 p)
{
	AF4 res = InputTexture.GatherRed(InputSampler, p, int2(0, 0));
	if(LINEAR)
		res = float4(AToSrgbF1(res.x), AToSrgbF1(res.y), AToSrgbF1(res.z), AToSrgbF1(res.w));
	return res;
}
AF4 FsrEasuGF(AF2 p)
{
	AF4 res = InputTexture.GatherGreen(InputSampler, p, int2(0, 0));
	if(LINEAR)
		res = float4(AToSrgbF1(res.x), AToSrgbF1(res.y), AToSrgbF1(res.z), AToSrgbF1(res.w));
	return res;
}
AF4 FsrEasuBF(AF2 p)
{
	AF4 res = InputTexture.GatherBlue(InputSampler, p, int2(0, 0));
	if(LINEAR)
		res = float4(AToSrgbF1(res.x), AToSrgbF1(res.y), AToSrgbF1(res.z), AToSrgbF1(res.w));
	return res;
}

#include "FidelityFX-FSR\ffx-fsr\ffx_fsr1.h"

void CurrFilter(int2 pos)
{
	AF3 c;
	FsrEasuF(c, pos, const0, const1, const2, const3);
	if(LINEAR)
		c = AFromSrgbF3(c);
	OutputTexture[pos] = float4(c, 1);
}

[numthreads(64, 1, 1)]
void mainCS(uint3 LocalThreadId : SV_GroupThreadID, uint3 WorkGroupId : SV_GroupID)
{
	// Do remapping of local xy in workgroup for a more PS-like swizzle pattern.
	AU2 gxy = ARmp8x8(LocalThreadId.x) + AU2(WorkGroupId.x << 3u, WorkGroupId.y << 3u);
	CurrFilter(gxy);
}
