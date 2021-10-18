#include "CTargetTouch.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"

#define TOUCHSCORE 300

CTargetTouch::CTargetTouch(CModel* model, CVector position, CVector rotation, CVector scale) {
	//モデル,位置,回転,拡縮を設定
	mpModel = model;		//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;			//拡縮の設定
	mTag = ESCOREBLOCK2;

	mPriority = 1; //優先度1
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
