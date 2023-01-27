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

    // Initialize the font.
    static void Begin() { s_Font.Begin(); };

    // Clean up the font.
    static void End() { s_Font.End(); };

    // Get the font height.
    static float GetFontHeight() { return s_Font.GetFontHeight(); }

    // Update the option.
    virtual void Update(ATG::GAMEPAD *pGamepad) = 0;

    // Render the text.
    virtual void Render(float x, float y, D3DCOLOR color = Layout::TextColor) = 0;

protected:
    std::wstring m_Text;
    Callback m_Callback;

    static ATG::Font s_Font;

private:
    static bool s_FontInitialized;

    // Creates the font used to render the text of all options.
    static HRESULT InitFont();
};

// Macro to create a shared pointer to an option. Being able to use templated arguments and std::forward
// would be much nicer but they were never implemented for the Xbox 360 compiler.
#define MakeOption(OptionType, ...) std::make_shared<OptionType>(__VA_ARGS__)
