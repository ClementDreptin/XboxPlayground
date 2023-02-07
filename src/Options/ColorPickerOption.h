#pragma once

#include "Options\SubOptionGroup.h"
#include "Core\ValueOrPtr.h"

// Disable the C4481 warning for the override keyword
#pragma warning(push)
#pragma warning(disable : 4481)

class ColorPickerOption : public SubOptionGroup
{
public:
    ColorPickerOption();

    ColorPickerOption(const std::wstring &name, Callback callback, const ValueOrPtr<D3DCOLOR> &color);

    virtual bool Update(ATG::GAMEPAD *pGamepad) override;

private:
    ValueOrPtr<D3DCOLOR> m_Color;
    uint32_t m_Red;
    uint32_t m_Green;
    uint32_t m_Blue;
    uint32_t m_Alpha;
};

#pragma warning(pop)