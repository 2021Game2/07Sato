#include "CTargetRL.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#include"CPlayer.h"

#define RLSCORE 300
#define MOVE 60

extern CSound ScoreAdd;
extern CSound Bomb;
extern CSound Hit;

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
	//モデル,位置,回転,拡縮を設定
	mpModel = model;		//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;			//拡縮の設定
	CCharacter::mTag = ESCOREBLOCK1;

	mMoveCount = 0;	//移動制御

	mPriority = 1; //優先度1
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
				Hit.Play();
				if (mHp <= 0) {
					CPlayer::mScore += RLSCORE;
					ScoreAdd.Play();
					Bomb.Play();
					new CEffect(m->mpParent->mPosition, 10.0f, 10.0f, "tga/exp.tga", 4, 4, 2);
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
