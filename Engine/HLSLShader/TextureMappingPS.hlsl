struct VSOutput
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float4 diffuseColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
    
    float3 lightDir = normalize(float3(500.0f, 500.0f, -500.f));
    float NdotL = dot(normalize(input.normal), lightDir);
    
    //return float4(NdotL, NdotL, NdotL, 1);
    return diffuseColor * NdotL;
}