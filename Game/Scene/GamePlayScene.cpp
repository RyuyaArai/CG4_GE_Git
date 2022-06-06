#include "GamePlayScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "TitleScene.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

GamePlayScene::GamePlayScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
}

void GamePlayScene::Initialize() {

	FbxObject3d::SetDevice(DirectXCommon::GetInstance()->GetDev());
	FbxObject3d::CreateGraphicsPipeline();
	CameraCreateSet();
	SpriteLoadTex();
	Create2D_object();
	Create3D_object();
	
}

void GamePlayScene::Finalize() {
	for (auto& sprite : sprites)
	{
		delete sprite;
	}
	//delete sprite;
	delete modelPost;
	delete modelChr;
	delete objChr;
	delete objPost;
	delete camera;
	delete fbxModel1;
	delete fbxObject1;

}

void GamePlayScene::Update() {
	Input* input = Input::GetInstance();

	
	if (input->TriggerKey(DIK_0)) {

		OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
	}


	if (input->PushKey(DIK_SPACE)) {
		fbxObject1->PlayAnimation();

	}

	// 座標操作
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {

	}


	if (input->PushKey(DIK_D) || input->PushKey(DIK_A)) {

	}

	ClassUpdate();
	
	if (input->TriggerKey(DIK_RETURN)) {
		ChangeScene();
	}
}

void GamePlayScene::Draw() {
	Object3d::PreDraw(DirectXCommon::GetInstance()->GetCmdList());
	//objPost->Draw();
	//objChr->Draw();
	fbxObject1->Draw(DirectXCommon::GetInstance()->GetCmdList());
	Object3d::PostDraw();
	SpriteCommon::GetInstance()->PreDraw();
	for (auto& sprite : sprites)
	{
		sprite->Draw();
	}
}

void GamePlayScene::Create3D_object() {

	modelPost = Model::LoadFromOBJ("posuto");
	modelChr = Model::LoadFromOBJ("chr_sword");

	objPost = Object3d::Create();
	objChr = Object3d::Create();

	objPost->SetModel(modelPost);
	objChr->SetModel(modelChr);

	objPost->SetPosition({ -10,0,-5 });
	objChr->SetPosition({ +10,0,+5 });

	objPost->Update();
	objChr->Update();


	fbxModel1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	fbxObject1 = new FbxObject3d;
	fbxObject1->Initialize();
	fbxObject1->SetModel(fbxModel1);


}

void GamePlayScene::Create2D_object() {

	//Sprite* sprite = Sprite::Create(0, { 0,0, }, false, false);
	//sprites.push_back(sprite);
	//sprite->SetPosition({ 500,300,0 });

	//for (int i = 0; i < 20; i++) {
	//	int texNum = rand() % 2;

	//	sprite = Sprite::Create(texNum, { 0,0 }, false, false);

	//	sprite->SetPosition({ (float)(rand() % 1280),(float)(rand() % 720),0 });

	//	//sprite->SetRotation((float)(rand() % 360));

	//	sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });

	//	sprite->TransferVertexBuffer();

	//	sprites.push_back(sprite);
	//	//sprite->SetPosition({ 500,300,0 });

	//}
}

void GamePlayScene::ChangeScene() {

	BaseScene* scene = new TitleScene(sceneManager_);
	sceneManager_->SetNextScene(scene);
}

void GamePlayScene::ClassUpdate() {

	objPost->Update();
	objChr->Update();
	fbxObject1->Update();
	for (auto& sprite : sprites)
	{
		sprite->Update();
	}
	camera->Update();

}

void GamePlayScene::SpriteLoadTex() {
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	spriteCommon->LoadTexture(0, L"Resources/texture.png");
	spriteCommon->LoadTexture(1, L"Resources/house.png");

}

void GamePlayScene::CameraCreateSet() {
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);

	Object3d::SetCamera(camera);
	FbxObject3d::SetCamera(camera);

	camera->SetTarget({ 0,0,0 });
	camera->SetDistance(30.0f);
	camera->SetEye({ 0, 0, 0 });
}
