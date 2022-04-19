#pragma once
#include"BaseScene.h"
#include"Sprite.h"
#include"Object3d.h"
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
	Sprite* sprite = nullptr;
	Sprite* sprite2 = nullptr;
	Model* modelPost = nullptr;
	Object3d* objPost = nullptr;
	DebugCamera* camera = nullptr;
	std::vector<Sprite*> sprites;
private:
	float gravity = 9.8f / 60.0f;
	float vy = 10.0f;

};

