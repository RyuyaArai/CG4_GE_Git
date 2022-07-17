#pragma once
#include"SceneBase.h"
#include"Sprite.h"
#include"Object3d.h"
#include"FbxObject3d.h"
#include"DebugCamera.h"
#include"PostEffect.h"


class DirectXBase;

class GamePlay : public SceneBase {
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
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
private:
	//更新
	void ChangeScene();
	void ClassUpdate();

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
};

