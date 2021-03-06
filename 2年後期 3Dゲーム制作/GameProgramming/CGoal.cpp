#include "CGoal.h"
#include "CSound.h"
#include"CCollisionManager.h"
#include"CTaskManager.h"

bool CGoal::mTouchGoal;

extern CSound Clear;

CGoal::CGoal(CModel* model, CVector position, CVector rotation, CVector scale)
:mCollider(this, &mMatrix, CVector(0.0f, 2.0f, 0.0f), 60.0f) {
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
	CTransform::Update();
}

//衝突処理
void CGoal::Collision(CCollider* m, CCollider* o) {
	if (CCollider::Collision(m, o)) {
		if (m->mpParent->mTag == EGOAL) {
			if (o->mpParent->mTag == EPLAYER) {
				if (mTouchGoal == false) {
					Clear.Play();
				}
				mTouchGoal = true;
			}
		}
	}
}

//衝突処理
void CGoal::TaskCollision() {
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}