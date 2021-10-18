#ifndef CGOAL_H
#define CGOAL_H

#include "CCharacter.h"
#include"CCollider.h"
#include"CColliderTriangle.h"

//ゴール判定用ブロック
class CGoal : public CCharacter {
private:



public:

	static bool mTouchGoal;

	CCollider mCollider;

	CGoal(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif