#include "pch.h"
#include "Core/App.h"

#include <AtgUtil.h>

#include "Core/Input.h"
#include "UI/Font.h"
#include "Core/Callbacks.h"
#include "Options/OptionGroup.h"
#include "Options/ClickOption.h"
#include "Options/ToggleOption.h"
#include "Options/RangeOption.h"
#include "Options/ColorPickerOption.h"

Font g_Font;

// The resolution is always 720p, 1080p is created by the hardware scaler
float g_DisplayWidth = 1280.0f;
float g_DisplayHeight = 720.0f;

bool g_ShowControlsTexts = true;

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

    // Calculate the line height
    Layout::LineHeight = g_Font.GetFontHeight() + Layout::Padding * 2;

    // Create the menu
    InitMenu();

    return hr;
}

HRESULT App::Update()
{
    HRESULT hr = S_OK;

    Input::Gamepad *pGamepad = Input::GetInput();

    // Toggle the menu by pressing LT and DPAD LEFT
    if (pGamepad->LastLeftTrigger && pGamepad->PressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
    {
        m_MenuOpen = !m_MenuOpen;
        return hr;
    }

    if (m_MenuOpen)
        m_Menu.Update(pGamepad);

    return hr;
}

HRESULT App::Render()
{
    HRESULT hr = S_OK;

    // Clear the viewport
    m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    if (m_MenuOpen)
    {
        hr = m_Menu.Render();
        if (FAILED(hr))
            return hr;
    }

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
        options.emplace_back(MakeOption(ClickOption, L"Click 1", Callback::ClickCallback));
        options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Integer Range 1", Callback::RangeCallback, 2, 0, 1, 1));
        options.emplace_back(MakeOption(RangeOption<float>, L"Float Range 1", Callback::RangeCallback, 0.2f, 0.0f, 1.0f, 0.1f));
        options.emplace_back(MakeOption(ToggleOption, L"Toggle 1", Callback::ToggleCallback, false));
        optionGroups.emplace_back(OptionGroup(L"First", options));
    }

    // Second group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(ClickOption, L"Click 1", Callback::ClickCallback));
        options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Integer Range 1", Callback::RangeCallback, 2, 0, 1, 1));
        options.emplace_back(MakeOption(RangeOption<float>, L"Float Range 1", Callback::RangeCallback, 0.2f, 0.0f, 1.0f, 0.1f));
        options.emplace_back(MakeOption(ToggleOption, L"Toggle 1", Callback::ToggleCallback, false));
        optionGroups.emplace_back(OptionGroup(L"Second", options));
    }

    m_Menu.Init(optionGroups);
}

HRESULT App::RenderControlsTexts()
{
    HRESULT hr = S_OK;

    float yOffset = 10.0f;
    float fontScale = 0.8f;
    float padding = Layout::Padding * fontScale;
    float borderWidth = Layout::BorderWidth * fontScale;

    Text::Props props = { 0 };
    props.X = 10.0f;
    props.FontScale = fontScale;
    props.Color = Layout::TextColor;
    props.BackgroundColor = Layout::BackgroundColor;
    props.BorderWidth = borderWidth;
    props.BorderColor = Layout::Color;
    props.BorderPosition = Border::Border_All;

    props.Y = yOffset;
    props.Text = L"Hold " GLYPH_LEFT_BUTTON L" & press " GLYPH_LEFT_TICK L" to " + std::wstring(!m_MenuOpen ? L"Open." : L"Close.");
    yOffset += g_Font.GetTextHeight(props.Text) * fontScale + padding * 3 + borderWidth * 2;
    hr = m_ControlsTexts[0].Render(props);
    if (FAILED(hr))
        return hr;

    props.Y = yOffset;
    props.Text = L"Use " GLYPH_UP_TICK GLYPH_DOWN_TICK L" to scroll, " GLYPH_X_BUTTON L" to select, " GLYPH_RIGHT_BUTTON L" to go back.";
    yOffset += g_Font.GetTextHeight(props.Text) * fontScale + padding * 3 + borderWidth * 2;
    hr = m_ControlsTexts[1].Render(props);
    if (FAILED(hr))
        return hr;

    props.Y = yOffset;
    props.Text = L"Use " GLYPH_LEFT_ARROW L" & " GLYPH_RIGHT_ARROW L" to switch menus.";
    yOffset += g_Font.GetTextHeight(props.Text) * fontScale + padding * 3 + borderWidth * 2;
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
