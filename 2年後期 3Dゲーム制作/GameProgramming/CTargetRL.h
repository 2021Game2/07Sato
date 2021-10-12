#ifndef CTARGETRL_H
#define CTARGETRL_H

#include"CCharacter.h"

//的,射撃で破壊され、スコアを加算する
//左右移動
class CTargetRL : public CCharacter {
private:


public:

	CTargetRL(const CVector& position, const CVector& rotation, const CVector& scale);

	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif
