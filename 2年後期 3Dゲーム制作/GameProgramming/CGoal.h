#ifndef CGOAL_H
#define CGOAL_H

#include "CCharacter.h"
#include"CCollider.h"
#include"CColliderTriangle.h"

//�S�[������p�u���b�N
class CGoal : public CCharacter {
private:



public:

	static bool mTouchGoal;

	CCollider mCollider;

	CGoal(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif