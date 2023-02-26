#include "pch.h"
#include "UI/Text.h"

#include "UI/Font.h"

HRESULT Text::Render(const Props &props)
{
    HRESULT hr = S_OK;

    bool hasBackgroundOrBorder = props.BackgroundColor != 0 || (props.BorderWidth > 0 && props.BorderPosition != Border::Border_None);
    float fontScale = props.FontScale != 0.0f ? props.FontScale : 1.0f;
    float padding = Layout::Padding * fontScale;

    // Render the background if needed
    if (hasBackgroundOrBorder)
    {
        Rectangle::Props rectProps = { 0 };
        rectProps.X = props.X;
        rectProps.Y = props.Y;
        rectProps.Width = g_Font.GetTextWidth(props.Text.c_str()) * fontScale + padding * 2;
        rectProps.Height = g_Font.GetFontHeight() * fontScale + padding * 2;
        rectProps.Color = props.BackgroundColor;
        rectProps.BorderWidth = props.BorderWidth;
        rectProps.BorderColor = props.BorderColor;
        rectProps.BorderPosition = props.BorderPosition;
        hr = m_Background.Render(rectProps);
        if (FAILED(hr))
            return hr;
    }

    // Render the text
    float x = props.X + (hasBackgroundOrBorder ? padding : 0.0f);
    float y = props.Y + (hasBackgroundOrBorder ? padding : 0.0f);
    g_Font.SetScaleFactors(fontScale, fontScale);
    g_Font.DrawText(x, y, props.Color, props.Text.c_str());
    g_Font.SetScaleFactors(1.0f, 1.0f);

    return hr;
}
