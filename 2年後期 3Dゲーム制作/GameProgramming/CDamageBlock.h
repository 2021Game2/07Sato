#ifndef CDAMAGEBLOCK_H
#define CDAMAGEBLOCK_H

#include "CCharacter.h"

//接触するとダメージを受けるブロック
class CDamageBlock : public CCharacter {
private:


public:
	CDamageBlock();
	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif
