#include "OBJShaderHeader.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{

	//法線にワールド行列によるスケーリング・回転を適用
	float4 wnormal = normalize(mul(world, float4(normal, 0)));
	float4 wpos = mul(world, pos);

	//ピクセルシェーダーに渡す値
	VSOutput output;
	//output.svpos = mul(mat, pos);
	output.svpos = mul(mul(viewproj, world), pos);
	////Lambert反射の計算
	output.color.rgb = dot(lightv, normal) * m_diffuse * lightcolor;
	output.color.a = m_alpha;
	output.uv = uv;
	//環境反射光
	float3 ambient = m_alpha;
	//拡散反射光
	float3 diffuse = dot(lightv, wnormal.xyz) * m_diffuse;
	//光沢度
	const float shininess = 4.0f;
	//頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - wpos.xyz);
	//反射光ベクトル
	float3 reflect = normalize(-lightv + 2 * dot(lightv, wnormal.xyz) * wnormal.xyz);

	//鏡面反射光
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;
	//全て加算する
	output.color.a = m_alpha;
	return output;
}