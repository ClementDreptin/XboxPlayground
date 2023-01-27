#pragma once

#include "UI\Layout.h"
#include "UI\Rectangle.h"

// Class to represent a piece of text.
class Text
{
public:
    struct Props
    {
        float X;
        float Y;
        std::wstring Text;
        D3DCOLOR Color;
        D3DCOLOR BackgroundColor;
        float BorderWidth;
        D3DCOLOR BorderColor;
        Border::Position BorderPosition;
    };

    Text();

    // Initialize the background if needed.
    HRESULT Init(const Props &props);

    inline Props &GetProps() { return m_Props; }

    // Render the text.
    void Render();

private:
    Props m_Props;
    Rectangle m_Background;
    bool m_HasBackgroundOrBorder;
};
