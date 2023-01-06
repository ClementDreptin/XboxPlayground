#include "pch.h"
#include "Renderer\PixelShader.h"

// Pixel shader source code
static const char *g_ShaderSource =
    " float4 c_color : register(c0);    "
    "                                   "
    " float4 main() : COLOR             "
    " {                                 "
    "     return c_color;               "
    " }                                 ";

HRESULT PixelShader::Init(D3DDevice *pDevice)
{
    HRESULT hr;

    // Compile the shader source code
    ID3DXBuffer *pShaderCode;
    ID3DXBuffer *pErrorMsg;
    hr = D3DXCompileShader(
        g_ShaderSource,
        strlen(g_ShaderSource),
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
            OutputDebugString(reinterpret_cast<char *>(pErrorMsg->GetBufferPointer()));

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
