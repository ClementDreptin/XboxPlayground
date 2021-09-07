#pragma once

#include <AtgApp.h>
#include <AtgFont.h>

#include "Renderer\VertexBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexShader.h"
#include "Renderer\PixelShader.h"


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

    VertexBuffer m_VertexBuffer;
    IndexBuffer m_IndexBuffer;
    VertexShader m_VertexShader;
    PixelShader m_PixelShader;
};
