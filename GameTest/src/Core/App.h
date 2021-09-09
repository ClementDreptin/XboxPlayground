#pragma once

#include <AtgApp.h>
#include <AtgFont.h>
#include <AtgUtil.h>

#include "Renderer\VertexBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexShader.h"
#include "Renderer\PixelShader.h"

#include "Elements\Rectangle.h"


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
    ATG::Timer m_Timer;

    ATG::Font m_Font;
    D3DCOLOR m_dwFontColor;

    UINT m_uiWidth;
    UINT m_uiHeight;

    Rectangle m_Rectangle;
};
