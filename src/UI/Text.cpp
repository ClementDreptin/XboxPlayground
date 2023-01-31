#include "pch.h"
#include "UI\Text.h"

#include "UI\Font.h"

Text::Text()
    : m_Props(), m_HasBackgroundOrBorder(false), m_IsInitialized(false)
{
}

HRESULT Text::SetProps(const Props &props)
{
    m_Props = props;
    m_HasBackgroundOrBorder = m_Props.BackgroundColor != 0 || (m_Props.BorderWidth > 0 && m_Props.BorderPosition != Border::Border_None);

    // If this is the first time SetProps is called, just initialize the text and return
    if (!m_IsInitialized)
        return Init();

    // Update the background from the new props
    return SetBackground();
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

HRESULT Text::Init()
{
    HRESULT hr = S_OK;

    // Initialize the background
    hr = SetBackground();
    if (FAILED(hr))
        return hr;

    m_IsInitialized = true;

    return hr;
}

HRESULT Text::SetBackground()
{
    Rectangle::Props props = { 0 };
    props.X = m_Props.X;
    props.Y = m_Props.Y;
    props.Width = g_Font.GetTextWidth(m_Props.Text.c_str()) + Layout::Padding * 2;
    props.Height = g_Font.GetFontHeight() + Layout::Padding * 2;
    props.Color = m_Props.BackgroundColor;
    props.BorderWidth = m_Props.BorderWidth;
    props.BorderColor = m_Props.BorderColor;
    props.BorderPosition = m_Props.BorderPosition;

    return m_Background.SetProps(props);
}
