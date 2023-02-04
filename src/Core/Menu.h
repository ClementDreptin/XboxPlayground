#pragma once

#include <AtgInput.h>

#include "UI\Rectangle.h"
#include "UI\Text.h"
#include "Core\OptionGroup.h"

// Class to represent to menu
class Menu
{
public:
    Menu();

    // Create the menu structure.
    HRESULT Init();

    // Listen to user input and allow the user to change the current option group.
    void Update(ATG::GAMEPAD *pGamepad);

    // Render the background, the option group headers and the currently selected option group.
    HRESULT Render();

private:
    std::vector<OptionGroup> m_OptionGroups;
    size_t m_CurrentOptionGroupIndex;

    std::vector<Text> m_OptionGroupHeaders;

    // Create the structure of the menu.
    void CreateStructure();

    // Render the option group headers.
    HRESULT RenderOptionGroupHeaders();

    // Calculate the menu dimensions from its structure.
    void CalculateMenuDimensions();
};