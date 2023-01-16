#pragma once

// Class to wrap common vertex shader operations.
class VertexShader
{
public:
    VertexShader() {}

    D3DVertexShader *Get() const { return m_pShader; }

    // Compile the vertex shader source and create the vertex shader.
    HRESULT Init();

private:
    D3DVertexShader *m_pShader;
};
