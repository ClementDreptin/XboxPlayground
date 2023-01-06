#pragma once

#include "Renderer\VertexBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexShader.h"
#include "Renderer\PixelShader.h"

// Class to create a 2D rectangle, inherits from HudElem.
class Rectangle
{
public:
    Rectangle() {}

    // Create the vertex and index buffers needed to create a rectangle. Set up the
    // matrices to project to rectangle.
    HRESULT Init(D3DDevice *pDevice, float fX, float fY, float fWidth, float fHeight, D3DCOLOR dwColor);

    float GetX() const { return m_fX; }

    float GetY() const { return m_fY; }

    void SetPosition(float fX, float fY)
    {
        m_fX = fX;
        m_fY = fY;
        CalculateWorldViewProjectionMatrix();
    }

    void SetX(float fX)
    {
        m_fX = fX;
        CalculateWorldViewProjectionMatrix();
    }

    void SetY(float fY)
    {
        m_fY = fY;
        CalculateWorldViewProjectionMatrix();
    }

    // Draw the rectangle.
    void Draw();

private:
    VertexBuffer m_VertexBuffer;
    IndexBuffer m_IndexBuffer;

    VertexShader m_VertexShader;
    PixelShader m_PixelShader;

    float m_fX;
    float m_fY;
    uint32_t m_uiWidth;
    uint32_t m_uiHeight;

    D3DCOLOR m_dwColor;

    D3DDevice *m_pDevice;

    XMMATRIX m_matWorld;
    XMMATRIX m_matView;
    XMMATRIX m_matProjection;
    XMMATRIX m_matWVP;

    // Apply a translation from the position andrecalculate the world view
    // projection matrix.
    void CalculateWorldViewProjectionMatrix();
};
