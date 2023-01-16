#include "pch.h"
#include "Core\App.h"

#include <AtgInput.h>
#include <AtgUtil.h>

#include "Core\Callbacks.h"

HRESULT App::Initialize()
{
    HRESULT hr = S_OK;

    // Get the width and height for the font
    ATG::GetVideoSettings(&m_Width, &m_Height);

    // Create the rectangle
    hr = m_Background.Init(100.0f, 100.0f, 200.0f, 500.0f, D3DCOLOR_XRGB(0, 0, 128));
    if (FAILED(hr))
        return hr;

    // Create menu structure

    // First group
    {
        std::vector<Option> options;
        options.emplace_back(Option(L"Option 1", Callback::Option1Callback));
        options.emplace_back(Option(L"Option 2", Callback::Option2Callback));
        m_OptionGroups.emplace_back(OptionGroup("cat1", options));
    }

    // Second group
    {
        std::vector<Option> options;
        options.emplace_back(Option(L"Option 3", Callback::Option3Callback));
        options.emplace_back(Option(L"Option 4", Callback::Option4Callback));
        m_OptionGroups.emplace_back(OptionGroup("cat2", options));
    }

    // Set the default option group to be the first one
    m_CurrentOptionGroupIndex = 0;

    return S_OK;
}

HRESULT App::Update()
{
    // Get the current gamepad state
    ATG::GAMEPAD *pGamepad = ATG::Input::GetMergedInput();

    // Allow the user to change the current option group with LB/RB
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
    {
        if (m_CurrentOptionGroupIndex > 0)
            m_CurrentOptionGroupIndex--;
    }
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
    {
        if (m_CurrentOptionGroupIndex < m_OptionGroups.size() - 1)
            m_CurrentOptionGroupIndex++;
    }

    // Update the currently selected option group
    m_OptionGroups[m_CurrentOptionGroupIndex].Update(pGamepad);

    return S_OK;
}

HRESULT App::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Render the background
    m_Background.Render();

    // Render the currently selected option group
    m_OptionGroups[m_CurrentOptionGroupIndex].Render();

    // Present the scene
    m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

    return S_OK;
}
