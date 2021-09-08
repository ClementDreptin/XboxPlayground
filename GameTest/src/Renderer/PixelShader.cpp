#include "pch.h"
#include "Renderer\PixelShader.h"


// Pixel shader source code
static LPCSTR g_ShaderSource =
" float4 c_color : register(c0);               "
"                                              "
" struct PS_IN                                 "
" {                                            "
"     float4 inColor : COLOR;                  "
" };                                           "
"                                              "
" float4 main(PS_IN input) : COLOR             "
" {                                            "
"     return c_color;                          "
" }                                            "; 

//--------------------------------------------------------------------------------------
// Name: Init()
// Desc: Compile the pixel shader source and create the pixel shader.
//--------------------------------------------------------------------------------------
HRESULT PixelShader::Init(LPDIRECT3DDEVICE9 pDevice)
{
    HRESULT hr;

    // Compile the shader source code
    ID3DXBuffer* pShaderCode;
    ID3DXBuffer* pErrorMsg;
    hr = D3DXCompileShader(
        g_ShaderSource,
        (UINT)strlen(g_ShaderSource),
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
            OutputDebugString((LPSTR)pErrorMsg->GetBufferPointer());

        return hr;
    }

    // Create the shader
    hr = pDevice->CreatePixelShader((LPDWORD)pShaderCode->GetBufferPointer(), &m_pShader);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the pixel shader");
        return hr;
    }

    return S_OK;
}
