#include "pch.h"
#include "Elements\OptionGroup.h"

#include "UI\Layout.h"

OptionGroup::OptionGroup()
    : m_CurrentScrollerPos(0)
{
}

OptionGroup::OptionGroup(const std::string &name, const std::vector<std::shared_ptr<Option>> &options)
    : m_Name(name), m_Options(options), m_CurrentScrollerPos(0)
{
    // Create the scroller
    Rectangle::Props props = { 0 };
    props.X = Layout::X;
    props.Y = Layout::Y;
    props.Width = Layout::Width;
    props.Height = 50.0f;
    props.Color = D3DCOLOR_ARGB(204, D3DCOLOR_GETRED(Layout::Color), D3DCOLOR_GETGREEN(Layout::Color), D3DCOLOR_GETBLUE(Layout::Color));
    m_Scroller.Init(props);
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

    // Rendern the options
    Option::Begin();
    for (size_t i = 0; i < m_Options.size(); i++)
        m_Options[i]->Render(100.0f, 100.0f + i * 50.0f);
    Option::End();
}

void OptionGroup::MoveScroller()
{
    m_Scroller.SetY(100.0f + 50.0f * m_CurrentScrollerPos);
}
