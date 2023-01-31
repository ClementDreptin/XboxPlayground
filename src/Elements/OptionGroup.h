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

    const std::wstring &GetName() const { return m_Name; }

    const std::vector<std::shared_ptr<Option>> &GetOptions() const { return m_Options; }

    // Change the currently selected option and update it.
    void Update(ATG::GAMEPAD *pGamepad);

    // Render the scroller and the options.
    void Render();

private:
    std::wstring m_Name;
    std::vector<std::shared_ptr<Option>> m_Options;

    Rectangle m_Scroller;
    size_t m_CurrentScrollerPos;

    float m_LineHeight;

    // Update the poition of the scroller according to the m_CurrentScrollerPos index.
    void MoveScroller();
};
