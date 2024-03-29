#include"PostEffectTest.hlsli"

Texture2D<float4>tex0:register(t0);//0番スロットに設定されたテクスチャ
Texture2D<float4>tex1:register(t1);//1番スロットに設定されたテクスチャ
SamplerState smp:register(s0);

float4 main(VSOutput input):SV_TARGET
{
	float4 texcolor = tex0.Sample(smp,input.uv);
	// //default
	//// return float4(texcolor.rgb, 1);
	//ぼかし
	// 2.5テクセル分ずらすためのUV値を求める
	float offsetU = 3.5f / 1280.0f;
	float offsetV = 3.5f / 720.0f;

	// 基準テクセルから右のテクセルのカラーをサンプリング
	texcolor += tex0.Sample(smp, input.uv + float2(offsetU, 0.0f));
	// 基準テクセルから左のテクセルのカラーをサンプリング
	texcolor += tex0.Sample(smp, input.uv + float2(-offsetU, 0.0f));
	// 基準テクセルから下のテクセルのカラーをサンプリング
	texcolor += tex0.Sample(smp, input.uv + float2(0.0f, offsetV));
	// 基準テクセルから上のテクセルのカラーをサンプリング
	texcolor += tex0.Sample(smp, input.uv + float2(0.0f, -offsetV));
	// 基準テクセルから右下のテクセルのカラーをサンプリング
	texcolor += tex0.Sample(smp, input.uv + float2(offsetU, offsetV));
	// 基準テクセルから右上のテクセルのカラーをサンプリング
	texcolor += tex0.Sample(smp, input.uv + float2(offsetU, -offsetV));
	// 基準テクセルから左下のテクセルのカラーをサンプリング
	texcolor += tex0.Sample(smp, input.uv + float2(-offsetU, offsetV));
	// 基準テクセルから左上のテクセルのカラーをサンプリング
	texcolor += tex0.Sample(smp, input.uv + float2(-offsetU, -offsetV));
	// 基準テクセルと近傍8テクセルの平均なので9で除算する
	texcolor /= 9.0f;

	return float4(texcolor.rgb,1);

	//------------ここまでぼかし--------

	//ボーダー
	//float4 colortex0 = tex0.Sample(smp,input.uv);
	//float4 colortex1 = tex1.Sample(smp,input.uv);

	//float4 color = colortex0;
	//if (fmod(input.uv.y, 0.1f) < 0.05f) {
	//    color = colortex1;
	//}

	//return float4(color.rgb, 1);
	//return float4(1.0f - texcolor.rgb, 1);

	//暗くなる
	//return float4(1-texcolor.rgb, 1);

	//明るくなる
	//return float4(texcolor.rgb*2, 1);
	//return tex.Sample(smp,input.uv) * color;
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}