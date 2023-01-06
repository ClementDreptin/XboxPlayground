#include "pch.h"
#include "Renderer\PixelShader.h"

// Pixel shader source code
static const char shaderSource[] =
    " float4 c_color : register(c0);    "
    "                                   "
    " float4 main() : COLOR             "
    " {                                 "
    "     return c_color;               "
    " }                                 ";

HRESULT PixelShader::Init(D3DDevice *pDevice)
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
        NULL,
        &pShaderCode,
        &pErrorMsg,
        nullptr
    );

    if (FAILED(hr))
    {
        Log::Error("Couldn't compile the pixel shader");

        if (pErrorMsg)
            Log::Error(reinterpret_cast<char *>(pErrorMsg->GetBufferPointer()));

        return hr;
    }

    // Create the shader
    hr = pDevice->CreatePixelShader(reinterpret_cast<DWORD *>(pShaderCode->GetBufferPointer()), &m_pShader);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the pixel shader");
        return hr;
    }

    return S_OK;
}
