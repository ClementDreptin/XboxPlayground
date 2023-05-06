#include "pch.h"
#include "Options/RangeOption.h"

#include "UI/Layout.h"
#include "UI/Font.h"

template<typename T>
RangeOption<T>::RangeOption()
    : Option(), m_Min(static_cast<T>(0)), m_Max(static_cast<T>(0)), m_Current(static_cast<T>(0))
{
}

template<typename T>
RangeOption<T>::RangeOption(const std::wstring &name, const ValueOrPtr<T> &value, T min, T max, T step)
    : Option(name, nullptr), m_Min(min), m_Max(max), m_Step(step), m_Current(value)
{
}

template<typename T>
RangeOption<T>::RangeOption(const std::wstring &name, Callback callback, const ValueOrPtr<T> &value, T min, T max, T step)
    : Option(name, callback), m_Min(min), m_Max(max), m_Step(step), m_Current(value)
{
}

template<typename T>
bool RangeOption<T>::Update(Input::Gamepad *pGamepad)
{
    // Allow the user to change the value with DPAD LEFT/DPAD RIGHT
    if (pGamepad->PressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
    {
        if (*m_Current < m_Max)
        {
            T newValue = m_Current + m_Step;
            if (m_Callback != nullptr)
            {
                bool success = m_Callback(&newValue);
                if (success)
                    m_Current = newValue;
            }
            else
                m_Current = newValue;
        }
    }
    else if (pGamepad->PressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
    {
        if (*m_Current > m_Min)
        {
            T newValue = m_Current - m_Step;
            if (m_Callback != nullptr)
            {
                bool success = m_Callback(&newValue);
                if (success)
                    m_Current = newValue;
            }
            else
                m_Current = newValue;
        }
    }

    return false;
}

template<typename T>
HRESULT RangeOption<T>::Render(float x, float y, float width)
{
    HRESULT hr = S_OK;

    // Call the parent to render the option name
    hr = Option::Render(x, y, width);
    if (FAILED(hr))
        return hr;

    // Create a wide string from the current number value
    std::wstring text = std::to_wstring(static_cast<long double>(*m_Current));

    // Calculate the width of the wide string of the number value
    float textWidth = g_Font.GetTextWidth(text.c_str());

    // Draw the text with the number
    Text::Props props = { 0 };
    props.X = x + width - textWidth - Layout::Padding;
    props.Y = y + Layout::Padding;
    props.Text = text;
    props.Color = Layout::TextColor;
    hr = m_Text.Render(props);

    return hr;
}

template class RangeOption<float>;
template class RangeOption<uint32_t>;
