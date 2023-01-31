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
    Text::Props textProps = { 0 };
    textProps.Text = text;
    m_Text.SetProps(textProps);
}

void Option::Render(float x, float y, D3DCOLOR color)
{
    Text::Props newProps = m_Text.GetProps();
    newProps.X = x + Layout::Padding;
    newProps.Y = y + Layout::Padding;
    newProps.Color = color;
    m_Text.SetProps(newProps);

    m_Text.Render();
}
