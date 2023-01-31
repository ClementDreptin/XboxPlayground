#pragma once

// Class to wrap common index buffer operations.
class IndexBuffer
{
public:
    IndexBuffer();

    inline D3DIndexBuffer *operator&() const { return m_pBuffer; }

    // Create the index buffer and copy data into it.
    HRESULT Init(uint16_t *pData, size_t numIndices);

    // Copy pData into the buffer on the GPU.
    HRESULT UpdateBuffer(uint16_t *pData, size_t numIndices);

private:
    D3DIndexBuffer *m_pBuffer;
};
