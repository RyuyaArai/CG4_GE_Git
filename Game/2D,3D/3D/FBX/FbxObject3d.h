#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

#include "FbxModel.h"
#include "Camera.h"
//#include"PipelineSet.h"

/// 3Dオブジェクト
class FbxObject3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	struct constBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMMATRIX cameraPos;
	};
public:
	void Initialize();
public:
	static void SetDevice(ID3D12Device* device) { FbxObject3d::device = device; }
	static void SetCamera(Camera* camera) { FbxObject3d::camera = camera; }
private:
	static ID3D12Device* device;
	static Camera* camera;
protected:
	ComPtr<ID3D12Resource> constBuffTransform;
};