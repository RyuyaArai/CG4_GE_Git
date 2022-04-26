#include "FbxObject3d.h"
#include <d3dcompiler.h>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

#pragma comment(lib, "d3dcompiler.lib")

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

ID3D12Device* FbxObject3d::device = nullptr;
Camera* FbxObject3d::camera = nullptr;

void FbxObject3d::Initialize() {
	HRESULT result;
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(constBufferDataTransform) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffTransform)
	);
}
