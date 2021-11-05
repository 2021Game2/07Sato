#ifndef CMOVEBLOCK_H
#define CMOVEBLOCK_H

#include "CCharacter.h"
#include "CColliderTriangle.h"

//接触するとダメージを受けるブロック
class CMoveBlock : public CCharacter {
private:
	//コライダ
	//Z軸の面
	CColliderTriangle mColliderZ1;
	CColliderTriangle mColliderZ2;
	CColliderTriangle mColliderZ3;
	CColliderTriangle mColliderZ4;
	//X軸の面
	CColliderTriangle mColliderX1;
	CColliderTriangle mColliderX2;
	CColliderTriangle mColliderX3;
	CColliderTriangle mColliderX4;
	//Y軸の面
	CColliderTriangle mColliderY1;
	CColliderTriangle mColliderY2;
	CColliderTriangle mColliderY3;
	CColliderTriangle mColliderY4;

	int mMoveCount;

public:
	CMoveBlock(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif
