#include "pch.h"
#include "UI\Rectangle.h"

#include <AtgUtil.h>

HRESULT Rectangle::Init(D3DDevice *pDevice, float x, float y, float width, float height, D3DCOLOR color)
{
    HRESULT hr = S_OK;

    // Save the display dimensions
    ATG::GetVideoSettings(&m_Width, &m_Height);

    // Save the position
    m_X = x;
    m_Y = y;

    // Save the color and the device
    m_Color = color;
    m_pDevice = pDevice;

    // Set up the matrices for orthographic projection
    m_ViewMatrix = XMMatrixIdentity();
    m_ProjectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(m_Width), 0.0f, static_cast<float>(m_Height), -1.0f, 1.0f);
    CalculateWorldViewProjectionMatrix();

    // Create the vertices
    // Since the Y axis goes upwards, if we want a height increase to make our
    // rectangle grow downwards along the Y axis, we need to substract its height
    // to the Y coordinate of each vertex.
    Vertex vertices[] = {
        Vertex(0.0f, 0.0f - height, 0.0f),     // Bottom Left
        Vertex(0.0f, height - height, 0.0f),   // Top Left
        Vertex(width, height - height, 0.0f),  // Top Right
        Vertex(width, 0.0f - height, 0.0f)     // Bottom Right
    };

    // Create the vertex buffer
    hr = m_VertexBuffer.Init(pDevice, vertices, ARRAYSIZE(vertices));
    if (FAILED(hr))
        return hr;

    // Create the indices
    uint16_t indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    // Create an index buffer
    hr = m_IndexBuffer.Init(pDevice, indices, ARRAYSIZE(indices));
    if (FAILED(hr))
        return hr;

    // Create the vertex shader
    hr = m_VertexShader.Init(pDevice);
    if (FAILED(hr))
        return hr;

    // Create the pixel shader
    hr = m_PixelShader.Init(pDevice);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void Rectangle::Render()
{
    // Initialize default device states
    m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    m_pDevice->SetVertexDeclaration(m_VertexBuffer.GetVertexDeclaration());
    m_pDevice->SetStreamSource(0, m_VertexBuffer.Get(), 0, sizeof(Vertex));
    m_pDevice->SetVertexShader(m_VertexShader.Get());
    m_pDevice->SetPixelShader(m_PixelShader.Get());
    m_pDevice->SetIndices(m_IndexBuffer.Get());

    // Pass the world view projection matrix to the vertex shader
    m_pDevice->SetVertexShaderConstantF(0, reinterpret_cast<float *>(&m_WVPMatrix), 4);

    // Turn the color into a float array and pass it to the pixel shader
    float color[4] = {
        ((m_Color & 0x00ff0000) >> 16) / 255.0f,
        ((m_Color & 0x0000ff00) >> 8) / 255.0f,
        ((m_Color & 0x000000ff) >> 0) / 255.0f,
        ((m_Color & 0xff000000) >> 24) / 255.0f,
    };

    m_pDevice->SetPixelShaderConstantF(0, color, 1);

    // Draw the rectangle
    m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 0, 0, 2);
}

void Rectangle::CalculateWorldViewProjectionMatrix()
{
    // Direct3D uses an upwards Y axis system which is a bit unintuitive when dealing
    // with 2D rendering, so we flip the Y axis
    m_WorldMatrix = XMMatrixTranslation(static_cast<float>(m_X), static_cast<float>(m_Height - m_Y), 0.0f);
    m_WVPMatrix = m_WorldMatrix * m_ViewMatrix * m_ProjectionMatrix;
}
