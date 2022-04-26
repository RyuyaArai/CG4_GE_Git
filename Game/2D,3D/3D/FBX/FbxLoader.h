#pragma once

#include "fbxsdk.h"
#include "FbxModel.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>

class FbxMeshLoader;

class FbxLoader {

private:
	using string = std::string;

	FbxMeshLoader* fbxMeshLoader;

public:
	static const string baseDirectory;

public:
	static FbxLoader* GetInstance();

	void Initialize(ID3D12Device* device);

	void Finalize();

	void LoatModelFromFile(const string& modelName);

	void ParseNodeRecursive(
		FbxModel* F_Model, FbxNode* fbxNode, Node* parent = nullptr);

	//メッシュ読み取り
	void ParseMesh(FbxModel* fbxModel, FbxNode* fbxNode);
	//頂点座標読み取り
	void ParseMeshVertices(FbxModel* fbxModel, FbxMesh* fbxMesh);
	//面情報読み取り
	void ParseMeshFaces(FbxModel* fbxModel, FbxMesh* fbxMesh);
	//マテリアル読み取り
	void ParseMaterial(FbxModel* fbxModel, FbxNode* fbxNode);
	//テクスチャ読み込み
	void LoadTexture(FbxModel* fbxModel, const std::string& fullpath);

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