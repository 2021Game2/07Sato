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
	int mMoveCount;

	int mHp;
public:

	//コライダ
	CCollider mCollider;
	CColliderTriangle mTri1;	//プレイヤー移動阻害用
	CColliderTriangle mTri2;	//プレイヤー移動阻害用

	CTargetRL(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif
