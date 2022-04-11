#include "SceneManager.h"

void SceneManager::Update()
{
	if (nextScene_) {
		//旧シーンの終了
		if (scene_) {
			scene_->Finalize();
			delete scene_;
		}
		scene_ = nextScene_;
		nextScene_ = nullptr;

		scene_->Initialize();
	}
	scene_->Update();
}

void SceneManager::Draw()
{
	scene_->Draw();
}
