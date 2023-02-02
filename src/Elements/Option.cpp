#include "pch.h"
#include "Elements\Option.h"

#include "UI\Font.h"

Option::Option()
    : m_Callback(nullptr), m_IsSelected(false)
{
}

Option::Option(const std::wstring &name, Callback callback)
    : m_Name(name), m_Callback(callback)
{
    Text::Props props = { 0 };
    props.Text = m_Name;
    m_Text.SetProps(props);
}

void Option::Render(float x, float y, D3DCOLOR color)
{
    // Render the background if the option is selected
    if (m_IsSelected)
    {
        Rectangle::Props props = { 0 };
        props.X = x + Layout::Gap;
        props.Y = y + Layout::Gap;
        props.Width = Layout::Width - Layout::Gap * 2;
        props.Height = Layout::LineHeight - Layout::Gap * 2;
        props.Color = Layout::Color;
        m_Background.SetProps(props);

        m_Background.Render();
    }

    Text::Props props = m_Text.GetProps();
    props.X = x + Layout::Padding;
    props.Y = y + Layout::Padding;
    props.Color = color;
    m_Text.SetProps(props);

    m_Text.Render();
}
