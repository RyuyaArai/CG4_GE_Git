#pragma once
#include"SceneBase.h"
#include"Sprite.h"
#include"Object3d.h"
#include"FbxObject3d.h"
#include"DebugCamera.h"


class DirectXBase;

class GamePlay : public SceneBase {

private:
	struct Jump {
		bool isJump;
		bool isDouble;
		bool isglide;
		float fallSpeed;
	};

public:
	GamePlay(SceneManager* sceneManager);
	
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
	void VariableInitialize();
private:
	//更新
	void ChangeScene();
	void ClassUpdate();

private:
	static const int MaxModel = 30;

	enum {
		post,
		chara
	};

	ObjModel* objModel[MaxModel] = { nullptr };
	Object3d* obj3dObj[MaxModel] = { nullptr };

private:

	Sprite* sprite = nullptr;

	ObjModel* modelPost = nullptr;
	ObjModel* modelChr = nullptr;
	
	Object3d* objPost = nullptr;
	Object3d* objChr = nullptr;
	
	FbxModel* fbxModel1 = nullptr;
	
	FbxObject3d* fbxObject1 = nullptr;
	
	DebugCamera* camera = nullptr;
	std::vector<Sprite*> sprites;

	Jump* jump = nullptr;

};

