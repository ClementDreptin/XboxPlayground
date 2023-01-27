#pragma once

#include "Renderer\VertexBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexShader.h"
#include "Renderer\PixelShader.h"
#include "UI\Line.h"

// Class to create a 2D rectangle.
class Rectangle
{
public:
    typedef enum _Border
    {
        Border_None = 0,
        Border_Left = 1 << 0,
        Border_Right = 1 << 1,
        Border_Top = 1 << 2,
        Border_Bottom = 1 << 3,
        Border_All = Border_Left | Border_Right | Border_Top | Border_Bottom,
    } Border;

    struct Props
    {
        float X;
        float Y;
        float Width;
        float Height;
        D3DCOLOR Color;
        float BorderWidth;
        D3DCOLOR BorderColor;
        Border Border;
    };

    Rectangle();

    // Create the vertex and index buffers needed to create a rectangle. Set up the
    // matrices to project the rectangle.
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

    Line m_LeftBorder;
    Line m_RightBorder;
    Line m_TopBorder;
    Line m_BottomBorder;

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
