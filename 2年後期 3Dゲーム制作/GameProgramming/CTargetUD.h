#ifndef CTARGETUD_H
#define CTARGETUD_H

#include"CCharacter.h"
#include"CBullet.h"
#include"CCollider.h"
#include"CColliderTriangle.h"
#include"CEffect.h"
#include"CSceneGame.h"


//的,射撃で破壊され、スコアを加算する
//上下移動
class CTargetUD : public CCharacter {
private:
	int mMoveCount;

	int mHp;
public:

	//コライダ
	CCollider mCollider;
	CColliderTriangle mTri1;	//プレイヤー移動阻害用
	CColliderTriangle mTri2;	//プレイヤー移動阻害用

	CTargetUD(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif
