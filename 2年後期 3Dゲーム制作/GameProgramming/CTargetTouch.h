#ifndef CTARGETTOUCH_H
#define CTARGETTOUCH_H

#include"CCharacter.h"

//�v���C���[�̐ڐG�Ŕj�󂳂�A�X�R�A�����Z����
class CTargetTouch : public CCharacter {
private:


public:

	CTargetTouch();

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif