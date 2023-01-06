#pragma once

#include <AtgFont.h>

// Class describing a clickable option in a menu.
class Option
{
public:
    typedef void (*Callback)(void *pParameters);

    Option() {}

    Option(const std::wstring &wstrText, uint32_t uiIndex, Callback fnCallback, D3DCOLOR dwColor = D3DCOLOR_XRGB(255, 255, 255));

    // Initialize the font.
    static void Begin() { s_Font.Begin(); };

    // Clean up the font.
    static void End() { s_Font.End(); };

    D3DCOLOR GetColor() const { return m_dwColor; }

    void SetColor(D3DCOLOR dwColor) { m_dwColor = dwColor; }

    // Draw the text.
    void Draw(float fX, float fY) { s_Font.DrawText(fX, fY, m_dwColor, m_wstrText.c_str()); }

    // Call the Option's callback.
    void OnClick(void *pParameters) { m_fnCallback(pParameters); }

private:
    std::wstring m_wstrText;
    uint32_t m_uiIndex;
    Callback m_fnCallback;
    D3DCOLOR m_dwColor;

    static bool s_bFontInitialized;
    static ATG::Font s_Font;

    // Creates the font used to render the text of all options.
    static HRESULT InitFont();
};
