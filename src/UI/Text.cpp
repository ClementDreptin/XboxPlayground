#include "pch.h"
#include "UI/Text.h"

#include "UI/Font.h"

void Text::Render(const Props &props)
{
    bool hasBackgroundOrBorder = props.BackgroundColor != 0 || (props.BorderWidth > 0 && props.BorderPosition != Border::Border_None);
    float fontScale = props.FontScale != 0.0f ? props.FontScale : 1.0f;
    g_Font.SetScaleFactors(fontScale, fontScale);
    float padding = Layout::Padding * fontScale;

    float textWidth = 0.0f;
    float textHeight = 0.0f;
    g_Font.GetTextDimensions(props.Text, &textWidth, &textHeight);
    float rectWidth = props.BackgroundWidth != 0.0f ? props.BackgroundWidth : (textWidth + padding * 2);
    float rectHeight = props.BackgroundHeight != 0.0f ? props.BackgroundHeight : (textHeight + padding * 2);

    // Render the background if needed
    if (hasBackgroundOrBorder)
    {
        Rectangle::Props rectProps = { 0 };
        rectProps.X = props.X;
        rectProps.Y = props.Y;
        rectProps.Width = rectWidth;
        rectProps.Height = rectHeight;
        rectProps.Color = props.BackgroundColor;
        rectProps.BorderWidth = props.BorderWidth;
        rectProps.BorderColor = props.BorderColor;
        rectProps.BorderPosition = props.BorderPosition;

        m_Background.Render(rectProps);
    }

    // Render the text
    float x = props.X + (hasBackgroundOrBorder ? padding : 0.0f);
    float y = props.Y + rectHeight / 2 - textHeight / 2;
    g_Font.DrawText(x, y, props.Color, props.Text.c_str());
    g_Font.SetScaleFactors(1.0f, 1.0f);
}
