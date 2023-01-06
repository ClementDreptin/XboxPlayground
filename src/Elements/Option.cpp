#include "pch.h"
#include "Elements\Option.h"

bool Option::s_FontInitialized = false;
ATG::Font Option::s_Font;

Option::Option(const std::wstring &text, uint32_t index, Callback callback, D3DCOLOR color)
    : m_Text(text), m_Index(index), m_Callback(callback), m_Color(color)
{
    if (!s_FontInitialized)
        InitFont();
}

HRESULT Option::InitFont()
{
    HRESULT hr = S_OK;

    // Make sure we only initialize the font once
    if (s_FontInitialized)
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

    s_FontInitialized = true;

    return S_OK;
}
