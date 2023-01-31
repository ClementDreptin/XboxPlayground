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
    {
        Line::Props props = { 0 };
        props.X = m_Props.X - m_Props.Thickness;
        props.Y = m_Props.Y;
        props.Width = m_Props.Thickness;
        props.Height = m_Props.Height + (m_Props.Position & Border_Bottom ? m_Props.Thickness : 0.0f);
        props.Color = m_Props.Color;
        hr = m_Left.SetProps(props);
        if (FAILED(hr))
            return hr;
    }

    // Set the right border
    {
        Line::Props props = { 0 };
        props.X = m_Props.X + m_Props.Width;
        props.Y = m_Props.Y - (m_Props.Position & Border_Top ? m_Props.Thickness : 0.0f);
        props.Width = m_Props.Thickness;
        props.Height = m_Props.Height + (m_Props.Position & Border_Top ? m_Props.Thickness : 0.0f);
        props.Color = m_Props.Color;
        hr = m_Right.SetProps(props);
        if (FAILED(hr))
            return hr;
    }

    // Set the top border if needed
    {
        Line::Props props = { 0 };
        props.X = m_Props.X - (m_Props.Position & Border_Left ? m_Props.Thickness : 0.0f);
        props.Y = m_Props.Y - m_Props.Thickness;
        props.Width = m_Props.Width + (m_Props.Position & Border_Left ? m_Props.Thickness : 0.0f);
        props.Height = m_Props.Thickness;
        props.Color = m_Props.Color;
        hr = m_Top.SetProps(props);
        if (FAILED(hr))
            return hr;
    }

    // Set the bottom border if needed
    {
        Line::Props props = { 0 };
        props.X = m_Props.X;
        props.Y = m_Props.Y + m_Props.Height;
        props.Width = m_Props.Width + (m_Props.Position & Border_Right ? m_Props.Thickness : 0.0f);
        props.Height = m_Props.Thickness;
        props.Color = m_Props.Color;
        hr = m_Bottom.SetProps(props);
        if (FAILED(hr))
            return hr;
    }

    return hr;
}
