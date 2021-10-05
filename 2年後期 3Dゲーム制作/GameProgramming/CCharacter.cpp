#include"CCharacter.h"
#include"CTaskManager.h"

CCharacter::CCharacter()
: mTag(EZERO)
{
	mpModel = NULL;
	//�^�X�N���X�g�ɒǉ�
	CTaskManager::Get()->Add(this);
}

CCharacter::~CCharacter(){
	//�^�X�N���X�g����폜
	CTaskManager::Get()->Remove(this);
}

//�`�揈��
void CCharacter::Render(){
	mpModel->Render(mMatrix);
}