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
    hr = m_Background.Init(m_pd3dDevice, 100.0f, 100.0f, 200.0f, 500.0f, D3DCOLOR_XRGB(0, 0, 128));
    if (FAILED(hr))
        return hr;

    // Create the options
    std::vector<Option> options;
    options.emplace_back(Option(L"Option 1", Callback::Option1Callback));
    options.emplace_back(Option(L"Option 2", Callback::Option2Callback));
    m_OptionGroup = OptionGroup("cat1", options);

    return S_OK;
}

HRESULT App::Update()
{
    // Get the current gamepad state
    ATG::GAMEPAD *pGamepad = ATG::Input::GetMergedInput();

    // Update the currently selected option
    m_OptionGroup.Update(pGamepad);

    return S_OK;
}

HRESULT App::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Render the rectangle
    m_Background.Render();

    // Render the options
    m_OptionGroup.Render();

    // Present the scene
    m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

    return S_OK;
}
