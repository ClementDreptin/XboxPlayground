#include "pch.h"
#include "Renderer\VertexBuffer.h"

#include "Renderer\D3DDevice.h"

VertexBuffer::VertexBuffer()
    : m_pBuffer(nullptr), m_pVertexDeclaration(nullptr)
{
}

HRESULT VertexBuffer::Init(Vertex *pData, size_t numVertices)
{
    HRESULT hr = S_OK;

    size_t dataSize = sizeof(Vertex) * numVertices;

    // Create the vertex buffer
    hr = g_pd3dDevice->CreateVertexBuffer(dataSize, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pBuffer, nullptr);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the vertex buffer");
        return hr;
    }

    // Define the vertex elements
    D3DVERTEXELEMENT9 vertexElements[] = {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        D3DDECL_END()
    };

    // Create a vertex declaration from the element descriptions
    hr = g_pd3dDevice->CreateVertexDeclaration(vertexElements, &m_pVertexDeclaration);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the vertex declaration");
        return hr;
    }

    // Copy the data into the vertex buffer
    hr = UpdateBuffer(pData, numVertices);
    if (FAILED(hr))
        return hr;

    return hr;
}

HRESULT VertexBuffer::UpdateBuffer(Vertex *pData, size_t numVertices)
{
    HRESULT hr = S_OK;

    // Make sure the vertex buffer is initialized
    if (m_pBuffer == nullptr)
    {
        Log::Error("Can't update the vertex buffer before initializing it");
        return hr;
    }

    size_t dataSize = sizeof(Vertex) * numVertices;
    void *pVertices = nullptr;

    // Lock the buffer
    hr = m_pBuffer->Lock(0, dataSize, reinterpret_cast<void **>(&pVertices), 0);
    if (FAILED(hr))
    {
        Log::Error("Couldn't lock the vertex buffer");
        return hr;
    }

    // Write to the buffer
    errno_t err = memcpy_s(pVertices, dataSize, pData, dataSize);
    if (err != 0)
    {
        Log::Error("Couldn't write to the vertex buffer");
        return E_FAIL;
    }

    // Unlock the buffer
    m_pBuffer->Unlock();

    return hr;
}
