#include "pch.h"
#include "Renderer\VertexBuffer.h"


//--------------------------------------------------------------------------------------
// Name: Init()
// Desc: Create the vertex buffer, copy data into it and set the vertex declaration.
//--------------------------------------------------------------------------------------
HRESULT VertexBuffer::Init(LPDIRECT3DDEVICE9 pDevice, Vertex* pData, UINT uiNumVertices)
{
    HRESULT hr;

    UINT uiDataSize = sizeof(Vertex) * uiNumVertices;

    // Create the vertex buffer
    hr = pDevice->CreateVertexBuffer(uiDataSize, D3DUSAGE_WRITEONLY, NULL, D3DPOOL_DEFAULT, &m_pBuffer, nullptr);
    if (FAILED(hr))
    {
        Log::Error("Couldn't create the vertex buffer");
        return hr;
    }

    // Copy the data into the vertex buffer
    LPVOID pVertices;
    hr = m_pBuffer->Lock(0, uiDataSize, (LPVOID*)&pVertices, NULL);
    if (FAILED(hr))
    {
        Log::Error("Couldn't lock the vertex buffer");
        return hr;
    }
    memcpy(pVertices, pData, uiDataSize);
    m_pBuffer->Unlock();

    // Define the vertex elements
    D3DVERTEXELEMENT9 vertexElements[] =
    {
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
