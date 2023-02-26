#include "pch.h"
#include "Core/App.h"

#include <AtgFont.h>
#include <AtgUtil.h>

#include "Core/Input.h"
#include "Core/Callbacks.h"
#include "Core/OptionGroup.h"
#include "Options/ClickOption.h"
#include "Options/ToggleOption.h"
#include "Options/RangeOption.h"
#include "Options/ColorPickerOption.h"

ATG::Font g_Font;
float g_DisplayWidth = 0.0f;
float g_DisplayHeight = 0.0f;
bool g_ShowControlsTexts = true;

App::App()
    : m_MenuOpen(false)
{
}

HRESULT App::Initialize()
{
    HRESULT hr = S_OK;

    // Save the display dimensions
    uint32_t displayWidth = 0;
    uint32_t displayHeight = 0;
    ATG::GetVideoSettings(&displayWidth, &displayHeight);
    g_DisplayWidth = static_cast<float>(displayWidth);
    g_DisplayHeight = static_cast<float>(displayHeight);

    // Create the font
    hr = g_Font.Create("game:\\Media\\Fonts\\Arial_16.xpr");
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the font");
        return hr;
    }

    // Calculate the line height
    Layout::LineHeight = g_Font.GetFontHeight() + Layout::Padding * 2;

    // Create the menu
    InitMenu();

    return hr;
}

HRESULT App::Update()
{
    HRESULT hr = S_OK;

    // Get the current gamepad state
    Input::Gamepad *pGamepad = Input::GetInput();

    // Toggle the menu by pressing LT and DPAD LEFT
    if (pGamepad->LastLeftTrigger && pGamepad->PressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
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
    HRESULT hr = S_OK;

    // Clear the viewport
    m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Render the menu if it's open
    if (m_MenuOpen)
    {
        hr = m_Menu.Render();
        if (FAILED(hr))
            return hr;
    }

    // Render the controls texts if enabled
    if (g_ShowControlsTexts)
    {
        hr = RenderControlsTexts();
        if (FAILED(hr))
            return hr;
    }

    // Render the frame rate text
    hr = RenderFrameRateText();
    if (FAILED(hr))
        return hr;

    // Present the scene
    m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

    return hr;
}

void App::InitMenu()
{
    std::vector<OptionGroup> optionGroups;

    // First group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(ToggleOption, L"God Mode", Callback::ToggleCallback));
        options.emplace_back(MakeOption(ToggleOption, L"Fall Damage", Callback::ToggleCallback));
        options.emplace_back(MakeOption(ToggleOption, L"Ammo", Callback::ToggleCallback));
        options.emplace_back(MakeOption(ClickOption, L"Spawn Care Package", Callback::ClickCallback));
        optionGroups.emplace_back(OptionGroup(L"Main", options));
    }

    // Second group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(ToggleOption, L"Save/Load Binds", Callback::ToggleCallback));
        options.emplace_back(MakeOption(ClickOption, L"Save Position", Callback::ClickCallback));
        options.emplace_back(MakeOption(ClickOption, L"Load Position", Callback::ClickCallback));
        options.emplace_back(MakeOption(ToggleOption, L"UFO", Callback::ToggleCallback));
        optionGroups.emplace_back(OptionGroup(L"Teleport", options));
    }

    m_Menu.Init(optionGroups);
}

HRESULT App::RenderControlsTexts()
{
    HRESULT hr = S_OK;

    float baseY = 10.0f;
    float textHeight = g_Font.GetFontHeight() + Layout::Padding * 2 + Layout::BorderWidth * 2;

    Text::Props props = { 0 };
    props.X = 10.0f;
    props.Color = Layout::TextColor;
    props.BackgroundColor = Layout::BackgroundColor;
    props.BorderWidth = Layout::BorderWidth;
    props.BorderColor = Layout::Color;
    props.BorderPosition = Border::Border_All;

    props.Y = baseY;
    props.Text = L"Hold " GLYPH_LEFT_BUTTON L" & press " GLYPH_LEFT_TICK L" to " + std::wstring(!m_MenuOpen ? L"Open." : L"Close.");
    hr = m_ControlsTexts[0].Render(props);
    if (FAILED(hr))
        return hr;

    props.Y = baseY + textHeight + Layout::Padding;
    props.Text = L"Use " GLYPH_UP_TICK GLYPH_DOWN_TICK L" to scroll, " GLYPH_X_BUTTON L" to select, " GLYPH_RIGHT_BUTTON L" to go back.";
    hr = m_ControlsTexts[1].Render(props);
    if (FAILED(hr))
        return hr;

    props.Y = baseY + ((textHeight + Layout::Padding) * 2);
    props.Text = L"Use " GLYPH_LEFT_ARROW L" & " GLYPH_RIGHT_ARROW L" to switch menus.";
    hr = m_ControlsTexts[2].Render(props);

    return hr;
}

HRESULT App::RenderFrameRateText()
{
    m_Timer.MarkFrame();

    Text::Props props = { 0 };
    props.X = 10.0f;
    props.Y = g_DisplayHeight - Layout::LineHeight - 10.0f;
    props.Text = m_Timer.GetFrameRate();
    props.Color = Layout::TextColor;
    props.BackgroundColor = Layout::BackgroundColor;
    props.BorderWidth = Layout::BorderWidth;
    props.BorderColor = Layout::Color;
    props.BorderPosition = Border::Border_All;

    return m_FrameRateText.Render(props);
}
