#include "CTargetTouch.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"

#define TOUCHSCORE 300

CTargetTouch::CTargetTouch(CModel* model, CVector position, CVector rotation, CVector scale) {
	//ƒ‚ƒfƒ‹,ˆÊ’u,‰ñ“],Šgk‚ðÝ’è
	mpModel = model;		//ƒ‚ƒfƒ‹‚ÌÝ’è
	mPosition = position;	//ˆÊ’u‚ÌÝ’è
	mRotation = rotation;	//‰ñ“]‚ÌÝ’è
	mScale = scale;			//Šgk‚ÌÝ’è
	mTag = ESCOREBLOCK2;

	mPriority = 1; //—Dæ“x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CTargetTouch::Update() {

	mRotation.mX += 2;
	mRotation.mZ -= 2;
}

void CTargetTouch::Collision(CCollider* m, CCollider* o) {
	if (o->mTag == EPLAYER) {
		//mScore += TOUCHSCORE
		mEnabled == false;
	}
}

void CTargetTouch::TaskCollision() {
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
