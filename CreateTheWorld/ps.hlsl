// “ü—Íî•ñ
struct PS_INPUT
{
	float4 OutPosition : SV_POSITION;
	float4 Color : COLOR0;
};

void PS(in PS_INPUT In, out float4 Out : SV_Target0)
{
	Out = In.Color;
}