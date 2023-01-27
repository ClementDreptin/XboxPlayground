#include "pch.h"
#include "UI\Text.h"

#include "UI\Font.h"

Text::Text()
    : m_Props(), m_HasBackgroundOrBorder(false)
{
}

HRESULT Text::Init(const Props &props)
{
    HRESULT hr = S_OK;

    // Save the props
    m_Props = props;

    // Initialize the background if needed
    m_HasBackgroundOrBorder = m_Props.BackgroundColor != 0 || (m_Props.BorderWidth > 0 && m_Props.BorderPosition != Border::Border_None);
    if (m_HasBackgroundOrBorder)
    {
        Rectangle::Props rectangleProps = { 0 };
        rectangleProps.X = m_Props.X;
        rectangleProps.Y = m_Props.Y;
        rectangleProps.Width = g_Font.GetTextWidth(m_Props.Text.c_str()) + Layout::Padding * 2;
        rectangleProps.Height = g_Font.GetFontHeight() + Layout::Padding * 2;
        rectangleProps.Color = m_Props.BackgroundColor;
        rectangleProps.BorderWidth = m_Props.BorderWidth;
        rectangleProps.BorderColor = m_Props.BorderColor;
        rectangleProps.BorderPosition = m_Props.BorderPosition;

        hr = m_Background.Init(rectangleProps);
        if (FAILED(hr))
            return hr;
    }

    return hr;
}

void Text::Render()
{
    // Render the background if needed
    if (m_HasBackgroundOrBorder)
        m_Background.Render();

    // Render the text
    float x = m_Props.X + (m_HasBackgroundOrBorder ? Layout::Padding : 0.0f);
    float y = m_Props.Y + (m_HasBackgroundOrBorder ? Layout::Padding : 0.0f);
    g_Font.DrawText(x, y, m_Props.Color, m_Props.Text.c_str());
}
