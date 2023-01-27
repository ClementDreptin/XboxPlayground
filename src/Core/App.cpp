#include "pch.h"
#include "Core\App.h"

#include <AtgInput.h>
#include <AtgFont.h>

ATG::Font g_Font;

App::App()
    : m_MenuOpen(false)
{
}

HRESULT App::Initialize()
{
    HRESULT hr = S_OK;

    // Create the font
    hr = g_Font.Create("game:\\Media\\Fonts\\Arial_20.xpr");
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the font");
        return hr;
    }

    // Create the controls text
    Text::Props controlsTextProps = { 0 };
    controlsTextProps.X = 10.0f;
    controlsTextProps.Y = 10.0f;
    controlsTextProps.Text = L"Press LT + DPAD_LEFT to Open/Close";
    controlsTextProps.Color = Layout::TextColor;
    controlsTextProps.BackgroundColor = Layout::BackgroundColor;
    controlsTextProps.BorderWidth = 5.0f;
    controlsTextProps.BorderColor = Layout::Color;
    controlsTextProps.BorderPosition = Border::Border_All;

    hr = m_ControlsText.Init(controlsTextProps);
    if (FAILED(hr))
        return hr;

    // Create the menu
    hr = m_Menu.Init();
    if (FAILED(hr))
        return hr;

    return hr;
}

HRESULT App::Update()
{
    HRESULT hr = S_OK;

    // Get the current gamepad state
    ATG::GAMEPAD *pGamepad = ATG::Input::GetMergedInput();

    // Toggle the menu by pressing LT and DPAD LEFT
    if (pGamepad->bLastLeftTrigger && pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
    {
        m_MenuOpen = !m_MenuOpen;
        return hr;
    }

    // Update the menu if it's open
    if (m_MenuOpen)
        m_Menu.Update(pGamepad);

    return hr;
}

HRESULT App::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Render the menu if it's open
    if (m_MenuOpen)
        m_Menu.Render();

    // Render the controls text
    m_ControlsText.Render();

    // Present the scene
    m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

    return S_OK;
}
