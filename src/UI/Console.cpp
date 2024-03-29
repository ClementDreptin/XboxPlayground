#include "pch.h"
#include "UI/Console.h"

#include "UI/Font.h"

Console::Console()
    : m_MessageCount(5)
{
}

Console::Console(size_t messageCount)
    : m_MessageCount(messageCount)
{
}

void Console::Log(const std::wstring &message)
{
    m_Messages.push_back(message);

    // Remove the last element when a new one is push to keep the size constant
    if (m_Messages.size() > m_MessageCount)
        m_Messages.pop_front();
}

void Console::Render(float x, float y)
{
    Text::Props props = {};
    props.X = x;
    props.Y = y;
    props.Text = L"";
    props.Color = Layout::TextColor;
    props.BackgroundColor = Layout::BackgroundColor;
    props.BorderWidth = Layout::BorderWidth;
    props.BorderColor = Layout::Color;
    props.BorderPosition = Border::Border_All;

    // Give a fixed the before any messages are logged
    if (m_Messages.empty())
        props.BackgroundWidth = 300.0f;

    // Generate the text from the messages
    for (size_t i = 0; i < m_MessageCount; i++)
    {
        if (i < m_Messages.size())
            props.Text += m_Messages[i];

        // Add a newline character between the messages (so not after the last one)
        if (i != m_Messages.size() - 1)
            props.Text += L'\n';
    }

    m_TextBox.Render(props);
}
