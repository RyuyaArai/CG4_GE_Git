#pragma once
#include "Sprite.h"

class PostEffect : public Sprite
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:

	//�R���X�g���N�^
	PostEffect();
	/// <summary>
  /// �p�C�v���C������
  /// </summary>
  /// <param name="cmdList"></param>
	void CreateGraphicsPipeline();
	//������
	void Initialize();

	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �V�[���`��O����
	/// </summary>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �V�[���`��㏈��
	/// </summary>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);
private://�ÓI�����o�ϐ�
	static const float clearColor[4];
private://�����o�ϐ�
	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff[2];
	//SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap>descHeapSRV;
	//�[�x�o�b�t�@
	ComPtr<ID3D12Resource> depthBuff;
	//RTV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//�O���t�B�b�N�X�p�C�v���C��
	ComPtr<ID3D12PipelineState>pipelineState;
	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature>rootSignature;
};