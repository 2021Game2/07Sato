#ifndef CBLOCK_H
#define CBLOCK_H

#include "CCharacter.h"

//�ڐG����ƃ_���[�W���󂯂�u���b�N
class CBlock : public CCharacter {
private:


public:
	CBlock();
	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
