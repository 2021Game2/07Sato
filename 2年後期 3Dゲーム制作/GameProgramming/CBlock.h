#ifndef CBLOCK_H
#define CBLOCK_H

#include "CCharacter.h"

//接触するとダメージを受けるブロック
class CBlock : public CCharacter {
private:


public:
	CBlock();
	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif
