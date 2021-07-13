# FidelityFX-CLI

Copyright (c) 2021 Advanced Micro Devices, Inc. All rights reserved.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

## Overview

Simple command line tool that processes image files using the FidelityFX Super Resolution (FSR) or Contrast Adaptive Sharpening (CAS) shader systems.

```
FidelityFX-CLI 1.0.0

Command line syntax:
  FidelityFX_CLI.exe [Options] <SrcFile1> <DstFile1> <SrcFile2> <DstFile2> ...

Options:
-Scale <DstWidth> <DstHeight>
-Mode <Mode>
  Modes from FSR package:
    EASU - Edge Adaptive Spatial Upsampling (default) aliases: FSR, FSR1
    RCAS - Robust Contrast Adaptive Sharpening (doesn't support Scale)
  Modes from CAS package:
    CAS - Contrast Adaptive Sharpening
  Modes from Windows Imaging Component (WICBitmapInterpolationMode):
    NearestNeighbor, Linear, Cubic, HighQualityCubic, Fant
-Sharpness <Value>
  -Mode CAS: range from 0.0 (default) to 1.0 (maximum extra sharpness)
  -Mode RCAS: range from 0.0 (maximum sharpness) to number of stops (halving) of the reduction of sharpness
-FP16
  If not set (default), uses R8G8B8A8_UNORM GPU texture format.
  If set, uses R16G16B16A16_FLOAT GPU texture format.
-Linear
  If not set (default), treats input and output image as sRGB.
  If set, treats input and output image as linear.
  Works only when -FP16 is not specified.

Supported input formats: BMP, PNG, ICO, JPG, TIF, GIF
```

Written in C++ using Visual Studio 2019. No external dependencies other than the WIC API and Direct3D 11. Image file formats are handled using the [Windows Imaging Component (WIC)](https://docs.microsoft.com/en-us/windows/win32/wic/-wic-about-windows-imaging-codec) framework. Shaders are compiled to H files (with a little help from the [Fx Batch Compiler](https://github.com/sawickiap/FxBatchCompiler) tool) and bundled with the source code to build the executable.


