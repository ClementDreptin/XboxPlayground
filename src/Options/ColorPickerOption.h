#pragma once

#include "Options\Option.h"
#include "Core\ValueOrPtr.h"
#include "Core\OptionGroup.h"

// Disable the C4481 warning for the override keyword
#pragma warning(push)
#pragma warning(disable : 4481)

class ColorPickerOption : public Option
{
public:
    ColorPickerOption();

    ColorPickerOption(const std::wstring &name, Callback callback, const ValueOrPtr<D3DCOLOR> &color);

    virtual void Update(ATG::GAMEPAD *pGamepad) override;

    virtual HRESULT Render(float x, float y) override;

private:
    ValueOrPtr<D3DCOLOR> m_Color;
    uint32_t m_Red;
    uint32_t m_Green;
    uint32_t m_Blue;
    uint32_t m_Alpha;

    bool m_Open;

    OptionGroup m_OptionGroup;
};

#pragma warning(pop)
