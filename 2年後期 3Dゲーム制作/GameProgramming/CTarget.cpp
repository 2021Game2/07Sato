#include "CTarget.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"

#define OBJ "Target.obj"	//���f���̃t�@�C��
#define MTL "Target.mtl"	//���f���̃}�e���A���t�@�C��

CModel CTarget::mTarget;

CTarget::CTarget(CModel* model, CVector position, CVector rotation, CVector scale) {
	//���f��,�ʒu,��],�g�k��ݒ�
	mpModel = model;		//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�
	mTag = ESCOREBLOCK1;

	//���f���������Ƃ��͓ǂݍ���
	if (mTarget.mTriangles.size() == 0) {
		mTarget.Load(OBJ, MTL);
	}

	mPriority = 1; //�D��x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}
	

void CTarget::Update() {

}

void CTarget::Collision(CCollider* m, CCollider* o){

}

void CTarget::TaskCollision(){
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
