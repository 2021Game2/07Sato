#ifndef CTARGET_H
#define CTARGET_H

#include"CCharacter.h"
#include"CBullet.h"
#include"CTaskManager.h"
#include"CColliderTriangle.h"
#include"CEffect.h"

//�I,�ˌ��Ŕj�󂳂�A�X�R�A�����Z����
class CTarget : public CCharacter{
private:


public:

	CTarget();

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
