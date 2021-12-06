#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�[�N���X�̃C���N���[�h
#include"CCharacter.h"
//�e�N���X�̃C���N���[�h
#include"CBullet.h"
#include"CTaskManager.h"
#include"CColliderLine.h"
#include"CColliderTriangle.h"
#include"CEffect.h"

/*�v���C���[�N���X
�@�L�����N�^�N���X���p��*/
class CPlayer : public CCharacter{
private:
	bool mJump;		//�W�����v���ł��邩�̔���
	int mJumpTimer;	//�W�����v�̃N�[���^�C��

	int mStep;	//�u�Ԉړ��Ɋ|����t���[����
	int mStepRecharge; //�u�Ԉړ��̃N�[���^�C��

	int mReloadTime;	//�e�̃����[�h����
	int mNotHit;	//�_���[�W�㖳�G����

	bool mFaildSound; //�Q�[���I�[�o�[�������Đ�����

	float mBeforMouseX;	//���O�}�E�X�ʒu
	float mBeforMouseY;
	float mMouseMoveX;	//�}�E�X�ړ���
	float mMouseMoveY;
	float mMouseSpeedX;	//�}�E�X���x
	float mMouseSpeedY;

public:

	static int mPlayerHp;	//�̗�

	static float mSpeedX;	//���E�����x
	static float mSpeedY;	//�㉺�����x
	static float mSpeedZ;	//�O������x


	static int mScore;

	static float mTime;
	bool mTimeCount;

	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2; //�����R���C�_
	CColliderLine mLine3; //�����R���C�_
	CCollider mCollider; //�{�̗p�R���C�_

	CColliderLine mSearchLine; //�u�Ԉړ� ������~�p

	CPlayer();
	//�X�V����
	void Update();

	//�Փˏ���
	void Collision(CCollider *m, CCollider *o);

	//�`�揈��
	void Render();

	//�Փˏ���
	void TaskCollision();

};

#endif