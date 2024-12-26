#include "pch.h"
#include "Options/OptionGroup.h"

#include "UI/Layout.h"
#include "UI/Font.h"

#define MAX_OPTIONS_TO_DISPLAY 8

OptionGroup::OptionGroup()
    : m_OptionsToDisplay(0),
      m_FirstOptionIndex(0),
      m_LastOptionIndex(0),
      m_CurrentSelectedOptionIndex(0),
      m_CachedMinWidth(0.0f),
      m_CachedMinHeight(0.0f)
{
}

OptionGroup::OptionGroup(const std::vector<std::shared_ptr<Option>> &options)
    : m_Options(options),
      m_OptionsToDisplay(m_Options.size() < MAX_OPTIONS_TO_DISPLAY ? m_Options.size() : MAX_OPTIONS_TO_DISPLAY),
      m_FirstOptionIndex(0),
      m_LastOptionIndex(m_OptionsToDisplay - 1),
      m_CurrentSelectedOptionIndex(0),
      m_CachedMinWidth(0.0f),
      m_CachedMinHeight(0.0f)
{
}

OptionGroup::OptionGroup(const std::wstring &name, const std::vector<std::shared_ptr<Option>> &options)
    : m_Name(name),
      m_Options(options),
      m_OptionsToDisplay(m_Options.size() < MAX_OPTIONS_TO_DISPLAY ? m_Options.size() : MAX_OPTIONS_TO_DISPLAY),
      m_FirstOptionIndex(0),
      m_LastOptionIndex(m_OptionsToDisplay - 1),
      m_CurrentSelectedOptionIndex(0),
      m_CachedMinWidth(0.0f),
      m_CachedMinHeight(0.0f)
{
}

void OptionGroup::Update(Input::Gamepad *pGamepad)
{
    XASSERT(pGamepad != nullptr);

    // Update the currently selected option and return if the option is blocking (meaning it opened a sub option group
    // and wants to prevent its parent option group from updating)
    bool blocking = m_Options[m_CurrentSelectedOptionIndex]->Update(pGamepad);
    if (blocking)
        return;

    // Allow the user to select options with the DPAD
    if (pGamepad->PressedButtons & XINPUT_GAMEPAD_DPAD_UP)
    {
        // If the scroller is already at the top, send it to the bottom
        if (m_CurrentSelectedOptionIndex == 0)
            m_CurrentSelectedOptionIndex = m_Options.size() - 1;
        else
            m_CurrentSelectedOptionIndex--;
    }
    else if (pGamepad->PressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
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
}

void OptionGroup::Render(float x, float y, float width, float height)
{
    float widthToUse = width != 0.0f ? width : GetMinWidth();
    float heightToUse = height != 0.0f ? height : GetMinHeight();

    RenderBackground(x, y, widthToUse, heightToUse);

    // If the scroller is going down past the last displayed option,
    // shift the view down
    if (m_CurrentSelectedOptionIndex > m_LastOptionIndex)
    {
        m_FirstOptionIndex = m_CurrentSelectedOptionIndex - m_OptionsToDisplay + 1;
        m_LastOptionIndex = m_CurrentSelectedOptionIndex;
    }

    // If the scroller is going up past the first displayed option,
    // shift the view up
    if (m_CurrentSelectedOptionIndex < m_FirstOptionIndex)
    {
        m_FirstOptionIndex = m_CurrentSelectedOptionIndex;
        m_LastOptionIndex = m_CurrentSelectedOptionIndex + m_OptionsToDisplay - 1;
    }

    for (size_t i = m_FirstOptionIndex; i <= m_LastOptionIndex; i++)
    {
        m_Options[i]->Render(x, y, widthToUse);
        y += m_Options[i]->GetMinHeight();
    }
}

float OptionGroup::GetMinWidth()
{
    // Return the cached value if the minimum width has already been calculated
    if (m_CachedMinWidth != 0.0f)
        return m_CachedMinWidth;

    // Find the longest option name
    for (size_t i = 0; i < m_Options.size(); i++)
    {
        float optionNameWidth = m_Options[i]->GetMinWidth();
        if (m_CachedMinWidth < optionNameWidth)
            m_CachedMinWidth = optionNameWidth;
    }

    return m_CachedMinWidth;
}

float OptionGroup::GetMinHeight()
{
    // Return the cached value if the minimum height has already been calculated
    if (m_CachedMinHeight != 0.0f)
        return m_CachedMinHeight;

    for (size_t i = 0; i < m_OptionsToDisplay; i++)
        m_CachedMinHeight += m_Options[i]->GetMinHeight();

    return m_CachedMinHeight;
}

void OptionGroup::RenderBackground(float x, float y, float width, float height)
{
    Rectangle::Props props = {};
    props.X = x;
    props.Y = y;
    props.Width = width;
    props.Height = height;
    props.Color = Layout::BackgroundColor;
    props.BorderWidth = Layout::BorderWidth;
    props.BorderColor = Layout::Color;
    props.BorderPosition = Border::Border_All;

    m_Background.Render(props);
}
