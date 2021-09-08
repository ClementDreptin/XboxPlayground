#pragma once


//--------------------------------------------------------------------------------------
// Name: struct Vertex
// Desc: Struct to describe a vertex.
//--------------------------------------------------------------------------------------
struct Vertex
{
    Vertex() {}
    Vertex(float x, float y, float z)
        : Pos(x, y, z) {}

    XMFLOAT3 Pos;
};


//--------------------------------------------------------------------------------------
// Name: class VertexBuffer
// Desc: Class to wrap common vertex buffer operations.
//--------------------------------------------------------------------------------------
class VertexBuffer
{
public:
    VertexBuffer() {}

    LPDIRECT3DVERTEXBUFFER9 Get() const { return m_pBuffer; }
    LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration() const { return m_pVertexDeclaration; }

    HRESULT Init(LPDIRECT3DDEVICE9 pDevice, Vertex* pData, UINT uiNumVertices);
private:
    LPDIRECT3DVERTEXBUFFER9 m_pBuffer;
    LPDIRECT3DVERTEXDECLARATION9 m_pVertexDeclaration;
};
