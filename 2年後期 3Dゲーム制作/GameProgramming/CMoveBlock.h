#ifndef CMOVEBLOCK_H
#define CMOVEBLOCK_H

#include "CCharacter.h"
#include "CColliderTriangle.h"

//�ڐG����ƃ_���[�W���󂯂�u���b�N
class CMoveBlock : public CCharacter {
private:
	//�R���C�_
	//Z���̖�
	CColliderTriangle mColliderZ1;
	CColliderTriangle mColliderZ2;
	CColliderTriangle mColliderZ3;
	CColliderTriangle mColliderZ4;
	//X���̖�
	CColliderTriangle mColliderX1;
	CColliderTriangle mColliderX2;
	CColliderTriangle mColliderX3;
	CColliderTriangle mColliderX4;
	//Y���̖�
	CColliderTriangle mColliderY1;
	CColliderTriangle mColliderY2;
	CColliderTriangle mColliderY3;
	CColliderTriangle mColliderY4;

	int mMoveCount;

public:
	CMoveBlock(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�Փˏ���
	void TaskCollision();

};

#endif
