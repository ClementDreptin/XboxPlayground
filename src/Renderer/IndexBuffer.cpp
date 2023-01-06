#include "pch.h"
#include "Renderer\IndexBuffer.h"

HRESULT IndexBuffer::Init(D3DDevice *pDevice, WORD *pwData, uint32_t uiNumIndices)
{
    HRESULT hr;

    uint32_t uiDataSize = sizeof(DWORD) * uiNumIndices;

    // Create the index buffer
    hr = pDevice->CreateIndexBuffer(uiDataSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, NULL, &m_pBuffer, nullptr);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the index buffer");
        return hr;
    }

    // Copy the data into the index buffer
    void *pIndices;
    hr = m_pBuffer->Lock(0, uiDataSize, reinterpret_cast<void **>(&pIndices), NULL);
    if (FAILED(hr))
    {
        Log::Error("Couldn't lock the index buffer");
        return hr;
    }
    memcpy(pIndices, pwData, uiDataSize);
    m_pBuffer->Unlock();

    return hr;
}
