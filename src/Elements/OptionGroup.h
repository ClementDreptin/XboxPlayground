#pragma once

#include <AtgInput.h>

#include "UI\Rectangle.h"
#include "Elements\Option.h"

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
    HRESULT Render(float x, float y);

    // Calculate the minimum width required for the option group.
    float GetMinWidth();

    // Calculate the minimum height required for the option group.
    float GetMinHeight();

private:
    std::wstring m_Name;
    std::vector<std::shared_ptr<Option>> m_Options;

    size_t m_CurrentSelectedOptionIndex;
};
