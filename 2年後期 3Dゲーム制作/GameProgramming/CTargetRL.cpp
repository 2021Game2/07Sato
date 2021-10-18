#include "CTargetRL.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"

CTargetRL::CTargetRL(CModel* model, CVector position, CVector rotation, CVector scale) {
	//���f��,�ʒu,��],�g�k��ݒ�
	mpModel = model;		//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�
	mTag = ESCOREBLOCK1;

	mPriority = 1; //�D��x1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);

}

void CTargetRL::Update() {


}

void CTargetRL::Collision(CCollider* m, CCollider* o) {

}

void CTargetRL::TaskCollision() {
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
