#ifndef CTARGET_H
#define CTARGET_H

#include"CCharacter.h"
#include"CBullet.h"
#include"CCollider.h"
#include"CColliderTriangle.h"
#include"CEffect.h"
#include"CSceneGame.h"

//�I,�ˌ��Ŕj�󂳂�A�X�R�A�����Z����
class CTarget : public CCharacter{
public:

	int mHp;

	//�R���C�_
	CCollider mCollider;
	CColliderTriangle mTri1;	//�v���C���[�ړ��j�Q�p
	CColliderTriangle mTri2;	//�v���C���[�ړ��j�Q�p

	CTarget(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
