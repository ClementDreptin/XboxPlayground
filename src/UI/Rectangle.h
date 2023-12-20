#pragma once

#include "Renderer/VertexBuffer.h"
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

    void Render(const Props &props);

private:
    Props m_Props;
    Border m_Border;
    bool m_IsInitialized;

    VertexBuffer m_VertexBuffer;

    static bool s_ShadersInitialized;
    static D3DVertexShader *s_pVertexShader;
    static D3DPixelShader *s_pPixelShader;

    XMMATRIX m_WorldMatrix;
    XMMATRIX m_ViewMatrix;
    XMMATRIX m_ProjectionMatrix;
    XMMATRIX m_WVPMatrix;

    HRESULT Init();

    static HRESULT InitShaders();

    void CalculateWorldViewProjectionMatrix();

    void UpdateVertexBuffer();
};
