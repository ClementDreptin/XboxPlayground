#include "pch.h"
#include "Options\ColorPickerOption.h"

#include "Options\RangeOption.h"

ColorPickerOption::ColorPickerOption()
    : Option(), m_pColor(nullptr), m_Red(0), m_Green(0), m_Blue(0), m_Alpha(0), m_Open(false)
{
}

ColorPickerOption::ColorPickerOption(const std::wstring &name, Callback callback, D3DCOLOR *pColor)
    : Option(name, callback), m_pColor(pColor), m_Red(D3DCOLOR_GETRED(*pColor)), m_Green(D3DCOLOR_GETGREEN(*pColor)), m_Blue(D3DCOLOR_GETBLUE(*pColor)), m_Alpha(D3DCOLOR_GETALPHA(*pColor)), m_Open(false)
{
    std::vector<std::shared_ptr<Option>> options;
    options.emplace_back(MakeOption(RangeOption, L"Red", nullptr, reinterpret_cast<float *>(&m_Red), 0.0f, 255.0f, 1.0f));
    options.emplace_back(MakeOption(RangeOption, L"Green", nullptr, reinterpret_cast<float *>(&m_Green), 0.0f, 255.0f, 1.0f));
    options.emplace_back(MakeOption(RangeOption, L"Blue", nullptr, reinterpret_cast<float *>(&m_Blue), 0.0f, 255.0f, 1.0f));
    options.emplace_back(MakeOption(RangeOption, L"Alpha", nullptr, reinterpret_cast<float *>(&m_Alpha), 0.0f, 255.0f, 1.0f));
    m_OptionGroup = OptionGroup(L"Color Picker", options);
}

void ColorPickerOption::Update(ATG::GAMEPAD *pGamepad)
{
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
        m_Open = true;

    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_B)
        m_Open = false;

    if (m_Open)
        m_OptionGroup.Update(pGamepad);

    *m_pColor = D3DCOLOR_RGBA(m_Red, m_Green, m_Blue, m_Alpha);
}

HRESULT ColorPickerOption::Render(float x, float y)
{
    HRESULT hr = S_OK;

    // Call the parent to render the text
    hr = Option::Render(x, y);
    if (FAILED(hr))
        return hr;

    // Render the option group if it's open
    if (m_Open)
        hr = m_OptionGroup.Render(x + Layout::Width + Layout::BorderWidth * 2, y);

    return hr;

}
