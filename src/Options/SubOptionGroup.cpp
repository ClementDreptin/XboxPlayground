#include "pch.h"
#include "Options/SubOptionGroup.h"

extern float g_DisplayWidth;

SubOptionGroup::SubOptionGroup()
    : Option(), m_Open(false)
{
}

SubOptionGroup::SubOptionGroup(const std::wstring &name, const std::vector<std::shared_ptr<Option>> &options)
    : Option(name, nullptr), m_Open(false), m_OptionGroup(OptionGroup(options))
{
}

bool SubOptionGroup::Update(Input::Gamepad *pGamepad)
{
    // Allow the user to close the sub option group with RS
    if (pGamepad->PressedButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
        m_Open = false;

    if (m_Open)
        m_OptionGroup.Update(pGamepad);

    // Allow the user to open the sub option group with X
    // Opening the option group is done after updating it so that its first option doesn't
    // get a gamepad state with X pressed. If opening was done before, the first option of
    // the option group would be click right after the option group is open.
    if (pGamepad->PressedButtons & XINPUT_GAMEPAD_X)
        m_Open = true;

    return m_Open;
}

HRESULT SubOptionGroup::Render(float x, float y, float width)
{
    HRESULT hr = S_OK;

    // Call the parent to render the option name
    hr = Option::Render(x, y, width);
    if (FAILED(hr))
        return hr;

    // If the option group is not open, don't go further
    if (!m_Open)
        return hr;

    // Render the sub option group on the left or the right of the menu, depending on where there's space
    float subOptionGroupWidth = m_OptionGroup.GetMinWidth() + Layout::BorderWidth * 2;
    float currentOptionWidth = width + Layout::BorderWidth * 2;
    float leftX = x - subOptionGroupWidth;
    float rightX = x + currentOptionWidth;

    float finalX = rightX;
    if (leftX < 0.0f)
        finalX = rightX;
    else if (rightX + subOptionGroupWidth > g_DisplayWidth)
        finalX = leftX;

    return m_OptionGroup.Render(finalX, y);
}
