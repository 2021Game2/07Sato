#include "CMoveBlock.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"

CMoveBlock::CMoveBlock(CModel* model, CVector position, CVector rotation, CVector scale) 
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
	//ƒ‚ƒfƒ‹,ˆÊ’u,‰ñ“],Šgk‚ðÝ’è
	mpModel = model;		//ƒ‚ƒfƒ‹‚ÌÝ’è
	mPosition = position;	//ˆÊ’u‚ÌÝ’è
	mRotation = rotation;	//‰ñ“]‚ÌÝ’è
	mScale = scale;			//Šgk‚ÌÝ’è

	mTag = EBLOCK;

	mPriority = 1; //—Dæ“x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CMoveBlock::Update() {
	CTransform::Update();

	mPosition.mX += 0.1f;
}

void CMoveBlock::Collision(CCollider* m, CCollider* o) {

}

void CMoveBlock::TaskCollision() {
	//ƒRƒ‰ƒCƒ_‚Ì—Dæ“x•ÏX
	//ZŽ²‚Ì–Ê
	mColliderZ1.ChangePriority();
	mColliderZ2.ChangePriority();
	mColliderZ3.ChangePriority();
	mColliderZ4.ChangePriority();
	//XŽ²‚Ì–Ê
	mColliderX1.ChangePriority();
	mColliderX2.ChangePriority();
	mColliderX3.ChangePriority();
	mColliderX4.ChangePriority();
	//YŽ²‚Ì–Ê
	mColliderY1.ChangePriority();
	mColliderY2.ChangePriority();
	mColliderY3.ChangePriority();
	mColliderY4.ChangePriority();
	//Õ“Ëˆ— ŽÀs
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
