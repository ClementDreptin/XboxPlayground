#include "pch.h"
#include "UI\Rectangle.h"

#include <AtgUtil.h>

#include "Renderer\D3DDevice.h"

VertexShader Rectangle::s_VertexShader;
PixelShader Rectangle::s_PixelShader;
bool Rectangle::s_ShadersInitialized = false;

Rectangle::Rectangle()
    : m_X(0.0f), m_Y(0.0f), m_Width(0.0f), m_Height(0.0f), m_DisplayWidth(0), m_DisplayHeight(0), m_Color(0)
{
}

HRESULT Rectangle::Init(float x, float y, float width, float height, D3DCOLOR color)
{
    HRESULT hr = S_OK;

    // Save the display dimensions
    ATG::GetVideoSettings(&m_DisplayWidth, &m_DisplayHeight);

    // Save the position, dimensions and color
    m_X = x;
    m_Y = y;
    m_Width = width;
    m_Height = height;
    m_Color = color;

    // Set up the matrices for orthographic projection
    m_ViewMatrix = XMMatrixIdentity();
    m_ProjectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(m_DisplayWidth), 0.0f, static_cast<float>(m_DisplayHeight), -1.0f, 1.0f);
    CalculateWorldViewProjectionMatrix();

    // Create the vertices
    // Since the Y axis goes upwards, if we want a height increase to make our
    // rectangle grow downwards along the Y axis, we need to substract its height
    // to the Y coordinate of each vertex.
    Vertex vertices[] = {
        Vertex(0.0f, 0.0f - height, 0.0f),    // Bottom Left
        Vertex(0.0f, height - height, 0.0f),  // Top Left
        Vertex(width, height - height, 0.0f), // Top Right
        Vertex(width, 0.0f - height, 0.0f)    // Bottom Right
    };

    // Create the shaders when the first rectangle is instantiated
    if (!s_ShadersInitialized)
    {
        // Create the vertex shader
        hr = s_VertexShader.Init();
        if (FAILED(hr))
            return hr;

        // Create the pixel shader
        hr = s_PixelShader.Init();
        if (FAILED(hr))
            return hr;

        s_ShadersInitialized = true;
    }

    // Create the vertex buffer
    hr = m_VertexBuffer.Init(vertices, ARRAYSIZE(vertices));
    if (FAILED(hr))
        return hr;

    // Create the indices
    uint16_t indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    // Create an index buffer
    hr = m_IndexBuffer.Init(indices, ARRAYSIZE(indices));
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void Rectangle::Render()
{
    // Initialize default device states
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    g_pd3dDevice->SetVertexDeclaration(m_VertexBuffer.GetVertexDeclaration());
    g_pd3dDevice->SetStreamSource(0, m_VertexBuffer.Get(), 0, sizeof(Vertex));
    g_pd3dDevice->SetVertexShader(s_VertexShader.Get());
    g_pd3dDevice->SetPixelShader(s_PixelShader.Get());
    g_pd3dDevice->SetIndices(m_IndexBuffer.Get());

    // Pass the world view projection matrix to the vertex shader
    g_pd3dDevice->SetVertexShaderConstantF(0, reinterpret_cast<float *>(&m_WVPMatrix), 4);

    // Turn the color into a float array and pass it to the pixel shader
    float color[4] = {
        ((m_Color & 0x00ff0000) >> 16) / 255.0f,
        ((m_Color & 0x0000ff00) >> 8) / 255.0f,
        ((m_Color & 0x000000ff) >> 0) / 255.0f,
        ((m_Color & 0xff000000) >> 24) / 255.0f,
    };

    g_pd3dDevice->SetPixelShaderConstantF(0, color, 1);

    // Draw the rectangle
    g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 0, 0, 2);
}

void Rectangle::CalculateWorldViewProjectionMatrix()
{
    // Direct3D uses an upwards Y axis system which is a bit unintuitive when dealing
    // with 2D rendering, so we flip the Y axis
    m_WorldMatrix = XMMatrixTranslation(static_cast<float>(m_X), static_cast<float>(m_DisplayHeight - m_Y), 0.0f);
    m_WVPMatrix = m_WorldMatrix * m_ViewMatrix * m_ProjectionMatrix;
}
