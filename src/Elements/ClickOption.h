#pragma once

#include "Elements\Option.h"

// Disable the C4481 warning for the override keyword
#pragma warning(push)
#pragma warning(disable : 4481)

// Class to represent a very basic option
class ClickOption : public Option
{
public:
    ClickOption();

    ClickOption(const std::wstring &name, Callback callback);

    // Check for user clicks.
    virtual void Update(ATG::GAMEPAD *pGamepad) override;

    // Render the text.
    virtual HRESULT Render(float x, float y) override;
};

#pragma warning(pop)
