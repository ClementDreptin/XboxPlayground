#include "pch.h"
#include "UI/Rectangle.h"

#include "Renderer/D3DDevice.h"

extern float g_DisplayWidth;
extern float g_DisplayHeight;

bool Rectangle::s_ShadersInitialized = false;
D3DVertexShader *Rectangle::s_pVertexShader = nullptr;
D3DPixelShader *Rectangle::s_pPixelShader = nullptr;

Rectangle::Rectangle()
    : m_IsInitialized(false)
{
}

void Rectangle::Render(const Props &props)
{
    // Check if the world view projection matrix and/or the vertex buffer need to be updated
    bool needToUpdateWorldViewProjectionMatrix = m_Props.X != props.X || m_Props.Y != props.Y;
    bool needToUpdateVertexBuffer = m_Props.Width != props.Width || m_Props.Height != props.Height;
    bool hasBorder = props.BorderPosition != Border::Border_None && props.BorderWidth > 0;

    m_Props = props;

    // If this is the first time Render is called, just initialize the rectangle and return
    if (!m_IsInitialized)
    {
        Init();
        return;
    }

    // Perform the updates if needed
    if (needToUpdateWorldViewProjectionMatrix)
        CalculateWorldViewProjectionMatrix();

    if (needToUpdateVertexBuffer)
        UpdateVertexBuffer();

    // Initialize default device states
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    g_pd3dDevice->SetVertexDeclaration(m_VertexBuffer.GetVertexDeclaration());
    g_pd3dDevice->SetStreamSource(0, &m_VertexBuffer, 0, sizeof(Vertex));
    g_pd3dDevice->SetVertexShader(s_pVertexShader);
    g_pd3dDevice->SetPixelShader(s_pPixelShader);

    // Pass the world view projection matrix to the vertex shader
    g_pd3dDevice->SetVertexShaderConstantF(0, reinterpret_cast<float *>(&m_WVPMatrix), 4);

    // Turn the color into a float array and pass it to the pixel shader
    float color[4] = {
        ((m_Props.Color & 0x00ff0000) >> 16) / 255.0f,
        ((m_Props.Color & 0x0000ff00) >> 8) / 255.0f,
        ((m_Props.Color & 0x000000ff) >> 0) / 255.0f,
        ((m_Props.Color & 0xff000000) >> 24) / 255.0f,
    };

    g_pd3dDevice->SetPixelShaderConstantF(0, color, 1);

    // Draw the rectangle
    g_pd3dDevice->DrawPrimitive(D3DPT_QUADLIST, 0, 1);

    // Render the border if needed
    if (hasBorder)
    {
        Border::Props props = { 0 };
        props.X = m_Props.X;
        props.Y = m_Props.Y;
        props.Thickness = m_Props.BorderWidth;
        props.Color = m_Props.BorderColor;
        props.Position = m_Props.BorderPosition;
        props.Width = m_Props.Width;
        props.Height = m_Props.Height;

        m_Border.Render(props);
    }
}

#define VERTICES \
    { \
        Vertex(0.0f, 0.0f - m_Props.Height, 0.0f),                        /* Bottom Left */ \
            Vertex(0.0f, m_Props.Height - m_Props.Height, 0.0f),          /* Top Left */ \
            Vertex(m_Props.Width, m_Props.Height - m_Props.Height, 0.0f), /* Top Right */ \
            Vertex(m_Props.Width, 0.0f - m_Props.Height, 0.0f),           /* Bottom Right */ \
    }

HRESULT Rectangle::Init()
{
    HRESULT hr = S_OK;

    // Set up the matrices for orthographic projection
    m_ViewMatrix = XMMatrixIdentity();
    m_ProjectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, g_DisplayWidth, 0.0f, g_DisplayHeight, -1.0f, 1.0f);
    CalculateWorldViewProjectionMatrix();

    // Create the shaders when the first rectangle is instantiated
    if (!s_ShadersInitialized)
    {
        hr = InitShaders();
        if (FAILED(hr))
            return hr;
    }

    // Create the vertex buffer
    Vertex vertices[] = VERTICES;
    hr = m_VertexBuffer.Init(vertices, ARRAYSIZE(vertices));
    if (FAILED(hr))
        return hr;

    m_IsInitialized = true;

    return hr;
}

HRESULT Rectangle::InitShaders()
{
    HRESULT hr = S_OK;

    hr = ATG::LoadVertexShader("game:\\Media\\Shaders\\Rectangle.xvu", &s_pVertexShader);
    if (FAILED(hr))
    {
        Log::Error("Couldn't load vertex shader");
        return hr;
    }

    hr = ATG::LoadPixelShader("game:\\Media\\Shaders\\Rectangle.xpu", &s_pPixelShader);
    if (FAILED(hr))
    {
        Log::Error("Couldn't load pixel shader");
        return hr;
    }

    s_ShadersInitialized = true;

    return hr;
}

void Rectangle::CalculateWorldViewProjectionMatrix()
{
    m_WorldMatrix = XMMatrixTranslation(m_Props.X, g_DisplayHeight - m_Props.Y, 0.0f);
    m_WVPMatrix = m_WorldMatrix * m_ViewMatrix * m_ProjectionMatrix;
}

void Rectangle::UpdateVertexBuffer()
{
    Vertex vertices[] = VERTICES;
    m_VertexBuffer.UpdateBuffer(vertices, ARRAYSIZE(vertices));
}
