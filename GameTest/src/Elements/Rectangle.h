#pragma once

#include "Renderer\VertexBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexShader.h"
#include "Renderer\PixelShader.h"


//--------------------------------------------------------------------------------------
// Name: class Rectangle
// Desc: Class to create a 2D rectangle, inherits from HudElem.
//--------------------------------------------------------------------------------------
class Rectangle
{
public:
    Rectangle() {}

    HRESULT Init(LPDIRECT3DDEVICE9 pDevice, FLOAT fX, FLOAT fY, FLOAT fWidth, FLOAT fHeight, D3DCOLOR dwColor);

    FLOAT GetX() CONST { return m_fX; }
    FLOAT GetY() CONST { return m_fY; }

    VOID SetPosition(FLOAT fX, FLOAT fY) { m_fX = fX; m_fY = fY; CalculateWorldViewProjectionMatrix(); }
    VOID SetX(FLOAT fX) { m_fX = fX; CalculateWorldViewProjectionMatrix(); }
    VOID SetY(FLOAT fY) { m_fY = fY; CalculateWorldViewProjectionMatrix(); }

    VOID Draw();
private:
    VertexBuffer m_VertexBuffer;
    IndexBuffer m_IndexBuffer;

    VertexShader m_VertexShader;
    PixelShader m_PixelShader;

    FLOAT m_fX;
    FLOAT m_fY;
    UINT m_uiWidth;
    UINT m_uiHeight;

    D3DCOLOR m_dwColor;

    LPDIRECT3DDEVICE9 m_pDevice;

    XMMATRIX m_matWorld;
    XMMATRIX m_matView;
    XMMATRIX m_matProjection;
    XMMATRIX m_matWVP;

    VOID CalculateWorldViewProjectionMatrix();
};
