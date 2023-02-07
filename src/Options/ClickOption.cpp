#include "pch.h"
#include "Options/ClickOption.h"

ClickOption::ClickOption()
    : Option()
{
}

ClickOption::ClickOption(const std::wstring &name, Callback callback)
    : Option(name, callback)
{
}

bool ClickOption::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to click on the option
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
        m_Callback(nullptr);

    return false;
}

HRESULT ClickOption::Render(float x, float y, float width)
{
    // Call the parent to render the option name
    return Option::Render(x, y, width);
}
