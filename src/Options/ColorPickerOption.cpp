#include "pch.h"
#include "Options/ColorPickerOption.h"

#include "Options/RangeOption.h"

ColorPickerOption::ColorPickerOption()
    : SubOptionGroup(), m_Color(D3DCOLOR(0)), m_Red(0), m_Green(0), m_Blue(0), m_Alpha(0)
{
}

ColorPickerOption::ColorPickerOption(const std::wstring &name, const ValueOrPtr<D3DCOLOR> &color)
    : SubOptionGroup(name, OptionGroup()), m_Color(color), m_Red(D3DCOLOR_GETRED(*color)), m_Green(D3DCOLOR_GETGREEN(*color)), m_Blue(D3DCOLOR_GETBLUE(*color)), m_Alpha(D3DCOLOR_GETALPHA(*color))
{
    std::vector<std::shared_ptr<Option>> options;
    options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Red", &m_Red, 0, 255, 1));
    options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Green", &m_Green, 0, 255, 1));
    options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Blue", &m_Blue, 0, 255, 1));
    options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Alpha", &m_Alpha, 0, 255, 1));
    m_OptionGroup = OptionGroup(L"Color Picker", options);
}

bool ColorPickerOption::Update(Input::Gamepad *pGamepad)
{
    // Call the parent Update method and return early if the sub option group is not open
    bool open = SubOptionGroup::Update(pGamepad);
    if (!open)
        return false;

    // Update the color value when it's changed with DPAD LEFT/DPAD RIGHT
    if (pGamepad->PressedButtons & XINPUT_GAMEPAD_DPAD_LEFT || pGamepad->PressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
        m_Color = D3DCOLOR_RGBA(m_Red, m_Green, m_Blue, m_Alpha);

    return true;
}
