#include "pch.h"
#include "App.h"

#include <AtgUtil.h>
#include <AtgInput.h>


//--------------------------------------------------------------------------------------
// Name: struct Vertex
// Desc: Struct to describe a vertex
//--------------------------------------------------------------------------------------
struct Vertex
{
    Vertex() {}
    Vertex(float x, float y, float z, D3DCOLOR color, float u, float v)
        : Pos(x, y, z), Color(color), TexCoord(u, v) {}

    XMFLOAT3 Pos;
    D3DCOLOR Color;
    XMFLOAT2 TexCoord;
};


//--------------------------------------------------------------------------------------
// Name: Initialize()
// Desc: Initialize app-dependent objects
//--------------------------------------------------------------------------------------
HRESULT App::Initialize()
{
    // Result of operations
    HRESULT hr;

    // Create the font
    hr = m_Font.Create("game:\\Media\\Fonts\\Consolas_16.xpr");
    if (FAILED(hr))
    {
        Log::Error("Couldn't create font");
        return hr;
    }

    // Set the default font color to white
    m_dwFontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

    // Get the width and height for the font
    ATG::GetVideoSettings(&m_uiWidth, &m_uiHeight);

    // Create the textures resource
    hr = m_Textures.Create("game:\\Media\\Textures\\Textures.xpr");
    if (FAILED(hr))
    {
        Log::Error("Couldn't create textures");
        return hr;
    }

    // Initialize the background
    hr = InitBackground();
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

    // Render the background
    m_pd3dDevice->SetTexture(0, m_pBackgroundTexture);
    m_pd3dDevice->SetVertexDeclaration(m_pBackgroundVertexDeclaration);
    m_pd3dDevice->SetStreamSource(0, m_pBackgroundVertexBuffer, 0, sizeof(Vertex));
    m_pd3dDevice->SetVertexShader(m_pBackgroundVertexShader);
    m_pd3dDevice->SetPixelShader(m_pBackgroundPixelShader);
    m_pd3dDevice->SetIndices(m_pBackgroundIndexBuffer);
    m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pBackgroundIndexBuffer->Size / sizeof(DWORD), 0, 2);

    // Set the text
    LPCWSTR wszText = L"Press A, X, Y or B to change my color!";

    // Calculate the text position
    FLOAT fTextWidth = m_Font.GetTextWidth(wszText);
    FLOAT fTextX = (FLOAT)(m_uiWidth - fTextWidth) / 2.0f;
    FLOAT fTextY = (FLOAT)(m_uiHeight - m_Font.GetFontHeight()) / 2.0f;

    // Draw the text
    m_Font.Begin();
    m_Font.DrawText(fTextX, fTextY, m_dwFontColor, wszText);
    m_Font.End();

    // Present the scene
    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Name: InitBackground()
// Desc: Create the vertices, vertex buffer/declaration and shaders relative to
//       the background.
//--------------------------------------------------------------------------------------
HRESULT App::InitBackground()
{
    HRESULT hr;

    // Get the texture from the bundled resources
    m_pBackgroundTexture = m_Textures.GetTexture("BackgroundTexture");

    // Create the vertices
    Vertex vertices[] =
    {
        Vertex(-1.0f, -1.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 0.0f, 1.0f ), // Bottom Left
        Vertex(-1.0f,  1.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 0.0f, 0.0f ), // Top Left
        Vertex( 1.0f,  1.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0.0f ), // Top Right
        Vertex( 1.0f, -1.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 1.0f )  // Bottom Right
    };

    // Create the vertex buffer
    hr = m_pd3dDevice->CreateVertexBuffer(sizeof(vertices), D3DUSAGE_WRITEONLY, NULL, D3DPOOL_DEFAULT, &m_pBackgroundVertexBuffer, nullptr);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the background vertex buffer");
        return hr;
    }

    // Copy the vertices into the vertex buffer
    VOID* pVertices;

    hr = m_pBackgroundVertexBuffer->Lock(0, sizeof(vertices), (VOID**)&pVertices, NULL);
    if (FAILED(hr))
    {
        Log::Error("Couldn't lock the background vertex buffer");
        return hr;
    }

    memcpy(pVertices, vertices, sizeof(vertices));
    m_pBackgroundVertexBuffer->Unlock();

    // Define the vertex elements
    D3DVERTEXELEMENT9 vertexElements[] =
    {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        { 0, sizeof(XMFLOAT3), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
        { 0, sizeof(XMFLOAT3) + sizeof(D3DCOLOR), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
        D3DDECL_END()
    };
    
    // Create a vertex declaration from the element descriptions
    hr = m_pd3dDevice->CreateVertexDeclaration(vertexElements, &m_pBackgroundVertexDeclaration);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the background vertex declaration");
        return hr;
    }

    // Create the indices
    DWORD indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    // Create an index buffer
    hr = m_pd3dDevice->CreateIndexBuffer(sizeof(indices), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, NULL, &m_pBackgroundIndexBuffer, NULL);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the background index buffer");
        return hr;
    }

    // Copy the vertices into the vertex buffer
    VOID* pIndices;

    hr = m_pBackgroundIndexBuffer->Lock(0, sizeof(indices), (VOID**)&pIndices, NULL);
    if (FAILED(hr))
    {
        Log::Error("Couldn't lock the background index buffer");
        return hr;
    }

    memcpy(pIndices, indices, sizeof(indices));
    m_pBackgroundIndexBuffer->Unlock();

    // Create the vertex shader
    hr = ATG::LoadVertexShader("game:\\Media\\Shaders\\Background.xvu", &m_pBackgroundVertexShader);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the background vertex shader");
        return hr;
    }

    // Create the pixel shader
    hr = ATG::LoadPixelShader("game:\\Media\\Shaders\\Background.xpu", &m_pBackgroundPixelShader);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the background pixel shader");
        return hr;
    }

    return S_OK;
}
