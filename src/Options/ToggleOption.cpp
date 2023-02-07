#include "pch.h"
#include "Options/ToggleOption.h"

#include "UI/Layout.h"

ToggleOption::ToggleOption()
    : Option(), m_Active(false)
{
}

ToggleOption::ToggleOption(const std::wstring &name, Callback callback)
    : Option(name, callback), m_Active(false)
{
}

bool ToggleOption::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to toggle the option
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
    {
        m_Active = !m_Active;
        m_Callback(&m_Active);
    }

    return false;
}

HRESULT ToggleOption::Render(float x, float y, float width)
{
    HRESULT hr = S_OK;

    // Call the parent to render the option name
    hr = Option::Render(x, y, width);
    if (FAILED(hr))
        return hr;

    // Render the radio box
    float radioBoxSize = Layout::LineHeight * 0.5f;
    Rectangle::Props props = { 0 };
    props.X = x + width - radioBoxSize - Layout::Padding;
    props.Y = y + Layout::LineHeight / 2 - radioBoxSize / 2;
    props.Width = radioBoxSize;
    props.Height = radioBoxSize;
    props.Color = m_Active ? Layout::Color : D3DCOLOR_XRGB(0, 0, 0);
    props.BorderWidth = 1.0f;
    props.BorderColor = D3DCOLOR_XRGB(255, 255, 255);
    props.BorderPosition = Border::Border_All;
    hr = m_RadioBox.Render(props);

    return hr;
}
