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
#include"CMoveBlock.h"
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

int CSceneGame::mScore = 0;

bool CSceneGame::mStartFlag = true;


	//CSound Bgm;

	CSound Fire;
	CSound Bomb;
	CSound Reloaded;
	CSound ScoreAdd;
	CSound Start;
	CSound Noise;	//�쓮��
	CSound Jump;
	CSound Step;
	CSound Clear;
	CSound Faild;
	CSound Moving;

void CSceneGame::Init()
{
	mScene = EGAME;

	//Bgm.Load("bgm.wav");
	//Bgm.Repeat();

	//SE
	Fire.Load("Fire.wav");
	Bomb.Load("Bomb.wav");
	Reloaded.Load("Reloaded.wav");
	ScoreAdd.Load("ScoreAdd.wav");
	Start.Load("Start.wav");
	Noise.Load("Noise.wav");
	Jump.Load("Jump.wav");
	Step.Load("Step.wav");
	Clear.Load("Clear.wav");
	Faild.Load("Faild.wav");
	Moving.Load("Moving.wav");

	Noise.Repeat();


	//���f���t�@�C���̓���
	mBackGround.Load("Load.obj", "Load.mtl");

	mModel.Load("Character.obj", "Character.mtl");
	mPillar.Load("Pillar.obj","Pillar.mtl");
	mBarricade.Load("barricade.obj", "barricade.mtl");
	mBlock.Load("Block.obj", "Block.mtl");
	mDamageBlock.Load("DamageBlock.obj", "DamageBlock.mtl");
	mTarget.Load("Target.obj", "Target.mtl");
	mGoal.Load("Goal.obj", "Goal.mtl");
	mTargetTouch.Load("ScoreBlock.obj", "ScoreBlock.mtl");
	//mGun.Load("Gun.obj", "Gun.mtl");

	CMatrix matrix;
	matrix.Print();

	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.0f);

	//�v���C���[
	mPlayer.mpModel = &mModel;
	mPlayer.mScale = CVector(0.5f, 0.5f, 0.5f);
	mPlayer.mPosition = CVector(0.0f, 10.0f, -215.0f) * mBackGroundMatrix;
	mPlayer.mRotation = CVector(0.0f, 0.0f, 0.0f);



	//�I
	new CTarget(&mTarget,
		CVector(5.0f, 5.0f, -50.0f) * mBackGroundMatrix,
		CVector(0.0f,90.0f,0.0f),
		CVector(1.0f, 1.0f, 1.0f));

	//���E�ɓ����I
	new CTargetRL(&mTarget,
		CVector(-20.0f, 50.0f, 30.0f) * mBackGroundMatrix,
		CVector(0.0f, 90.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f));

	//�㉺�ɓ����I
	new CTargetUD(&mTarget,
		CVector(-30.0f, 50.0f, -90.0f) * mBackGroundMatrix,
		CVector(0.0f, 90.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f));

	//�ڐG�^
	new CTargetTouch(&mTargetTouch,
		CVector(0.0f, 7.0f, 50.0f) * mBackGroundMatrix,
		CVector(0.0f,0.0f,0.0f),
		CVector(3.0f, 3.0f, 3.0f));

	//�u���b�N
	new CBlock(&mBlock, 
		CVector(0.0f, 30.0f, 0.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(3.0f, 3.0f, 3.0f));

	//�u���b�N
	new CBlock(&mBlock,
		CVector(40.0f, 0.0f, 60.0f) * mBackGroundMatrix,
		CVector(-60.0f, 0.0f, 0.0f),
		CVector(3.0f, 2.0f, 3.0f));

	//�����u���b�N
	new CMoveBlock(&mBlock,
		CVector(-50.0f, 40.0f, -40.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(3.0f, 3.0f, 3.0f));

	//�_���[�W���󂯂�u���b�N
	new CDamageBlock(&mDamageBlock,
		CVector(0.0f, 20.0f, -150.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(2.0f, 2.0f, 2.0f));
	new CDamageBlock(&mDamageBlock,
		CVector(20.0f, 20.0f, -150.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(2.0f, 2.0f, 2.0f));
	new CDamageBlock(&mDamageBlock,
		CVector(0.0f, 5.0f, -150.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(2.0f, 2.0f, 2.0f));
	new CDamageBlock(&mDamageBlock,
		CVector(20.0f, 5.0f, -150.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(2.0f, 2.0f, 2.0f));
	new CDamageBlock(&mDamageBlock,
		CVector(0.0f, 20.0f, -100.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(2.0f, 2.0f, 2.0f));

	//�S�[��
	new CGoal(&mGoal,
		CVector(45.0f, 1.0f, 900.0f) * mBackGroundMatrix,
		CVector(0.0f, 90.0f, 0.0f),
		CVector(20.0f, 20.0f, 20.0f));


	mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);


	//�J�����ʒu
	mCamX = 0.0f;
	mCamY = 13.0f;
	mCamZ = -15.0f;
	
	mFcamX = 0.0f;
	mFcamY = 8.5f;
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

	//�X�^�[�g���ꎞ�X�g�b�v
	if (mStartFlag == true) {
		if (CKey::Once(VK_SPACE)) {
			mStartFlag = false;
		}
	}

	//�S�[�����X�R�A�\��
	/*if (CGoal::mTouchGoal == true) {
		mClearScore = mScore;
		mClearTime = CPlayer::mTime;
		mResultTimer--;
	}*/

	//�Q�[���I�[�o�[��
	if (CPlayer::mPlayerHp == 0) {
		if (CKey::Once('R')) {
			CPlayer::mPlayerHp = 5;
			Init();

			mStartFlag = true;
		}
		if (CKey::Once('T')) {
			CPlayer::mPlayerHp = 5;
			mStartFlag = true;
		}
	}

	//�`��
	CTaskManager::Get()->Render();
	CCollisionManager::Get()->Render();
}

//���̃V�[���̎擾
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}