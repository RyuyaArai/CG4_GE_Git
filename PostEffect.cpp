#include "PostEffect.h"
#include <d3d12.h>

using namespace DirectX;

PostEffect::PostEffect()
	: Sprite(
		(UINT)100,
		{0.0f,0.0f},
		false,
		false)
{
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList) {

    SpriteBase* spriteCommon = SpriteBase::GetInstance();
    if (isInvisible_) {
        return;
    }

    ID3D12GraphicsCommandList* cmdList = spriteCommon->GetCmd();

    // ���_�o�b�t�@���Z�b�g
    cmdList->IASetVertexBuffers(0, 1, &vbView_);

    // �萔�o�b�t�@���Z�b�g
    cmdList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

    // �V�F�[�_���\�[�X�r���[���Z�b�g
    spriteCommon->SetGraphicsRootDescriptorTable(1, texNumber_);
    // �|���S���̕`��i4���_�Ŏl�p�`�j
    cmdList->DrawInstanced(4, 1, 0, 0);
}
