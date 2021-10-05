#ifndef CTARGETTOUCH_H
#define CTARGETTOUCH_H

#include"CCharacter.h"

//プレイヤーの接触で破壊され、スコアを加算する
class CTargetTouch : public CCharacter {
private:


public:

	CTargetTouch();

	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif