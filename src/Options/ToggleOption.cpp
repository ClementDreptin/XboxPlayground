#include "pch.h"
#include "Options/ToggleOption.h"

#include "UI/Layout.h"
#include "UI/Font.h"

ToggleOption::ToggleOption()
    : Option(), m_Active(false)
{
}

ToggleOption::ToggleOption(const std::wstring &name, const ValueOrPtr<bool> &active)
    : Option(name, nullptr), m_Active(active)
{
}

ToggleOption::ToggleOption(const std::wstring &name, Callback callback, const ValueOrPtr<bool> &active)
    : Option(name, callback), m_Active(active)
{
}

bool ToggleOption::Update(Input::Gamepad *pGamepad)
{
    XASSERT(pGamepad != nullptr);

    // Allow the user to toggle the option
    if (pGamepad->PressedButtons & XINPUT_GAMEPAD_X)
    {
        bool newValue = !m_Active;

        // If there is a callback, only update the value if the call succeeds
        if (m_Callback != nullptr)
        {
            bool success = m_Callback(&newValue);
            if (success)
                m_Active = newValue;
        }
        else
            m_Active = newValue;
    }

    return false;
}

void ToggleOption::Render(float x, float y, float width)
{
    // Call the parent to render the option name
    Option::Render(x, y, width);

    // Render the radio box
    float lineHeight = g_Font.GetFontHeight() + Layout::Padding * 2;
    float radioBoxSize = lineHeight * 0.5f;
    Rectangle::Props props = {};
    props.X = x + width - radioBoxSize - Layout::Padding;
    props.Y = y + GetMinHeight() / 2 - radioBoxSize / 2;
    props.Width = radioBoxSize;
    props.Height = radioBoxSize;
    props.Color = m_Active ? Layout::Color : D3DCOLOR_XRGB(0, 0, 0);
    props.BorderWidth = 1.0f;
    props.BorderColor = D3DCOLOR_XRGB(255, 255, 255);
    props.BorderPosition = Border::Border_All;

    m_RadioBox.Render(props);
}
