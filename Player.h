#pragma once
#include"Object3d.h"
#include"FbxObject3d.h"

class Player {
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	struct Jump {
		bool isJump;
		bool isDouble;
		bool isglide;
		float fallSpeed;
	};

public:
	void Initialize();

	void Finalize();

	void Update();

	void Draw();

private:
	ObjModel* modelChr = nullptr;

	Object3d* objChr = nullptr;

	Jump jump;

};

