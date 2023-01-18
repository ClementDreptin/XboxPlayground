#include "pch.h"
#include "Elements\ClickableOption.h"

ClickableOption::ClickableOption()
    : Option()
{
}

ClickableOption::ClickableOption(const std::wstring &text, Callback callback)
    : Option(text, callback)
{
}

void ClickableOption::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to click on the option
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
        m_Callback(nullptr);
}

void ClickableOption::Render(float x, float y, D3DCOLOR color)
{
    // Call the parent to render the text
    Option::Render(x, y, color);
}
