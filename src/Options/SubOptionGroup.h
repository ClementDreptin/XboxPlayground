#pragma once

#include "Core/OptionGroup.h"

// Disable the C4481 warning for the override keyword
#pragma warning(push)
#pragma warning(disable : 4481)

class SubOptionGroup : public Option
{
public:
    SubOptionGroup();

    SubOptionGroup(const std::wstring &name, Callback callback, const OptionGroup &optionGroup);

    virtual bool Update(ATG::GAMEPAD *pGamepad) override;

    virtual HRESULT Render(float x, float y, float width) override;

protected:
    bool m_Open;
    OptionGroup m_OptionGroup;
};

#pragma warning(pop)
