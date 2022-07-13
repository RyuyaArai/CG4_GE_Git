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

    // 頂点バッファをセット
    cmdList->IASetVertexBuffers(0, 1, &vbView_);

    // 定数バッファをセット
    cmdList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

    // シェーダリソースビューをセット
    spriteCommon->SetGraphicsRootDescriptorTable(1, texNumber_);
    // ポリゴンの描画（4頂点で四角形）
    cmdList->DrawInstanced(4, 1, 0, 0);
}
