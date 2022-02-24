#pragma once


// Class to wrap common index buffer operations.
class IndexBuffer
{
public:
    IndexBuffer() {}

    D3DIndexBuffer *Get() const { return m_pBuffer; }

    // Create the index buffer and copy data into it.
    HRESULT Init(D3DDevice *pDevice, WORD *pwData, uint32_t uiNumIndices);
private:
    D3DIndexBuffer *m_pBuffer;
};
