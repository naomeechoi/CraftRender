struct VSInput
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

cbuffer Transform : register(b0)
{
    matrix worldMatrix;
};

cbuffer Camera : register(b1)
{
    matrix cameraMatrix;
    float3 cameraPosition;
    float padding;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 cameraPosition : TEXCOORD1;
};

VSOutput main(VSInput input)
{
    VSOutput output;
   // output.position = float4(input.position, 1);
    output.position = mul(float4(input.position, 1), worldMatrix);
    output.position = mul(output.position, cameraMatrix);
    
    output.texCoord = input.texCoord;
    
    output.normal = normalize(mul(input.normal, (float3x3) worldMatrix));
    output.cameraPosition = cameraPosition;
    
    return output;
}