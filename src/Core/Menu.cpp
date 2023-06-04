#include "pch.h"
#include "Core/Menu.h"

#include "Options/OptionGroup.h"
#include "Options/ToggleOption.h"
#include "Options/RangeOption.h"
#include "Options/SubOptionGroup.h"
#include "Options/ColorPickerOption.h"
#include "UI/Layout.h"
#include "UI/Font.h"

extern float g_DisplayWidth;
extern float g_DisplayHeight;
extern bool g_ShowControlsTexts;

// Take a color and override its alpha channel.
#define D3DCOLOR_ALPHA(color, alpha) D3DCOLOR_ARGB(alpha, D3DCOLOR_GETRED(color), D3DCOLOR_GETGREEN(color), D3DCOLOR_GETBLUE(color))

Menu::Menu()
    : m_CurrentOptionGroupIndex(0), m_CachedOptionGroupHeadersHeight(0.0f)
{
}

void Menu::Init(const std::vector<OptionGroup> &optionGroups)
{
    m_OptionGroups = optionGroups;

    AddCustomizationGroup();

    CalculateMenuDimensions();

    m_OptionGroupHeaders = std::vector<Text>(m_OptionGroups.size(), Text());
}

void Menu::Update(Input::Gamepad *pGamepad)
{
    // Allow the user to change the current option group with LB/RB
    if (pGamepad->PressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
    {
        if (m_CurrentOptionGroupIndex > 0)
            m_CurrentOptionGroupIndex--;
    }
    else if (pGamepad->PressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
    {
        if (m_CurrentOptionGroupIndex < m_OptionGroups.size() - 1)
            m_CurrentOptionGroupIndex++;
    }

    m_OptionGroups[m_CurrentOptionGroupIndex].Update(pGamepad);
}

HRESULT Menu::Render()
{
    HRESULT hr = S_OK;

    hr = RenderOptionGroupHeaders();
    if (FAILED(hr))
        return hr;

    float highestOptionGroupHeader = GetOptionGroupHeadersHeight();
    hr = m_OptionGroups[m_CurrentOptionGroupIndex].Render(Layout::X, Layout::Y + highestOptionGroupHeader, Layout::Width, Layout::Height);

    return hr;
}

void Menu::AddCustomizationGroup()
{
    std::vector<std::shared_ptr<Option>> options;

    options.emplace_back(MakeOption(ToggleOption, L"Show Controls", &g_ShowControlsTexts));

    std::vector<std::shared_ptr<Option>> menuPositionOptions;
    menuPositionOptions.emplace_back(MakeOption(RangeOption<float>, L"X", &Layout::X, Layout::BorderWidth, g_DisplayWidth, 10.0f));
    menuPositionOptions.emplace_back(MakeOption(RangeOption<float>, L"Y", &Layout::Y, Layout::BorderWidth, g_DisplayHeight, 10.0f));
    options.emplace_back(MakeOption(SubOptionGroup, L"Menu Position", menuPositionOptions));

    options.emplace_back(MakeOption(ColorPickerOption, L"Menu Color", &Layout::Color));
    m_OptionGroups.emplace_back(OptionGroup(L"Customization", options));
}

float Menu::GetOptionGroupHeadersHeight() const
{
    // Return the cached value if the minimum width has already been calculated
    if (m_CachedOptionGroupHeadersHeight != 0.0f)
        return m_CachedOptionGroupHeadersHeight;

    float m_CachedOptionGroupHeadersHeight = 0.0f;
    for (size_t i = 0; i < m_OptionGroupHeaders.size(); i++)
    {
        float currentOptionGroupHeaderHeight = g_Font.GetTextHeight(m_OptionGroups[i].GetName()) + Layout::Padding * 2;
        if (currentOptionGroupHeaderHeight > m_CachedOptionGroupHeadersHeight)
            m_CachedOptionGroupHeadersHeight = currentOptionGroupHeaderHeight;
    }
    m_CachedOptionGroupHeadersHeight += Layout::BorderWidth;

    return m_CachedOptionGroupHeadersHeight;
}

HRESULT Menu::RenderOptionGroupHeaders()
{
    HRESULT hr = S_OK;

    float highestOptionGroupHeader = GetOptionGroupHeadersHeight();

    for (size_t i = 0; i < m_OptionGroupHeaders.size(); i++)
    {
        // The X offset is the sum of the previous option group header widths
        float offset = Layout::X;
        for (size_t j = 0; j < i; j++)
            offset += (g_Font.GetTextWidth(m_OptionGroups[j].GetName()) + Layout::Padding * 2 + Layout::BorderWidth);

        Text::Props props = { 0 };
        props.X = offset;
        props.Y = Layout::Y;
        props.Text = m_OptionGroups[i].GetName();
        props.BackgroundHeight = highestOptionGroupHeader;
        props.BorderWidth = Layout::BorderWidth;

        // Make the header more transparent when the option group header is not selected
        uint8_t alpha = 100;
        props.Color = i == m_CurrentOptionGroupIndex ? Layout::TextColor : D3DCOLOR_ALPHA(Layout::TextColor, alpha);
        props.BackgroundColor = i == m_CurrentOptionGroupIndex ? Layout::BackgroundColor : D3DCOLOR_ALPHA(Layout::BackgroundColor, alpha);
        props.BorderColor = i == m_CurrentOptionGroupIndex ? Layout::Color : D3DCOLOR_ALPHA(Layout::Color, alpha);

        // m_OptionGroups[i] is selected
        if (i == m_CurrentOptionGroupIndex)
            props.BorderPosition = static_cast<Border::Position>(Border::Border_Left | Border::Border_Top | Border::Border_Right);

        // m_OptionGroups[i] is to the left of the selected option group
        else if (i < m_CurrentOptionGroupIndex)
            props.BorderPosition = static_cast<Border::Position>(Border::Border_Left | Border::Border_Top);

        // m_OptionGroups[i] is to the right of the selected option group
        else if (i > m_CurrentOptionGroupIndex)
            props.BorderPosition = static_cast<Border::Position>(Border::Border_Right | Border::Border_Top);

        hr = m_OptionGroupHeaders[i].Render(props);
        if (FAILED(hr))
            return hr;
    }

    return hr;
}

void Menu::CalculateMenuDimensions()
{
    float allOptionGroupNamesWidth = 0.0f;
    float biggestOptionGroupWidth = 0.0f;
    float biggestOptionGroupHeight = 0.0f;

    for (size_t i = 0; i < m_OptionGroups.size(); i++)
    {
        // Accumulate all the option group names width
        allOptionGroupNamesWidth += (g_Font.GetTextWidth(m_OptionGroups[i].GetName()) + Layout::Padding * 2);

        // Find the option group with the biggest width
        float optionGroupWidth = m_OptionGroups[i].GetMinWidth();
        if (biggestOptionGroupWidth < optionGroupWidth)
            biggestOptionGroupWidth = optionGroupWidth;

        // Find the option group with the biggest height
        float optionGroupHeight = m_OptionGroups[i].GetMinHeight();
        if (biggestOptionGroupHeight < optionGroupHeight)
            biggestOptionGroupHeight = optionGroupHeight;
    }

    // Take the space between each group header into account
    allOptionGroupNamesWidth += Layout::BorderWidth * (m_OptionGroups.size() - 1);

    // Make the menu width the max between all the option names width and the longest option name
    Layout::Width = std::max<float>(allOptionGroupNamesWidth, biggestOptionGroupWidth);

    // Make the menu tall enough for the biggest option group
    Layout::Height = biggestOptionGroupHeight;

    // Move the menu to right side of the screen (double cast to rounded to closest integer value)
    Layout::X = static_cast<float>(static_cast<uint32_t>(g_DisplayWidth - Layout::Width - 10.0f));
}
