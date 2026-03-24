struct VSOutput
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 cameraPosition : TEXCOORD1;
};

Texture2D map;
SamplerState mapSampler;

float4 main(VSOutput input) : SV_TARGET
{
    float4 diffuseMapColor = map.Sample(mapSampler, input.texCoord);
    
    // light direction.
    float3 lightDir = normalize(float3(500.0f, 500.0f, -500.0f));
    
    // world normal.
    float3 worldNormal = normalize(input.normal);
    
    // NdotL.
    float NdotL = dot(worldNormal, lightDir);
    
    // Half-Lambert.
    NdotL = pow(NdotL * 0.5f + 0.5f, 2);
    
    // Specular (Phong-shader).
    float specular = 0.0f;
    if (NdotL > 0)
    {
        // RdotV.
        // R: reflection vector of light direction vector.
        // V: View-Direction Vector.
        float3 reflection = reflect(lightDir, worldNormal);
        
        // View Direction.
        float3 viewDir = normalize(input.cameraPosition - input.position.xyz);

        // RdotV.
        //float RdotV = max(0, dot(reflection, viewDir));
        float RdotV = saturate(dot(reflection, viewDir));
        
        // specular.
        specular = pow(RdotV, 2);
    }
    
    // Diffuse + Specular + Ambient(Global-Illumination/Local-Illumination).
    
    //return float4(1.0f, 1.0f, 0.0f, 1.0f);
    //return diffuseMapColor * NdotL;
    //return float4(NdotL, NdotL, NdotL, 1);
    
    return float4(specular, specular, specular, 1);
}