#include "CTarget.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#include"CPlayer.h"

#define SCORE 150

extern CSound ScoreAdd;
extern CSound Bomb;
extern CSound Hit;


CTarget::CTarget(CModel* model, CVector position, CVector rotation, CVector scale)
:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 5.0f)
,mTri1(this,&mMatrix,
	CVector(1.0f,-8.0f,0.0f),
	CVector(1.0f,4.0f,-6.0f),
	CVector(1.0f,4.0f,6.0f))
,mTri2(this, &mMatrix,
	CVector(-1.0f, -8.0f, 0.0f),
	CVector(-1.0f, 4.0f, 6.0f),
	CVector(-1.0f, 4.0f, -6.0f))
{
	//ƒ‚ƒfƒ‹,ˆÊ’u,‰ñ“],Šgk‚ðÝ’è
	mpModel = model;		//ƒ‚ƒfƒ‹‚ÌÝ’è
	mPosition = position;	//ˆÊ’u‚ÌÝ’è
	mRotation = rotation;	//‰ñ“]‚ÌÝ’è
	mScale = scale;			//Šgk‚ÌÝ’è
	CCharacter::mTag = ESCOREBLOCK1;

	mPriority = 1; //—Dæ“x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);

	mHp = 9;
}
	

void CTarget::Update() {
	CTransform::Update();
}

void CTarget::Collision(CCollider* m, CCollider* o){
	if (CCollider::Collision(m, o)) {
		if (o->mType == CCollider::ESPHERE) {
			if (o->mpParent->mTag == EBULLET) {
				mHp -= CBullet::mDamage;
				Hit.Play();
				new CEffect(o->mpParent->mPosition, 2.0f, 2.0f, "exp.tga", 4, 4, 2);
				if (mHp <= 0) {
					CPlayer::mScore += SCORE;
					new CEffect(m->mpParent->mPosition, 10.0f, 10.0f, "exp.tga", 4, 4, 2);
					ScoreAdd.Play();
					Bomb.Play();
					mEnabled = false;
				}

			}
		}
	}
}

void CTarget::TaskCollision(){
	mCollider.ChangePriority();
	mTri1.ChangePriority();
	mTri2.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mTri1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mTri2, COLLISIONRANGE);
}
