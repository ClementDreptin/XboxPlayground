#include "pch.h"
#include "App.h"

#include <AtgUtil.h>
#include <AtgInput.h>


//--------------------------------------------------------------------------------------
// Name: Initialize()
// Desc: Initialize app-dependent objects
//--------------------------------------------------------------------------------------
HRESULT App::Initialize()
{
    // Result of operations
    HRESULT hr;

    // Create the font
    hr = m_Font.Create("game:\\Media\\Fonts\\Arial_20.xpr");
    if (FAILED(hr))
    {
        Log::Error("Couldn't create font");
        return hr;
    }

    // Set the default font color to white
    m_dwFontColor = D3DCOLOR_XRGB(255, 255, 255);

    // Get the width and height for the font
    ATG::GetVideoSettings(&m_uiWidth, &m_uiHeight);

    // Create the vertices
    FLOAT left = (FLOAT)m_uiWidth / 4.0f;
    FLOAT right = 3.0f * ((FLOAT)m_uiWidth / 4.0f);
    FLOAT bottom = (FLOAT)m_uiHeight / 4.0f;
    FLOAT top = 3.0f * ((FLOAT)m_uiHeight / 4.0f);

    Vertex vertices[] =
    {
        Vertex( left,  bottom, 0.0f ), // Bottom Left
        Vertex( left,  top,    0.0f ), // Top Left
        Vertex( right, top,    0.0f ), // Top Right
        Vertex( right, bottom, 0.0f )  // Bottom Right
    };

    // Create the vertex buffer
    hr = m_VertexBuffer.Init(m_pd3dDevice, vertices, ARRAYSIZE(vertices));
    if (FAILED(hr))
        return hr;

    // Create the indices
    WORD indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    // Create an index buffer
    hr = m_IndexBuffer.Init(m_pd3dDevice, indices, ARRAYSIZE(indices));
    if (FAILED(hr))
        return hr;

    // Create the vertex shader
    hr = m_VertexShader.Init(m_pd3dDevice);
    if (FAILED(hr))
        return hr;

    // Create the pixel shader
    hr = m_PixelShader.Init(m_pd3dDevice);
    if (FAILED(hr))
        return hr;

    // Create the rectangle
    hr = m_Rectangle.Init(m_pd3dDevice, 100.0f, 100.0f, 200.0f, 200.0f, D3DCOLOR_XRGB(255, 255, 0));
    if (FAILED(hr))
        return hr;

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Name: Update()
// Desc: Called once per frame, the call is the entry point for animating the scene.
//--------------------------------------------------------------------------------------
HRESULT App::Update()
{
    // Get the current gamepad state
    ATG::GAMEPAD* pGamepad = ATG::Input::GetMergedInput();

    // Allow the user to change the font color,
    // the font color is set to the button's color
    if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_A)
        m_dwFontColor = D3DCOLOR_XRGB(0, 255, 0);
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_X)
        m_dwFontColor = D3DCOLOR_XRGB(0, 0, 255);
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_Y)
        m_dwFontColor = D3DCOLOR_XRGB(255, 255, 0);
    else if (pGamepad->wPressedButtons & XINPUT_GAMEPAD_B)
        m_dwFontColor = D3DCOLOR_XRGB(255, 0, 0);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Name: Render()
// Desc: Called once per frame, the call is the entry point for 3D rendering. This 
//       function sets up render states, clears the viewport, and renders the scene.
//--------------------------------------------------------------------------------------
HRESULT App::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Initialize default device states at the start of the frame
    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

    m_pd3dDevice->SetVertexDeclaration(m_VertexBuffer.GetVertexDeclaration());
    m_pd3dDevice->SetStreamSource(0, m_VertexBuffer.Get(), 0, sizeof(Vertex));
    m_pd3dDevice->SetVertexShader(m_VertexShader.Get());
    m_pd3dDevice->SetPixelShader(m_PixelShader.Get());
    m_pd3dDevice->SetIndices(m_IndexBuffer.Get());

    // Create the world-projection matrix and pass it to the vertex shader
    XMMATRIX matWorld = XMMatrixTranslation((FLOAT)m_uiWidth / 4.0f, 0.0f, 0.0f);
    XMMATRIX matProj = XMMatrixOrthographicOffCenterLH(0.0f, (FLOAT)m_uiWidth, 0.0f, (FLOAT)m_uiHeight, -1.0f, 1.0f);
    XMMATRIX matWP = matWorld * matProj;
    m_pd3dDevice->SetVertexShaderConstantF(0, (PFLOAT)&matWP, 4);

    // Create a color and pass it to the pixel shader
    FLOAT vColor[4];
    vColor[0] = 1.0f;
    vColor[1] = 0.0f;
    vColor[2] = 1.0f;
    vColor[3] = 1.0f;
    m_pd3dDevice->SetPixelShaderConstantF(0, vColor, 1);

    // Draw the rectangle
    m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 0, 0, 2);

    // Draw the rectangle
    m_Rectangle.Draw();

    // Set the text
    static LPCWSTR wszText = L"Press A, X, Y or B to change my color!";

    // Calculate the text position
    static FLOAT fTextWidth = m_Font.GetTextWidth(wszText);
    static FLOAT fTextX = (FLOAT)(m_uiWidth - fTextWidth) / 2.0f;
    static FLOAT fTextY = (FLOAT)(m_uiHeight - m_Font.GetFontHeight()) / 2.0f;

    // Draw the text
    m_Font.Begin();
    m_Font.DrawText(fTextX, fTextY, m_dwFontColor, wszText);
    m_Font.End();

    // Present the scene
    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

    return S_OK;
}
