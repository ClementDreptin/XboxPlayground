#include "pch.h"
#include "Options\Option.h"

#include "UI\Font.h"

Option::Option()
    : m_Callback(nullptr), m_IsSelected(false)
{
}

Option::Option(const std::wstring &name, Callback callback)
    : m_Name(name), m_Callback(callback)
{
}

HRESULT Option::Render(float x, float y)
{
    HRESULT hr = S_OK;

    // Render the background if the option is selected
    if (m_IsSelected)
    {
        Rectangle::Props props = { 0 };
        props.X = x + Layout::Gap;
        props.Y = y + Layout::Gap;
        props.Width = Layout::Width - Layout::Gap * 2;
        props.Height = Layout::LineHeight - Layout::Gap * 2;
        props.Color = Layout::Color;
        hr = m_Background.Render(props);
        if (FAILED(hr))
            return hr;
    }

    // Render the text
    Text::Props props = { 0 };
    props.X = x + Layout::Padding;
    props.Y = y + Layout::Padding;
    props.Text = m_Name;
    props.Color = Layout::TextColor;
    hr = m_Text.Render(props);

    return hr;
}
