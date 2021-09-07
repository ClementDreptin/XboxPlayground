#pragma once


//--------------------------------------------------------------------------------------
// Name: class IndexBuffer
// Desc: Class to wrap common index buffer operations.
//--------------------------------------------------------------------------------------
class IndexBuffer
{
public:
    IndexBuffer() {}

    LPDIRECT3DINDEXBUFFER9 Get() const { return m_pBuffer; }

    HRESULT Init(LPDIRECT3DDEVICE9 pDevice, LPWORD pData, UINT uiNumIndices);
private:
    LPDIRECT3DINDEXBUFFER9 m_pBuffer;
};
