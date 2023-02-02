#pragma once

#include "Elements\Option.h"
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
    virtual void Update(ATG::GAMEPAD *pGamepad) override;

    // Render the text and the radio box.
    virtual void Render(float x, float y, D3DCOLOR color = Layout::TextColor) override;

private:
    bool m_Active;

    Rectangle m_RadioBox;
    static float s_RadioBoxSize;
};

#pragma warning(pop)
