#pragma once

#include <AtgApp.h>

#include "UI\Rectangle.h"
#include "Elements\OptionGroup.h"

// Main class to run this application. Most functionality is inherited
// from the ATG::Application base class.
class App : public ATG::Application
{
public:
    App();

    // Initialize app-dependent objects.
    virtual HRESULT Initialize();

    // Called once per frame, the call is the entry point for animating the scene.
    virtual HRESULT Update();

    // Called once per frame, the call is the entry point for 3D rendering. This
    // function sets up render states, clears the viewport, and renders the scene.
    virtual HRESULT Render();

private:
    Rectangle m_Background;

    std::vector<OptionGroup> m_OptionGroups;
    size_t m_CurrentOptionGroupIndex;
};
