#pragma once

#include <AtgInput.h>

#include "UI\Rectangle.h"
#include "UI\Text.h"
#include "Elements\OptionGroup.h"

// Class to represent to menu
class Menu
{
public:
    Menu();

    // Create the background and the menu structure.
    HRESULT Init();

    // Listen to user input and allow the user to change the current option group.
    void Update(ATG::GAMEPAD *pGamepad);

    // Render the background and the currently selected option group.
    void Render();

private:
    Rectangle m_Background;

    std::vector<OptionGroup> m_OptionGroups;
    size_t m_CurrentOptionGroupIndex;

    std::vector<Text> m_OptionGroupHeaders;

    // Create the structure of the menu.
    void CreateStructure();

    // Create the background of the menu.
    HRESULT CreateBackground();

    // Update the option group headers according to the currently selected option group.
    HRESULT UpdateOptionGroupHeaders();
};
