#include "CSceneGame.h"
//OpenGL
#include"glut.h"
#include"CVector.h"
#include"CTriangle.h"
#include"CMatrix.h"
#include"CTransform.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CColliderTriangle.h"

#include"CPlayer.h"
#include"CTarget.h"
#include"CTargetRL.h"
#include"CTargetUD.h"
#include"CTargetTouch.h"
#include"CGoal.h"
#include"CBlock.h"
#include"CDamageBlock.h"
#include"CBillBoard.h"
#include"CSphere.h"
#include"CBarricade.h"
#include"CPillar.h"

#include"CInput.h"
#include"CKey.h"
#include"CCamera.h"
#include"CSound.h"

CVector mEye;

//CSound Bgm;
//CSound Se;

int CSceneGame::mScore;

void CSceneGame::Init() {

	//���f���t�@�C���̓���

	mBackGround.Load("Load Base.obj", "Load Base.mtl");

	mModel.Load("Character.obj", "Character.mtl");
	mPillar.Load("Pillar.obj","Pillar.mtl");
	mBarricade.Load("barricade.obj", "barricade.mtl");
	mTarget.Load("Target.obj", "Target.mtl");
	mGoal.Load("Goal.obj", "Goal.mtl");
	mTargetTouch.Load("ScoreBlock.obj", "ScoreBlock.mtl");
	//mGun.Load("Gun.obj", "Gun.mtl");

	//wav�ǂݍ���
	//Bgm.Load(".wav");

	CMatrix matrix;
	matrix.Print();

	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.0f);

	mPlayer.mpModel = &mModel;
	mPlayer.mScale = CVector(0.5f, 0.5f, 0.5f);
	mPlayer.mPosition = CVector(0.0f, 5.0f, -200.0f) * mBackGroundMatrix;
	mPlayer.mRotation = CVector(0.0f, 0.0f, 0.0f);


	new CTarget(&mTarget,
		CVector(5.0f, 5.0f, -50.0f) * mBackGroundMatrix,
		CVector(0.0f,90.0f,0.0f),
		CVector(1.0f, 1.0f, 1.0f));

	new CTargetTouch(&mTargetTouch,
		CVector(0.0f, 7.0f, 50.0f) * mBackGroundMatrix,
		CVector(),
		CVector(5.0f, 5.0f, 5.0f));

	new CTargetRL(&mTarget,
		CVector(-20.0f, 50.0f, 30.0f) * mBackGroundMatrix,
		CVector(0.0f, 90.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f));

	new CTargetUD(&mTarget,
		CVector(-30.0f, 50.0f, -90.0f) * mBackGroundMatrix,
		CVector(0.0f, 90.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f));

	new CGoal(&mGoal,
		CVector(0.0f, 1.0f, 350.0f) * mBackGroundMatrix,
		CVector(0.0f, 90.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f));


	mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);


	//�J�����ʒu
	mCamX = 0.0f;
	mCamY = 15.0f;
	mCamZ = -20.0f;
	
	mFcamX = 0.0f;
	mFcamY = 10.0f;
	mFcamZ = 50.0f;

}

void CSceneGame::Update() {

	CTaskManager::Get()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
	CTaskManager::Get()->TaskCollision();

	//���_1,���_2,���_3,�@���f�[�^�̍쐬
	CVector v0, v1, v2, n;
	//�@����������Őݒ�
	n.mX = 0.0f; n.mY = 1.0f; n.mZ = 0.0f;
	//���_1�̍��W��ݒ�
	v0.mX = 0.0f; v0.mY = 0.0f; v0.mZ = 0.5f;
	//���_2�̍��W��ݒ�
	v1.mX = 1.0f; v1.mY = 0.0f; v1.mZ = 0.0f;
	//���_3�̍��W��ݒ�
	v2.mX = 0.0f; v2.mY = 0.0f; v2.mZ = -0.5f;

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;	//���_,�����_,�����


	//���_�����߂�
	e = CVector(mCamX, mCamY, mCamZ) * mPlayer.mMatrix;
	//�����_�����߂�
	c = CVector(mFcamX, mFcamY, mFcamZ) * mPlayer.mMatrix;
	//����������߂�
	u = CVector(0, 1, 0);

	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	mBackGround.Render();

	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();

	//�`��
	CTaskManager::Get()->Render();
	CCollisionManager::Get()->Render();
}