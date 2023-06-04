#include "pch.h"
#include "Options/Option.h"

#include "UI/Font.h"

Option::Option()
    : m_Callback(nullptr), m_IsSelected(false), m_CachedMinWidth(0.0f), m_CachedMinHeight(0.0f)
{
}

Option::Option(const std::wstring &name, Callback callback)
    : m_Name(name), m_Callback(callback), m_CachedMinWidth(0.0f), m_CachedMinHeight(0.0f)
{
}

HRESULT Option::Render(float x, float y, float width)
{
    HRESULT hr = S_OK;

    // Render the background if the option is selected
    if (m_IsSelected)
    {
        Rectangle::Props props = { 0 };
        props.X = x + Layout::Gap;
        props.Y = y + Layout::Gap;
        props.Width = width - Layout::Gap * 2;
        props.Height = GetMinHeight() - Layout::Gap * 2;
        props.Color = Layout::Color;
        hr = m_Background.Render(props);
        if (FAILED(hr))
            return hr;
    }

    // Render the text
    Text::Props props = { 0 };
    props.X = x + Layout::Padding;
    props.Y = y;
    props.Text = m_Name;
    props.Color = Layout::TextColor;
    hr = m_Text.Render(props);

    return hr;
}

float Option::GetMinWidth() const
{
    // Return the cached value if the minimum width has already been calculated
    if (m_CachedMinWidth != 0.0f)
        return m_CachedMinWidth;

    m_CachedMinWidth = g_Font.GetTextWidth(m_Name) + Layout::Padding * 2;

    // Take into account some space between the option name and the potential text on the right (e.g. the number for RangeOption)
    m_CachedMinWidth += 100.0f;

    return m_CachedMinWidth;
}

float Option::GetMinHeight() const
{
    // Return the cached value if the minimum height has already been calculated
    if (m_CachedMinHeight != 0.0f)
        return m_CachedMinHeight;

    m_CachedMinHeight = g_Font.GetTextHeight(m_Name) + Layout::Padding * 2;

    return m_CachedMinHeight;
}
