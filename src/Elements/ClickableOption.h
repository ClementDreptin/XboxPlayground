#pragma once

#include "Elements\Option.h"

// Disable the C4481 warning for the override keyword
#pragma warning(push)
#pragma warning(disable : 4481)

// Class to represent a very basic option
class ClickableOption : public Option
{
public:
    ClickableOption();

    ClickableOption(const std::wstring &name, Callback callback);

    // Check for user clicks.
    virtual void Update(ATG::GAMEPAD *pGamepad) override;

    // Render the text.
    virtual void Render(float x, float y, D3DCOLOR color = Layout::TextColor) override;
};

#pragma warning(pop)
