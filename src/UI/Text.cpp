#include "pch.h"
#include "UI\Text.h"

#include "UI\Font.h"

HRESULT Text::Render(const Props &props)
{
    HRESULT hr = S_OK;

    bool hasBackgroundOrBorder = props.BackgroundColor != 0 || (props.BorderWidth > 0 && props.BorderPosition != Border::Border_None);

    // Render the background if needed
    if (hasBackgroundOrBorder)
    {
        Rectangle::Props rectProps = { 0 };
        rectProps.X = props.X;
        rectProps.Y = props.Y;
        rectProps.Width = g_Font.GetTextWidth(props.Text.c_str()) + Layout::Padding * 2;
        rectProps.Height = Layout::LineHeight;
        rectProps.Color = props.BackgroundColor;
        rectProps.BorderWidth = props.BorderWidth;
        rectProps.BorderColor = props.BorderColor;
        rectProps.BorderPosition = props.BorderPosition;
        hr = m_Background.Render(rectProps);
        if (FAILED(hr))
            return hr;
    }

    // Render the text
    float x = props.X + (hasBackgroundOrBorder ? Layout::Padding : 0.0f);
    float y = props.Y + (hasBackgroundOrBorder ? Layout::Padding : 0.0f);
    g_Font.DrawText(x, y, props.Color, props.Text.c_str());

    return hr;
}
