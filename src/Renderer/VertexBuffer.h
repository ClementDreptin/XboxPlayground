#pragma once

// Struct to describe a vertex.
struct Vertex
{
    Vertex() {}

    Vertex(float x, float y, float z)
        : Pos(x, y, z) {}

    XMFLOAT3 Pos;
};

// Class to wrap common vertex buffer operations.
class VertexBuffer
{
public:
    VertexBuffer() {}

    D3DVertexBuffer *Get() const { return m_pBuffer; }

    D3DVertexDeclaration *GetVertexDeclaration() const { return m_pVertexDeclaration; }

    // Create the vertex buffer, copy data into it and set the vertex declaration.
    HRESULT Init(D3DDevice *pDevice, Vertex *pData, uint32_t numVertices);

private:
    D3DVertexBuffer *m_pBuffer;
    D3DVertexDeclaration *m_pVertexDeclaration;
};
