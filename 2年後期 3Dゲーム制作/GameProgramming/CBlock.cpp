#include "CBlock.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"

CBlock::CBlock(CModel* model, CVector position, CVector rotation, CVector scale) 
:mColliderZ1(this, &mMatrix,
	CVector(-4.0f, -4.0f, 4.0f),
	CVector(4.0f, -4.0f, 4.0f),
	CVector(-4.0f, 4.0f, 4.0f))
, mColliderZ2(this, &mMatrix,
	CVector(-4.0f, 4.0f, 4.0f),
	CVector(4.0f, -4.0f, 4.0f),
	CVector(4.0f, 4.0f, 4.0f))
, mColliderZ3(this, &mMatrix,
	CVector(4.0f, -4.0f, -4.0f),
	CVector(-4.0f, -4.0f, -4.0f),
	CVector(-4.0f, 4.0f, -4.0f))
, mColliderZ4(this, &mMatrix,
	CVector(-4.0f, 4.0f, -4.0f),
	CVector(4.0f, 4.0f, -4.0f),
	CVector(4.0f, -4.0f, -4.0f))

, mColliderX1(this, &mMatrix,
	CVector(4.0f, -4.0f, 4.0f),
	CVector(4.0f, -4.0f, -4.0f),
	CVector(4.0f, 4.0f, 4.0f))
, mColliderX2(this, &mMatrix,
	CVector(4.0f, 4.0f, 4.0f),
	CVector(4.0f, -4.0f, -4.0f),
	CVector(4.0f, 4.0f, -4.0f))
, mColliderX3(this, &mMatrix,
	CVector(-4.0f, -4.0f, -4.0f),
	CVector(-4.0f, -4.0f, 4.0f),
	CVector(-4.0f, 4.0f, 4.0f))
, mColliderX4(this, &mMatrix,
	CVector(-4.0f, 4.0f, 4.0f),
	CVector(-4.0f, 4.0f, -4.0f),
	CVector(-4.0f, -4.0f, -4.0f))

, mColliderY1(this, &mMatrix,
	CVector(-4.0f, 4.0f, 4.0f),
	CVector(4.0f, 4.0f, 4.0f),
	CVector(4.0f, 4.0f, -4.0f))
, mColliderY2(this, &mMatrix,
	CVector(-4.0f, 4.0f, 4.0f),
	CVector(4.0f, 4.0f, -4.0f),
	CVector(-4.0f, 4.0f, -4.0f))
, mColliderY3(this, &mMatrix,
	CVector(4.0f, -4.0f, 4.0f),
	CVector(-4.0f, -4.0f, 4.0f),
	CVector(-4.0f, -4.0f, -4.0f))
, mColliderY4(this, &mMatrix,
	CVector(4.0f, -4.0f, 4.0f),
	CVector(-4.0f, -4.0f, -4.0f),
	CVector(4.0f, -4.0f, -4.0f))
{
	//モデル,位置,回転,拡縮を設定
	mpModel = model;		//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;			//拡縮の設定

	mTag = EBLOCK;

	mPriority = 1; //優先度1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CBlock::Update() {
	CTransform::Update();
}

void CBlock::Collision(CCollider* m, CCollider* o) {
	if (CCollider::Collision(m, o)) {
		return;
	}
}

void CBlock::TaskCollision() {
	//コライダの優先度変更
	//Z軸の面
	mColliderZ1.ChangePriority();
	mColliderZ2.ChangePriority();
	mColliderZ3.ChangePriority();
	mColliderZ4.ChangePriority();
	//X軸の面
	mColliderX1.ChangePriority();
	mColliderX2.ChangePriority();
	mColliderX3.ChangePriority();
	mColliderX4.ChangePriority();
	//Y軸の面
	mColliderY1.ChangePriority();
	mColliderY2.ChangePriority();
	mColliderY3.ChangePriority();
	mColliderY4.ChangePriority();
	//衝突処理 実行
	CCollisionManager::Get()->Collision(&mColliderZ1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderZ2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderZ3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderZ4, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderX1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderX2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderX3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderX4, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderY1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderY2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderY3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColliderY4, COLLISIONRANGE);
}
