#pragma once

#include <AtgFont.h>

// Class describing a clickable option in a menu.
class Option
{
public:
    typedef void (*Callback)(void *pParameters);

    Option() {}

    Option(const std::wstring &text, uint32_t index, Callback callback, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

    // Initialize the font.
    static void Begin() { s_Font.Begin(); };

    // Clean up the font.
    static void End() { s_Font.End(); };

    D3DCOLOR GetColor() const { return m_Color; }

    void SetColor(D3DCOLOR dwColor) { m_Color = dwColor; }

    // Render the text.
    void Render(float x, float y) { s_Font.DrawText(x, y, m_Color, m_Text.c_str()); }

    // Call the Option's callback.
    void OnClick(void *pParameters) { m_Callback(pParameters); }

private:
    std::wstring m_Text;
    uint32_t m_Index;
    Callback m_Callback;
    D3DCOLOR m_Color;

    static bool s_FontInitialized;
    static ATG::Font s_Font;

    // Creates the font used to render the text of all options.
    static HRESULT InitFont();
};
