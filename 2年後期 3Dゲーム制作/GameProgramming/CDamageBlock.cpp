#include "CDamageBlock.h"
#include"CCollisionManager.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CSound.h"



extern CSound Bomb;

CDamageBlock::CDamageBlock(CModel* model, CVector position, CVector rotation, CVector scale)
:mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),5.0f)
{
	
	//���f��,�ʒu,��],�g�k��ݒ�
	mpModel = model;		//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�
	
	mTag = EDAMAGEBLOCK;

	mPriority = 1; //�D��x1
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
	//�R���C�_�̗D��x�ύX
//Z���̖�
	mCollider.ChangePriority();

	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
