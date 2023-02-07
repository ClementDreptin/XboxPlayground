#pragma once

#include <AtgApp.h>
#include <AtgUtil.h>

#include "Core\Menu.h"
#include "UI\Text.h"

class App : public ATG::Application
{
public:
    App();

    virtual HRESULT Initialize();

    virtual HRESULT Update();

    virtual HRESULT Render();

private:
    Menu m_Menu;
    bool m_MenuOpen;

    Text m_ControlsText;

    ATG::Timer m_Timer;
    Text m_FrameRateText;

    HRESULT RenderControlsText();

    HRESULT RenderFrameRateText();
};
