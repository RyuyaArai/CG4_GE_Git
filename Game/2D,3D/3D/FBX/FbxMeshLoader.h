#pragma once
#include "FbxModel.h"
#include "FbxLoader.h"

class FbxMeshLoader
{
private:
	// DirectX::���ȗ�
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
	//���b�V���ǂݎ��
	void ParseMesh(FbxModel* fbxModel, FbxNode* fbxNode);
	//���_���W�ǂݎ��
	void ParseMeshVertices(FbxMesh* fbxMesh);
	//�ʏ��ǂݎ��
	void ParseMeshFaces(FbxModel* fbxModel, FbxMesh* fbxMesh);
	//�}�e���A���ǂݎ��
	void ParseMaterial(FbxModel* fbxModel, FbxNode* fbxNode);
	//�e�N�X�`���ǂݍ���
	void LoadTexture(FbxModel* fbxModel, const std::string& fullpath);

	//���b�V�����
	void ParseMeshNode(FbxModel* fbxModel, FbxNode* fbxNode, Node* node);

private:
	//���b�V�������m�[�h
	Node* meshNode = nullptr;
	//���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	//���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;

};

