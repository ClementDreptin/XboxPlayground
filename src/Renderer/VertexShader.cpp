#include "pch.h"
#include "Renderer\VertexShader.h"

#include "Renderer\D3DDevice.h"

// Vertex shader source code
static const char shaderSource[] =
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

VertexShader::VertexShader()
    : m_pShader(nullptr)
{
}

HRESULT VertexShader::Init()
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
            Log::Error(reinterpret_cast<char *>(pErrorMsg->GetBufferPointer()));

        return hr;
    }

    // Create the shader
    hr = g_pd3dDevice->CreateVertexShader(reinterpret_cast<DWORD *>(pShaderCode->GetBufferPointer()), &m_pShader);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the vertex shader");
        return hr;
    }

    return S_OK;
}
