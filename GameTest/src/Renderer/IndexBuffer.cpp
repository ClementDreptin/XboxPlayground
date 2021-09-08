#include "pch.h"
#include "Renderer\IndexBuffer.h"


//--------------------------------------------------------------------------------------
// Name: Init()
// Desc: Create the index buffer and copy data into it.
//--------------------------------------------------------------------------------------
HRESULT IndexBuffer::Init(LPDIRECT3DDEVICE9 pDevice, LPWORD pwData, UINT uiNumIndices)
{
    HRESULT hr;

    UINT uiDataSize = sizeof(DWORD) * uiNumIndices;

    // Create the index buffer
    hr = pDevice->CreateIndexBuffer(uiDataSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, NULL, &m_pBuffer, nullptr);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the index buffer");
        return hr;
    }

    // Copy the data into the index buffer
    LPVOID pIndices;
    hr = m_pBuffer->Lock(0, uiDataSize, (LPVOID*)&pIndices, NULL);
    if (FAILED(hr))
    {
        Log::Error("Couldn't lock the index buffer");
        return hr;
    }
    memcpy(pIndices, pwData, uiDataSize);
    m_pBuffer->Unlock();

    return hr;
}
