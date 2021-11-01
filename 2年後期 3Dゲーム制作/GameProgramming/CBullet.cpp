#include"CBullet.h"
#include"CCollisionManager.h"

//�f�t�H���g�R���X�g���N�^
CBullet::CBullet()
:mLife(50)
,mCollider(this,&mMatrix,CVector(0.0f,0.0f,5.0f),1.0f)
{}

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

//�X�V
void CBullet::Update(){
	//�������Ԃ̔���
	if (mLife-- > 0){
		CTransform::Update();
		//�ʒu�X�V
		mPosition = CVector(0.0f, 0.0f, 15.0f) * mMatrix;
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
	//�R���C�_��m��o���Փ˂��Ă��邩����
	if (CCollider::Collision(m, o)) {
		if (o->mType == CCollider::ESPHERE) {
			//���肪�S�[���̎��͖߂�
			if (o->mpParent->mTag == EGOAL) {
				return;
			}
			mEnabled = false;
		}
	}
}

//�Փˏ���
void CBullet::TaskCollision(){
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��� ���s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}