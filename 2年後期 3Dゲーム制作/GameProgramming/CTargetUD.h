#ifndef CTARGETUD_H
#define CTARGETUD_H

#include"CCharacter.h"

//�I,�ˌ��Ŕj�󂳂�A�X�R�A�����Z����
//�㉺�ړ�
class CTargetUD : public CCharacter {
private:


public:

	CTargetUD();

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
