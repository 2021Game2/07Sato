#ifndef CDAMAGEBLOCK_H
#define CDAMAGEBLOCK_H

#include "CCharacter.h"

//�ڐG����ƃ_���[�W���󂯂�u���b�N
class CDamageBlock : public CCharacter {
private:


public:
	CDamageBlock();
	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
