#include "pch.h"
#include "Options\ColorPickerOption.h"

#include "Options\RangeOption.h"

ColorPickerOption::ColorPickerOption()
    : Option(), m_Color(D3DCOLOR(0)), m_Red(0), m_Green(0), m_Blue(0), m_Alpha(0), m_Open(false)
{
}

ColorPickerOption::ColorPickerOption(const std::wstring &name, Callback callback, const ValueOrPtr<D3DCOLOR> &color)
    : Option(name, callback), m_Color(color), m_Red(D3DCOLOR_GETRED(*color)), m_Green(D3DCOLOR_GETGREEN(*color)), m_Blue(D3DCOLOR_GETBLUE(*color)), m_Alpha(D3DCOLOR_GETALPHA(*color)), m_Open(false)
{
    std::vector<std::shared_ptr<Option>> options;
    options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Red", nullptr, &m_Red, 0, 255, 1));
    options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Green", nullptr, &m_Green, 0, 255, 1));
    options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Blue", nullptr, &m_Blue, 0, 255, 1));
    options.emplace_back(MakeOption(RangeOption<uint32_t>, L"Alpha", nullptr, &m_Alpha, 0, 255, 1));
    m_OptionGroup = OptionGroup(L"Color Picker", options);
}

void ColorPickerOption::Update(ATG::GAMEPAD *pGamepad)
{
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
        m_Open = true;
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_B)
        m_Open = false;

    if (!m_Open)
        return;

    m_OptionGroup.Update(pGamepad);

    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT || pGamepad->wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
    {
        m_Color = D3DCOLOR_RGBA(m_Red, m_Green, m_Blue, m_Alpha);
        if (m_Callback != nullptr)
            m_Callback(&m_Color);
    }
}

HRESULT ColorPickerOption::Render(float x, float y, float width)
{
    HRESULT hr = S_OK;

    // Call the parent to render the text
    hr = Option::Render(x, y, width);
    if (FAILED(hr))
        return hr;

    // Render the option group if it's open
    if (m_Open)
        hr = m_OptionGroup.Render(x + width + Layout::BorderWidth * 2, y);

    return hr;
}
