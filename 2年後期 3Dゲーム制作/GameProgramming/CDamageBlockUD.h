#ifndef CDAMAGEBLOCKUD_H
#define CDAMAGEBLOCKUD_H

#include "CCharacter.h"

//�ڐG����ƃ_���[�W���󂯂�u���b�N
//�㉺�Ɉړ�����
class CDamageBlockUD : public CCharacter {
private:


public:
	CDamageBlockUD();
	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
