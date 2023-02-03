#include "pch.h"
#include "Elements\ToggleOption.h"

#include "UI\Layout.h"

ToggleOption::ToggleOption()
    : Option(), m_Active(false)
{
}

ToggleOption::ToggleOption(const std::wstring &name, Callback callback)
    : Option(name, callback), m_Active(false)
{
}

void ToggleOption::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to toggle the option
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
    {
        m_Active = !m_Active;
        m_Callback(&m_Active);
    }
}

HRESULT ToggleOption::Render(float x, float y)
{
    HRESULT hr = S_OK;

    // Call the parent to render the text
    hr = Option::Render(x, y);
    if (FAILED(hr))
        return hr;

    // Render the radio box
    float radioBoxSize = Layout::LineHeight * 0.5f;
    Rectangle::Props props = { 0 };
    props.X = x + Layout::Width - radioBoxSize - Layout::Padding;
    props.Y = y + Layout::LineHeight / 2 - radioBoxSize / 2;
    props.Width = radioBoxSize;
    props.Height = radioBoxSize;
    props.Color = m_Active ? Layout::Color : D3DCOLOR_XRGB(0, 0, 0);
    props.BorderWidth = 2.0f;
    props.BorderColor = D3DCOLOR_XRGB(255, 255, 255);
    props.BorderPosition = Border::Border_All;
    hr = m_RadioBox.Render(props);
    if (FAILED(hr))
        return hr;

    return hr;
}
