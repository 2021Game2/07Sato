#ifndef CSCENERESULT_H
#define CSCENERESULT_H
#include"CScene.h"
#include"CSceneGame.h"

class CSceneResult : public CScene{
private:
	int mScores[10];
	float mTimes[10];


public:

	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//���̃V�[���̎擾
	EScene GetNextScene();
};
#endif