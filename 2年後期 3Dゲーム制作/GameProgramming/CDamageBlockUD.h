#ifndef CDAMAGEBLOCKUD_H
#define CDAMAGEBLOCKUD_H

#include "CCharacter.h"

//接触するとダメージを受けるブロック
//上下に移動する
class CDamageBlockUD : public CCharacter {
private:


public:
	CDamageBlockUD();
	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif
