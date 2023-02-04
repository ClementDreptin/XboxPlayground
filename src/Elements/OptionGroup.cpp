#include "pch.h"
#include "Elements\OptionGroup.h"

#include "UI\Layout.h"
#include "UI\Font.h"

OptionGroup::OptionGroup()
    : m_CurrentSelectedOptionIndex(0)
{
}

OptionGroup::OptionGroup(const std::wstring &name, const std::vector<std::shared_ptr<Option>> &options)
    : m_Name(name), m_Options(options), m_CurrentSelectedOptionIndex(0)
{
}

void OptionGroup::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to select options with the DPAD
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
    {
        // If the scroller is already at the top, send it to the bottom
        if (m_CurrentSelectedOptionIndex == 0)
            m_CurrentSelectedOptionIndex = m_Options.size() - 1;
        else
            m_CurrentSelectedOptionIndex--;
    }
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
    {
        // If the scroller is already at the bottom, send it to the top
        if (m_CurrentSelectedOptionIndex == m_Options.size() - 1)
            m_CurrentSelectedOptionIndex = 0;
        else
            m_CurrentSelectedOptionIndex++;
    }

    // Change the option states according to the currently selected option
    for (size_t i = 0; i < m_Options.size(); i++)
        m_Options[i]->Select(i == m_CurrentSelectedOptionIndex);

    // Update the currently selected option
    m_Options[m_CurrentSelectedOptionIndex]->Update(pGamepad);
}

HRESULT OptionGroup::Render(float x, float y)
{
    HRESULT hr = S_OK;

    // Render the options
    for (size_t i = 0; i < m_Options.size(); i++)
    {
        hr = m_Options[i]->Render(x, y + (i + 1) * Layout::LineHeight + Layout::BorderWidth);
        if (FAILED(hr))
            return hr;
    }

    return hr;
}

float OptionGroup::GetMinWidth()
{
    float longestOptionNameWidth = 0.0f;

    for (size_t i = 0; i < m_Options.size(); i++)
    {
        float optionNameWidth = g_Font.GetTextWidth(m_Options[i]->GetName().c_str()) + Layout::Padding * 2;
        if (longestOptionNameWidth < optionNameWidth)
            longestOptionNameWidth = optionNameWidth;
    }

    // Take into account some space between the option name and the potential text on the right (e.g. the number for RangeOption)
    return longestOptionNameWidth + 100.0f;
}

float OptionGroup::GetMinHeight()
{
    return m_Options.size() * Layout::LineHeight;
}
