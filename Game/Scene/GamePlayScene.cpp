#include "GamePlayScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "TitleScene.h"

GamePlayScene::GamePlayScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
}

void GamePlayScene::Initialize() {
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	spriteCommon->LoadTexture(0, L"Resources/texture.png");
	spriteCommon->LoadTexture(1, L"Resources/house.png");

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Object3d::SetCamera(camera);

	//modelPost = Model::LoadFromOBJ("posuto");

	//objPost = Object3d::Create();

	//objPost->SetModel(modelPost);

	//objPost->SetPosition({ 0,100,0 });

	//objPost->Update();

	sprite2 = Sprite::Create(1, { 0,0 }, false, false);
	sprite2->SetPosition({ 500,500,0 });
	sprite2->TransferVertexBuffer();

	camera->SetTarget({ 0,0,-10 });
	camera->SetEye({ 0, 0, 0 });

#pragma endregion 描画初期化処理
}

void GamePlayScene::Finalize() {
	for (auto& sprite : sprites)
	{
		delete sprite;
	}
	//delete sprite;
	delete modelPost;
	delete objPost;
	delete camera;

}

void GamePlayScene::Update() {

	Input* input = Input::GetInstance();

	float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

	if (input->TriggerKey(DIK_SPACE)) {
		sprite2->SetPosition({ 0.0f,400.0f,0.0f });
		vy = 10.0f;
	}
	float tempY = sprite2->GetPosition().y;

	vy -= gravity;
	tempY -= vy;

	sprite2->SetPosition({ 0, tempY, 0 });

	sprite2->Update();
	camera->Update();

	if (input->TriggerKey(DIK_RETURN)) {
		BaseScene* scene = new TitleScene(sceneManager_);
		sceneManager_->SetNextScene(scene);
	}
	// DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

void GamePlayScene::Draw() {
	//objPost->Draw();
	SpriteCommon::GetInstance()->PreDraw();
	sprite2->Draw();
	for (auto& sprite : sprites)
	{
		sprite->Draw();
	}
}
