#include "CTargetTouch.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#include"CPlayer.h"

#define TOUCHSCORE 200

extern CSound ScoreAdd;
extern CSound Bomb;

CTargetTouch::CTargetTouch(CModel* model, CVector position, CVector rotation, CVector scale)
:mSphere(this,&mMatrix,CVector(0.0f,0.0f,0.0f),5.0f)
{
	//���f��,�ʒu,��],�g�k��ݒ�
	mpModel = model;		//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�

	mTag = ESCOREBLOCK2;

	mEnabled = true;

	mPriority = 1; //�D��x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CTargetTouch::Update() {
	CTransform::Update();

	mRotation.mX += 3;
	mRotation.mZ -= 3;
}

void CTargetTouch::Collision(CCollider* m, CCollider* o) {
	if (CCollider::Collision(m, o)) {
		if (o->mpParent->mTag != ESCOREBLOCK2) {
			if (o->mpParent->mTag == EBULLET) {
				return;
			}
			CPlayer::mScore += TOUCHSCORE;
			new CEffect(m->mpParent->mPosition, 10.0f, 10.0f, "exp.tga", 4, 4, 2);
			ScoreAdd.Play();
			Bomb.Play();
			mEnabled = false;
		}
	}
}

void CTargetTouch::TaskCollision() {
	mSphere.ChangePriority();
	CCollisionManager::Get()->Collision(&mSphere, COLLISIONRANGE);
}
