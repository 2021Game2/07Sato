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

public:

	//�R���C�_
	CCollider mCollider;
	CColliderTriangle mTri1;
	CColliderTriangle mTri2;

	CTargetRL(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
