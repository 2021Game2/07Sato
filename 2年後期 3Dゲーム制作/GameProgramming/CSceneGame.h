#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include"CScene.h"
#include"CModel.h"
#include"CCharacter.h"
#include"CPlayer.h"
#include"CColliderTriangle.h"
#include"CColliderMesh.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
private:

	float mCamX;
	float mCamY;
	float mCamZ;

	float mFcamX;
	float mFcamY;
	float mFcamZ;

public:
	//���f���N���X�̃C���X�^���X�쐬
	CModel mModel;

	CMatrix mBackGroundMatrix;
	//���f������R���C�_�𐶐�
	CColliderMesh mColliderMesh;


	CModel mBackGround; //�w�i
	CModel mPillar;
	CModel mBarricade;
	CModel mTarget;
	CModel mTargetTouch;
	CModel mGoal;

	CPlayer mPlayer;

	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};

#endif
