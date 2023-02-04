#include "pch.h"
#include "Options\ClickOption.h"

ClickOption::ClickOption()
    : Option()
{
}

ClickOption::ClickOption(const std::wstring &name, Callback callback)
    : Option(name, callback)
{
}

void ClickOption::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to click on the option
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
        m_Callback(nullptr);
}

HRESULT ClickOption::Render(float x, float y)
{
    // Call the parent to render the text
    return Option::Render(x, y);
}
