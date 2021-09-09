#pragma once

#include <AtgFont.h>


//--------------------------------------------------------------------------------------
// Name: class Option
// Desc: Class describing a clickable option in a menu.
//--------------------------------------------------------------------------------------
class Option
{
public:
    typedef VOID (*Callback)(LPVOID pParameters);

    Option() {}
    Option(CONST std::wstring& wstrText, UINT uiIndex, Callback fnCallback, D3DCOLOR dwColor = D3DCOLOR_XRGB(255, 255, 255));

    static VOID Begin() { s_Font.Begin(); };
    static VOID End() { s_Font.End(); };

    D3DCOLOR GetColor() CONST { return m_dwColor; }

    VOID SetColor(D3DCOLOR dwColor) { m_dwColor = dwColor; }

    VOID Draw(FLOAT fX, FLOAT fY) { s_Font.DrawText(fX, fY, m_dwColor, m_wstrText.c_str()); }

    VOID OnClick(LPVOID pParameters) { m_fnCallback(pParameters); }
private:
    std::wstring m_wstrText;
    UINT m_uiIndex;
    Callback m_fnCallback;
    D3DCOLOR m_dwColor;

    static BOOL s_bFontInitialized;
    static ATG::Font s_Font;

    static HRESULT InitFont();
};
