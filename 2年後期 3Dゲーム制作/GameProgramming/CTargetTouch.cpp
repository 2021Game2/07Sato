#include "CTargetTouch.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"

#define TOUCHSCORE 200


CTargetTouch::CTargetTouch(CModel* model, CVector position, CVector rotation, CVector scale)
:mSphere(this,&mMatrix,CVector(0.0f,0.0f,0.0f),5.0f)
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

	mRotation.mX += 3;
	mRotation.mZ -= 3;
}

void CTargetTouch::Collision(CCollider* m, CCollider* o) {
	if(CCollider::Collision(m, o)){
		if (o->mpParent->mTag == EBULLET) {
			return;
		}
		//mScore(‰¼) += TOUCHSCORE;
		new CEffect(m->mpParent->mPosition, 10.0f, 10.0f, "exp.tga", 4, 4, 2);
		mEnabled = false;
		CTransform::Update();
	}
}

void CTargetTouch::TaskCollision() {
	mSphere.ChangePriority();
	CCollisionManager::Get()->Collision(&mSphere, COLLISIONRANGE);
}
