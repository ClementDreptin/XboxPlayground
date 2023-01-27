#pragma once

#include "Renderer\VertexBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexShader.h"
#include "Renderer\PixelShader.h"

// Class that represents a line.
class Line
{
public:
    struct Props
    {
        float X;
        float Y;
        float Width;
        float Height;
        D3DCOLOR Color;
    };

    Line();

    // Create the vertex and index buffers needed to create a line. Set up the
    // matrices to project the line.
    HRESULT Init(const Props &props);

    float GetX() const { return m_Props.X; }

    float GetY() const { return m_Props.Y; }

    void SetPosition(float x, float y)
    {
        m_Props.X = x;
        m_Props.Y = y;
        CalculateWorldViewProjectionMatrix();
    }

    void SetX(float x)
    {
        m_Props.X = x;
        CalculateWorldViewProjectionMatrix();
    }

    void SetY(float y)
    {
        m_Props.Y = y;
        CalculateWorldViewProjectionMatrix();
    }

    // Render the rectangle.
    void Render();

private:
    Props m_Props;

    float m_DisplayWidth;
    float m_DisplayHeight;

    VertexBuffer m_VertexBuffer;
    IndexBuffer m_IndexBuffer;

    static VertexShader s_VertexShader;
    static PixelShader s_PixelShader;
    static bool s_ShadersInitialized;

    XMMATRIX m_WorldMatrix;
    XMMATRIX m_ViewMatrix;
    XMMATRIX m_ProjectionMatrix;
    XMMATRIX m_WVPMatrix;

    // Apply a translation from the position and recalculate the world view
    // projection matrix.
    void CalculateWorldViewProjectionMatrix();
};
