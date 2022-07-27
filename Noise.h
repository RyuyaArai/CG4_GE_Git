#pragma once
#include <DirectXMath.h>
#include <wrl.h>

class Noise {

private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	float Wavelet(float t, float a);
	float PerlinNoise(float t, float a);
	float TwoDimensionalWavelet(float x, float y, float ax, float ay);
	float ThreeDimensionalWavelet(float x, float y, float z, float ax, float ay, float az);

};

