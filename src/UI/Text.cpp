#include "pch.h"
#include "UI\Text.h"

#include "UI\Font.h"

Text::Text(const std::wstring &text)
    : m_Text(text)
{
}

void Text::Render(float x, float y, D3DCOLOR color)
{
    g_Font.DrawText(x, y, color, m_Text.c_str());
}
