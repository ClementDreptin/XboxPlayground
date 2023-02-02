#include "pch.h"
#include "Elements\ToggleOption.h"

#include "UI\Layout.h"

float ToggleOption::s_RadioBoxSize = 0.0f;

ToggleOption::ToggleOption()
    : Option(), m_Active(false)
{
}

ToggleOption::ToggleOption(const std::wstring &name, Callback callback)
    : Option(name, callback), m_Active(false)
{
    // Set the radio box size the first time a ToggleOption is created
    if (s_RadioBoxSize == 0.0f)
        s_RadioBoxSize = Layout::LineHeight * 0.5f;

    // Create the radio box
    Rectangle::Props props = { 0 };
    props.BorderWidth = 2.0f;
    props.BorderColor = D3DCOLOR_XRGB(255, 255, 255);
    props.BorderPosition = Border::Border_All;
    props.Width = s_RadioBoxSize;
    props.Height = s_RadioBoxSize;

    m_RadioBox.SetProps(props);
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

void ToggleOption::Render(float x, float y, D3DCOLOR color)
{
    // Call the parent to render the text
    Option::Render(x, y, color);

    // Render the radio box
    Rectangle::Props props = m_RadioBox.GetProps();
    props.X = x + Layout::Width - s_RadioBoxSize - Layout::Padding;
    props.Y = y + Layout::LineHeight / 2 - s_RadioBoxSize / 2;
    props.Color = m_Active ? Layout::Color : D3DCOLOR_XRGB(0, 0, 0);
    m_RadioBox.SetProps(props);
    m_RadioBox.Render();
}
