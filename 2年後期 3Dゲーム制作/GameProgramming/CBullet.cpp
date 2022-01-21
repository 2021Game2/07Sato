#include"CBullet.h"
#include"CCollisionManager.h"
#include"CEffect.h"

int CBullet::mDamage;

//�f�t�H���g�R���X�g���N�^
CBullet::CBullet()
:mLife(50)
,mCollider(this,&mMatrix,CVector(0.0f,0.0f,5.0f),1.5f)
,mCollider2(this, &mMatrix, CVector(0.0f, 0.0f, -2.0f), 1.5f)
{
	mTag = CCharacter::EBULLET;
}

//���Ɖ��s���̐ݒ�
//Set(��,���s��)
void CBullet::Set(float w, float d){
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ�
	mT.SetVertex(CVector(-w, 0.0, 0.0),CVector(w, 0.0, 0.0),CVector(0.0, 0.0, d));
	//�O�p�`�̖@���ݒ�
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//�U����
void CBullet::Damage(int damage) {
	mDamage = damage;
}

//�X�V
void CBullet::Update(){
	//�������Ԃ̔���
	if (mLife-- > 0){
		CTransform::Update();
		//�ʒu�X�V
		mPosition = CVector(0.0f, 0.0f, 19.0f) * mMatrix;
		mRotation.mZ += 240;
	}
	else{
		//�����ɂ���
		mEnabled = false;
	}
}

//�`��
void CBullet::Render(){
	//DIFFUSE���F�ݒ�
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	mT.Render(mMatrix);
}

//�Փˏ���
//Collision(�R���C�_1,�R���C�_2)
void CBullet::Collision(CCollider* m, CCollider* o) {
	if (CCollider::Collision(m, o)) {
		if (o->mpParent->mTag == EPLAYER) {
			return;
		}
	}
	//�R���C�_��m��o���Փ˂��Ă��邩����
	if (CCollider::Collision(m, o)) {
		if (o->mType == CCollider::ESPHERE) {
			new CEffect(m->mpParent->mPosition, 2.0f, 2.0f, "tga/exp.tga", 4, 4, 2);
			//���肪�S�[���̎��͖߂�
			if (o->mpParent->mTag == EGOAL) {
				return;
			}
			mEnabled = false;
		}
	}
	if (o->mpParent != nullptr) {
		if (o->mpParent->mTag == EBLOCK || o->mpParent->mTag == EMOVEBLOCK) {
			CVector adjust;		//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			return;

		}
	}
}

//�Փˏ���
void CBullet::TaskCollision(){
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	mCollider2.ChangePriority();
	//�Փˏ��� ���s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider2, COLLISIONRANGE);
}