#include"CSceneResult.h"
#include"CText.h"
#include"CUtil.h"

void CSceneResult::Init() {
	mScene = ERESULT;
}

void CSceneResult::Update() {

}

//Ÿ‚ÌƒV[ƒ“‚Ìæ“¾
CScene::EScene CSceneResult::GetNextScene() {
	return mScene;
}