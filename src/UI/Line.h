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

    inline Props GetProps() const { return m_Props; }

    // Set the new props and update the world view projection matrix and/or the vertex buffer if necessary.
    HRESULT SetProps(const Props &props);

    // Render the rectangle.
    void Render();

private:
    Props m_Props;
    bool m_IsInitialized;

    VertexBuffer m_VertexBuffer;
    IndexBuffer m_IndexBuffer;

    static VertexShader s_VertexShader;
    static PixelShader s_PixelShader;
    static bool s_ShadersInitialized;

    XMMATRIX m_WorldMatrix;
    XMMATRIX m_ViewMatrix;
    XMMATRIX m_ProjectionMatrix;
    XMMATRIX m_WVPMatrix;

    // Create the vertex and index buffers needed to create a line. Set up the
    // matrices to project the line.
    HRESULT Init();

    // Apply a translation from the position and recalculate the world view
    // projection matrix.
    void CalculateWorldViewProjectionMatrix();

    // Update the vertex buffer from the props.
    HRESULT UpdateVertexBuffer();
};
