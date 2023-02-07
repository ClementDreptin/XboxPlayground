#include "pch.h"
#include "Renderer\IndexBuffer.h"

#include "Renderer\D3DDevice.h"

IndexBuffer::IndexBuffer()
    : m_pBuffer(nullptr)
{
}

HRESULT IndexBuffer::Init(uint16_t *pData, size_t numIndices)
{
    HRESULT hr = S_OK;

    size_t dataSize = sizeof(uint16_t) * numIndices;

    // Create the index buffer
    hr = g_pd3dDevice->CreateIndexBuffer(dataSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, 0, &m_pBuffer, nullptr);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the index buffer");
        return hr;
    }

    // Copy the data into the index buffer
    hr = UpdateBuffer(pData, numIndices);

    return hr;
}

HRESULT IndexBuffer::UpdateBuffer(uint16_t *pData, size_t numIndices)
{
    HRESULT hr = S_OK;

    // Make sure the index buffer is initialized
    if (m_pBuffer == nullptr)
    {
        Log::Error("Can't update the vertex buffer before initializing it");
        return hr;
    }

    size_t dataSize = sizeof(uint16_t) * numIndices;
    void *pIndices = nullptr;

    // Lock the buffer
    hr = m_pBuffer->Lock(0, dataSize, &pIndices, 0);
    if (FAILED(hr))
    {
        Log::Error("Couldn't lock the index buffer");
        return hr;
    }

    // Write to the buffer
    errno_t err = memcpy_s(pIndices, dataSize, pData, dataSize);
    if (err != 0)
    {
        Log::Error("Couldn't write to the index buffer");
        return E_FAIL;
    }

    // Unlock the buffer
    m_pBuffer->Unlock();

    return hr;
}
