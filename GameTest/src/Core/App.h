#pragma once

#include <AtgApp.h>
#include <AtgFont.h>


//--------------------------------------------------------------------------------------
// Name: class App
// Desc: Main class to run this application. Most functionality is inherited
//       from the ATG::Application base class.
//--------------------------------------------------------------------------------------
class App : public ATG::Application
{
public:
    virtual HRESULT Initialize();
    virtual HRESULT Update();
    virtual HRESULT Render();
private:
    ATG::Font m_Font;
    D3DCOLOR m_dwFontColor;

    UINT m_uiWidth;
    UINT m_uiHeight;

    ATG::PackedResource m_Textures;

    LPDIRECT3DTEXTURE9 m_pBackgroundTexture;
    LPDIRECT3DVERTEXBUFFER9 m_pBackgroundVertexBuffer;
    LPDIRECT3DVERTEXDECLARATION9 m_pBackgroundVertexDeclaration;
    LPDIRECT3DINDEXBUFFER9 m_pBackgroundIndexBuffer;
    LPDIRECT3DVERTEXSHADER9 m_pBackgroundVertexShader;
    LPDIRECT3DPIXELSHADER9 m_pBackgroundPixelShader;

    HRESULT InitBackground();
};
