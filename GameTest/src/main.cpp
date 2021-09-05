#include "pch.h"

#include <AtgUtil.h>

#include "Core\App.h"


//-------------------------------------------------------------------------------------
// Name: main()
// Desc: The application's entry point
//-------------------------------------------------------------------------------------
void __cdecl main()
{
    App app;
    ATG::GetVideoSettings(&app.m_d3dpp.BackBufferWidth, &app.m_d3dpp.BackBufferHeight);

    // Make sure display is gamma correct.
    app.m_d3dpp.BackBufferFormat = (D3DFORMAT)MAKESRGBFMT(D3DFMT_A8R8G8B8);
    app.m_d3dpp.FrontBufferFormat = (D3DFORMAT)MAKESRGBFMT(D3DFMT_LE_X8R8G8B8);

    app.Run();
}
