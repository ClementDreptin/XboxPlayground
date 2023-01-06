#include "pch.h"
#include "Renderer\VertexBuffer.h"

HRESULT VertexBuffer::Init(D3DDevice *pDevice, Vertex *pData, uint32_t uiNumVertices)
{
    HRESULT hr;

    uint32_t uiDataSize = sizeof(Vertex) * uiNumVertices;

    // Create the vertex buffer
    hr = pDevice->CreateVertexBuffer(uiDataSize, D3DUSAGE_WRITEONLY, NULL, D3DPOOL_DEFAULT, &m_pBuffer, nullptr);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the vertex buffer");
        return hr;
    }

    // Copy the data into the vertex buffer
    void *pVertices;
    hr = m_pBuffer->Lock(0, uiDataSize, reinterpret_cast<void **>(&pVertices), NULL);
    if (FAILED(hr))
    {
        Log::Error("Couldn't lock the vertex buffer");
        return hr;
    }
    memcpy(pVertices, pData, uiDataSize);
    m_pBuffer->Unlock();

    // Define the vertex elements
    D3DVERTEXELEMENT9 VertexElements[] = {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        D3DDECL_END()
    };

    // Create a vertex declaration from the element descriptions
    hr = pDevice->CreateVertexDeclaration(VertexElements, &m_pVertexDeclaration);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the vertex declaration");
        return hr;
    }

    return hr;
}
