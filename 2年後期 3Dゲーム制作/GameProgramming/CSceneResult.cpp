#include"CSceneResult.h"
#include"CText.h"
#include"CUtil.h"

void CSceneResult::Init() {
	mScene = ERESULT;
}

void CSceneResult::Update() {

}

//���̃V�[���̎擾
CScene::EScene CSceneResult::GetNextScene() {
	return mScene;
}