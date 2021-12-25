#include "CTargetRL.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#include"CPlayer.h"

#define RLSCORE 300
#define MOVE 60

extern CSound ScoreAdd;

CTargetRL::CTargetRL(CModel* model, CVector position, CVector rotation, CVector scale)
:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 5.0f) 
, mTri1(this, &mMatrix,
	CVector(1.0f, -8.0f, 0.0f),
	CVector(1.0f, 4.0f, -6.0f),
	CVector(1.0f, 4.0f, 6.0f))
, mTri2(this, &mMatrix,
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

	mMoveCount = 0;	//ˆÚ“®§Œä

	mPriority = 1; //—Dæ“x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);

	mHp = 7;
}

void CTargetRL::Update() {
	CTransform::Update();
	mMoveCount++;
	if (mMoveCount > MOVE) {
		mMoveCount = -MOVE;
	}

	if (mMoveCount > 0) {
		mPosition.mX += 0.5f;
	}
	if (mMoveCount < 0) {
		mPosition.mX -= 0.5f;
	}
}

void CTargetRL::Collision(CCollider* m, CCollider* o) {
	if (CCollider::Collision(m, o)) {
		if (o->mType == CCollider::ESPHERE) {
			if (o->mpParent->mTag == EBULLET) {
				mHp -= CBullet::mDamage;
				new CEffect(o->mpParent->mPosition, 3.0f, 3.0f, "exp.tga", 4, 4, 2);
				if (mHp <= 0) {
					CPlayer::mScore += RLSCORE;
					ScoreAdd.Play();
					new CEffect(m->mpParent->mPosition, 10.0f, 10.0f, "exp.tga", 4, 4, 2);
					mEnabled = false;
				}
			}
		}
	}
}

void CTargetRL::TaskCollision(){
	mCollider.ChangePriority();
	mTri1.ChangePriority();
	mTri2.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mTri1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mTri2, COLLISIONRANGE);
}
