﻿#include "FbxLoader.h"

#include <cassert>

const std::string FbxLoader::baseDirectory = "Resources/";


FbxLoader* FbxLoader::GetInstance()
{
    static FbxLoader instance;
    return &instance;
}

void FbxLoader::Initialize(ID3D12Device* device) {

    //再初期化チェック
    assert(fbxManager == nullptr);
    //引数からメンバ変数に代入
    this->device = device;
    //FBXマネージャの生成
    fbxManager = FbxManager::Create();
    //FBXマネージャの入出力設定
    FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
    fbxManager->SetIOSettings(ios);
    //FBXインポータの生成
    fbxImporter = FbxImporter::Create(fbxManager, "");
}

void FbxLoader::Finalize() {

    fbxImporter->Destroy();
    fbxManager->Destroy();
}

void FbxLoader::LoatModelFromFile(const string& modelName) {
    
    const string directoryPath = baseDirectory + modelName + "/";
    const string fileName = modelName + ".fbx";
    const string fullpath = directoryPath + fileName;

    if (!fbxImporter->Initialize(fullpath.c_str(), -1, fbxManager->GetIOSettings())) {
        assert(0);
    }
    //シーン生成
    FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");
    //ファイルからロードしたFBXの情報をシーンにインポート
    fbxImporter->Import(fbxScene);
}
