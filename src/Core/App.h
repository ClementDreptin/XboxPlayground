#pragma once

#include <AtgApp.h>
#include <AtgFont.h>
#include <AtgUtil.h>

#include "Elements\Rectangle.h"
#include "Elements\Option.h"

// Main class to run this application. Most functionality is inherited
// from the ATG::Application base class.
class App : public ATG::Application
{
public:
    // Initialize app-dependent objects.
    virtual HRESULT Initialize();

    // Called once per frame, the call is the entry point for animating the scene.
    virtual HRESULT Update();

    // Called once per frame, the call is the entry point for 3D rendering. This
    // function sets up render states, clears the viewport, and renders the scene.
    virtual HRESULT Render();

private:
    uint32_t m_uiWidth;
    uint32_t m_uiHeight;

    Rectangle m_Rectangle;
    Rectangle m_Scroller;
    int m_iCurrentScrollerPos;

    std::vector<Option> m_Options;

    // Update the poition of the scroller according to the m_iCurrentScrollerPos index.
    void MoveScroller();
};
