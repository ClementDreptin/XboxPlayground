#include "pch.h"
#include "Renderer/PixelShader.h"

#include "Renderer/D3DDevice.h"

// Pixel shader source code
static const char shaderSource[] =
    " float4 c_color : register(c0);    "
    "                                   "
    " float4 main() : COLOR             "
    " {                                 "
    "     return c_color;               "
    " }                                 ";

PixelShader::PixelShader()
    : m_pShader(nullptr)
{
}

HRESULT PixelShader::Init()
{
    HRESULT hr = S_OK;

    // Compile the shader source code
    ID3DXBuffer *pShaderCode = nullptr;
    ID3DXBuffer *pErrorMsg = nullptr;
    hr = D3DXCompileShader(
        shaderSource,
        sizeof(shaderSource),
        nullptr,
        nullptr,
        "main",
        "ps_2_0",
        0,
        &pShaderCode,
        &pErrorMsg,
        nullptr
    );

    if (FAILED(hr))
    {
        Log::Error("Couldn't compile the pixel shader");

        if (pErrorMsg != nullptr)
            Log::Error(reinterpret_cast<char *>(pErrorMsg->GetBufferPointer()));

        return hr;
    }

    // Create the shader
    hr = g_pd3dDevice->CreatePixelShader(reinterpret_cast<DWORD *>(pShaderCode->GetBufferPointer()), &m_pShader);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the pixel shader");
        return hr;
    }

    return hr;
}
