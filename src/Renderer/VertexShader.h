#pragma once

#include "pch.h"

class VertexShader
{
public:
    VertexShader();

    inline D3DVertexShader *operator&() const { return m_pShader; }

    HRESULT Init();

private:
    D3DVertexShader *m_pShader;
};
