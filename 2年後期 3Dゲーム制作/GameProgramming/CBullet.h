#ifndef CBULLET_H
#define CBULLET_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//三角形クラスのインクルード
#include"CTriangle.h"
#include"CCollider.h"
#include"CColliderLine.h"

/*弾クラス
 三角形を飛ばす*/
class CBullet : public CCharacter{
public:
	//三角形
	CTriangle mT;

	//生存時間
	int mLife;
	static int mDamage;

	CBullet();

	CCollider mCollider;
	CCollider mCollider2;

	//幅と奥行きの設定
	//Set(幅,奥行き)
	void Set(float w, float d);
	//攻撃力
	void Damage(int damage);
	//更新
	void Update();
	//描画
	void Render();
	//衝突処理
	//Collision(コライダ1,コライダ2)
	void Collision(CCollider *m, CCollider *o);
	void TaskCollision();
};

#endif