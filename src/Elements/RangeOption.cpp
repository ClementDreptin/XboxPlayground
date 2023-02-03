#include "pch.h"
#include "Elements\RangeOption.h"

#include "UI\Layout.h"
#include "UI\Font.h"

RangeOption::RangeOption()
    : Option(), m_Min(0.0f), m_Max(0.0f), m_Current(0.0f)
{
}

RangeOption::RangeOption(const std::wstring &name, Callback callback, float min, float max, float step)
    : Option(name, callback), m_Min(min), m_Max(max), m_Step(step), m_Current(min)
{
}

void RangeOption::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to change the value with DPAD LEFT/DPAD RIGHT
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
    {
        if (m_Current < m_Max)
        {
            m_Current += m_Step;
            m_Callback(&m_Current);
        }
    }
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
    {
        if (m_Current > m_Min)
        {
            m_Current -= m_Step;
            m_Callback(&m_Current);
        }
    }
}

HRESULT RangeOption::Render(float x, float y)
{
    HRESULT hr = S_OK;

    // Call the parent to render the text
    hr = Option::Render(x, y);
    if (FAILED(hr))
        return hr;

    // Create a wide string from the current number value
    std::wstring text = std::to_wstring(static_cast<long double>(m_Current));

    // Calculate the width of the wide string of the number value
    float textWidth = g_Font.GetTextWidth(text.c_str());

    // Draw the text with the number
    Text::Props props = { 0 };
    props.X = x + Layout::Width - textWidth - Layout::Padding;
    props.Y = y + Layout::Padding;
    props.Text = text;
    props.Color = Layout::TextColor;
    hr = m_Text.Render(props);

    return hr;
}
