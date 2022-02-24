#include "pch.h"
#include "Elements\Rectangle.h"

#include <AtgUtil.h>


HRESULT Rectangle::Init(D3DDevice *pDevice, float fX, float fY, float fWidth, float fHeight, D3DCOLOR dwColor)
{
    HRESULT hr;

    // Save the display dimensions
    ATG::GetVideoSettings(&m_uiWidth, &m_uiHeight);

    // Save the position
    m_fX = fX;
    m_fY = fY;

    // Save the color and the device
    m_dwColor = dwColor;
    m_pDevice = pDevice;

    // Set up the matrices for orthographic projection
    m_matView = XMMatrixIdentity();
    m_matProjection = XMMatrixOrthographicOffCenterLH(0.0f, static_cast<float>(m_uiWidth), 0.0f, static_cast<float>(m_uiHeight), -1.0f, 1.0f);
    CalculateWorldViewProjectionMatrix();

    // Create the vertices
    // Since the Y axis goes upwards, if we want a height increase to make our
    // rectangle grow downwards along the Y axis, we need to substract its height
    // to the Y coordinate of each vertex.
    Vertex vertices[] =
    {
        Vertex( 0.0f,   0.0f    - fHeight, 0.0f ), // Bottom Left
        Vertex( 0.0f,   fHeight - fHeight, 0.0f ), // Top Left
        Vertex( fWidth, fHeight - fHeight, 0.0f ), // Top Right
        Vertex( fWidth, 0.0f    - fHeight, 0.0f )  // Bottom Right
    };

    // Create the vertex buffer
    hr = m_VertexBuffer.Init(pDevice, vertices, ARRAYSIZE(vertices));
    if (FAILED(hr))
        return hr;

    // Create the indices
    WORD indices[] =
    {
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

void Rectangle::Draw()
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
    m_pDevice->SetVertexShaderConstantF(0, reinterpret_cast<float *>(&m_matWVP), 4);

    // Turn the color into a float array and pass it to the pixel shader
    float vColor[4];
    vColor[0] = ((m_dwColor & 0x00ff0000) >> 16) / 255.0f;
    vColor[1] = ((m_dwColor & 0x0000ff00) >> 8 ) / 255.0f;
    vColor[2] = ((m_dwColor & 0x000000ff) >> 0 ) / 255.0f;
    vColor[3] = ((m_dwColor & 0xff000000) >> 24) / 255.0f;
    m_pDevice->SetPixelShaderConstantF(0, vColor, 1);

    // Draw the rectangle
    m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 0, 0, 2);
}

void Rectangle::CalculateWorldViewProjectionMatrix()
{
    // Direct3D uses an upwards Y axis system which is a bit unintuitive when dealing
    // with 2D rendering, so we flip the Y axis
    m_matWorld = XMMatrixTranslation(m_fX, (float)m_uiHeight - m_fY, 0.0f);
    m_matWVP = m_matWorld * m_matView * m_matProjection;
}
