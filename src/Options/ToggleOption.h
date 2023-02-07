#pragma once

#include "Options\Option.h"
#include "UI\Rectangle.h"

// Disable the C4481 warning for the override keyword
#pragma warning(push)
#pragma warning(disable : 4481)

class ToggleOption : public Option
{
public:
    ToggleOption();

    ToggleOption(const std::wstring &name, Callback callback);

    virtual bool Update(ATG::GAMEPAD *pGamepad) override;

    virtual HRESULT Render(float x, float y, float width) override;

private:
    bool m_Active;

    Rectangle m_RadioBox;
};

#pragma warning(pop)
