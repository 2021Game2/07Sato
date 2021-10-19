#include "CTargetTouch.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"

#define TOUCHSCORE 300


CTargetTouch::CTargetTouch(CModel* model, CVector position, CVector rotation, CVector scale)
:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 5.0f)
{
	//ƒ‚ƒfƒ‹,ˆÊ’u,‰ñ“],Šgk‚ðÝ’è
	mpModel = model;		//ƒ‚ƒfƒ‹‚ÌÝ’è
	mPosition = position;	//ˆÊ’u‚ÌÝ’è
	mRotation = rotation;	//‰ñ“]‚ÌÝ’è
	mScale = scale;			//Šgk‚ÌÝ’è

	mTag = ESCOREBLOCK2;

	mEnabled = true;

	mPriority = 1; //—Dæ“x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CTargetTouch::Update() {
	CTransform::Update();

	mRotation.mX += 2;
	mRotation.mZ -= 2;
}

void CTargetTouch::Collision(CCollider* m, CCollider* o) {
	if(CCollider::Collision(m, o)){
		if (m->mType == CCollider::ESPHERE && o->mType == CCollider::ELINE) {
			if (o->mpParent->mTag == EPLAYER) {
				//mScore += TOUCHSCORE
				mEnabled == false;
			}
		}
	}
}

void CTargetTouch::TaskCollision() {
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
