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
        // If newValue is greater than m_Max, don't go further
        // We also need to check if newValue is not smaller than m_Current,
        // this can happen when newValue overflows beyond the integer type upper limit.
        // e.g. with 8-bit unsigned integers: 254 + 2 = 1 and not 256 => If newValue
        // is smaller than m_Current after adding m_Step, then we overflowed.
        T newValue = m_Current + m_Step;
        if (newValue > m_Max || newValue < m_Current)
            return false;

        if (m_Callback != nullptr)
        {
            bool success = m_Callback(&newValue);
            if (success)
                m_Current = newValue;
        }
        else
            m_Current = newValue;
    }
    else if (pGamepad->PressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
    {
        // If newValue is smaller than m_Min, don't go further
        // We also need to check if newValue is not bigger than m_Current,
        // this can happen when newValue overflows beyond the integer type lower limit.
        // e.g. with 8-bit unsigned integers: 1 - 2 = 255 and not -1 => If newValue
        // is greater than m_Current after substracting m_Step, then we overflowed.
        T newValue = m_Current - m_Step;
        if (newValue < m_Min || newValue > m_Current)
            return false;

        // If there is a callback, only update the value if the call succeeds
        if (m_Callback != nullptr)
        {
            bool success = m_Callback(&newValue);
            if (success)
                m_Current = newValue;
        }
        else
            m_Current = newValue;
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
    std::wstring text = std::to_wstring(static_cast<long double>(m_Current));

    // Calculate the width of the wide string of the number value
    float textWidth = g_Font.GetTextWidth(text.c_str());

    // Draw the text with the number
    Text::Props props = { 0 };
    props.X = x + width - textWidth - Layout::Padding;
    props.Y = y + Layout::Padding;
    props.Text = text;
    props.Color = Layout::TextColor;

    return m_Text.Render(props);
}

template class RangeOption<float>;
template class RangeOption<uint32_t>;
