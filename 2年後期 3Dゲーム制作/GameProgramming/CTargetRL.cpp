#include "CTargetRL.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"

#define RLSCORE 300
#define MOVE 30

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
	//���f��,�ʒu,��],�g�k��ݒ�
	mpModel = model;		//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�
	CCharacter::mTag = ESCOREBLOCK1;

	mMoveCount = 0;	//�ړ�����

	mPriority = 1; //�D��x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);

}

void CTargetRL::Update() {
	CTransform::Update();
	mMoveCount++;
	if (mMoveCount > MOVE) {
		mMoveCount = -MOVE;
	}

	if (mMoveCount > 0) {
		mPosition.mX++;
	}
	if (mMoveCount < 0) {
		mPosition.mX--;
	}
}

void CTargetRL::Collision(CCollider* m, CCollider* o) {
	if (o->mType == CCollider::ESPHERE) {
		if (o->mpParent->mTag == EBULLET) {
			//mScore += RLSCORE;
			new CEffect(m->mpParent->mPosition, 10.0f, 10.0f, "exp.tga", 4, 4, 2);
			mEnabled = false;
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
