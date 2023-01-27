#pragma once

#include <AtgFont.h>
#include <AtgInput.h>

#include "UI\Layout.h"

// Abstract class describing an option in a menu (need to be derived to be instantiated).
class Option
{
public:
    typedef void (*Callback)(void *pParameters);

    Option();

    virtual ~Option() {}

    Option(const std::wstring &text, Callback callback);

    // Update the option.
    virtual void Update(ATG::GAMEPAD *pGamepad) = 0;

    // Render the text.
    virtual void Render(float x, float y, D3DCOLOR color = Layout::TextColor) = 0;

protected:
    std::wstring m_Text;
    Callback m_Callback;
};

// Macro to create a shared pointer to an option. Being able to use templated arguments and std::forward
// would be much nicer but they were never implemented for the Xbox 360 compiler.
#define MakeOption(OptionType, ...) std::make_shared<OptionType>(__VA_ARGS__)
