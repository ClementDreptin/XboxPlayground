#pragma once

#include <AtgInput.h>

#include "UI\Layout.h"
#include "UI\Text.h"
#include "UI\Rectangle.h"

// Abstract class describing an option in a menu (need to be derived to be instantiated).
class Option
{
public:
    typedef void (*Callback)(void *pParameters);

    Option();

    virtual ~Option() {}

    Option(const std::wstring &text, Callback callback);

    // Set the option state (selected or not).
    void Select(bool selected) { m_IsSelected = selected; }

    // Update the option.
    virtual void Update(ATG::GAMEPAD *pGamepad) = 0;

    // Render the text.
    virtual void Render(float x, float y, D3DCOLOR color = Layout::TextColor) = 0;

protected:
    Text m_Text;
    Callback m_Callback;

    bool m_IsSelected;
    Rectangle m_Background;
};

// Macro to create a shared pointer to an option. Being able to use templated arguments and std::forward
// would be much nicer but they were never implemented for the Xbox 360 compiler.
#define MakeOption(OptionType, ...) std::make_shared<OptionType>(__VA_ARGS__)
