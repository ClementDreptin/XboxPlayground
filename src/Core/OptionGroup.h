#pragma once

#include "UI\Rectangle.h"
#include "Options\Option.h"

// Class to represent a menu category.
class OptionGroup
{
public:
    OptionGroup();

    OptionGroup(const std::wstring &name, const std::vector<std::shared_ptr<Option>> &options);

    inline const std::wstring &GetName() const { return m_Name; }

    inline const std::vector<std::shared_ptr<Option>> &GetOptions() const { return m_Options; }

    // Change the currently selected option and update it.
    void Update(ATG::GAMEPAD *pGamepad);

    // Render the options.
    HRESULT Render(float x, float y, float width = 0.0f, float height = 0.0f);

    // Calculate the minimum width required for the option group.
    float GetMinWidth();

    // Calculate the minimum height required for the option group.
    float GetMinHeight();

private:
    std::wstring m_Name;
    std::vector<std::shared_ptr<Option>> m_Options;

    size_t m_CurrentSelectedOptionIndex;

    float m_CachedMinWidth;
    float m_CachedMinHeight;

    Rectangle m_Background;

    // Render the background of the option group.
    HRESULT RenderBackground(float x, float y, float width, float height);
};
