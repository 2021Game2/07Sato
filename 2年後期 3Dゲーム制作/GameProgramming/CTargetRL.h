#ifndef CTARGETRL_H
#define CTARGETRL_H

#include"CCharacter.h"

//�I,�ˌ��Ŕj�󂳂�A�X�R�A�����Z����
//���E�ړ�
class CTargetRL : public CCharacter {
private:


public:

	CTargetRL(const CVector& position, const CVector& rotation, const CVector& scale);

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
