#pragma once

#include <AtgFont.h>
#include <AtgInput.h>

// Class describing a clickable option in a menu.
class Option
{
public:
    typedef void (*Callback)(void *pParameters);

    Option() {}

    Option(const std::wstring &text, Callback callback, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

    // Initialize the font.
    static void Begin() { s_Font.Begin(); };

    // Clean up the font.
    static void End() { s_Font.End(); };

    D3DCOLOR GetColor() const { return m_Color; }

    void SetColor(D3DCOLOR dwColor) { m_Color = dwColor; }

    // Update the option.
    void Update(ATG::GAMEPAD *pGamepad);

    // Render the text.
    void Render(float x, float y) { s_Font.DrawText(x, y, m_Color, m_Text.c_str()); }

private:
    std::wstring m_Text;
    Callback m_Callback;
    D3DCOLOR m_Color;

    static bool s_FontInitialized;
    static ATG::Font s_Font;

    // Creates the font used to render the text of all options.
    static HRESULT InitFont();
};
