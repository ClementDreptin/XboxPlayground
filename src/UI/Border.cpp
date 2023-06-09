#include "pch.h"
#include "UI/Border.h"

HRESULT Border::Render(const Props &props)
{
    HRESULT hr = S_OK;

    // Return early if no borders need to be rendered
    if (props.Position == Border_None || props.Thickness == 0)
        return hr;

    // Render the left border if needed
    if (props.Position & Border_Left)
    {
        Line::Props lineProps = { 0 };
        lineProps.X = props.X - props.Thickness;
        lineProps.Y = props.Y;
        lineProps.Width = props.Thickness;
        lineProps.Height = props.Height + (props.Position & Border_Bottom ? props.Thickness : 0.0f);
        lineProps.Color = props.Color;
        hr = m_Left.Render(lineProps);
        if (FAILED(hr))
            return hr;
    }

    // Render the right border if needed
    if (props.Position & Border_Right)
    {
        Line::Props lineProps = { 0 };
        lineProps.X = props.X + props.Width;
        lineProps.Y = props.Y - (props.Position & Border_Top ? props.Thickness : 0.0f);
        lineProps.Width = props.Thickness;
        lineProps.Height = props.Height + (props.Position & Border_Top ? props.Thickness : 0.0f);
        lineProps.Color = props.Color;
        hr = m_Right.Render(lineProps);
        if (FAILED(hr))
            return hr;
    }

    // Render the top border if needed
    if (props.Position & Border_Top)
    {
        Line::Props lineProps = { 0 };
        lineProps.X = props.X - (props.Position & Border_Left ? props.Thickness : 0.0f);
        lineProps.Y = props.Y - props.Thickness;
        lineProps.Width = props.Width + (props.Position & Border_Left ? props.Thickness : 0.0f);
        lineProps.Height = props.Thickness;
        lineProps.Color = props.Color;
        hr = m_Top.Render(lineProps);
        if (FAILED(hr))
            return hr;
    }

    // Render the bottom border if needed
    if (props.Position & Border_Bottom)
    {
        Line::Props lineProps = { 0 };
        lineProps.X = props.X;
        lineProps.Y = props.Y + props.Height;
        lineProps.Width = props.Width + (props.Position & Border_Right ? props.Thickness : 0.0f);
        lineProps.Height = props.Thickness;
        lineProps.Color = props.Color;
        hr = m_Bottom.Render(lineProps);
        if (FAILED(hr))
            return hr;
    }

    return hr;
}
