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
#include"CAim.h"

/*�v���C���[�N���X
�@�L�����N�^�N���X���p��*/
class CPlayer : public CCharacter,CAim{
private:
	bool mJump;		//�W�����v���ł��邩�̔���
	int mJumpTimer;	//�W�����v�̃N�[���^�C��

	int mStep;	//�u�Ԉړ��Ɋ|����t���[����
	int mStepRecharge; //�u�Ԉړ��̃N�[���^�C��

	int mReloadTime;	//�e�̃����[�h����

	float mSpeedX;	//���E�����x
	float mSpeedY;	//�㉺�����x
	float mSpeedZ;	//�O������x

public:

	static int mPlayerHp;	//�̗�

	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2; //�����R���C�_
	CColliderLine mLine3; //�����R���C�_
	CColliderLine mLine4; //�����R���C�_
	CColliderLine mLine5; //�����R���C�_
	CCollider mCollider; //�{�̗p�R���C�_

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