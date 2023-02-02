#include "pch.h"
#include "Elements\Menu.h"

#include "Core\Callbacks.h"
#include "Elements\ClickableOption.h"
#include "Elements\RangeOption.h"
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

    // Create the background
    hr = CreateBackground();
    if (FAILED(hr))
        return hr;

    // Set the default option group to be the first one
    m_CurrentOptionGroupIndex = 0;

    // Create the option group headers
    m_OptionGroupHeaders = std::vector<Text>(m_OptionGroups.size(), Text());
    UpdateOptionGroupHeaders();

    return hr;
}

void Menu::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to change the current option group with LB/RB
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
    {
        if (m_CurrentOptionGroupIndex > 0)
        {
            m_CurrentOptionGroupIndex--;
            UpdateOptionGroupHeaders();
        }
    }
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
    {
        if (m_CurrentOptionGroupIndex < m_OptionGroups.size() - 1)
        {
            m_CurrentOptionGroupIndex++;
            UpdateOptionGroupHeaders();
        }
    }

    // Update the currently selected option group
    m_OptionGroups[m_CurrentOptionGroupIndex].Update(pGamepad);
}

void Menu::Render()
{
    // Render the background
    m_Background.Render();

    // Render the option group headers
    for (size_t i = 0; i < m_OptionGroupHeaders.size(); i++)
        m_OptionGroupHeaders[i].Render();

    // Render the currently selected option group
    m_OptionGroups[m_CurrentOptionGroupIndex].Render();
}

void Menu::CreateStructure()
{
    // First group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(ClickableOption, L"God Mode", Callback::Option1Callback));
        options.emplace_back(MakeOption(ClickableOption, L"Fall Damage", Callback::Option1Callback));
        options.emplace_back(MakeOption(ClickableOption, L"Ammo", Callback::Option1Callback));
        options.emplace_back(MakeOption(ClickableOption, L"Spawn Care Package", Callback::Option1Callback));
        m_OptionGroups.emplace_back(OptionGroup(L"Main", options));
    }

    // Second group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(ClickableOption, L"Save/Load Binds", Callback::Option1Callback));
        options.emplace_back(MakeOption(ClickableOption, L"Save Position", Callback::Option1Callback));
        options.emplace_back(MakeOption(ClickableOption, L"Load Position", Callback::Option1Callback));
        options.emplace_back(MakeOption(ClickableOption, L"UFO", Callback::Option1Callback));
        m_OptionGroups.emplace_back(OptionGroup(L"Teleport", options));
    }

    CalculateDynamicLayoutValues();
}

HRESULT Menu::CreateBackground()
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

    return m_Background.SetProps(props);
}

HRESULT Menu::UpdateOptionGroupHeaders()
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

        hr = m_OptionGroupHeaders[i].SetProps(props);
        if (FAILED(hr))
            return hr;
    }

    return hr;
}

void Menu::CalculateDynamicLayoutValues()
{
    // Calculate the menu width
    float allOptionGroupNamesWidth = 0.0f;
    float longestOptionNameWidth = 0.0f;
    for (size_t i = 0; i < m_OptionGroups.size(); i++)
    {
        allOptionGroupNamesWidth += (g_Font.GetTextWidth(m_OptionGroups[i].GetName().c_str()) + Layout::Padding * 2);
        for (size_t j = 0; j < m_OptionGroups[i].GetOptions().size(); j++)
        {
            float optionNameWidth = g_Font.GetTextWidth(m_OptionGroups[i].GetOptions()[j]->GetName().c_str()) + Layout::Padding * 2;
            if (longestOptionNameWidth < optionNameWidth)
                longestOptionNameWidth = optionNameWidth;
        }
    }
    longestOptionNameWidth += 100.0f;
    Layout::Width += std::max<float>(allOptionGroupNamesWidth, longestOptionNameWidth);
    Layout::Width += Layout::BorderWidth * (m_OptionGroups.size() - 1);

    // Calculate the line height
    Layout::LineHeight = g_Font.GetFontHeight() + Layout::Padding * 2;
}
