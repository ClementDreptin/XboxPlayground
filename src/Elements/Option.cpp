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
    m_Text.Init(textProps);
}

void Option::Render(float x, float y, D3DCOLOR color)
{
    m_Text.GetProps().X = x + Layout::Padding;
    m_Text.GetProps().Y = y + Layout::Padding;
    m_Text.GetProps().Color = color;

    m_Text.Render();
}
