// LICENSE
// =======
// Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
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

#include "pch.hpp"

#define A_CPU 1
#define FSR_EASU_F 1
#define FSR_RCAS_F 1
#include "Shaders/FidelityFX-FSR/ffx-fsr/ffx_a.h"
#include "Shaders/FidelityFX-CAS/ffx-cas/ffx_cas.h"
#include "Shaders/FidelityFX-FSR/ffx-fsr/ffx_fsr1.h"

namespace CAS_NoScaling0_Linear0
{
    #include "Shaders/CompiledShader_CAS_NoScaling=0_Linear=0.h"
}
namespace CAS_NoScaling1_Linear0
{
    #include "Shaders/CompiledShader_CAS_NoScaling=1_Linear=0.h"
}
namespace CAS_NoScaling0_Linear1
{
    #include "Shaders/CompiledShader_CAS_NoScaling=0_Linear=1.h"
}
namespace CAS_NoScaling1_Linear1
{
    #include "Shaders/CompiledShader_CAS_NoScaling=1_Linear=1.h"
}
namespace EASU_Linear0
{
    #include "Shaders/CompiledShader_EASU_Linear=0.h"
}
namespace EASU_Linear1
{
    #include "Shaders/CompiledShader_EASU_Linear=1.h"
}
namespace RCAS_Linear0
{
    #include "Shaders/CompiledShader_RCAS_Linear=0.h"
}
namespace RCAS_Linear1
{
    #include "Shaders/CompiledShader_RCAS_Linear=1.h"
}

static const wchar_t* const APP_NAME = L"FidelityFX-CLI";
static const wchar_t* const EXE_NAME = L"FidelityFX_CLI";
static const wchar_t* const APP_VERSION = L"1.0.2";

enum class InterpolationMode
{
    EASU, RCAS,
    CAS,
    NearestNeighbor, Linear, Cubic, HighQualityCubic, Fant, Count
};

static InterpolationMode StrToInterpolationMode(const wchar_t* s)
{
    if(_wcsicmp(s, L"EASU") == 0 || _wcsicmp(s, L"FSR") == 0 || _wcsicmp(s, L"FSR1") == 0)
        return InterpolationMode::EASU;
    if(_wcsicmp(s, L"RCAS") == 0)
        return InterpolationMode::RCAS;
    if(_wcsicmp(s, L"CAS") == 0)
        return InterpolationMode::CAS;
    if(_wcsicmp(s, L"NearestNeighbor") == 0)
        return InterpolationMode::NearestNeighbor;
    if(_wcsicmp(s, L"Linear") == 0)
        return InterpolationMode::Linear;
    if(_wcsicmp(s, L"Cubic") == 0)
        return InterpolationMode::Cubic;
    if(_wcsicmp(s, L"HighQualityCubic") == 0)
        return InterpolationMode::HighQualityCubic;
    if(_wcsicmp(s, L"Fant") == 0)
        return InterpolationMode::Fant;
    return InterpolationMode::Count;
}

static WICBitmapInterpolationMode InterpolationModeToWicInterpolationMode(InterpolationMode mode)
{
    switch(mode)
    {
    case InterpolationMode::NearestNeighbor:
        return WICBitmapInterpolationModeNearestNeighbor;
    case InterpolationMode::Linear:
        return WICBitmapInterpolationModeLinear;
    case InterpolationMode::Cubic:
        return WICBitmapInterpolationModeCubic;
    case InterpolationMode::HighQualityCubic:
        return WICBitmapInterpolationModeHighQualityCubic;
    case InterpolationMode::Fant:
        return WICBitmapInterpolationModeFant;
    default:
        assert(0);
        return WICBitmapInterpolationModeNearestNeighbor;
    }
}

static inline bool InterpolationModeNeedsGpu(InterpolationMode mode)
{
    return mode == InterpolationMode::EASU ||
        mode == InterpolationMode::RCAS ||
        mode == InterpolationMode::CAS;
}

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)
#define CHECK_BOOL(expr)  do { if(!(expr)) throw std::runtime_error(__FILE__ "(" LINE_STRING "): !( " #expr " )"); } while(false)
#define CHECK_HR(expr)  do { if(FAILED(expr)) throw std::runtime_error(__FILE__ "(" LINE_STRING "): FAILED( " #expr " )"); } while(false)

struct uvec2
{
    uint32_t x, y;
    uvec2() { }
    uvec2(uint32_t x_, uint32_t y_) : x(x_), y(y_) { }

    bool operator==(const uvec2& rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const uvec2& rhs) const { return x != rhs.x || y != rhs.y; }
};

template <typename T>
inline T DivideRoundingUp(T x, T y)
{
    return (x+y-1) / y;
}

inline bool EndsWith(const wchar_t* s, const wchar_t* subS)
{
    size_t sLen = wcslen(s);
    size_t subSLen = wcslen(subS);
    if(sLen >= subSLen)
    {
        return _wcsicmp(s + (sLen - subSLen), subS) == 0;
    }
    return false;
}

struct FileToProcess
{
    std::wstring srcFilePath;
    std::wstring dstFilePath;
};

struct LaunchParameters
{
    static void PrintCommandLineSyntax();

    InterpolationMode interpolationMode = InterpolationMode::EASU;
    bool linear = false;
    bool fp16 = false;
    float sharpness = FLT_MAX;
    uvec2 dstSize = uvec2(UINT32_MAX, UINT32_MAX);
    std::vector<FileToProcess> filesToProcess;

    bool HasScaling() const { return dstSize.x != UINT32_MAX || dstSize.y != UINT32_MAX; }
    void ParseCommandLine(int argCount, const wchar_t* const* args);
};

class CoInitializeObj
{
public:
    CoInitializeObj() { CoInitializeEx(NULL, COINIT_MULTITHREADED); }
    ~CoInitializeObj() { CoUninitialize(); }
};

static GUID FilePathToContainerFormatGuid(const wchar_t* filePath)
{
    if(EndsWith(filePath, L".bmp") || EndsWith(filePath, L".dib"))
        return GUID_ContainerFormatBmp;
    else if(EndsWith(filePath, L".png"))
        return GUID_ContainerFormatPng;
    else if(EndsWith(filePath, L".ico"))
        return GUID_ContainerFormatIco;
    else if(EndsWith(filePath, L".jpg") || EndsWith(filePath, L".jpeg") || EndsWith(filePath, L".jpe"))
        return GUID_ContainerFormatJpeg;
    else if(EndsWith(filePath, L".tif") || EndsWith(filePath, L".tiff"))
        return GUID_ContainerFormatTiff;
    else if(EndsWith(filePath, L".gif"))
        return GUID_ContainerFormatGif;
    else if(EndsWith(filePath, L".dds"))
        return GUID_ContainerFormatDds;
    else if(EndsWith(filePath, L".wmp"))
        return GUID_ContainerFormatWmp;
    return GUID_NULL;
}

class GpuResources
{
public:
    GpuResources(const LaunchParameters& params);

    CComPtr<ID3D11Device> m_Dev;
    CComPtr<ID3D11DeviceContext> m_Ctx;

    void EASU(
        ID3D11UnorderedAccessView* dstUav, uvec2 dstSize,
        ID3D11ShaderResourceView* srcSrv, uvec2 srcSize) const;
    void RCAS(
        float sharpness,
        ID3D11UnorderedAccessView* dstUav, uvec2 dstSize,
        ID3D11ShaderResourceView* srcSrv, uvec2 srcSize) const;
    void CAS(
        float sharpness,
        ID3D11UnorderedAccessView* dstUav, uvec2 dstSize,
        ID3D11ShaderResourceView* srcSrv, uvec2 srcSize) const;

private:
    struct CASConstantBufferStructure
    {
        varAU4(const0);
        varAU4(const1);
    };
    struct EASUConstantBufferStructure
    {
        varAU4(const0);
        varAU4(const1);
        varAU4(const2);
        varAU4(const3);
    };
    struct RCASConstantBufferStructure
    {
        varAU4(const0);
    };

    CComPtr<ID3D11Buffer> m_ConstantBuffer;
    CComPtr<ID3D11ComputeShader> m_EASUComputeShader;
    CComPtr<ID3D11ComputeShader> m_RCASComputeShader;
    CComPtr<ID3D11ComputeShader> m_CASComputeShader;
    CComPtr<ID3D11ComputeShader> m_CASComputeShader_NoScaling;

    static void GetCASShaderCode(
        const BYTE*& outCode_NoScaling0, size_t& outCodeSize_NoScaling0,
        const BYTE*& outCode_NoScaling1, size_t& outCodeSize_NoScaling1,
        const LaunchParameters& params);
};

class Application
{
public:
    Application(const LaunchParameters& params);
    ~Application() { }
    void Process() const;

private:
    const LaunchParameters& m_Params;
    CComPtr<IWICImagingFactory> m_WICImagingFactory;
    std::unique_ptr<GpuResources> m_GpuResources;

    void PrintColorSpaceInformation() const;
    void ProcessFile(const FileToProcess& fileToProcess) const;
    void ProcessImageOnGpu(IWICBitmapSource* bitmapSource, uvec2 dstSize, uvec2 srcSize, const wchar_t* dstFilePath) const;
    void ProcessImageOnCpu(IWICBitmapSource* bitmapSource, uvec2 dstSize, uvec2 srcSize, const wchar_t* dstFilePath) const;
    void SaveFile(IWICBitmapSource* bitmapSource, const wchar_t* filePath) const;
};

void LaunchParameters::PrintCommandLineSyntax()
{
    wprintf(L"%s %s\n", APP_NAME, APP_VERSION);
    wprintf(L"Command line syntax:\n");
    wprintf(L"  %s.exe [Options] <SrcFile1> <DstFile1> <SrcFile2> <DstFile2> ...\n", EXE_NAME);
    wprintf(
        L"Options:\n"
        L"-Scale <DstWidth> <DstHeight>\n"
        L"-Mode <Mode>\n"
        L"  Modes from FSR package:\n"
        L"    EASU - Edge Adaptive Spatial Upsampling (default) aliases: FSR, FSR1\n"
        L"    RCAS - Robust Contrast Adaptive Sharpening (doesn't support Scale)\n"
        L"  Modes from CAS package:\n"
        L"    CAS - Contrast Adaptive Sharpening\n"
        L"  Modes from Windows Imaging Component:\n"
        L"    NearestNeighbor, Linear, Cubic, HighQualityCubic, Fant\n"
        L"-Sharpness <Value>\n"
        L"  -Mode CAS: range from 0.0 (default) to 1.0 (maximum extra sharpness)\n"
        L"  -Mode RCAS: range from 0.0 (maximum sharpness) to number of stops (halving) of the reduction of sharpness\n"
        L"-FP16\n"
        L"  If not set (default), uses R8G8B8A8_UNORM GPU texture format.\n"
        L"  If set, uses R16G16B16A16_FLOAT GPU texture format.\n"
        L"-Linear\n"
        L"  If not set (default), treats input and output image as sRGB.\n"
        L"  If set, treats input and output image as linear.\n"
        L"  Works only when -FP16 is not specified.\n"
        L"Supported formats: BMP, PNG, ICO, JPG, TIF, GIF\n");
}

void LaunchParameters::ParseCommandLine(int argCount, const wchar_t* const* args)
{
    int i = 0;

    // Options
    for(; i < argCount && args[i][0] == L'-'; ++i)
    {
        if(wcscmp(args[i], L"-Mode") == 0 && i + 1 < argCount)
        {
            this->interpolationMode = StrToInterpolationMode(args[++i]);
            if(this->interpolationMode == InterpolationMode::Count)
            {
                throw std::runtime_error("Invalid Mode.");
            }
        }
        else if(wcscmp(args[i], L"-Scale") == 0 && i + 2 < argCount)
        {
            this->dstSize.x = (uint32_t)_wtoi(args[++i]);
            this->dstSize.y = (uint32_t)_wtoi(args[++i]);
        }
        else if(wcscmp(args[i], L"-Linear") == 0)
        {
            this->linear = true;
        }
        else if(wcscmp(args[i], L"-FP16") == 0)
        {
            this->fp16 = true;
        }
        else if(wcscmp(args[i], L"-Sharpness") == 0 && i + 1 < argCount)
        {
            this->sharpness = (float)_wtof(args[++i]);
        }
        else
        {
            throw std::runtime_error("Unknown command line option.");
        }
    }

    // Files
    if((argCount - i) % 2)
    {
        throw std::runtime_error("Invalid command line syntax.");
    }
    for(; i < argCount; i += 2)
    {
        FileToProcess cmd;
        cmd.srcFilePath = args[i];
        cmd.dstFilePath = args[i + 1];
        this->filesToProcess.push_back(std::move(cmd));
    }

    // Validate
    if(this->interpolationMode == InterpolationMode::RCAS && HasScaling())
    {
        throw std::runtime_error("RCAS mode cannot be used with Scale.");
    }
    if(this->sharpness == FLT_MAX)
    {
        this->sharpness = this->interpolationMode == InterpolationMode::RCAS
            ? 0.2f  // Default sharpness for RCAS
            : 0.0f; // Default sharpness for CAS
    }
    else
    {
        if(this->interpolationMode != InterpolationMode::CAS &&
            this->interpolationMode != InterpolationMode::RCAS)
        {
            throw std::runtime_error("Sharpness can only be used in CAS or RCAS mode.");
        }
    }
}

GpuResources::GpuResources(const LaunchParameters& params)
{
    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };

    D3D_FEATURE_LEVEL outFeatureLevel;
    CHECK_HR( D3D11CreateDevice(
        nullptr, // pAdapter
        D3D_DRIVER_TYPE_HARDWARE, // DriverType
        NULL, // Software
        D3D11_CREATE_DEVICE_SINGLETHREADED, // Flags
        featureLevels, // pFeatureLevels
        _countof(featureLevels), // FeatureLevels
        D3D11_SDK_VERSION, // SDKVersion
        &m_Dev, // ppDevice
        &outFeatureLevel, // pFeatureLevel
        &m_Ctx) ); // ppImmediateContext

    if(params.interpolationMode == InterpolationMode::EASU)
    {
        CD3D11_BUFFER_DESC constantBufferDesc = CD3D11_BUFFER_DESC(sizeof(EASUConstantBufferStructure), D3D11_BIND_CONSTANT_BUFFER);
        CHECK_HR( m_Dev->CreateBuffer(&constantBufferDesc, nullptr, &m_ConstantBuffer) );

        if(params.linear)
        {
            CHECK_HR( m_Dev->CreateComputeShader(EASU_Linear1::g_mainCS, _countof(EASU_Linear1::g_mainCS),
                nullptr, &m_EASUComputeShader) );
        }
        else
        {
            CHECK_HR( m_Dev->CreateComputeShader(EASU_Linear0::g_mainCS, _countof(EASU_Linear0::g_mainCS),
                nullptr, &m_EASUComputeShader) );
        }
    }
    else if(params.interpolationMode == InterpolationMode::RCAS)
    {
        CD3D11_BUFFER_DESC constantBufferDesc = CD3D11_BUFFER_DESC(sizeof(RCASConstantBufferStructure), D3D11_BIND_CONSTANT_BUFFER);
        CHECK_HR( m_Dev->CreateBuffer(&constantBufferDesc, nullptr, &m_ConstantBuffer) );

        if(params.linear)
        {
            CHECK_HR( m_Dev->CreateComputeShader(RCAS_Linear1::g_mainCS, _countof(RCAS_Linear1::g_mainCS),
                nullptr, &m_RCASComputeShader) );
        }
        else
        {
            CHECK_HR( m_Dev->CreateComputeShader(RCAS_Linear0::g_mainCS, _countof(RCAS_Linear0::g_mainCS),
                nullptr, &m_RCASComputeShader) );
        }
    }
    else if(params.interpolationMode == InterpolationMode::CAS)
    {
        CD3D11_BUFFER_DESC constantBufferDesc = CD3D11_BUFFER_DESC(sizeof(CASConstantBufferStructure), D3D11_BIND_CONSTANT_BUFFER);
        CHECK_HR( m_Dev->CreateBuffer(&constantBufferDesc, nullptr, &m_ConstantBuffer) );

        const BYTE* shaderCode_NoScaling0;
        const BYTE* shaderCode_NoScaling1;
        size_t shaderCodeSize_NoScaling0;
        size_t shaderCodeSize_NoScaling1;
        GetCASShaderCode(
            shaderCode_NoScaling0, shaderCodeSize_NoScaling0,
            shaderCode_NoScaling1, shaderCodeSize_NoScaling1,
            params);
        CHECK_HR( m_Dev->CreateComputeShader(shaderCode_NoScaling0, shaderCodeSize_NoScaling0,
            nullptr, &m_CASComputeShader) );
        CHECK_HR( m_Dev->CreateComputeShader(shaderCode_NoScaling1, shaderCodeSize_NoScaling1,
            nullptr, &m_CASComputeShader_NoScaling) );
    }
    else
        assert(0);
}

void GpuResources::GetCASShaderCode(
    const BYTE*& outCode_NoScaling0, size_t& outCodeSize_NoScaling0,
    const BYTE*& outCode_NoScaling1, size_t& outCodeSize_NoScaling1,
    const LaunchParameters& params)
{
    // When half-float format is used, conversion from/to linear is performed implicitly by WIC.
    if(params.linear || params.fp16)
    {
        outCode_NoScaling0 = CAS_NoScaling0_Linear1::g_mainCS;
        outCodeSize_NoScaling0 = _countof(CAS_NoScaling0_Linear1::g_mainCS);
        outCode_NoScaling1 = CAS_NoScaling1_Linear1::g_mainCS;
        outCodeSize_NoScaling1 = _countof(CAS_NoScaling1_Linear1::g_mainCS);
    }
    else
    {
        outCode_NoScaling0 = CAS_NoScaling0_Linear0::g_mainCS;
        outCodeSize_NoScaling0 = (uint32_t)_countof(CAS_NoScaling0_Linear0::g_mainCS);
        outCode_NoScaling1 = CAS_NoScaling1_Linear0::g_mainCS;
        outCodeSize_NoScaling1 = (uint32_t)_countof(CAS_NoScaling1_Linear0::g_mainCS);
    }
}

void GpuResources::EASU(
    ID3D11UnorderedAccessView* dstUav, uvec2 dstSize,
    ID3D11ShaderResourceView* srcSrv, uvec2 srcSize) const
{
    EASUConstantBufferStructure constBufStruct;

    FsrEasuCon(
        constBufStruct.const0, constBufStruct.const1, constBufStruct.const2, constBufStruct.const3,
        (float)srcSize.x, (float)srcSize.y,
        (float)srcSize.x, (float)srcSize.y,
        (float)dstSize.x, (float)dstSize.y);
    m_Ctx->UpdateSubresource(m_ConstantBuffer, 0, NULL, &constBufStruct, sizeof(constBufStruct), 0);

    ID3D11ComputeShader* const computeShader = m_EASUComputeShader;
    m_Ctx->CSSetShader(computeShader, nullptr, 0);

    ID3D11Buffer* cbPtr = m_ConstantBuffer;
    m_Ctx->CSSetConstantBuffers(0, 1, &cbPtr);

    m_Ctx->CSSetShaderResources(0, 1, &srcSrv);

    m_Ctx->CSSetUnorderedAccessViews(0, 1, &dstUav, nullptr);

    m_Ctx->Dispatch(DivideRoundingUp(dstSize.x, 8u), DivideRoundingUp(dstSize.y, 8u), 1);
}

void GpuResources::RCAS(
    float sharpness,
    ID3D11UnorderedAccessView* dstUav, uvec2 dstSize,
    ID3D11ShaderResourceView* srcSrv, uvec2 srcSize) const
{
    assert(dstSize == srcSize);

    RCASConstantBufferStructure constBufStruct;

    FsrRcasCon(constBufStruct.const0, sharpness);
    m_Ctx->UpdateSubresource(m_ConstantBuffer, 0, NULL, &constBufStruct, sizeof(constBufStruct), 0);

    ID3D11ComputeShader* const computeShader = m_RCASComputeShader;
    m_Ctx->CSSetShader(computeShader, nullptr, 0);

    ID3D11Buffer* cbPtr = m_ConstantBuffer;
    m_Ctx->CSSetConstantBuffers(0, 1, &cbPtr);

    m_Ctx->CSSetShaderResources(0, 1, &srcSrv);

    m_Ctx->CSSetUnorderedAccessViews(0, 1, &dstUav, nullptr);

    m_Ctx->Dispatch(DivideRoundingUp(dstSize.x, 8u), DivideRoundingUp(dstSize.y, 8u), 1);
}

void GpuResources::CAS(
    float sharpness,
    ID3D11UnorderedAccessView* dstUav, uvec2 dstSize,
    ID3D11ShaderResourceView* srcSrv, uvec2 srcSize) const
{
    CASConstantBufferStructure constBufStruct;

    CasSetup(constBufStruct.const0, constBufStruct.const1, sharpness, (float)srcSize.x, (float)srcSize.y, (float)dstSize.x, (float)dstSize.y);
    m_Ctx->UpdateSubresource(m_ConstantBuffer, 0, NULL, &constBufStruct, sizeof(constBufStruct), 0);

    const bool noScaling = dstSize.x == srcSize.x && dstSize.y == srcSize.y;
    ID3D11ComputeShader* const computeShader = noScaling ? m_CASComputeShader_NoScaling : m_CASComputeShader;
    m_Ctx->CSSetShader(computeShader, nullptr, 0);

    ID3D11Buffer* cbPtr = m_ConstantBuffer;
    m_Ctx->CSSetConstantBuffers(0, 1, &cbPtr);

    m_Ctx->CSSetShaderResources(0, 1, &srcSrv);

    m_Ctx->CSSetUnorderedAccessViews(0, 1, &dstUav, nullptr);

    m_Ctx->Dispatch(DivideRoundingUp(dstSize.x, 16u), DivideRoundingUp(dstSize.y, 16u), 1);
}

Application::Application(const LaunchParameters& params) :
    m_Params(params)
{
    CHECK_HR( CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_WICImagingFactory)) );

    if(InterpolationModeNeedsGpu(params.interpolationMode))
    {
        m_GpuResources = std::make_unique<GpuResources>(params);
    }
}

void Application::Process() const
{
    PrintColorSpaceInformation();

    for(const FileToProcess& file : m_Params.filesToProcess)
    {
        ProcessFile(file);
    }
}

void Application::PrintColorSpaceInformation() const
{
    if(!m_Params.fp16)
    {
        switch(m_Params.interpolationMode)
        {
        case InterpolationMode::CAS:
            if(m_Params.linear)
                wprintf(L"Treating input/output images as linear space, processing as linear.\n");
            else
                wprintf(L"Treating input/output images as sRGB space, converting to linear for processing.\n");
            break;
        case InterpolationMode::EASU:
        case InterpolationMode::RCAS:
            if(m_Params.linear)
                wprintf(L"Treating input/output images as linear space, converting to sRGB for processing.\n");
            else
                wprintf(L"Treating input/output images as sRGB space, processing as sRGB.\n");
            break;
        }
    }
}

void Application::ProcessFile(const FileToProcess& fileToProcess) const
{
    wprintf(L"Loading \"%s\"...\n", fileToProcess.srcFilePath.c_str());

    CComPtr<IWICBitmapDecoder> decoder;
    CHECK_HR( m_WICImagingFactory->CreateDecoderFromFilename(
        fileToProcess.srcFilePath.c_str(),
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnDemand,
        &decoder) );
    
    CComPtr<IWICBitmapFrameDecode> frameDecode;
    CHECK_HR( decoder->GetFrame(0, &frameDecode) );

    uvec2 srcSize = uvec2(0, 0);
    CHECK_HR( frameDecode->GetSize(&srcSize.x, &srcSize.y) );

    const uvec2 dstSize = uvec2(
        m_Params.dstSize.x != UINT32_MAX ? m_Params.dstSize.x : srcSize.x,
        m_Params.dstSize.y != UINT32_MAX ? m_Params.dstSize.y : srcSize.y);

    if(InterpolationModeNeedsGpu(m_Params.interpolationMode))
    {
        ProcessImageOnGpu(frameDecode, dstSize, srcSize, fileToProcess.dstFilePath.c_str());
    }
    else
    {
        ProcessImageOnCpu(frameDecode, dstSize, srcSize, fileToProcess.dstFilePath.c_str());
    }
}

void Application::ProcessImageOnGpu(IWICBitmapSource* bitmapSource, uvec2 dstSize, uvec2 srcSize, const wchar_t* dstFilePath) const
{
    assert(m_GpuResources);
    ID3D11Device* const dev = m_GpuResources->m_Dev;
    ID3D11DeviceContext* const ctx = m_GpuResources->m_Ctx;

    const WICPixelFormatGUID gpuTexturePixelFormat = m_Params.fp16 ?
        GUID_WICPixelFormat64bppRGBAHalf : GUID_WICPixelFormat32bppRGBA;
    const uint32_t rgbaBytesPerPixel = m_Params.fp16 ? 8 : 4;

    CComPtr<IWICFormatConverter> srcFormatConverter;
    CHECK_HR( m_WICImagingFactory->CreateFormatConverter(&srcFormatConverter) );
    CHECK_HR( srcFormatConverter->Initialize(bitmapSource, gpuTexturePixelFormat, WICBitmapDitherTypeNone,
        NULL, 0.f, WICBitmapPaletteTypeCustom) );

    const uint32_t srcTextureRowStride = srcSize.x * rgbaBytesPerPixel;
    const uint32_t srcTextureBufSize = srcSize.y * srcTextureRowStride;
    std::vector<uint8_t> srcTextureData(srcTextureBufSize);
    WICRect rect = {0, 0, (int32_t)srcSize.x, (int32_t)srcSize.y};
    srcFormatConverter->CopyPixels(&rect, srcTextureRowStride, srcSize.y * srcTextureRowStride, srcTextureData.data());

    srcFormatConverter.Release();

    const DXGI_FORMAT d3dTextureFormat = m_Params.fp16 ?
        DXGI_FORMAT_R16G16B16A16_FLOAT : DXGI_FORMAT_R8G8B8A8_UNORM;

    CD3D11_TEXTURE2D_DESC srcTextureDesc = CD3D11_TEXTURE2D_DESC(
        d3dTextureFormat, srcSize.x, srcSize.y, 1, 1, D3D11_BIND_SHADER_RESOURCE,
        D3D11_USAGE_DEFAULT);
    D3D11_SUBRESOURCE_DATA srcTextureSubresData = { srcTextureData.data(), srcTextureRowStride };
    CComPtr<ID3D11Texture2D> srcTexture;
    CHECK_HR( dev->CreateTexture2D(&srcTextureDesc, &srcTextureSubresData, &srcTexture) );

    if(!CasSupportScaling((float)dstSize.x, (float)dstSize.y, (float)srcSize.x, (float)srcSize.y))
    {
        wprintf(L"WARNING: Scaling factor is greater than recommended %g.\n", CAS_AREA_LIMIT);
    }

    CD3D11_TEXTURE2D_DESC dstTextureDesc = CD3D11_TEXTURE2D_DESC(
        d3dTextureFormat, dstSize.x, dstSize.y, 1, 1, D3D11_BIND_UNORDERED_ACCESS,
        D3D11_USAGE_DEFAULT);
    CComPtr<ID3D11Texture2D> dstTexture;
    CHECK_HR( dev->CreateTexture2D(&dstTextureDesc, nullptr, &dstTexture) );

    CD3D11_SHADER_RESOURCE_VIEW_DESC srcTextureViewDesc = CD3D11_SHADER_RESOURCE_VIEW_DESC(
        srcTexture, D3D11_SRV_DIMENSION_TEXTURE2D);
    CComPtr<ID3D11ShaderResourceView> srcTextureView;
    CHECK_HR( dev->CreateShaderResourceView(srcTexture, &srcTextureViewDesc, &srcTextureView) );

    CD3D11_UNORDERED_ACCESS_VIEW_DESC dstTextureViewDesc = CD3D11_UNORDERED_ACCESS_VIEW_DESC(
        dstTexture, D3D11_UAV_DIMENSION_TEXTURE2D);
    CComPtr<ID3D11UnorderedAccessView> dstTextureView;
    CHECK_HR( dev->CreateUnorderedAccessView(dstTexture, &dstTextureViewDesc, &dstTextureView) );

    switch(m_Params.interpolationMode)
    {
    case InterpolationMode::RCAS:
        m_GpuResources->RCAS(m_Params.sharpness, dstTextureView, dstSize, srcTextureView, srcSize);
        break;
    case InterpolationMode::EASU:
        m_GpuResources->EASU(dstTextureView, dstSize, srcTextureView, srcSize);
        break;
    case InterpolationMode::CAS:
        m_GpuResources->CAS(m_Params.sharpness, dstTextureView, dstSize, srcTextureView, srcSize);
        break;
    default:
        assert(0);
    }

    srcTextureView.Release();
    srcTexture.Release();

    CD3D11_TEXTURE2D_DESC dstStagingTextureDesc = CD3D11_TEXTURE2D_DESC(
        d3dTextureFormat, dstSize.x, dstSize.y, 1, 1, 0, D3D11_USAGE_STAGING, D3D11_CPU_ACCESS_READ);
    CComPtr<ID3D11Texture2D> dstStagingTexture;
    CHECK_HR( dev->CreateTexture2D(&dstStagingTextureDesc, nullptr, &dstStagingTexture) );

    ctx->CopyResource(dstStagingTexture, dstTexture);

    dstTextureView.Release();
    dstTexture.Release();

    D3D11_MAPPED_SUBRESOURCE mappedDstTexture;
    CHECK_HR( ctx->Map(dstStagingTexture, 0, D3D11_MAP_READ, 0, &mappedDstTexture) );

    CComPtr<IWICBitmap> downloadedBitmap;
    CHECK_HR( m_WICImagingFactory->CreateBitmapFromMemory(dstSize.x, dstSize.y, gpuTexturePixelFormat, mappedDstTexture.RowPitch,
        mappedDstTexture.RowPitch * dstSize.y, (BYTE*)mappedDstTexture.pData, &downloadedBitmap) );
    
    ctx->Unmap(dstStagingTexture, 0);
    dstStagingTexture.Release();

    const WICPixelFormatGUID dstFilePixelFormat = GUID_WICPixelFormat24bppBGR;

    CComPtr<IWICFormatConverter> dstFormatConverter;
    CHECK_HR( m_WICImagingFactory->CreateFormatConverter(&dstFormatConverter) );
    CHECK_HR( dstFormatConverter->Initialize(downloadedBitmap, dstFilePixelFormat, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeCustom) );

    SaveFile(dstFormatConverter, dstFilePath);
}

void Application::ProcessImageOnCpu(IWICBitmapSource* bitmapSource, uvec2 dstSize, uvec2 srcSize, const wchar_t* dstFilePath) const
{
    CComPtr<IWICBitmapScaler> scaler;
    CHECK_HR( m_WICImagingFactory->CreateBitmapScaler(&scaler) );
    CHECK_HR( scaler->Initialize(bitmapSource, dstSize.x, dstSize.y,
        InterpolationModeToWicInterpolationMode(m_Params.interpolationMode)) );

    SaveFile(scaler, dstFilePath);
}

void Application::SaveFile(IWICBitmapSource* bitmapSource, const wchar_t* filePath) const
{
    wprintf(L"Saving \"%s\"...\n", filePath);

    CComPtr<IWICStream> dstStream;
    CHECK_HR( m_WICImagingFactory->CreateStream(&dstStream) );
    CHECK_HR( dstStream->InitializeFromFilename(filePath, GENERIC_WRITE) );

    CComPtr<IWICBitmapEncoder> encoder;
    const GUID containerFormatGuid = FilePathToContainerFormatGuid(filePath);
    CHECK_BOOL( containerFormatGuid != GUID_NULL );
    CHECK_HR( m_WICImagingFactory->CreateEncoder(containerFormatGuid, NULL, &encoder) );
    CHECK_HR( encoder->Initialize(dstStream, WICBitmapEncoderNoCache) );

    CComPtr<IWICBitmapFrameEncode> frameEncode;
    CComPtr<IPropertyBag2> propertyBag;
    CHECK_HR( encoder->CreateNewFrame(&frameEncode, &propertyBag) );
    CHECK_HR( frameEncode->Initialize(propertyBag) );
    CHECK_HR( frameEncode->WriteSource(bitmapSource, nullptr) );
    CHECK_HR( frameEncode->Commit() );
    CHECK_HR( encoder->Commit() );
}

int wmain(int argc, wchar_t** argv)
{
    try
    {
        if(argc <= 1)
        {
            LaunchParameters::PrintCommandLineSyntax();
            return 1;
        }

        LaunchParameters params;
        params.ParseCommandLine(argc - 1, argv + 1);

        CoInitializeObj coInitializeObj;

        Application app(params);
        app.Process();
        
        return 0;
    }
    catch(const std::exception& ex)
    {
        fprintf(stderr, "ERROR: %s\n", ex.what());
        return -1;
    }
}
