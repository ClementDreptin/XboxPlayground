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
    hr = g_Font.Create("game:\\Media\\Fonts\\Arial_16.xpr");
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the font");
        return hr;
    }

    // Create the controls text
    Text::Props controlsTextProps = { 0 };
    controlsTextProps.X = 10.0f;
    controlsTextProps.Y = 10.0f;
    controlsTextProps.Text = L"Press " GLYPH_LEFT_BUTTON L" + " GLYPH_LEFT_TICK L" to Open";
    controlsTextProps.Color = Layout::TextColor;
    controlsTextProps.BackgroundColor = Layout::BackgroundColor;
    controlsTextProps.BorderWidth = 5.0f;
    controlsTextProps.BorderColor = Layout::Color;
    controlsTextProps.BorderPosition = Border::Border_All;
    hr = m_ControlsText.SetProps(controlsTextProps);
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

        // Update the controls text
        Text::Props newProps = m_ControlsText.GetProps();
        newProps.Text = L"Press " GLYPH_LEFT_BUTTON L" + " GLYPH_LEFT_TICK L" to " + std::wstring(!m_MenuOpen ? L"Open" : L"Close");
        m_ControlsText.SetProps(newProps);

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
