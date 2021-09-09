#pragma once

#include <AtgApp.h>
#include <AtgFont.h>
#include <AtgUtil.h>

#include "Elements\Rectangle.h"
#include "Elements\Option.h"


//--------------------------------------------------------------------------------------
// Name: class App
// Desc: Main class to run this application. Most functionality is inherited
//       from the ATG::Application base class.
//--------------------------------------------------------------------------------------
class App : public ATG::Application
{
public:
    virtual HRESULT Initialize();
    virtual HRESULT Update();
    virtual HRESULT Render();
private:
    UINT m_uiWidth;
    UINT m_uiHeight;

    Rectangle m_Rectangle;
    Rectangle m_Scroller;
    INT m_iCurrentScrollerPos;

    std::vector<Option> m_Options;

    VOID MoveScroller();
};
