#ifndef CDAMAGEBLOCKRL_H
#define CDAMAGEBLOCKRL_H

#include "CCharacter.h"

//接触するとダメージを受けるブロック
//左右に移動する
class CDamageBlockRL : public CCharacter {
private:


public:
	CDamageBlockRL();
	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif