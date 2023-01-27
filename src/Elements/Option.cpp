#include "pch.h"
#include "Elements\Option.h"

extern ATG::Font g_Font;

Option::Option()
    : m_Callback(nullptr)
{
}

Option::Option(const std::wstring &text, Callback callback)
    : m_Text(text), m_Callback(callback)
{
}

void Option::Render(float x, float y, D3DCOLOR color)
{
    g_Font.DrawText(x + Layout::Padding, y + Layout::Padding, color, m_Text.c_str());
}
