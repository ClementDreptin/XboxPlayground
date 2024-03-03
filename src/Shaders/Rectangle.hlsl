float4x4 c_WVPMatrix : register(c0);

struct Vertex
{
    float4 Position : POSITION;
};

Vertex RectangleVertex(Vertex input)
{
    Vertex output;
    output.Position = mul(c_WVPMatrix, input.Position);

    return output;
}

float4 c_Color : register(c0);

float4 RectanglePixel() : COLOR
{
    return c_Color;
}
