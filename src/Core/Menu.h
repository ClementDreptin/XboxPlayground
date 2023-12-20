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

    void Render();

private:
    std::vector<OptionGroup> m_OptionGroups;
    size_t m_CurrentOptionGroupIndex;

    std::vector<Text> m_OptionGroupHeaders;

    mutable float m_CachedOptionGroupHeadersHeight;

    void AddCustomizationGroup();

    float GetOptionGroupHeadersHeight() const;

    void RenderOptionGroupHeaders();

    void CalculateMenuDimensions();
};
