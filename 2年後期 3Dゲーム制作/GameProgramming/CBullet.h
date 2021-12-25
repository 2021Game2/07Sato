#ifndef CBULLET_H
#define CBULLET_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�O�p�`�N���X�̃C���N���[�h
#include"CTriangle.h"
#include"CCollider.h"
#include"CColliderLine.h"

/*�e�N���X
 �O�p�`���΂�*/
class CBullet : public CCharacter{
public:
	//�O�p�`
	CTriangle mT;

	//��������
	int mLife;
	static int mDamage;

	CBullet();

	CCollider mCollider;
	CCollider mCollider2;

	//���Ɖ��s���̐ݒ�
	//Set(��,���s��)
	void Set(float w, float d);
	//�U����
	void Damage(int damage);
	//�X�V
	void Update();
	//�`��
	void Render();
	//�Փˏ���
	//Collision(�R���C�_1,�R���C�_2)
	void Collision(CCollider *m, CCollider *o);
	void TaskCollision();
};

#endif