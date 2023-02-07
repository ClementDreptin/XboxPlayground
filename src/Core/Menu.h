#pragma once

#include <AtgInput.h>

#include "UI/Rectangle.h"
#include "UI/Text.h"
#include "Core/OptionGroup.h"

class Menu
{
public:
    Menu();

    void Init();

    void Update(ATG::GAMEPAD *pGamepad);

    HRESULT Render();

private:
    std::vector<OptionGroup> m_OptionGroups;
    size_t m_CurrentOptionGroupIndex;

    std::vector<Text> m_OptionGroupHeaders;

    void CreateStructure();

    HRESULT RenderOptionGroupHeaders();

    void CalculateMenuDimensions();
};
