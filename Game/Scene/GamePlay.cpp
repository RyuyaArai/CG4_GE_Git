#include "GamePlay.h"
#include "SceneManager.h"
#include "Input.h"
#include "DirectXBase.h"
#include "Title.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

GamePlay::GamePlay(SceneManager* sceneManager)
	:SceneBase(sceneManager)
{
}

void GamePlay::Initialize() {

	FbxObject3d::SetDevice(DirectXBase::GetInstance()->GetDev());
	FbxObject3d::CreateGraphicsPipeline();
	VariableInitialize();
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

	if (jump->isglide == true) {
		jump->fallSpeed = 0.2f;
	}

	if (jump->isJump == false) {
		jump->isJump = true;
	}
	else if (jump->isDouble == false) {
		jump->isDouble = true;
	}
	else {
		jump->isglide = true;
	}
		

	if (input->PushKey(DIK_SPACE)) {

	}

	// 座標操作
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {


		if (input->PushKey(DIK_UP)) {
		}
	}


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
	//objChr->Draw();
	fbxObject1->Draw(DirectXBase::GetInstance()->GetCmdList());
	Object3d::PostDraw();
	SpriteBase::GetInstance()->PreDraw();
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

	objPost->SetPosition({ -10,0,-5 });
	objChr->SetPosition({ +10,0,+5 });

	objPost->Update();
	objChr->Update();


	//fbxModel1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	//fbxObject1 = new FbxObject3d;
	//fbxObject1->Initialize();
	//fbxObject1->SetModel(fbxModel1);
	//fbxObject1->SetRotation()


}

void GamePlay::Create2D_object() {

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

void GamePlay::ChangeScene() {

	SceneBase* scene = new Title(sceneManager_);
	sceneManager_->SetNextScene(scene);
}

void GamePlay::ClassUpdate() {

	objPost->Update();
	objChr->Update();
	fbxObject1->Update();
	for (auto& sprite : sprites)
	{
		sprite->Update();
	}
	camera->Update();

}

void GamePlay::SpriteLoadTex() {
	SpriteBase* spriteCommon = SpriteBase::GetInstance();
	spriteCommon->LoadTexture(0, L"Resources/texture.png");
	spriteCommon->LoadTexture(1, L"Resources/house.png");

}

void GamePlay::CameraCreateSet() {
	camera = new DebugCamera(WindowsAPP::window_width, WindowsAPP::window_height);

	Object3d::SetCamera(camera);
	FbxObject3d::SetCamera(camera);

	camera->SetTarget({ 0,2.5f,0 });
	camera->SetDistance(8.0f);
	camera->SetEye({ 0, 0, 0 });
}

void GamePlay::VariableInitialize() {
	jump->isJump = false;
	jump->isDouble = false;
	jump->isglide = false;
	jump->fallSpeed = 2.0f;
}
