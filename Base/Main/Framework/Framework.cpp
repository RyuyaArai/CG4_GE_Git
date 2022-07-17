#include "Framework.h"
#include "FbxLoader.h"

void Framework::Run() {
	Initialize();

	while (true)  // ゲームループ
	{
		Update();
		if (GetGameloopEndReqest() == true) {
			break;
		}
		Draw();
	}

	Finalize();
}

void Framework::Initialize() {

#pragma region WindowsAPI初期化

	winApp_ = new WindowsAPP();
	winApp_->Initialize();

	MSG msg{};  // メッセージ

#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理


	dxCommon_ = DirectXBase::GetInstance();
	dxCommon_->Initialize(winApp_);

	input_ = Input::GetInstance();
	input_->Initialize(winApp_);
	
	Sprite::StaticInitialize(
		DirectXBase::GetInstance()->GetDev(),
		DirectXBase::GetInstance()->GetCmdList(),
		winApp_->window_width,
		winApp_->window_height
);
	postEffect_ = new PostEffect();
	postEffect_->Initialize();

	Object3d::StaticInitialize(dxCommon_->GetDev());
	
	sceneManager_ = new SceneManager();

	FbxLoader::GetInstance()->Initialize(dxCommon_->GetDev());

#pragma endregion DirectX初期化処理

}

void Framework::Finalize() {
	// XAudio2解放
// xAudio2.Reset();
 // 音声データ解放
// SoundUnload(&soundData1);
	FbxLoader::GetInstance()->Finalize();

#pragma region WindowsAPI後始末
	winApp_->Finalize();
#pragma endregion WindowsAPI後始末
	delete winApp_;
}

void Framework::Update() {
#pragma region ウィンドウメッセージ処理
	if (winApp_->ProcessMessage()) {
		gameloopEndReqest_ = true;
		return;
	}
#pragma endregion ウィンドウメッセージ処理
	input_->Update();
	sceneManager_->Update();
}

void Framework::Draw() {
	//postEffect_->PreDrawScene(DirectXBase::GetInstance()->GetCmdList());
	sceneManager_->Draw();
	//postEffect_->PostDrawScene(DirectXBase::GetInstance()->GetCmdList());
	dxCommon_->PreDraw();
	sceneManager_->Draw();

	//postEffect_->Draw(DirectXBase::GetInstance()->GetCmdList());

	dxCommon_->PostDraw();
}
