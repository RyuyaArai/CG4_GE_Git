#include "FbxMeshLoader.h"

void FbxMeshLoader::ParseMesh(FbxModel* fbxModel, FbxNode* fbxNode) {
	//�m�[�h�̃��b�V�����擾
	FbxMesh* fbxMesh = fbxNode->GetMesh();
	//���_���W�ǂݎ��
	ParseMeshVertices(fbxMesh);
	//�ʂ��\������f�[�^�̓ǂݎ��
	ParseMeshFaces(fbxModel, fbxMesh);
	//�}�e���A���̓ǂݎ��
	ParseMaterial(fbxModel, fbxNode);
}

void FbxMeshLoader::ParseMeshVertices(FbxMesh* fbxMesh) {
	
	auto& vertices = this->vertices;
	
	//���_���W�f�[�^�̐�
	const int controlPointCount =
		fbxMesh->GetControlPointsCount();
	//�K�v���������_�f�[�^�z����m��
	VertexPosNormalUv vert{};
	this->vertices.resize(controlPointCount, vert);

	//FBX���b�V���̒��_���W�z����擾
	FbxVector4* pCoord =
		fbxMesh->GetControlPoints();
	//FBX���b�V���̑S���_���W�����f�����̔z��ɃR�s�[����
	for (int i = 0; i < controlPointCount; i++) {
		VertexPosNormalUv& vertex = vertices[i];
		//���W�̃R�s�[
		vertex.pos.x = (float)pCoord[i][0];
		vertex.pos.y = (float)pCoord[i][1];
		vertex.pos.z = (float)pCoord[i][2];
	}
}

void FbxMeshLoader::ParseMeshFaces(FbxModel* fbxModel, FbxMesh* fbxMesh) {

	auto& vertices = this->vertices;
	auto& indices = this->indices;

	//1�t�@�C���ɕ������b�V���̃��f���͔�Ή�
	assert(indices.size() == 0);
	//�ʂ̐�
	const int polygonCount = fbxMesh->GetPolygonCount();
	//UV�f�[�^�̐�
	const int textureUVCount = fbxMesh->GetTextureUVCount();
	//UV�����X�g
	FbxStringList uvNames;
	fbxMesh->GetUVSetNames(uvNames);

	//�ʖ��̏��ǂݎ��
	for (int i = 0; i < polygonCount; i++) {
		//�ʂ��\�����钸�_�̐����擾(3�Ȃ�O�p�`�|���S��)
		const int polygonSize = fbxMesh->GetPolygonSize(i);
		assert(polygonSize <= 4);

		//1���_������
		for (int j; j < polygonSize; j++) {
			//FBX���_�z��̃C���f�b�N�X
			int index = fbxMesh->GetPolygonVertex(i, j);
			assert(index >= 0);

			//���_�@���ǂݍ���
			VertexPosNormalUv& vertex = vertices[index];
			FbxVector4 normal;
			if (fbxMesh->GetPolygonVertexNormal(i, j, normal)) {
				vertex.normal.x = (float)normal[0];
				vertex.normal.y = (float)normal[1];
				vertex.normal.z = (float)normal[2];
			}

			//�e�N�X�`��UV�Ǎ�
			if (textureUVCount > 0) {
				FbxVector2 uvs;
				bool lUnmappedUV;
				//0�Ԍ��ߑł��œǂݍ���
				if (fbxMesh->GetPolygonVertexUV(i, j, uvNames[0], uvs, lUnmappedUV)) {
					vertex.uv.x = (float)uvs[0];
					vertex.uv.y = (float)uvs[1];
				}
			}
			//�C���f�b�N�X�z��ɒ��_�C���f�b�N�X�ǉ�
			//3���_�ڂ܂łȂ�
			if (j < 3) {
				//1�_�ǉ����A����2�_�ƎO�p�`���\�z����
				indices.push_back(index);
			}//4���_��
			else {
				//3�_�ǉ����A
				//�l�p�`��0,1,2,3�̓� 2,3,0�ŎO�p�`���\�z����
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
	//FBX�m�[�h�̃��b�V���������
	FbxNodeAttribute* fbxNodeAttribute = fbxNode->GetNodeAttribute();

	if (fbxNodeAttribute) {
		if (fbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
			meshNode = node;
			ParseMesh(fbxModel, fbxNode);
		}
	}

}
