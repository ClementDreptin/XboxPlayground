#pragma once

#include "Core/Input.h"
#include "Options/OptionGroup.h"
#include "UI/Rectangle.h"
#include "UI/Text.h"

class Menu
{
public:
    Menu();

    void Init(const std::vector<OptionGroup> &optionGroups);

    void Update(Input::Gamepad *pGamepad);

    HRESULT Render();

private:
    std::vector<OptionGroup> m_OptionGroups;
    size_t m_CurrentOptionGroupIndex;

    std::vector<Text> m_OptionGroupHeaders;

    void AddCustomizationGroup();

    float GetOptionGroupHeadersHeight() const;

    HRESULT RenderOptionGroupHeaders();

    void CalculateMenuDimensions();
};
