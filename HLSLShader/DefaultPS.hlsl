struct VSOutput
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

float4 main(VSOutput input) : SV_TARGET
{
	return float4(input.texCoord, 0.0f, 1.0f);
}