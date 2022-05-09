#pragma once
#include"BaseScene.h"
#include"Sprite.h"
#include"Object3d.h"
#include"FbxObject3d.h"
#include"DebugCamera.h"


class DirectXCommon;

class GamePlayScene : public BaseScene {
public:
	GamePlayScene(SceneManager* sceneManager);
	
	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;
private:
	//初期化処理
	void Create3D_object();
	void Create2D_object();
	void SpriteLoadTex();
	void CameraCreateSet();
private:
	//更新
	void ChangeScene();
	void ClassUpdate();

private:
	Sprite* sprite = nullptr;

	Model* modelPost = nullptr;
	Model* modelChr = nullptr;
	
	Object3d* objPost = nullptr;
	Object3d* objChr = nullptr;
	
	FbxModel* fbxModel1 = nullptr;
	
	FbxObject3d* fbxObject1 = nullptr;
	
	DebugCamera* camera = nullptr;
	std::vector<Sprite*> sprites;
};

