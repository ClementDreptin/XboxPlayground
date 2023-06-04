#include "pch.h"
#include "UI/Text.h"

#include "UI/Font.h"

HRESULT Text::Render(const Props &props)
{
    HRESULT hr = S_OK;

    bool hasBackgroundOrBorder = props.BackgroundColor != 0 || (props.BorderWidth > 0 && props.BorderPosition != Border::Border_None);
    float fontScale = props.FontScale != 0.0f ? props.FontScale : 1.0f;
    float padding = Layout::Padding * fontScale;
    g_Font.SetScaleFactors(fontScale, fontScale);

    // Render the background if needed
    if (hasBackgroundOrBorder)
    {
        Rectangle::Props rectProps = { 0 };
        rectProps.X = props.X;
        rectProps.Y = props.Y;

        float textWidth = 0.0f;
        float textHeight = 0.0f;
        g_Font.GetTextDimensions(props.Text, &textWidth, &textHeight);
        rectProps.Width = props.BackgroundWidth != 0.0f ? props.BackgroundWidth : (textWidth + padding * 2);
        rectProps.Height = props.BackgroundHeight != 0.0f ? props.BackgroundHeight : (textHeight + padding * 2);

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
    g_Font.DrawText(x, y, props.Color, props.Text.c_str());
    g_Font.SetScaleFactors(1.0f, 1.0f);

    return hr;
}
