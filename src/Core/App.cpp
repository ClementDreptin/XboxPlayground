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
    std::vector<Option> options;
    options.emplace_back(Option(L"Option 1", Callback::Option1Callback));
    options.emplace_back(Option(L"Option 2", Callback::Option1Callback));
    m_OptionGroup = OptionGroup("cat1", options);

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
        // If the scroller is already at the top, send it to the bottom
        if (m_CurrentScrollerPos == 0)
            m_CurrentScrollerPos = m_OptionGroup.GetOptions().size() - 1;
        else
            m_CurrentScrollerPos--;
    }
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
    {
        // If the scroller is already at the bottom, send it to the top
        if (m_CurrentScrollerPos == m_OptionGroup.GetOptions().size())
            m_CurrentScrollerPos = 0;
        else
            m_CurrentScrollerPos++;
    }

    MoveScroller();

    // Update the currently selected option
    m_OptionGroup.Update(pGamepad);

    return S_OK;
}

HRESULT App::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Render the rectangle
    m_Rectangle.Render();

    // Render the scroller
    m_Scroller.Render();

    // Render the options
    Option::Begin();
    m_OptionGroup.Render();
    Option::End();

    // Present the scene
    m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

    return S_OK;
}

void App::MoveScroller()
{
    m_Scroller.SetY(100.0f + 50.0f * m_CurrentScrollerPos);
}
