#include "CGoal.h"

#include"CCollisionManager.h"
#include"CTaskManager.h"

bool CGoal::mTouchGoal;

CGoal::CGoal(CModel* model, CVector position, CVector rotation, CVector scale) {
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

}

//�Փˏ���
void CGoal::Collision(CCollider* m, CCollider* o) {
	if (o->mTag == CCharacter::EPLAYER) {
		mTouchGoal == true;
	}
}

//�Փˏ���
void CGoal::TaskCollision() {
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}