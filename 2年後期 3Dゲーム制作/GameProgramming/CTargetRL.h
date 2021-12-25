#ifndef CTARGETRL_H
#define CTARGETRL_H

#include"CCharacter.h"
#include"CBullet.h"
#include"CCollider.h"
#include"CColliderTriangle.h"
#include"CEffect.h"

//�I,�ˌ��Ŕj�󂳂�A�X�R�A�����Z����
//���E�ړ�
class CTargetRL : public CCharacter {
private:
	int mMoveCount;

	int mHp;
public:

	//�R���C�_
	CCollider mCollider;
	CColliderTriangle mTri1;	//�v���C���[�ړ��j�Q�p
	CColliderTriangle mTri2;	//�v���C���[�ړ��j�Q�p

	CTargetRL(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
