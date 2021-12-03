#include "CDamageBlock.h"
#include"CCollisionManager.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CSound.h"



extern CSound Bomb;

CDamageBlock::CDamageBlock(CModel* model, CVector position, CVector rotation, CVector scale)
:mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),5.0f)
{
	
	//ƒ‚ƒfƒ‹,ˆÊ’u,‰ñ“],Šgk‚ðÝ’è
	mpModel = model;		//ƒ‚ƒfƒ‹‚ÌÝ’è
	mPosition = position;	//ˆÊ’u‚ÌÝ’è
	mRotation = rotation;	//‰ñ“]‚ÌÝ’è
	mScale = scale;			//Šgk‚ÌÝ’è
	
	mTag = EDAMAGEBLOCK;

	mPriority = 1; //—Dæ“x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CDamageBlock::Update() {
	CTransform::Update();
}

void CDamageBlock::Collision(CCollider* m, CCollider* o) {
	if (CCollider::Collision(m, o)) {
		if (o->mpParent->mTag == EBULLET) {
			new CEffect(m->mpParent->mPosition, 10.0f, 10.0f, "exp.tga", 4, 4, 2);
			Bomb.Play();
			mEnabled = false;
		}
	}
}

void CDamageBlock::TaskCollision(){
	//ƒRƒ‰ƒCƒ_‚Ì—Dæ“x•ÏX
//ZŽ²‚Ì–Ê
	mCollider.ChangePriority();

	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
