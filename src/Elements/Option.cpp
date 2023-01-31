#include "pch.h"
#include "Elements\Option.h"

#include "UI\Font.h"

Option::Option()
    : m_Callback(nullptr)
{
}

Option::Option(const std::wstring &text, Callback callback)
    : m_Callback(callback)
{
    Text::Props props = { 0 };
    props.Text = text;
    m_Text.SetProps(props);
}

void Option::Render(float x, float y, D3DCOLOR color)
{
    Text::Props props = m_Text.GetProps();
    props.X = x + Layout::Padding;
    props.Y = y + Layout::Padding;
    props.Color = color;
    m_Text.SetProps(props);

    m_Text.Render();
}
