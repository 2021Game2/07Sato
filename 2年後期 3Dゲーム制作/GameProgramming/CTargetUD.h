#ifndef CTARGETUD_H
#define CTARGETUD_H

#include"CCharacter.h"
#include"CBullet.h"
#include"CCollider.h"
#include"CColliderTriangle.h"
#include"CEffect.h"


//�I,�ˌ��Ŕj�󂳂�A�X�R�A�����Z����
//�㉺�ړ�
class CTargetUD : public CCharacter {
private:


public:

	//�R���C�_
	CCollider mCollider;

	CTargetUD(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
