#include"CSceneResult.h"
#include"CText.h"
#include"CUtil.h"

void CSceneResult::Init() {
	mScene = ERESULT;
}

void CSceneResult::Update() {

}

//次のシーンの取得
CScene::EScene CSceneResult::GetNextScene() {
	return mScene;
}