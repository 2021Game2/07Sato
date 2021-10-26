#ifndef CTARGETTOUCH_H
#define CTARGETTOUCH_H

#include"CCharacter.h"
#include"CBullet.h"
#include"CCollider.h"
#include"CColliderTriangle.h"
#include"CEffect.h"


//プレイヤーの接触で破壊され、スコアを加算する
class CTargetTouch : public CCharacter {
public:

	//三角コライダ
	CCollider mSphere;

	CTargetTouch(CModel* model, CVector position, CVector rotation, CVector scale);

	void Update();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//衝突処理
	void TaskCollision();

};

#endif