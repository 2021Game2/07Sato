#include "CMoveBlock.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CEffect.h"

#define MOVE 140

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
	//���f��,�ʒu,��],�g�k��ݒ�
	mpModel = model;		//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�

	mTag = EMOVEBLOCK;

	mMoveCount = 0;

	mPriority = 1; //�D��x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CMoveBlock::Update() {
	CTransform::Update();

	if (mMoveCount > MOVE) {
		mMoveCount = -MOVE;
	}

	if (mMoveCount > 0) {
		mPosition.mX += 1.0f;
	}
	else if (mMoveCount < 0) {
		mPosition.mX -= 1.0f;
	}
	mMoveCount++;
}

void CMoveBlock::Collision(CCollider* m, CCollider* o) {
	CVector adjust;
	if (o->mpParent != nullptr) {
		switch (o->CCollider::mType) {
		case CCollider::ELINE:
			if (CCollider::CollisionTriangleLine(m, o, &adjust)) {
				if (o->mpParent->mTag == EPLAYER) {
					o->mPosition = mPosition - adjust * -1;
				}
				break;
			}
		case CCollider::ESPHERE:
			if (CCollider::CollisionTriangleSphere(m, o, &adjust)) {
				if (o->mpParent->mTag == EPLAYER) {
					break;
				}
				if (o->mpParent->mTag == EBULLET) {
					CCollider::CollisionTriangleSphere(o, m, &adjust);
					new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
					o->mEnabled = false;
				}

			}

		}
	}
}

void CMoveBlock::TaskCollision() {
	//�R���C�_�̗D��x�ύX
	//Z���̖�
	mColliderZ1.ChangePriority();
	mColliderZ2.ChangePriority();
	mColliderZ3.ChangePriority();
	mColliderZ4.ChangePriority();
	//X���̖�
	mColliderX1.ChangePriority();
	mColliderX2.ChangePriority();
	mColliderX3.ChangePriority();
	mColliderX4.ChangePriority();
	//Y���̖�
	mColliderY1.ChangePriority();
	mColliderY2.ChangePriority();
	mColliderY3.ChangePriority();
	mColliderY4.ChangePriority();
	//�Փˏ��� ���s
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
