#include "pch.h"
#include "Core\App.h"

#include <AtgInput.h>

#include "Core\Callbacks.h"

HRESULT App::Initialize()
{
    HRESULT hr = S_OK;

    // Get the width and height for the font
    ATG::GetVideoSettings(&m_Width, &m_Height);

    // Create the rectangle
    hr = m_Rectangle.Init(m_pd3dDevice, 100.0f, 100.0f, 200.0f, 500.0f, D3DCOLOR_XRGB(0, 0, 128));
    if (FAILED(hr))
        return hr;

    // Create the scroller
    hr = m_Scroller.Init(m_pd3dDevice, 100.0f, 100.0f, 200.0f, 50.0f, D3DCOLOR_XRGB(128, 128, 128));
    if (FAILED(hr))
        return hr;

    // Create the options
    m_Options.emplace_back(Option(L"Option 1", 0, Callback::Option1Callback));

    // Initialize the scroller position
    m_CurrentScrollerPos = 0;

    return S_OK;
}

HRESULT App::Update()
{
    // Get the current gamepad state
    ATG::GAMEPAD *pGamepad = ATG::Input::GetMergedInput();

    // Allow the user to select options with the DPAD
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
    {
        m_CurrentScrollerPos--;

        // If the scroller is already at the top, send it to the bottom
        if (m_CurrentScrollerPos < 0)
            m_CurrentScrollerPos = m_Options.size() - 1;

        MoveScroller();
    }
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
    {
        m_CurrentScrollerPos++;

        // If the scroller is already at the bottom, send it to the top
        if (m_CurrentScrollerPos >= static_cast<int>(m_Options.size()))
            m_CurrentScrollerPos = 0;

        MoveScroller();
    }

    // Allow the user to click on an option
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
        m_Options[m_CurrentScrollerPos].OnClick(nullptr);

    return S_OK;
}

HRESULT App::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Draw the rectangle
    m_Rectangle.Draw();

    // Draw the scroller
    m_Scroller.Draw();

    // Draw the options
    Option::Begin();
    for (size_t i = 0; i < m_Options.size(); i++)
        m_Options[i].Draw(100.0f, 100.0f + i * 50.0f);
    Option::End();

    // Present the scene
    m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

    return S_OK;
}

void App::MoveScroller()
{
    m_Scroller.SetY(100.0f + 50.0f * m_CurrentScrollerPos);
}
