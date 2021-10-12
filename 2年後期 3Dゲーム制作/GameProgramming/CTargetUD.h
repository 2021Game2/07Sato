#ifndef CTARGETUD_H
#define CTARGETUD_H

#include"CCharacter.h"

//的,射撃で破壊され、スコアを加算する
//上下移動
class CTargetUD : public CCharacter {
private:


public:

	CTargetUD(const CVector& position, const CVector& rotation, const CVector& scale);

	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif
