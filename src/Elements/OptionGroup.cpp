#include "pch.h"
#include "Elements\OptionGroup.h"

#include "UI\Layout.h"
#include "UI\Font.h"

OptionGroup::OptionGroup()
    : m_CurrentScrollerPos(0)
{
}

OptionGroup::OptionGroup(const std::wstring &name, const std::vector<std::shared_ptr<Option>> &options)
    : m_Name(name), m_Options(options), m_CurrentScrollerPos(0), m_LineHeight(g_Font.GetFontHeight() + Layout::Padding * 2)
{
    // Create the scroller
    Rectangle::Props props = { 0 };
    props.X = Layout::X + Layout::Gap;
    props.Y = Layout::Y + Layout::Gap;
    props.Width = Layout::Width - Layout::Gap * 2;
    props.Height = m_LineHeight - Layout::Gap * 2;
    props.Color = Layout::Color;
    m_Scroller.SetProps(props);
}

void OptionGroup::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to select options with the DPAD
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
    {
        // If the scroller is already at the top, send it to the bottom
        if (m_CurrentScrollerPos == 0)
            m_CurrentScrollerPos = m_Options.size() - 1;
        else
            m_CurrentScrollerPos--;
    }
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
    {
        // If the scroller is already at the bottom, send it to the top
        if (m_CurrentScrollerPos == m_Options.size() - 1)
            m_CurrentScrollerPos = 0;
        else
            m_CurrentScrollerPos++;
    }

    MoveScroller();

    // Update the currently selected option
    m_Options[m_CurrentScrollerPos]->Update(pGamepad);
}

void OptionGroup::Render()
{
    // Render the scroller
    m_Scroller.Render();

    // Render the options
    for (size_t i = 0; i < m_Options.size(); i++)
        m_Options[i]->Render(Layout::X, Layout::Y + (i + 1) * m_LineHeight + Layout::BorderWidth);
}

void OptionGroup::MoveScroller()
{
    Rectangle::Props props = m_Scroller.GetProps();
    props.Y = Layout::Y + Layout::Gap + m_LineHeight * m_CurrentScrollerPos;
    m_Scroller.SetProps(props);
}
