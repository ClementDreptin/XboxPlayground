#pragma once

// Class to wrap common pixel shader operations.
class PixelShader
{
public:
    PixelShader() {}

    D3DPixelShader *Get() const { return m_pShader; }

    // Compile the pixel shader source and create the pixel shader.
    HRESULT Init();

private:
    D3DPixelShader *m_pShader;
};
