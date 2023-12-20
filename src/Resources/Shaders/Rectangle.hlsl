float4x4 c_matWP : register(c0);

struct VS_IN
{
    float4 inPos    : POSITION;
};

struct VS_OUT
{
    float4 outPos   : POSITION;
};

VS_OUT RectangleVertex(VS_IN input)
{
    VS_OUT output;
    output.outPos = mul(c_matWP, input.inPos);

    return output;
}

float4 c_color : register(c0);

float4 RectanglePixel() : COLOR
{
    return c_color;
}
