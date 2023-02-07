#pragma once

#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexShader.h"
#include "Renderer/PixelShader.h"
#include "UI/Border.h"

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

    HRESULT Render(const Props &props);

private:
    Props m_Props;
    Border m_Border;
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

    HRESULT Init();

    void CalculateWorldViewProjectionMatrix();

    HRESULT UpdateVertexBuffer();
};
