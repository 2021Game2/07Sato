#ifndef CDAMAGEBLOCKRL_H
#define CDAMAGEBLOCKRL_H

#include "CCharacter.h"

//�ڐG����ƃ_���[�W���󂯂�u���b�N
//���E�Ɉړ�����
class CDamageBlockRL : public CCharacter {
private:


public:
	CDamageBlockRL();
	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif