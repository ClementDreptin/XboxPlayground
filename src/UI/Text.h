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

    inline Props GetProps() const { return m_Props; }

    // Set the new props and update the background if needed.
    HRESULT SetProps(const Props &props);

    // Render the text.
    void Render();

private:
    Props m_Props;
    Rectangle m_Background;
    bool m_HasBackgroundOrBorder;
    bool m_IsInitialized;

    // Initialize the background if needed.
    HRESULT Init();

    // Generate the background props.
    Rectangle::Props GenerateBackgroundProps();
};
