#include "pch.h"
#include "App.h"

#include <AtgInput.h>


//--------------------------------------------------------------------------------------
// Name: Initialize()
// Desc: Initialize app-dependent objects
//--------------------------------------------------------------------------------------
HRESULT App::Initialize()
{
    // Result of operations
    HRESULT hr;

    // Create the font
    hr = m_Font.Create("game:\\Media\\Fonts\\Arial_20.xpr");
    if (FAILED(hr))
    {
        Log::Error("Couldn't create font");
        return hr;
    }

    // Set the default font color to white
    m_dwFontColor = D3DCOLOR_XRGB(255, 255, 255);

    // Get the width and height for the font
    ATG::GetVideoSettings(&m_uiWidth, &m_uiHeight);

    // Create the rectangle
    hr = m_Rectangle.Init(m_pd3dDevice, 100.0f, 100.0f, 200.0f, 200.0f, D3DCOLOR_XRGB(255, 255, 0));
    if (FAILED(hr))
        return hr;

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Name: Update()
// Desc: Called once per frame, the call is the entry point for animating the scene.
//--------------------------------------------------------------------------------------
HRESULT App::Update()
{
    // Get the time elapsed
    FLOAT fElapsedTime = (FLOAT)m_Timer.GetElapsedTime();

    // Get the current gamepad state
    ATG::GAMEPAD* pGamepad = ATG::Input::GetMergedInput();

    // Allow the user to change the font color,
    // the font color is set to the button's color
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
        m_dwFontColor = D3DCOLOR_XRGB(0, 255, 0);
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_X)
        m_dwFontColor = D3DCOLOR_XRGB(0, 0, 255);
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_Y)
        m_dwFontColor = D3DCOLOR_XRGB(255, 255, 0);
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_B)
        m_dwFontColor = D3DCOLOR_XRGB(255, 0, 0);

    // Allow the user to move the rectangle with the DPAD
    FLOAT fRectangleX = m_Rectangle.GetX();
    FLOAT fRectangleY = m_Rectangle.GetY();

    fRectangleX += pGamepad->fX1 * fElapsedTime * 200.0f;
    fRectangleY -= pGamepad->fY1 * fElapsedTime * 200.0f;

    m_Rectangle.SetPosition(fRectangleX, fRectangleY);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Name: Render()
// Desc: Called once per frame, the call is the entry point for 3D rendering. This 
//       function sets up render states, clears the viewport, and renders the scene.
//--------------------------------------------------------------------------------------
HRESULT App::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Draw the rectangle
    m_Rectangle.Draw();

    // Set the text
    static LPCWSTR wszText = L"Press A, X, Y or B to change my color!";

    // Calculate the text position
    static FLOAT fTextWidth = m_Font.GetTextWidth(wszText);
    static FLOAT fTextX = (FLOAT)(m_uiWidth - fTextWidth) / 2.0f;
    static FLOAT fTextY = (FLOAT)(m_uiHeight - m_Font.GetFontHeight()) / 2.0f;

    // Draw the text
    m_Font.Begin();
    m_Font.DrawText(fTextX, fTextY, m_dwFontColor, wszText);
    m_Font.End();

    // Present the scene
    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

    return S_OK;
}
