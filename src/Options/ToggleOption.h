#pragma once

#include "Options\Option.h"
#include "UI\Rectangle.h"

// Disable the C4481 warning for the override keyword
#pragma warning(push)
#pragma warning(disable : 4481)

// Class to represent an option with a toggleable boolean value.
class ToggleOption : public Option
{
public:
    ToggleOption();

    ToggleOption(const std::wstring &name, Callback callback);

    // Toggle the option on user clicks.
    virtual bool Update(ATG::GAMEPAD *pGamepad) override;

    // Render the text and the radio box.
    virtual HRESULT Render(float x, float y, float width) override;

private:
    bool m_Active;

    Rectangle m_RadioBox;
};

#pragma warning(pop)
