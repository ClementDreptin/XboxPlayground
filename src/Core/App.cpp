#include "pch.h"
#include "Core/App.h"

#include "Core/Input.h"
#include "Core/Callbacks.h"
#include "UI/Console.h"
#include "UI/Font.h"
#include "Options/OptionGroup.h"
#include "Options/ClickOption.h"
#include "Options/ToggleOption.h"
#include "Options/RangeOption.h"
#include "Options/ColorPickerOption.h"

Console g_Console;
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
    // Clear the viewport
    m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    if (m_MenuOpen)
        m_Menu.Render();

    if (g_ShowControlsTexts)
        RenderControlsTexts();

    // Render the frame rate text
    RenderFrameRateText();

    // Render the console
    g_Console.Render(10.0f, 300.0f);

    // Present the scene
    m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

    return S_OK;
}

void App::InitMenu()
{
    std::vector<OptionGroup> optionGroups;

    // First group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(ClickOption, L"Click 1", Callback::ClickCallback));
        options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Integer Range 1", Callback::IntegerRangeCallback, 2, 0, 10, 1));
        options.emplace_back(MakeOption(RangeOption<float>, L"Float Range 1", Callback::FloatRangeCallback, 0.2f, 0.0f, 1.0f, 0.1f));
        options.emplace_back(MakeOption(ToggleOption, L"Toggle 1", Callback::ToggleCallback, false));
        optionGroups.emplace_back(OptionGroup(L"First", options));
    }

    // Second group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(ClickOption, L"Click 2", Callback::ClickCallback));
        options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Integer Range 2", Callback::IntegerRangeCallback, 2, 0, 10, 1));
        options.emplace_back(MakeOption(RangeOption<float>, L"Float Range 2", Callback::FloatRangeCallback, 0.2f, 0.0f, 1.0f, 0.1f));
        options.emplace_back(MakeOption(ToggleOption, L"Toggle 2", Callback::ToggleCallback, false));
        optionGroups.emplace_back(OptionGroup(L"Second", options));
    }

    m_Menu.Init(optionGroups);
}

void App::RenderControlsTexts()
{
    float yOffset = 10.0f;
    float fontScale = 0.8f;
    float padding = Layout::Padding * fontScale;
    float borderWidth = Layout::BorderWidth * fontScale;

    Text::Props props = {};
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
    m_ControlsTexts[0].Render(props);

    props.Y = yOffset;
    props.Text = L"Use " GLYPH_UP_TICK GLYPH_DOWN_TICK L" to scroll, " GLYPH_X_BUTTON L" to select, " GLYPH_RIGHT_BUTTON L" to go back.";
    yOffset += g_Font.GetTextHeight(props.Text) * fontScale + padding * 3 + borderWidth * 2;
    m_ControlsTexts[1].Render(props);

    props.Y = yOffset;
    props.Text = L"Use " GLYPH_LEFT_ARROW L" & " GLYPH_RIGHT_ARROW L" to switch menus.";
    yOffset += g_Font.GetTextHeight(props.Text) * fontScale + padding * 3 + borderWidth * 2;
    m_ControlsTexts[2].Render(props);
}

void App::RenderFrameRateText()
{
    m_Timer.MarkFrame();

    const wchar_t *text = m_Timer.GetFrameRate();

    Text::Props props = {};
    props.X = 10.0f;
    props.Y = g_DisplayHeight - (g_Font.GetTextHeight(text) + Layout::Padding * 2) - 10.0f;
    props.Text = text;
    props.Color = Layout::TextColor;
    props.BackgroundColor = Layout::BackgroundColor;
    props.BorderWidth = Layout::BorderWidth;
    props.BorderColor = Layout::Color;
    props.BorderPosition = Border::Border_All;

    m_FrameRateText.Render(props);
}
