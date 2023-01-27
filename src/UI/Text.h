#pragma once

#include "UI\Layout.h"

// Class to represent a piece of text.
class Text
{
public:
    Text() {}
    Text(const std::wstring &text);

    // Render the text.
    void Render(float x, float y, D3DCOLOR color = Layout::TextColor);

private:
    std::wstring m_Text;
};
