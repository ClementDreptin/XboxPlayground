#include "pch.h"
#include "Renderer\VertexShader.h"

// Vertex shader source code
static const char *g_strShaderSource =
    " float4x4 c_matWP : register(c0);                  "
    "                                                   "
    " struct VS_IN                                      "
    " {                                                 "
    "     float4 inPos    : POSITION;                   "
    " };                                                "
    "                                                   "
    " struct VS_OUT                                     "
    " {                                                 "
    "     float4 outPos   : POSITION;                   "
    " };                                                "
    "                                                   "
    " VS_OUT main(VS_IN input)                          "
    " {                                                 "
    "     VS_OUT output;                                "
    "     output.outPos = mul(c_matWP, input.inPos);    "
    "                                                   "
    "     return output;                                "
    " }                                                 ";

HRESULT VertexShader::Init(D3DDevice *pDevice)
{
    HRESULT hr;

    // Compile the shader source code
    ID3DXBuffer *pShaderCode;
    ID3DXBuffer *pErrorMsg;
    hr = D3DXCompileShader(
        g_strShaderSource,
        strlen(g_strShaderSource),
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
            OutputDebugString(reinterpret_cast<char *>(pErrorMsg->GetBufferPointer()));

        return hr;
    }

    // Create the shader
    hr = pDevice->CreateVertexShader(reinterpret_cast<DWORD *>(pShaderCode->GetBufferPointer()), &m_pShader);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the vertex shader");
        return hr;
    }

    return S_OK;
}
