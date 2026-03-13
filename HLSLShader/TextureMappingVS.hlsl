struct VSInput
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
};

cbuffer Transform : register(b0)
{
    matrix worldMatrix;
};

cbuffer Camera : register(b1)
{
    matrix viewMatrix;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

VSOutput main(VSInput input)
{
    VSOutput output;
   // output.position = float4(input.position, 1);
    output.position = mul(float4(input.position, 1), worldMatrix);
    output.texCoord = input.texCoord;
    
    return output;
}