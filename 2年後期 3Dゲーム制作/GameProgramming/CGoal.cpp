#include "CGoal.h"

#include"CCollisionManager.h"
#include"CTaskManager.h"

bool CGoal::mTouchGoal;

CGoal::CGoal(CModel* model, CVector position, CVector rotation, CVector scale) {
	//モデル,位置,回転,拡縮を設定
	mpModel = model;		//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;			//拡縮の設定
	mTag = EGOAL;

	mTouchGoal == false;

	mPriority = 1; //優先度1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CGoal::Update() {

}

//衝突処理
void CGoal::Collision(CCollider* m, CCollider* o) {
	if (o->mTag == CCharacter::EPLAYER) {
		mTouchGoal == true;
	}
}

//衝突処理
void CGoal::TaskCollision() {
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}