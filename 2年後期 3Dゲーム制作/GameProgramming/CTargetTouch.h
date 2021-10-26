#ifndef CTARGETTOUCH_H
#define CTARGETTOUCH_H

#include"CCharacter.h"
#include"CBullet.h"
#include"CCollider.h"
#include"CColliderTriangle.h"
#include"CEffect.h"


//�v���C���[�̐ڐG�Ŕj�󂳂�A�X�R�A�����Z����
class CTargetTouch : public CCharacter {
public:

	//�O�p�R���C�_
	CCollider mSphere;

	CTargetTouch(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif