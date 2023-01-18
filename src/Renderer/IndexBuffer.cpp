#include "pch.h"
#include "Renderer\IndexBuffer.h"

#include "Renderer\D3DDevice.h"

IndexBuffer::IndexBuffer()
    : m_pBuffer(nullptr)
{
}

HRESULT IndexBuffer::Init(uint16_t *pData, uint32_t numIndices)
{
    HRESULT hr = S_OK;

    uint32_t dataSize = sizeof(uint16_t) * numIndices;

    // Create the index buffer
    hr = g_pd3dDevice->CreateIndexBuffer(dataSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, NULL, &m_pBuffer, nullptr);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the index buffer");
        return hr;
    }

    // Copy the data into the index buffer
    void *pIndices = nullptr;
    hr = m_pBuffer->Lock(0, dataSize, reinterpret_cast<void **>(&pIndices), NULL);
    if (FAILED(hr))
    {
        Log::Error("Couldn't lock the index buffer");
        return hr;
    }
    memcpy(pIndices, pData, dataSize);
    m_pBuffer->Unlock();

    return hr;
}
