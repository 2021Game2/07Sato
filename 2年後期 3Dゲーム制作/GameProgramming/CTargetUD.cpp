#include "CTargetUD.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"

#define UDSCORE 300
#define MOVE 80

CTargetUD::CTargetUD(CModel* model, CVector position, CVector rotation, CVector scale)
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

	mMoveCount = 0;

	mPriority = 1; //�D��x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CTargetUD::Update() {
	CTransform::Update();
	mMoveCount++;
	if (mMoveCount > MOVE) {
		mMoveCount = -MOVE;
	}

	if (mMoveCount > 0) {
		mPosition.mY += 0.3f;
	}
	if (mMoveCount < 0) {
		mPosition.mY -= 0.3f;
	}
}

void CTargetUD::Collision(CCollider* m, CCollider* o) {
	if (m->mType == CCollider::ESPHERE) {
		if (o->mType == CCollider::ELINE) {
			if (o->mpParent->mTag == EBULLET) {
				//mScore(��) += UDSCORE;
				new CEffect(m->mpParent->mPosition, 10.0f, 10.0f, "exp.tga", 4, 4, 2);
				mEnabled = false;
			}
		}
	}
}

void CTargetUD::TaskCollision(){
	mCollider.ChangePriority();
	mTri1.ChangePriority();
	mTri2.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mTri1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mTri2, COLLISIONRANGE);
}
