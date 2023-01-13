#include "pch.h"
#include "Elements\OptionGroup.h"

#include <AtgDevice.h>

OptionGroup::OptionGroup(const std::string &name, const std::vector<Option> &options)
    : m_Name(name), m_Options(options)
{
}

void OptionGroup::Update(ATG::GAMEPAD *pGamepad)
{
    for (size_t i = 0; i < m_Options.size(); i++)
        m_Options[i].Update(pGamepad);
}

void OptionGroup::Render()
{
    for (size_t i = 0; i < m_Options.size(); i++)
        m_Options[i].Render(100.0f, 100.0f + i * 50.0f);
}
