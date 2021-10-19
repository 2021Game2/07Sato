#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタークラスのインクルード
#include"CCharacter.h"
//弾クラスのインクルード
#include"CBullet.h"
#include"CTaskManager.h"
#include"CColliderLine.h"
#include"CColliderTriangle.h"
#include"CEffect.h"
#include"CAim.h"

/*プレイヤークラス
　キャラクタクラスを継承*/
class CPlayer : public CCharacter,CAim{
private:
	bool mJump;		//ジャンプができるかの判定
	int mJumpTimer;	//ジャンプのクールタイム

	int mStep;	//瞬間移動に掛けるフレーム数
	int mStepRecharge; //瞬間移動のクールタイム

	int mReloadTime;	//銃のリロード時間

	float mSpeedX;	//左右加速度
	float mSpeedY;	//上下加速度
	float mSpeedZ;	//前後加速度

public:

	static int mPlayerHp;	//体力

	CColliderLine mLine; //線分コライダ
	CColliderLine mLine2; //線分コライダ
	CColliderLine mLine3; //線分コライダ
	CColliderLine mLine4; //線分コライダ
	CColliderLine mLine5; //線分コライダ
	CCollider mCollider; //本体用コライダ

	CPlayer();
	//更新処理
	void Update();

	//衝突処理
	void Collision(CCollider *m, CCollider *o);

	//描画処理
	void Render();

	//衝突処理
	void TaskCollision();

};

#endif