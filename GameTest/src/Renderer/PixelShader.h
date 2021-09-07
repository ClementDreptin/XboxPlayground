#pragma once


//--------------------------------------------------------------------------------------
// Name: class PixelShader
// Desc: Class to wrap common pixel shader operations.
//--------------------------------------------------------------------------------------
class PixelShader
{
public:
    PixelShader() {}

    LPDIRECT3DPIXELSHADER9 Get() const { return m_pShader; }

    HRESULT Init(LPDIRECT3DDEVICE9 pDevice);
private:
    LPDIRECT3DPIXELSHADER9 m_pShader;
};
