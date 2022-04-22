#pragma once

#include "fbxsdk.h"
#include "FbxModel.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>

class FbxLoader {

private:
	using string = std::string;

public:
	static const string baseDirectory;

public:
	static FbxLoader* GetInstance();

	void Initialize(ID3D12Device* device);

	void Finalize();

	void LoatModelFromFile(const string& modelName);

	void ParseNodeRecursive(
		FbxModel* F_Model, FbxNode* fbxNode, Node* parent = nullptr);

private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;

	ID3D12Device* device = nullptr;
	FbxManager* fbxManager = nullptr;
	FbxImporter* fbxImporter = nullptr;
};