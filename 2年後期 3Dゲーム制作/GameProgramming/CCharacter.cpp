#include"CCharacter.h"
#include"CTaskManager.h"

CCharacter::CCharacter()
: mTag(EZERO)
{
	mpModel = NULL;
	//タスクリストに追加
	CTaskManager::Get()->Add(this);
}

CCharacter::~CCharacter(){
	//タスクリストから削除
	CTaskManager::Get()->Remove(this);
}

//描画処理
void CCharacter::Render(){
	mpModel->Render(mMatrix);
}