#pragma once

#include <AtgApp.h>
#include <AtgUtil.h>

#include "Core\Menu.h"
#include "UI\Text.h"

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
    Menu m_Menu;
    bool m_MenuOpen;

    Text m_ControlsText;

    ATG::Timer m_Timer;
    Text m_FrameRateText;

    // Render the controls text.
    HRESULT RenderControlsText();

    // Render the frame rate text.
    HRESULT RenderFrameRateText();
};
