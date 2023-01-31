#include "pch.h"
#include "UI\Border.h"

Border::Border()
    : m_Props(), m_IsInitialized(false)
{
}

HRESULT Border::SetProps(const Props &props)
{
    m_Props = props;

    // If this is the first time SetProps is called, just initialize the borders and return
    if (!m_IsInitialized)
        return Init();

    // Set the borders from the props
    return SetBorders();
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

HRESULT Border::Init()
{
    HRESULT hr = S_OK;

    // Set the borders from the props
    hr = SetBorders();
    if (FAILED(hr))
        return hr;

    m_IsInitialized = true;

    return hr;
}

HRESULT Border::SetBorders()
{
    HRESULT hr = S_OK;

    // Set the left border
    Line::Props leftBorderProps = { 0 };
    leftBorderProps.X = m_Props.X - m_Props.Thickness;
    leftBorderProps.Y = m_Props.Y;
    leftBorderProps.Width = m_Props.Thickness;
    leftBorderProps.Height = m_Props.Height + (m_Props.Position & Border_Bottom ? m_Props.Thickness : 0.0f);
    leftBorderProps.Color = m_Props.Color;
    hr = m_Left.SetProps(leftBorderProps);
    if (FAILED(hr))
        return hr;

    // Set the right border
    Line::Props rightBorderProps = { 0 };
    rightBorderProps.X = m_Props.X + m_Props.Width;
    rightBorderProps.Y = m_Props.Y - (m_Props.Position & Border_Top ? m_Props.Thickness : 0.0f);
    rightBorderProps.Width = m_Props.Thickness;
    rightBorderProps.Height = m_Props.Height + (m_Props.Position & Border_Top ? m_Props.Thickness : 0.0f);
    rightBorderProps.Color = m_Props.Color;
    hr = m_Right.SetProps(rightBorderProps);
    if (FAILED(hr))
        return hr;

    // Set the top border if needed
    Line::Props topBorderProps = { 0 };
    topBorderProps.X = m_Props.X - (m_Props.Position & Border_Left ? m_Props.Thickness : 0.0f);
    topBorderProps.Y = m_Props.Y - m_Props.Thickness;
    topBorderProps.Width = m_Props.Width + (m_Props.Position & Border_Left ? m_Props.Thickness : 0.0f);
    topBorderProps.Height = m_Props.Thickness;
    topBorderProps.Color = m_Props.Color;
    hr = m_Top.SetProps(topBorderProps);
    if (FAILED(hr))
        return hr;

    // Set the bottom border if needed
    Line::Props bottomBorderProps = { 0 };
    bottomBorderProps.X = m_Props.X;
    bottomBorderProps.Y = m_Props.Y + m_Props.Height;
    bottomBorderProps.Width = m_Props.Width + (m_Props.Position & Border_Right ? m_Props.Thickness : 0.0f);
    bottomBorderProps.Height = m_Props.Thickness;
    bottomBorderProps.Color = m_Props.Color;
    hr = m_Bottom.SetProps(bottomBorderProps);
    if (FAILED(hr))
        return hr;

    return hr;
}
