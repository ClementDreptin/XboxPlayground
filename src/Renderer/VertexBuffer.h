#pragma once

#include "pch.h"

struct Vertex
{
    Vertex() {}

    Vertex(float x, float y, float z)
        : Pos(x, y, z) {}

    XMFLOAT3 Pos;
};

class VertexBuffer
{
public:
    VertexBuffer();

    inline D3DVertexBuffer *operator&() const { return m_pBuffer; }

    inline D3DVertexDeclaration *GetVertexDeclaration() const { return m_pVertexDeclaration; }

    HRESULT Init(Vertex *pData, size_t numVertices);

    HRESULT UpdateBuffer(Vertex *pData, size_t numVertices);

private:
    D3DVertexBuffer *m_pBuffer;
    D3DVertexDeclaration *m_pVertexDeclaration;
};
