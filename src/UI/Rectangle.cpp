#include "pch.h"
#include "UI\Rectangle.h"

#include "Renderer\D3DDevice.h"

extern float g_DisplayWidth;
extern float g_DisplayHeight;

VertexShader Rectangle::s_VertexShader;
PixelShader Rectangle::s_PixelShader;
bool Rectangle::s_ShadersInitialized = false;

Rectangle::Rectangle()
    : m_Props(), m_HasBorder(false), m_IsInitialized(false)
{
}

HRESULT Rectangle::SetProps(const Props &props)
{
    HRESULT hr = S_OK;

    // Check if the world view project matrix and/or the vertex buffer need to be updated
    bool needToUpdateWorldViewProjectionMatrix = m_Props.X != props.X || m_Props.Y != props.Y;
    bool needToUpdateVertexBuffer = m_Props.Width != props.Width || m_Props.Height != props.Height;

    m_Props = props;
    m_HasBorder = m_Props.BorderPosition != Border::Border_None && m_Props.BorderWidth > 0;

    // If this is the first time SetProps is called, just initialize the rectangle and return
    if (!m_IsInitialized)
        return Init();

    // Update the border
    hr = SetBorder();
    if (FAILED(hr))
        return hr;

    // Perform the updates if needed
    if (needToUpdateWorldViewProjectionMatrix)
        CalculateWorldViewProjectionMatrix();

    if (needToUpdateVertexBuffer)
        hr = UpdateVertexBuffer();

    return hr;
}

void Rectangle::Render()
{
    // Initialize default device states
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    g_pd3dDevice->SetVertexDeclaration(m_VertexBuffer.GetVertexDeclaration());
    g_pd3dDevice->SetStreamSource(0, &m_VertexBuffer, 0, sizeof(Vertex));
    g_pd3dDevice->SetVertexShader(&s_VertexShader);
    g_pd3dDevice->SetPixelShader(&s_PixelShader);
    g_pd3dDevice->SetIndices(&m_IndexBuffer);

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
    g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 0, 0, 2);

    // Render the border if needed
    if (m_HasBorder)
        m_Border.Render();
}

HRESULT Rectangle::Init()
{
    HRESULT hr = S_OK;

    // Set up the matrices for orthographic projection
    m_ViewMatrix = XMMatrixIdentity();
    m_ProjectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, g_DisplayWidth, 0.0f, g_DisplayHeight, -1.0f, 1.0f);
    CalculateWorldViewProjectionMatrix();

    // Create the vertices
    // Since the Y axis goes upwards, if we want a height increase to make our
    // rectangle grow downwards along the Y axis, we need to substract its height
    // to the Y coordinate of each vertex.
    Vertex vertices[] = {
        Vertex(0.0f, 0.0f - m_Props.Height, 0.0f),                    // Bottom Left
        Vertex(0.0f, m_Props.Height - m_Props.Height, 0.0f),          // Top Left
        Vertex(m_Props.Width, m_Props.Height - m_Props.Height, 0.0f), // Top Right
        Vertex(m_Props.Width, 0.0f - m_Props.Height, 0.0f)            // Bottom Right
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

    // Initialize the border
    hr = SetBorder();
    if (FAILED(hr))
        return hr;

    m_IsInitialized = true;

    return hr;
}

HRESULT Rectangle::SetBorder()
{
    Border::Props borderProps = { 0 };
    borderProps.X = m_Props.X;
    borderProps.Y = m_Props.Y;
    borderProps.Thickness = m_Props.BorderWidth;
    borderProps.Color = m_Props.BorderColor;
    borderProps.Position = m_Props.BorderPosition;
    borderProps.Width = m_Props.Width;
    borderProps.Height = m_Props.Height;

    return m_Border.SetProps(borderProps);
}

void Rectangle::CalculateWorldViewProjectionMatrix()
{
    // Direct3D uses an upwards Y axis system which is a bit unintuitive when dealing
    // with 2D rendering, so we flip the Y axis
    m_WorldMatrix = XMMatrixTranslation(m_Props.X, g_DisplayHeight - m_Props.Y, 0.0f);
    m_WVPMatrix = m_WorldMatrix * m_ViewMatrix * m_ProjectionMatrix;
}

HRESULT Rectangle::UpdateVertexBuffer()
{
    // Create the vertices
    // Since the Y axis goes upwards, if we want a height increase to make our
    // rectangle grow downwards along the Y axis, we need to substract its height
    // to the Y coordinate of each vertex.
    Vertex vertices[] = {
        Vertex(0.0f, 0.0f - m_Props.Height, 0.0f),                    // Bottom Left
        Vertex(0.0f, m_Props.Height - m_Props.Height, 0.0f),          // Top Left
        Vertex(m_Props.Width, m_Props.Height - m_Props.Height, 0.0f), // Top Right
        Vertex(m_Props.Width, 0.0f - m_Props.Height, 0.0f)            // Bottom Right
    };

    // Send the new vertices to the vertex buffer
    return m_VertexBuffer.UpdateBuffer(vertices, ARRAYSIZE(vertices));
}
