#include "pch.h"
#include "Elements\RangeOption.h"

#include "UI\Layout.h"
#include "UI\Font.h"

RangeOption::RangeOption()
    : Option(), m_Min(0.0f), m_Max(0.0f), m_Current(0.0f)
{
}

RangeOption::RangeOption(const std::wstring &text, Callback callback, float min, float max, float step)
    : Option(text, callback), m_Min(min), m_Max(max), m_Step(step), m_Current(min)
{
}

void RangeOption::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to change the value
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT && m_Current < m_Max)
    {
        m_Current += m_Step;
        m_Callback(&m_Current);
    }
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT && m_Current > m_Min)
    {
        m_Current -= m_Step;
        m_Callback(&m_Current);
    }
}

void RangeOption::Render(float x, float y, D3DCOLOR color)
{
    // Call the parent to render the text
    Option::Render(x, y, color);

    // Create a wide string from the current number value
    std::wstring text = std::to_wstring(static_cast<long double>(m_Current));

    // Calculate the width of the wide string of the number value
    float textWidth = g_Font.GetTextWidth(text.c_str());

    // Draw the wide string of the number value
    g_Font.DrawText(x + Layout::Width - textWidth - Layout::Padding, y + Layout::Padding, color, text.c_str());
}
