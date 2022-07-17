#include "Title.h"
#include "SceneManager.h"
#include "Input.h"
#include "DirectXBase.h"
#include "GamePlay.h"

Title::Title(SceneManager* sceneManager)
	:SceneBase(sceneManager)
{
}

void Title::Initialize() {


}

void Title::Finalize() {
}

void Title::Update() {
	Input* input = Input::GetInstance();
	if (input->PushKey(DIK_SPACE))     // スペースキーが押されていたら
	{
		// 画面クリアカラーの数値を書き換える
		//clearColor[1] = 1.0f;
	}
	if (input->TriggerKey(DIK_RETURN)) {
		SceneBase* scene = new GamePlay(sceneManager_);
		sceneManager_->SetNextScene(scene);
	}
}

void Title::Draw() {
	for (auto& sprite : sprites)
	{
		sprite->Draw();
	}
}
