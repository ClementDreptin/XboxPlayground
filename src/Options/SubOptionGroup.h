#pragma once

#include "pch.h"
#include "Core/OptionGroup.h"

class SubOptionGroup : public Option
{
public:
    SubOptionGroup();

    SubOptionGroup(const std::wstring &name, const OptionGroup &optionGroup);

    virtual bool Update(Input::Gamepad *pGamepad) override;

    virtual HRESULT Render(float x, float y, float width) override;

protected:
    bool m_Open;
    OptionGroup m_OptionGroup;
};
