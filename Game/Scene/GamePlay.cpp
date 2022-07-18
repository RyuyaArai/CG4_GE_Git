#include "GamePlay.h"
#include "SceneManager.h"
#include "Input.h"
#include "DirectXBase.h"
#include "Title.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

using namespace DirectX;

GamePlay::GamePlay(SceneManager* sceneManager)
	:SceneBase(sceneManager)
{
}

void GamePlay::Initialize() {

	FbxObject3d::SetDevice(DirectXBase::GetInstance()->GetDev());
	FbxObject3d::CreateGraphicsPipeline();
	CameraCreateSet();
	SpriteLoadTex();
	Create2D_object();
	Create3D_object();
	
}

void GamePlay::Finalize() {
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

void GamePlay::Update() {
	Input* input = Input::GetInstance();

	
	if (input->TriggerKey(DIK_0)) {

		OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
	}


	if (input->PushKey(DIK_SPACE)) {
		fbxObject1->PlayAnimation();

	}

	// 座標操作
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {


		if (input->PushKey(DIK_UP)) {
		}
	}
	static XMVECTOR lightDir = { 0,1,5,0 };

	if (input->PushKey(DIK_W)) { lightDir.m128_f32[1] += 1.0f; }
	else if (input->PushKey(DIK_S)) { lightDir.m128_f32[1] -= 1.0f; }
	if (input->PushKey(DIK_D)) { lightDir.m128_f32[0] += 1.0f; }
	else if (input->PushKey(DIK_A)) { lightDir.m128_f32[0] -= 1.0f; }
	light->SetLightDir(lightDir);


	if (input->PushKey(DIK_D) || input->PushKey(DIK_A)) {

	}

	ClassUpdate();
	
	if (input->TriggerKey(DIK_RETURN)) {
		ChangeScene();
	}
}

void GamePlay::Draw() {
	Object3d::PreDraw(DirectXBase::GetInstance()->GetCmdList());
	//objPost->Draw();
	objChr->Draw();
	//fbxObject1->Draw(DirectXBase::GetInstance()->GetCmdList());
	Object3d::PostDraw();
	for (auto& sprite : sprites)
	{
		sprite->Draw();
	}
}

void GamePlay::Create3D_object() {

	modelPost = ObjModel::LoadFromOBJ("posuto");
	modelChr = ObjModel::LoadFromOBJ("chr_sword");

	objPost = Object3d::Create();
	objChr = Object3d::Create();

	objPost->SetModel(modelPost);
	objChr->SetModel(modelChr);

	objPost->SetPosition({ 0,0,0 });
	objChr->SetPosition({ 0,0,0 });

	objPost->Update();
	objChr->Update();


	fbxModel1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	fbxObject1 = new FbxObject3d;
	fbxObject1->Initialize();
	fbxObject1->SetModel(fbxModel1);
	fbxObject1->SetRotation({ 0,90,0 });

	light = Light::Create();
	light->SetLightColor({ 1,1,1 });
	Object3d::SetLight(light);

}

void GamePlay::Create2D_object() {
	


}

void GamePlay::ChangeScene() {

	SceneBase* scene = new Title(sceneManager_);
	sceneManager_->SetNextScene(scene);
}

void GamePlay::ClassUpdate() {

	objPost->Update();
	objChr->Update();
	fbxObject1->Update();
	light->Update();

	for (auto& sprite : sprites)
	{
	}
	camera->Update();

}

void GamePlay::SpriteLoadTex() {
	Sprite::LoadTexture(100, L"Resources/white1x1.png");

}

void GamePlay::CameraCreateSet() {
	camera = new DebugCamera(WindowsAPP::window_width, WindowsAPP::window_height);

	Object3d::SetCamera(camera);
	FbxObject3d::SetCamera(camera);

	camera->SetTarget({ 0,2.5f,0 });
	camera->SetDistance(100.0f);
	camera->SetEye({ 0, 0, 0 });
}
