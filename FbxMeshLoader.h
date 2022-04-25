#pragma once
#include "FbxModel.h"
#include "FbxLoader.h"

class FbxMeshLoader
{
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	struct VertexPosNormalUv {
		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT2 uv;
	};

public:
	//メッシュ読み取り
	void ParseMesh(FbxModel* fbxModel, FbxNode* fbxNode);
	//頂点座標読み取り
	void ParseMeshVertices(FbxMesh* fbxMesh);
	//面情報読み取り
	void ParseMeshFaces(FbxModel* fbxModel, FbxMesh* fbxMesh);
	//マテリアル読み取り
	void ParseMaterial(FbxModel* fbxModel, FbxNode* fbxNode);
	//テクスチャ読み込み
	void LoadTexture(FbxModel* fbxModel, const std::string& fullpath);

	//メッシュ解析
	void ParseMeshNode(FbxModel* fbxModel, FbxNode* fbxNode, Node* node);

private:
	//メッシュを持つノード
	Node* meshNode = nullptr;
	//頂点データ配列
	std::vector<VertexPosNormalUv> vertices;
	//頂点インデックス配列
	std::vector<unsigned short> indices;

};

