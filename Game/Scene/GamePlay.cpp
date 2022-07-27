#include "GamePlay.h"
#include "SceneManager.h"
#include "Input.h"
#include "DirectXBase.h"
#include "Title.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "Noise.h"

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
	delete modelblock;
	delete modelChr;
	delete objChr;
	delete objblock;
	delete camera;
	//delete fbxModel1;
	//delete fbxObject1;

}

void GamePlay::Update() {
	Input* input = Input::GetInstance();


	if (input->TriggerKey(DIK_0)) {

		OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
	}


	if (objChr->GetPosition().y > 0.0f) {
		XMFLOAT3 chrpos = objChr->GetPosition();

		if (jump.isglide == true) {
			if (jump.fallSpeed <= 0.2f) {
				jump.fallSpeed += 0.1f;
			}
			if (jump.fallSpeed >= 0.2f) {
				jump.fallSpeed -= 0.02f;
			}
		}
		else {
			jump.fallSpeed += 0.2f;

		}
		objChr->SetPosition({ chrpos.x,chrpos.y - jump.fallSpeed,chrpos.z });

	}
	
	if (objChr->GetPosition().y <= 0.0f) {
		objChr->SetPosition({ objChr->GetPosition().x, 0, objChr->GetPosition().z });
		jump.isJump = false;
		jump.isDouble = false;
		jump.isglide = false;
		jump.fallSpeed = 0.0f;
	}

	if (input->TriggerKey(DIK_SPACE)) {
		XMFLOAT3 chrpos = objChr->GetPosition();

		if (jump.isglide == false && jump.isDouble == true) {
			jump.isglide = true;
		}
		else if (jump.isglide == true) {
			jump.isglide = false;
		}

		if (jump.isDouble == false && jump.isJump == true) {
			jump.isDouble = true;
			jump.fallSpeed -= 6.0f;
		}

		if (jump.isJump == false) {
			jump.isJump = true;
			jump.fallSpeed -= 6.0f;
		}

		objChr->SetPosition({ chrpos.x,chrpos.y - jump.fallSpeed,chrpos.z });

	}


	// 座標操作
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) ||
		input->PushKey(DIK_D) || input->PushKey(DIK_A)) {

		float move = 3.0;
		XMFLOAT3 chrpos = objChr->GetPosition();

		if (input->PushKey(DIK_W)) {
			chrpos.z += move;
			if (jump.isglide == true) {
				objChr->SetRotation({ 20,0,0 });
			}
		}
		if (input->PushKey(DIK_S)) {
			chrpos.z -= move;
			if (jump.isglide == true) {
				objChr->SetRotation({ -20,0,0 });
			}
		}
		if (input->PushKey(DIK_D)) {
			chrpos.x += move;
			if (jump.isglide == true) {
				objChr->SetRotation({ 0,0,-20 });
			}
		}
		if (input->PushKey(DIK_A)) {
			chrpos.x -= move;
			if (jump.isglide == true) {
				objChr->SetRotation({ 0,0,20 });
			}
		}

		objChr->SetPosition(chrpos);
		if (jump.isglide == false) {
			objChr->SetRotation({ 0,0,0 });
		}
	}
	else {
		objChr->SetRotation({ 0,0,0 });
	}

	ClassUpdate();

	if (input->TriggerKey(DIK_RETURN)) {
		/*	Noise* noise = new Noise();
			noise->SampleOctavePerlinNoise(5.0f, 2.0f);*/

		ChangeScene();
	}
}

void GamePlay::Draw() {
	Object3d::PreDraw(DirectXBase::GetInstance()->GetCmdList());
	objblock->Draw();
	objChr->Draw();
	//fbxObject1->Draw(DirectXBase::GetInstance()->GetCmdList());
	Object3d::PostDraw();
	SpriteBase::GetInstance()->PreDraw();
	for (auto& sprite : sprites)
	{
		sprite->Draw();
	}
}

void GamePlay::Create3D_object() {

	modelblock = ObjModel::LoadFromOBJ("block");
	modelChr = ObjModel::LoadFromOBJ("chr_sword");

	objblock = Object3d::Create();
	objChr = Object3d::Create();

	objblock->SetModel(modelblock);
	objChr->SetModel(modelChr);

	objblock->SetPosition({ 0,-2,0 });
	objChr->SetPosition({ +10,50,+5 });

	XMFLOAT3 scale = { 50.0,1.0,50.0 };
	objblock->SetScale(scale);

	objblock->Update();
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

	objblock->Update();
	objChr->Update();
	//fbxObject1->Update();
	for (auto& sprite : sprites)
	{
		sprite->Update();
	}
	CameraUpdate();
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

	camera->SetTarget({ 0,0,0 });
	camera->SetDistance(20.0f);
	camera->SetEye({ 0,0,0 });
}

void GamePlay::VariableInitialize() {
	jump.isJump = false;
	jump.isDouble = false;
	jump.isglide = false;
	jump.fallSpeed = 2.0f;
}

void GamePlay::CameraUpdate() {

	XMFLOAT3 chrpos = objChr->GetPosition();
	camera->SetTarget({ chrpos.x,chrpos.y + 40.0f,chrpos.z - 60.0f });
	camera->SetDistance(20.0f);
	camera->SetEye({ chrpos.x,chrpos.y,chrpos.z });
	camera->Update();
}