#include "CGoal.h"

#include"CCollisionManager.h"
#include"CTaskManager.h"

bool CGoal::mTouchGoal;

CGoal::CGoal(CModel* model, CVector position, CVector rotation, CVector scale)
:mCollider(this, &mMatrix, CVector(0.0f, 2.0f, 0.0f), 30.0f) {
	//���f��,�ʒu,��],�g�k��ݒ�
	mpModel = model;		//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�
	mTag = EGOAL;

	mTouchGoal == false;

	mPriority = 1; //�D��x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CGoal::Update() {
	CTransform::Update();
}

//�Փˏ���
void CGoal::Collision(CCollider* m, CCollider* o) {
	if (o->mTag == EPLAYER) {
		mTouchGoal == true;
	}
}

//�Փˏ���
void CGoal::TaskCollision() {
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}