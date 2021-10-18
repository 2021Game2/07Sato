#ifndef CTARGETRL_H
#define CTARGETRL_H

#include"CCharacter.h"
#include"CBullet.h"
#include"CCollider.h"
#include"CColliderTriangle.h"
#include"CEffect.h"

//的,射撃で破壊され、スコアを加算する
//左右移動
class CTargetRL : public CCharacter {
private:


public:

	//コライダ
	CCollider mCollider;

	CTargetRL(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif
