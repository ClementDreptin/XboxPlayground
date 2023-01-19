#pragma once

#include "Renderer\VertexBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexShader.h"
#include "Renderer\PixelShader.h"

// Class to create a 2D rectangle, inherits from HudElem.
class Rectangle
{
public:
    Rectangle();

    // Create the vertex and index buffers needed to create a rectangle. Set up the
    // matrices to project to rectangle.
    HRESULT Init(float x, float y, float width, float height, D3DCOLOR color);

    float GetX() const { return m_X; }

    float GetY() const { return m_Y; }

    void SetPosition(float x, float y)
    {
        m_X = x;
        m_Y = y;
        CalculateWorldViewProjectionMatrix();
    }

    void SetX(float x)
    {
        m_X = x;
        CalculateWorldViewProjectionMatrix();
    }

    void SetY(float y)
    {
        m_Y = y;
        CalculateWorldViewProjectionMatrix();
    }

    // Render the rectangle.
    void Render();

private:
    VertexBuffer m_VertexBuffer;
    IndexBuffer m_IndexBuffer;

    static VertexShader s_VertexShader;
    static PixelShader s_PixelShader;
    static bool s_ShadersInitialized;

    float m_X;
    float m_Y;
    float m_Width;
    float m_Height;

    uint32_t m_DisplayWidth;
    uint32_t m_DisplayHeight;

    D3DCOLOR m_Color;

    XMMATRIX m_WorldMatrix;
    XMMATRIX m_ViewMatrix;
    XMMATRIX m_ProjectionMatrix;
    XMMATRIX m_WVPMatrix;

    // Apply a translation from the position andrecalculate the world view
    // projection matrix.
    void CalculateWorldViewProjectionMatrix();
};
