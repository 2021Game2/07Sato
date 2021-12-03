#include "CSceneTitle.h"
#include "CKey.h"
#include "CPlayer.h"
#include "CBullet.h"

void CSceneTitle::Init() {
	//�V�[���̐ݒ�
	mScene = ETITLE;
}

//�X�V�����̃I�[�o�[���C�h
void CSceneTitle::Update() {
		//CText::DrawString("TITLE", -200, 0, 50, 50);
		//CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//���̃V�[���̓Q�[��
			mScene = EGAME;
		}
		glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
		//CText::DrawString("Game Clear", -250, 0, 30, 30);
		//CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
}

//���̃V�[���̎擾
CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}
