#include "pch.h"
#include "Elements\Menu.h"

#include "Core\Callbacks.h"
#include "Elements\ClickOption.h"
#include "Elements\RangeOption.h"
#include "Elements\ToggleOption.h"
#include "UI\Layout.h"
#include "UI\Font.h"

Menu::Menu()
    : m_CurrentOptionGroupIndex(0)
{
}

HRESULT Menu::Init()
{
    HRESULT hr = S_OK;

    // Create menu structure
    CreateStructure();

    // Set the default option group to be the first one
    m_CurrentOptionGroupIndex = 0;

    // Create the option group headers
    m_OptionGroupHeaders = std::vector<Text>(m_OptionGroups.size(), Text());

    return hr;
}

void Menu::Update(ATG::GAMEPAD *pGamepad)
{
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
}

HRESULT Menu::Render()
{
    HRESULT hr = S_OK;

    // Render the background
    hr = RenderBackground();
    if (FAILED(hr))
        return hr;

    // Render the option group headers
    hr = RenderOptionGroupHeaders();
    if (FAILED(hr))
        return hr;

    // Render the currently selected option group
    m_OptionGroups[m_CurrentOptionGroupIndex].Render();

    return hr;
}

void Menu::CreateStructure()
{
    // First group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(ClickOption, L"God Mode", Callback::ClickCallback));
        options.emplace_back(MakeOption(ClickOption, L"Fall Damage", Callback::ClickCallback));
        options.emplace_back(MakeOption(ClickOption, L"Ammo", Callback::ClickCallback));
        options.emplace_back(MakeOption(ClickOption, L"Spawn Care Package", Callback::ClickCallback));
        options.emplace_back(MakeOption(RangeOption, L"Some Number", Callback::RangeCallback, 1.0f, 5.0f, 1.0f));
        options.emplace_back(MakeOption(ToggleOption, L"Toggle Me", Callback::ToggleCallback));
        m_OptionGroups.emplace_back(OptionGroup(L"Main", options));
    }

    // Second group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(ClickOption, L"Save/Load Binds", Callback::ClickCallback));
        options.emplace_back(MakeOption(ClickOption, L"Save Position", Callback::ClickCallback));
        options.emplace_back(MakeOption(ClickOption, L"Load Position", Callback::ClickCallback));
        options.emplace_back(MakeOption(ClickOption, L"UFO", Callback::ClickCallback));
        m_OptionGroups.emplace_back(OptionGroup(L"Teleport", options));
    }

    CalculateMenuWidth();
}

HRESULT Menu::RenderBackground()
{
    Rectangle::Props props = { 0 };
    props.X = Layout::X;
    props.Y = Layout::Y + Layout::LineHeight + Layout::BorderWidth;
    props.Width = Layout::Width;
    props.Height = Layout::Height;
    props.Color = Layout::BackgroundColor;
    props.BorderWidth = Layout::BorderWidth;
    props.BorderColor = Layout::Color;
    props.BorderPosition = Border::Border_All;

    return m_Background.Render(props);
}

HRESULT Menu::RenderOptionGroupHeaders()
{
    HRESULT hr = S_OK;

    for (size_t i = 0; i < m_OptionGroupHeaders.size(); i++)
    {
        // The X offset is the sum of the previous option group header widths
        float offset = Layout::X;
        for (size_t j = 0; j < i; j++)
            offset += (g_Font.GetTextWidth(m_OptionGroups[j].GetName().c_str()) + Layout::Padding * 2 + Layout::BorderWidth);

        // Create the props
        Text::Props props = { 0 };
        props.X = offset;
        props.Y = Layout::Y;
        props.Text = m_OptionGroups[i].GetName();
        props.BorderWidth = Layout::BorderWidth;

        // Make the header more transparent when the option group header is not selected
        props.Color = i == m_CurrentOptionGroupIndex ? Layout::TextColor : D3DCOLOR_ARGB(30, D3DCOLOR_GETRED(Layout::TextColor), D3DCOLOR_GETGREEN(Layout::TextColor), D3DCOLOR_GETBLUE(Layout::TextColor));
        props.BackgroundColor = i == m_CurrentOptionGroupIndex ? Layout::BackgroundColor : D3DCOLOR_ARGB(30, D3DCOLOR_GETRED(Layout::BackgroundColor), D3DCOLOR_GETGREEN(Layout::BackgroundColor), D3DCOLOR_GETBLUE(Layout::BackgroundColor));
        props.BorderColor = i == m_CurrentOptionGroupIndex ? Layout::Color : D3DCOLOR_ARGB(30, D3DCOLOR_GETRED(Layout::Color), D3DCOLOR_GETGREEN(Layout::Color), D3DCOLOR_GETBLUE(Layout::Color));

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

void Menu::CalculateMenuWidth()
{
    float allOptionGroupNamesWidth = 0.0f;
    float longestOptionNameWidth = 0.0f;

    for (size_t i = 0; i < m_OptionGroups.size(); i++)
    {
        // Accumulate all the option group names width
        allOptionGroupNamesWidth += (g_Font.GetTextWidth(m_OptionGroups[i].GetName().c_str()) + Layout::Padding * 2);

        // Find the longest option name
        for (size_t j = 0; j < m_OptionGroups[i].GetOptions().size(); j++)
        {
            float optionNameWidth = g_Font.GetTextWidth(m_OptionGroups[i].GetOptions()[j]->GetName().c_str()) + Layout::Padding * 2;
            if (longestOptionNameWidth < optionNameWidth)
                longestOptionNameWidth = optionNameWidth;
        }
    }

    // Take the space between each group header into account
    allOptionGroupNamesWidth += Layout::BorderWidth * (m_OptionGroups.size() - 1);

    // Take into account some space between with option name and the potential text on the right (e.g. the number for RangeOption)
    longestOptionNameWidth += 100.0f;

    // Increase the menu width by the max between all the option names width and the longest option name
    Layout::Width += std::max<float>(allOptionGroupNamesWidth, longestOptionNameWidth);
}
