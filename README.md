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

## Introduction

FidelityFX Super Resolution (FSR) is an open source, high-quality solution for producing high resolution frames from lower resolution inputs. For more information, see dedciated page on [amd.com](https://www.amd.com/en/technologies/radeon-software-fidelityfx-super-resolution), [GPUOpen.com](https://gpuopen.com/fsr), [GitHub](https://github.com/GPUOpen-Effects/FidelityFX-FSR).

Contrast Adaptive Sharpening (CAS) is a low overhead adaptive sharpening algorithm with optional up-sampling. For more information, see dedciated page on [amd.com](https://www.amd.com/en/technologies/radeon-software-fidelityfx), [GPUOpen.com](https://gpuopen.com/fidelityfx-cas/), [GitHub](https://github.com/GPUOpen-Effects/FidelityFX-CAS).

This project is a small command-line Windows tool that processes image files using the FSR or CAS algorithm. It allows to test how the shaders would affect screenshots from your game. Releases contain executable binary while this respository contains source code.

## Command line syntax

```
FidelityFX-CLI 1.0.3
Command line syntax:
  FidelityFX_CLI.exe [Options] <SrcFile1> <DstFile1> <SrcFile2> <DstFile2> ...
Options:
-Scale <DstWidth> <DstHeight>
  Width, Height can be:
    Number: -Scale 3840 2160
    Scale factor: -Scale 2x 2x
    Percent: -Scale 150% 150%
-QualityMode <Quality>
  Specify instead of -Scale to use one of the predefined scaling factors.
  Quality can be: UltraQuality (1.3x), Quality (1.5x), Balanced (1.7x), Performance (2x)
-Mode <Mode>
  Modes from FSR package:
    EASU - Edge Adaptive Spatial Upsampling (default) aliases: FSR, FSR1
    RCAS - Robust Contrast Adaptive Sharpening (doesn't support Scale)
  Modes from CAS package:
    CAS - Contrast Adaptive Sharpening
  Modes from Windows Imaging Component:
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
Supported formats: BMP, PNG, ICO, JPG, TIF, GIF
```

## Additional information

Written in C++ using Visual Studio 2019 and Cmake. No external dependencies other than the Windows API and Direct3D 11. Image file formats are handled using the [Windows Imaging Component (WIC)](https://docs.microsoft.com/en-us/windows/win32/wic/-wic-about-windows-imaging-codec) framework (part of Windows API). Shaders are compiled to H files (with a little help from the [Fx Batch Compiler](https://github.com/sawickiap/FxBatchCompiler) tool) and bundled with the source code to build the executable.
