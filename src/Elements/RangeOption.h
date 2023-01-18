#pragma once

#include "Elements\Option.h"

// Disable the C4481 warning for the override keyword
#pragma warning(push)
#pragma warning(disable : 4481)

// Class to represent an option with a changeable number value.
class RangeOption : public Option
{
public:
    RangeOption();

    RangeOption(const std::wstring &text, Callback callback, float min, float max, float step);

    // Check for user clicks.
    virtual void Update(ATG::GAMEPAD *pGamepad) override;

    // Render the text.
    virtual void Render(float x, float y, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

private:
    float m_Min;
    float m_Max;
    float m_Step;
    float m_Current;
};

#pragma warning(pop)
