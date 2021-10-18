#include "CGoal.h"

#include"CCollisionManager.h"
#include"CTaskManager.h"

bool CGoal::mTouchGoal;

CGoal::CGoal(CModel* model, CVector position, CVector rotation, CVector scale) {
	//ƒ‚ƒfƒ‹,ˆÊ’u,‰ñ“],Šgk‚ðÝ’è
	mpModel = model;		//ƒ‚ƒfƒ‹‚ÌÝ’è
	mPosition = position;	//ˆÊ’u‚ÌÝ’è
	mRotation = rotation;	//‰ñ“]‚ÌÝ’è
	mScale = scale;			//Šgk‚ÌÝ’è
	mTag = EGOAL;

	mTouchGoal == false;

	mPriority = 1; //—Dæ“x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CGoal::Update() {

}

//Õ“Ëˆ—
void CGoal::Collision(CCollider* m, CCollider* o) {
	if (o->mTag == CCharacter::EPLAYER) {
		mTouchGoal == true;
	}
}

//Õ“Ëˆ—
void CGoal::TaskCollision() {
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}