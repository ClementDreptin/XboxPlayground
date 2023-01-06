#include "pch.h"
#include "Renderer\VertexBuffer.h"

HRESULT VertexBuffer::Init(D3DDevice *pDevice, Vertex *pData, uint32_t numVertices)
{
    HRESULT hr = S_OK;

    uint32_t dataSize = sizeof(Vertex) * numVertices;

    // Create the vertex buffer
    hr = pDevice->CreateVertexBuffer(dataSize, D3DUSAGE_WRITEONLY, NULL, D3DPOOL_DEFAULT, &m_pBuffer, nullptr);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the vertex buffer");
        return hr;
    }

    // Copy the data into the vertex buffer
    void *pVertices = nullptr;
    hr = m_pBuffer->Lock(0, dataSize, reinterpret_cast<void **>(&pVertices), NULL);
    if (FAILED(hr))
    {
        Log::Error("Couldn't lock the vertex buffer");
        return hr;
    }
    memcpy(pVertices, pData, dataSize);
    m_pBuffer->Unlock();

    // Define the vertex elements
    D3DVERTEXELEMENT9 vertexElements[] = {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        D3DDECL_END()
    };

    // Create a vertex declaration from the element descriptions
    hr = pDevice->CreateVertexDeclaration(vertexElements, &m_pVertexDeclaration);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the vertex declaration");
        return hr;
    }

    return hr;
}
