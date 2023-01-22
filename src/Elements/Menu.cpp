#include "pch.h"
#include "Elements\Menu.h"

#include "Core\Callbacks.h"
#include "Elements\ClickableOption.h"
#include "Elements\RangeOption.h"
#include "UI\Layout.h"

Menu::Menu()
    : m_CurrentOptionGroupIndex(0)
{
}

HRESULT Menu::Init()
{
    HRESULT hr = S_OK;

    // Create the background
    hr = m_Background.Init(Layout::X, Layout::Y, Layout::Width, Layout::Height, Layout::BackgroundColor);
    if (FAILED(hr))
        return hr;

    // Create menu structure

    // First group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(RangeOption, L"Option 1", Callback::Option1Callback, 2.2f, 4.0f, 0.2f));
        options.emplace_back(MakeOption(ClickableOption, L"Option 2", Callback::Option2Callback));
        m_OptionGroups.emplace_back(OptionGroup("cat1", options));
    }

    // Second group
    {
        std::vector<std::shared_ptr<Option>> options;
        options.emplace_back(MakeOption(ClickableOption, L"Option 3", Callback::Option3Callback));
        options.emplace_back(MakeOption(ClickableOption, L"Option 4", Callback::Option4Callback));
        m_OptionGroups.emplace_back(OptionGroup("cat2", options));
    }

    // Set the default option group to be the first one
    m_CurrentOptionGroupIndex = 0;

    return hr;
}

void Menu::Update(ATG::GAMEPAD *pGamepad)
{
    // Allow the user to change the current option group with LB/RB
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
    {
        if (m_CurrentOptionGroupIndex > 0)
            m_CurrentOptionGroupIndex--;
    }
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
    {
        if (m_CurrentOptionGroupIndex < m_OptionGroups.size() - 1)
            m_CurrentOptionGroupIndex++;
    }

    // Update the currently selected option group
    m_OptionGroups[m_CurrentOptionGroupIndex].Update(pGamepad);
}

void Menu::Render()
{
    // Render the background
    m_Background.Render();

    // Render the currently selected option group
    m_OptionGroups[m_CurrentOptionGroupIndex].Render();
}
