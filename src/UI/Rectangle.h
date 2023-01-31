#pragma once

#include "Renderer\VertexBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexShader.h"
#include "Renderer\PixelShader.h"
#include "UI\Border.h"

// Class to create a 2D rectangle.
class Rectangle
{
public:
    struct Props
    {
        float X;
        float Y;
        float Width;
        float Height;
        D3DCOLOR Color;
        float BorderWidth;
        D3DCOLOR BorderColor;
        Border::Position BorderPosition;
    };

    Rectangle();

    inline Props GetProps() const { return m_Props; }

    // Set the new props and update the world view projection matrix and/or the vertex buffer if necessary.
    HRESULT SetProps(const Props &props);

    // Render the rectangle.
    void Render();

private:
    Props m_Props;
    Border m_Border;
    bool m_HasBorder;
    bool m_IsInitialized;

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

    // Create the vertex and index buffers needed to create a rectangle. Set up the
    // matrices to project the rectangle.
    HRESULT Init();

    // Set the border from the props.
    HRESULT SetBorder();

    // Apply a translation from the position and recalculate the world view
    // projection matrix.
    void CalculateWorldViewProjectionMatrix();

    // Update the vertex buffer from the props.
    HRESULT UpdateVertexBuffer();
};
