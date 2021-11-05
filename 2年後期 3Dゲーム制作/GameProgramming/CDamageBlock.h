#ifndef CDAMAGEBLOCK_H
#define CDAMAGEBLOCK_H

#include "CCharacter.h"
#include "CCollider.h"

//接触するとダメージを受けるブロック
class CDamageBlock : public CCharacter {
private:
	//コライダ
	CCollider mCollider;

public:
	CDamageBlock(CModel* model, CVector position, CVector rotation, CVector scale);
	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif
