#include "pch.h"
#include "Options\SubOptionGroup.h"

SubOptionGroup::SubOptionGroup()
    : Option(), m_Open(false)
{
}

SubOptionGroup::SubOptionGroup(const std::wstring &name, Callback callback, const OptionGroup &optionGroup)
    : Option(name, callback), m_Open(false), m_OptionGroup(optionGroup)
{
}

bool SubOptionGroup::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to open/close the sub option group with A/B
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
        m_Open = true;
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_B)
        m_Open = false;

    // Update the sub option group if it's open
    if (m_Open)
        m_OptionGroup.Update(pGamepad);

    return m_Open;
}

HRESULT SubOptionGroup::Render(float x, float y, float width)
{
    HRESULT hr = S_OK;

    // Call the parent to render the option name
    hr = Option::Render(x, y, width);
    if (FAILED(hr))
        return hr;

    // Render the option group if it's open
    if (m_Open)
        hr = m_OptionGroup.Render(x + width + Layout::BorderWidth * 2, y);

    return hr;
}
