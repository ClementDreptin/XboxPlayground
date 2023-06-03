#include "pch.h"
#include "UI/Font.h"

float Font::GetTextWidth(const std::wstring &text)
{
    float width = 0.0f;
    GetTextDimensions(text, &width);

    return width;
}

float Font::GetTextHeight(const std::wstring &text)
{
    float height = 0.0f;
    GetTextDimensions(text, nullptr, &height);

    return height;
}

void Font::GetTextDimensions(const std::wstring &text, float *pWidth, float *pHeight) const
{
    float width = 0.0f;
    float height = m_fFontHeight;
    const wchar_t *str = text.c_str();

    wchar_t letter = L'\0';
    while ((letter = *str) != 0)
    {
        ++str;

        if (letter == L'\n')
        {
            width = 0.0f;
            height += m_fFontYAdvance;

            continue;
        }

        if (letter == L'\r')
            continue;

        if (letter > m_cMaxGlyph)
            letter = L'\0';
        else
            letter = m_TranslatorTable[letter];

        const ATG::GLYPH_ATTR *pGlyph = &m_Glyphs[letter];
        width += pGlyph->wOffset + pGlyph->wAdvance;
    }

    width *= m_fXScaleFactor;
    height *= m_fYScaleFactor;

    if (pWidth != nullptr)
        *pWidth = width;

    if (pHeight != nullptr)
        *pHeight = height;
}
