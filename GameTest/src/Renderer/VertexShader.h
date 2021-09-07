#pragma once


//--------------------------------------------------------------------------------------
// Name: class VertexShader
// Desc: Class to wrap common vertex shader operations.
//--------------------------------------------------------------------------------------
class VertexShader
{
public:
    VertexShader() {}

    LPDIRECT3DVERTEXSHADER9 Get() const { return m_pShader; }

    HRESULT Init(LPDIRECT3DDEVICE9 pDevice);
private:
    LPDIRECT3DVERTEXSHADER9 m_pShader;
};
