#pragma once

#include "Options/Option.h"
#include "Core/ValueOrPtr.h"
#include "UI/Rectangle.h"

class ToggleOption : public Option
{
public:
    ToggleOption();

    ToggleOption(const std::wstring &name, const ValueOrPtr<bool> &activefalse);

    ToggleOption(const std::wstring &name, Callback callback, const ValueOrPtr<bool> &active);

    virtual bool Update(Input::Gamepad *pGamepad) override;

    virtual void Render(float x, float y, float width) override;

private:
    ValueOrPtr<bool> m_Active;

    Rectangle m_RadioBox;
};
