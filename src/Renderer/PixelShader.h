#pragma once

class PixelShader
{
public:
    PixelShader();

    inline D3DPixelShader *operator&() const { return m_pShader; }

    HRESULT Init();

private:
    D3DPixelShader *m_pShader;
};
