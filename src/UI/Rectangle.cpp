#include "pch.h"
#include "UI\Rectangle.h"

#include <AtgUtil.h>

#include "Renderer\D3DDevice.h"

VertexShader Rectangle::s_VertexShader;
PixelShader Rectangle::s_PixelShader;
bool Rectangle::s_ShadersInitialized = false;

Rectangle::Rectangle()
    : m_Props(), m_DisplayWidth(0.0f), m_DisplayHeight(0.0f)
{
}

HRESULT Rectangle::Init(const Props &props)
{
    HRESULT hr = S_OK;

    // Get the display dimensions
    uint32_t displayWidth = 0;
    uint32_t displayHeight = 0;
    ATG::GetVideoSettings(&displayWidth, &displayHeight);

    // Set the members
    m_Props = props;
    m_DisplayWidth = static_cast<float>(displayWidth);
    m_DisplayHeight = static_cast<float>(displayHeight);

    // Set up the matrices for orthographic projection
    m_ViewMatrix = XMMatrixIdentity();
    m_ProjectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, m_DisplayWidth, 0.0f, m_DisplayHeight, -1.0f, 1.0f);
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

    // Create the borders if needed
    if (m_Props.Border != Border_None && m_Props.BorderWidth > 0)
    {
        if (m_Props.Border & Border_Left)
        {
            Line::Props leftBorderProps = { 0 };
            leftBorderProps.X = m_Props.X - m_Props.BorderWidth;
            leftBorderProps.Y = m_Props.Y;
            leftBorderProps.Width = m_Props.BorderWidth;
            leftBorderProps.Height = m_Props.Height + (m_Props.Border & Border_Bottom ? m_Props.BorderWidth : 0.0f);
            leftBorderProps.Color = m_Props.BorderColor;
            hr = m_LeftBorder.Init(leftBorderProps);
            if (FAILED(hr))
                return hr;
        }

        if (m_Props.Border & Border_Right)
        {
            Line::Props rightBorderProps = { 0 };
            rightBorderProps.X = m_Props.X + m_Props.Width;
            rightBorderProps.Y = m_Props.Y - (m_Props.Border & Border_Top ? m_Props.BorderWidth : 0.0f);
            rightBorderProps.Width = m_Props.BorderWidth;
            rightBorderProps.Height = m_Props.Height + (m_Props.Border & Border_Top ? m_Props.BorderWidth : 0.0f);
            rightBorderProps.Color = m_Props.BorderColor;
            hr = m_RightBorder.Init(rightBorderProps);
            if (FAILED(hr))
                return hr;
        }

        if (m_Props.Border & Border_Top)
        {
            Line::Props topBorderProps = { 0 };
            topBorderProps.X = m_Props.X - (m_Props.Border & Border_Left ? m_Props.BorderWidth : 0.0f);
            topBorderProps.Y = m_Props.Y - m_Props.BorderWidth;
            topBorderProps.Width = m_Props.Width + (m_Props.Border & Border_Left ? m_Props.BorderWidth : 0.0f);
            topBorderProps.Height = m_Props.BorderWidth;
            topBorderProps.Color = m_Props.BorderColor;
            hr = m_TopBorder.Init(topBorderProps);
            if (FAILED(hr))
                return hr;
        }

        if (m_Props.Border & Border_Bottom)
        {
            Line::Props bottomBorderProps = { 0 };
            bottomBorderProps.X = m_Props.X;
            bottomBorderProps.Y = m_Props.Y + m_Props.Height;
            bottomBorderProps.Width = m_Props.Width + (m_Props.Border & Border_Right ? m_Props.BorderWidth : 0.0f);
            bottomBorderProps.Height = m_Props.BorderWidth;
            bottomBorderProps.Color = m_Props.BorderColor;
            hr = m_BottomBorder.Init(bottomBorderProps);
            if (FAILED(hr))
                return hr;
        }
    }

    return hr;
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
        ((m_Props.Color & 0x00ff0000) >> 16) / 255.0f,
        ((m_Props.Color & 0x0000ff00) >> 8) / 255.0f,
        ((m_Props.Color & 0x000000ff) >> 0) / 255.0f,
        ((m_Props.Color & 0xff000000) >> 24) / 255.0f,
    };

    g_pd3dDevice->SetPixelShaderConstantF(0, color, 1);

    // Draw the rectangle
    g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 0, 0, 2);

    // Draw the borders if needed
    if (m_Props.Border != Border_None && m_Props.BorderWidth > 0)
    {
        if (m_Props.Border & Border_Left)
            m_LeftBorder.Render();

        if (m_Props.Border & Border_Right)
            m_RightBorder.Render();

        if (m_Props.Border & Border_Top)
            m_TopBorder.Render();

        if (m_Props.Border & Border_Bottom)
            m_BottomBorder.Render();
    }
}

void Rectangle::CalculateWorldViewProjectionMatrix()
{
    // Direct3D uses an upwards Y axis system which is a bit unintuitive when dealing
    // with 2D rendering, so we flip the Y axis
    m_WorldMatrix = XMMatrixTranslation(m_Props.X, m_DisplayHeight - m_Props.Y, 0.0f);
    m_WVPMatrix = m_WorldMatrix * m_ViewMatrix * m_ProjectionMatrix;
}
