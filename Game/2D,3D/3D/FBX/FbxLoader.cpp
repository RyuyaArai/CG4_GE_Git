﻿#include "FbxLoader.h"

#include <cassert>

using namespace DirectX;


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
    
    //モデル生成
    FbxModel* F_Model = new FbxModel();
    F_Model->name = modelName;
    //FBXノードの数を取得
    int nodeCount = fbxScene->GetNodeCount();
    //あらかじめ必要数分のメモリを確保することでアドレスがずれるのを予防
    F_Model->nodes.reserve(nodeCount);
    //ルートノードから順に解析してモデルに流し込む
    ParseNodeRecursive(F_Model, fbxScene->GetRootNode());
    //FBXシーン開放
    fbxScene->Destroy();
}

void FbxLoader::ParseNodeRecursive(FbxModel* F_Model, FbxNode* fbxNode, Node* parent) {
    //モデルにノードを追加()
    F_Model->nodes.emplace_back();
    Node& node = F_Model->nodes.back();
    //ノード名を取得
    string name = fbxNode->GetName();
    //FBXノードのローカル移動情報
    FbxDouble3 rotation = fbxNode->LclRotation.Get();
    FbxDouble3 scaling = fbxNode->LclScaling.Get();
    FbxDouble3 translation = fbxNode->LclTranslation.Get();
    //形式変換して代入
    node.rotation = { (float)rotation[0],(float)rotation[1],(float)rotation[2],0.0f };
    node.scaling = { (float)scaling[0],(float)scaling[1],(float)scaling[2],0.0f };
    node.translation = { (float)translation[0],(float)translation[1],(float)translation[2],1.0f };
    //回転角をDegree(度)からラジアンに変換
    node.rotation.m128_f32[0] = XMConvertToRadians(node.rotation.m128_f32[0]);
    node.rotation.m128_f32[1] = XMConvertToRadians(node.rotation.m128_f32[1]);
    node.rotation.m128_f32[2] = XMConvertToRadians(node.rotation.m128_f32[2]);
    //スケール、回転、平行移動行列の計算
    XMMATRIX matScaling, matRotation, matTranslation;
    matScaling = XMMatrixScalingFromVector(node.scaling);
    matRotation = XMMatrixRotationRollPitchYawFromVector(node.rotation);
    matTranslation = XMMatrixTranslationFromVector(node.translation);
    //ローカル変形行列の計算
    node.transform = XMMatrixIdentity();
    node.transform *= matScaling;
    node.transform *= matRotation;
    node.transform *= matTranslation;
    //FBXノードの情報を解析してノードに記録()
    //グローバル変形行列の計算
    node.globalTransform = node.transform;
    if (parent) {
        node.parent = parent;
        //親の変形を乗算
        node.globalTransform *= parent->globalTransform;
    }
    //FBXノードのメッシュ情報を解析()
    
    //子ノードに対して再帰呼び出し
    for (int i = 0; i < fbxNode->GetChildCount(); i++) {
        ParseNodeRecursive(F_Model, fbxNode->GetChild(i), &node);
    }
}
