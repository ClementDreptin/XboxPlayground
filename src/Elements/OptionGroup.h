#pragma once

#include <AtgInput.h>

#include "UI\Rectangle.h"
#include "Elements\Option.h"

class OptionGroup
{
public:
    OptionGroup() {}

    OptionGroup(const std::string &name, const std::vector<Option> &options);

    const std::string &GetName() const { return m_Name; }

    const std::vector<Option> &GetOptions() const { return m_Options; }

    void Update(ATG::GAMEPAD *pGamepad);

    void Render();

private:
    std::string m_Name;
    std::vector<Option> m_Options;
};
