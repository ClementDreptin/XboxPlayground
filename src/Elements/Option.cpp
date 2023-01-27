#include "pch.h"
#include "Elements\Option.h"

#include "UI\Font.h"

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
    m_Text.Render(x, y, color);
}
