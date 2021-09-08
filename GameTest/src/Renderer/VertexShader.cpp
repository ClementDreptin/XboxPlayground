#include "pch.h"
#include "Renderer\VertexShader.h"


// Vertex shader source code
static LPCSTR g_strShaderSource =
" float4x4 matWP : register(c0);                "
"                                               "
" struct VS_IN                                  "
" {                                             "
"     float4 inPos    : POSITION;               "
"     float4 inColor  : COLOR;                  "
" };                                            "
"                                               "
" struct VS_OUT                                 "
" {                                             "
"     float4 outPos   : POSITION;               "
"     float4 outColor : COLOR;                  "
" };                                            "
"                                               "
" VS_OUT main(VS_IN input)                      "
" {                                             "
"     VS_OUT output;                            "
"     output.outPos = mul(matWP, input.inPos);  "
"     output.outColor = input.inColor;          "
"                                               "
"     return output;                            "
" }                                             ";

//--------------------------------------------------------------------------------------
// Name: Init()
// Desc: Compile the vertex shader source and create the vertex shader.
//--------------------------------------------------------------------------------------
HRESULT VertexShader::Init(LPDIRECT3DDEVICE9 pDevice)
{
    HRESULT hr;

    // Compile the shader source code
    ID3DXBuffer* pShaderCode;
    ID3DXBuffer* pErrorMsg;
    hr = D3DXCompileShader(
        g_strShaderSource,
        (UINT)strlen(g_strShaderSource),
        nullptr,
        nullptr,
        "main",
        "vs_2_0",
        NULL,
        &pShaderCode,
        &pErrorMsg,
        nullptr
    );

    if (FAILED(hr))
    {
        Log::Error("Couldn't compile the vertex shader");
        
        if (pErrorMsg)
            OutputDebugString((LPSTR)pErrorMsg->GetBufferPointer());

        return hr;
    }

    // Create the shader
    hr = pDevice->CreateVertexShader((LPDWORD)pShaderCode->GetBufferPointer(), &m_pShader);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the vertex shader");
        return hr;
    }

    return S_OK;
}
