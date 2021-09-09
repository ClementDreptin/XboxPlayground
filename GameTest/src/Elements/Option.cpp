#include "pch.h"
#include "Elements\Option.h"


//--------------------------------------------------------------------------------------
// Declarations of static members
//--------------------------------------------------------------------------------------
BOOL Option::s_bFontInitialized = FALSE;
ATG::Font Option::s_Font;


//--------------------------------------------------------------------------------------
// Name: Option()
// Desc: Constructor.
//--------------------------------------------------------------------------------------
Option::Option(CONST std::wstring& wstrText, UINT uiIndex, Callback fnCallback, D3DCOLOR dwColor)
    : m_wstrText(wstrText), m_uiIndex(uiIndex), m_fnCallback(fnCallback), m_dwColor(dwColor)
{
    if (!s_bFontInitialized) InitFont();
}


//--------------------------------------------------------------------------------------
// Name: InitFont()
// Desc: Creates the font used to render the text of all options.
//--------------------------------------------------------------------------------------
HRESULT Option::InitFont()
{
    HRESULT hr;

    // Make sure we only initialize the font once
    if (s_bFontInitialized)
    {
        Log::Error("Font already initialized");
        return E_FAIL;
    }

    // Create the font
    hr = s_Font.Create("game:\\Media\\Fonts\\Arial_20.xpr");
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the font");
        return hr;
    }

    s_bFontInitialized = TRUE;

    return S_OK;
}