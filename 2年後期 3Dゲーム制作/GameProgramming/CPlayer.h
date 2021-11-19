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

/*プレイヤークラス
　キャラクタクラスを継承*/
class CPlayer : public CCharacter{
private:
	bool mJump;		//ジャンプができるかの判定
	int mJumpTimer;	//ジャンプのクールタイム

	int mStep;	//瞬間移動に掛けるフレーム数
	int mStepRecharge; //瞬間移動のクールタイム

	int mReloadTime;	//銃のリロード時間
	int mNotHit;	//ダメージ後無敵時間

	float mBeforMouseX;	//直前マウス位置
	float mBeforMouseY;
	float mMouseMoveX;	//マウス移動量
	float mMouseMoveY;
	float mMouseSpeedX;	//マウス感度
	float mMouseSpeedY;

public:

	static int mPlayerHp;	//体力

	static float mSpeedX;	//左右加速度
	static float mSpeedY;	//上下加速度
	static float mSpeedZ;	//前後加速度


	static int mScore;

	static float mTime;
	bool mTimeCount;

	CColliderLine mLine; //線分コライダ
	CColliderLine mLine2; //線分コライダ
	CColliderLine mLine3; //線分コライダ
	CCollider mCollider; //本体用コライダ

	CColliderLine mSearchLine; //瞬間移動 強制停止用

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