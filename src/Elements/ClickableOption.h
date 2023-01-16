#pragma once

#include "Elements\Option.h"

// Disable the C4201 warning for the override keyword
#pragma warning(push)
#pragma warning(disable : 4481)

class ClickableOption : public Option
{
public:
    ClickableOption() {}

    ClickableOption(const std::wstring &text, Callback callback);

    // Check for user clicks.
    virtual void Update(ATG::GAMEPAD *pGamepad) override;

    // Render the text.
    virtual void Render(float x, float y, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

private:
};

#pragma warning(pop)
