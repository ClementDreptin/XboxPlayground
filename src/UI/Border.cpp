#include "pch.h"
#include "UI\Border.h"

Border::Border()
    : m_Props()
{
}

HRESULT Border::Init(const Props &props)
{
    HRESULT hr = S_OK;

    // Save the props
    m_Props = props;

    // Return early if no borders need to be initialized
    if (m_Props.Position == Border_None || m_Props.Thickness == 0)
        return hr;

    // Initialize the left border if needed
    if (m_Props.Position & Border_Left)
    {
        Line::Props leftBorderProps = { 0 };
        leftBorderProps.X = m_Props.X - m_Props.Thickness;
        leftBorderProps.Y = m_Props.Y;
        leftBorderProps.Width = m_Props.Thickness;
        leftBorderProps.Height = m_Props.Height + (m_Props.Position & Border_Bottom ? m_Props.Thickness : 0.0f);
        leftBorderProps.Color = m_Props.Color;

        hr = m_Left.Init(leftBorderProps);
        if (FAILED(hr))
            return hr;
    }

    // Initialize the right border if needed
    if (m_Props.Position & Border_Right)
    {
        Line::Props rightBorderProps = { 0 };
        rightBorderProps.X = m_Props.X + m_Props.Width;
        rightBorderProps.Y = m_Props.Y - (m_Props.Position & Border_Top ? m_Props.Thickness : 0.0f);
        rightBorderProps.Width = m_Props.Thickness;
        rightBorderProps.Height = m_Props.Height + (m_Props.Position & Border_Top ? m_Props.Thickness : 0.0f);
        rightBorderProps.Color = m_Props.Color;

        hr = m_Right.Init(rightBorderProps);
        if (FAILED(hr))
            return hr;
    }

    // Initialize the top border if needed
    if (m_Props.Position & Border_Top)
    {
        Line::Props topBorderProps = { 0 };
        topBorderProps.X = m_Props.X - (m_Props.Position & Border_Left ? m_Props.Thickness : 0.0f);
        topBorderProps.Y = m_Props.Y - m_Props.Thickness;
        topBorderProps.Width = m_Props.Width + (m_Props.Position & Border_Left ? m_Props.Thickness : 0.0f);
        topBorderProps.Height = m_Props.Thickness;
        topBorderProps.Color = m_Props.Color;

        hr = m_Top.Init(topBorderProps);
        if (FAILED(hr))
            return hr;
    }

    // Initialize the bottom border if needed
    if (m_Props.Position & Border_Bottom)
    {
        Line::Props bottomBorderProps = { 0 };
        bottomBorderProps.X = m_Props.X;
        bottomBorderProps.Y = m_Props.Y + m_Props.Height;
        bottomBorderProps.Width = m_Props.Width + (m_Props.Position & Border_Right ? m_Props.Thickness : 0.0f);
        bottomBorderProps.Height = m_Props.Thickness;
        bottomBorderProps.Color = m_Props.Color;

        hr = m_Bottom.Init(bottomBorderProps);
        if (FAILED(hr))
            return hr;
    }

    return hr;
}

void Border::Render()
{
    // Return early if no borders need to be rendered
    if (m_Props.Position == Border_None || m_Props.Thickness == 0)
        return;

    // Render the left border if needed
    if (m_Props.Position & Border_Left)
        m_Left.Render();

    // Render the right border if needed
    if (m_Props.Position & Border_Right)
        m_Right.Render();

    // Render the top border if needed
    if (m_Props.Position & Border_Top)
        m_Top.Render();

    // Render the bottom border if needed
    if (m_Props.Position & Border_Bottom)
        m_Bottom.Render();
}
