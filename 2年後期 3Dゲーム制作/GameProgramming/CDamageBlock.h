#ifndef CDAMAGEBLOCK_H
#define CDAMAGEBLOCK_H

#include "CCharacter.h"
#include "CCollider.h"

//�ڐG����ƃ_���[�W���󂯂�u���b�N
class CDamageBlock : public CCharacter {
private:
	//�R���C�_
	CCollider mCollider;

public:
	CDamageBlock(CModel* model, CVector position, CVector rotation, CVector scale);
	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
