#include "FbxMeshLoader.h"

void FbxMeshLoader::ParseMesh(FbxModel* fbxModel, FbxNode* fbxNode) {
	//ノードのメッシュを取得
	FbxMesh* fbxMesh = fbxNode->GetMesh();
	//頂点座標読み取り
	ParseMeshVertices(fbxMesh);
	//面を構成するデータの読み取り
	ParseMeshFaces(fbxModel, fbxMesh);
	//マテリアルの読み取り
	ParseMaterial(fbxModel, fbxNode);
}

void FbxMeshLoader::ParseMeshVertices(FbxMesh* fbxMesh) {
	
	auto& vertices = this->vertices;
	
	//頂点座標データの数
	const int controlPointCount =
		fbxMesh->GetControlPointsCount();
	//必要数だけ頂点データ配列を確保
	VertexPosNormalUv vert{};
	this->vertices.resize(controlPointCount, vert);

	//FBXメッシュの頂点座標配列を取得
	FbxVector4* pCoord =
		fbxMesh->GetControlPoints();
	//FBXメッシュの全頂点座標をモデル内の配列にコピーする
	for (int i = 0; i < controlPointCount; i++) {
		VertexPosNormalUv& vertex = vertices[i];
		//座標のコピー
		vertex.pos.x = (float)pCoord[i][0];
		vertex.pos.y = (float)pCoord[i][1];
		vertex.pos.z = (float)pCoord[i][2];
	}
}

void FbxMeshLoader::ParseMeshFaces(FbxModel* fbxModel, FbxMesh* fbxMesh) {

	auto& vertices = this->vertices;
	auto& indices = this->indices;

	//1ファイルに複数メッシュのモデルは非対応
	assert(indices.size() == 0);
	//面の数
	const int polygonCount = fbxMesh->GetPolygonCount();
	//UVデータの数
	const int textureUVCount = fbxMesh->GetTextureUVCount();
	//UV名リスト
	FbxStringList uvNames;
	fbxMesh->GetUVSetNames(uvNames);

	//面毎の情報読み取り
	for (int i = 0; i < polygonCount; i++) {
		//面を構成する頂点の数を取得(3なら三角形ポリゴン)
		const int polygonSize = fbxMesh->GetPolygonSize(i);
		assert(polygonSize <= 4);

		//1頂点ずつ処理
		for (int j; j < polygonSize; j++) {
			//FBX頂点配列のインデックス
			int index = fbxMesh->GetPolygonVertex(i, j);
			assert(index >= 0);

			//頂点法線読み込み
			VertexPosNormalUv& vertex = vertices[index];
			FbxVector4 normal;
			if (fbxMesh->GetPolygonVertexNormal(i, j, normal)) {
				vertex.normal.x = (float)normal[0];
				vertex.normal.y = (float)normal[1];
				vertex.normal.z = (float)normal[2];
			}

			//テクスチャUV読込
			if (textureUVCount > 0) {
				FbxVector2 uvs;
				bool lUnmappedUV;
				//0番決め打ちで読み込み
				if (fbxMesh->GetPolygonVertexUV(i, j, uvNames[0], uvs, lUnmappedUV)) {
					vertex.uv.x = (float)uvs[0];
					vertex.uv.y = (float)uvs[1];
				}
			}
			//インデックス配列に頂点インデックス追加
			//3頂点目までなら
			if (j < 3) {
				//1点追加し、他の2点と三角形を構築する
				indices.push_back(index);
			}//4頂点目
			else {
				//3点追加し、
				//四角形の0,1,2,3の内 2,3,0で三角形を構築する
				int index2 = indices[indices.size() - 1];
				int index3 = index;
				int index4 = indices[indices.size() - 3];
				indices.push_back(index2);
				indices.push_back(index3);
				indices.push_back(index4);
			}
		}
	}
}

void FbxMeshLoader::ParseMaterial(FbxModel* fbxModel, FbxNode* fbxNode)
{
}

void FbxMeshLoader::LoadTexture(FbxModel* fbxModel, const std::string& fullpath)
{
}

void FbxMeshLoader::ParseMeshNode(FbxModel* fbxModel, FbxNode* fbxNode, Node* node) {
	//FBXノードのメッシュ情報を解析
	FbxNodeAttribute* fbxNodeAttribute = fbxNode->GetNodeAttribute();

	if (fbxNodeAttribute) {
		if (fbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
			meshNode = node;
			ParseMesh(fbxModel, fbxNode);
		}
	}

}
