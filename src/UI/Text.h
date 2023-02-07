#pragma once

#include "UI/Layout.h"
#include "UI/Rectangle.h"

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

    Text() {}

    HRESULT Render(const Props &props);

private:
    Rectangle m_Background;
};
