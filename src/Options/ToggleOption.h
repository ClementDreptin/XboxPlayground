#pragma once

#include "Options/Option.h"
#include "Core/ValueOrPtr.h"
#include "UI/Rectangle.h"

class ToggleOption : public Option
{
public:
    ToggleOption();

    ToggleOption(const std::wstring &name, Callback callback, const ValueOrPtr<bool> &active = false);

    virtual bool Update(Input::Gamepad *pGamepad) override;

    virtual HRESULT Render(float x, float y, float width) override;

private:
    ValueOrPtr<bool> m_Active;

    Rectangle m_RadioBox;
};
