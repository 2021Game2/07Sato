//プレイヤークラスのインクルード
#include"CPlayer.h"
#include"CKey.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CText.h"
#include"CUtil.h"
#include"CInput.h"
#include"CSound.h"

#define GLAVITY -0.02f //重力
#define JUMPPOWER 0.7f	//ジャンプ力
#define JUMPRECHARGE 70	//次ジャンプまでの待ち時間

#define STEPSPEED 2
#define STEPRECHARGE 120

#define VELOCITY 0.065f	//移動力
#define SPEEDREMIT 0.6	//速度制限
#define MOUSESPEEDX 1.2f	//マウス横感度
#define MOUSESPEEDY 1.2f	//マウス縦感度
#define SUBERI 2	//滑り易さ

#define RELOAD 120

#define PHP 150	//HP

int CPlayer::mPlayerHp = PHP;

CText mText;


CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 0.0f, -6.0f), CVector(0.0f, 0.0f, 6.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 6.0f, 0.0f), CVector(0.0f, -6.0f, 0.0f))
, mLine3(this, &mMatrix, CVector(6.0f, 0.0f, 0.0f), CVector(-6.0f, 0.0f, 0.0f))
, mLine4(this, &mMatrix, CVector(0.0f, 4.0f, 4.0f), CVector(0.0f, -4.0f, -4.0f))
, mLine5(this, &mMatrix, CVector(0.0f, -4.0f, 4.0f), CVector(0.0f, 4.0f, -4.0f))
, mCollider(this, &mMatrix, CVector(0.0f,0.0f,0.0f),3.5f)
{
	mText.LoadTexture("FontWhite.tga", 1, 64);
	mTag = EPLAYER; //タグの設定
	mSpeedX = NULL;
	mSpeedY = NULL;
	mSpeedZ = NULL;
	mJumpTimer = 0;
	mJump = true;
	mStep = 0;

	mBeforMouseX = 0;
	mBeforMouseY = 0;
	mMouseMoveX = 0;
	mMouseMoveY = 0;

	mReloadTime = 0;

	mMouseSpeedX = MOUSESPEEDX;
	mMouseSpeedY = MOUSESPEEDY;
}

//更新処理
void CPlayer::Update(){
  //マウス設定
	float mMousePosX, mMousePosY;	//マウスカーソル座標取得用
	//マウスカーソル座標の取得
	CInput::GetMousePos(&mMousePosX, &mMousePosY);

	//ゲーム画面中心からの座標へ変換
	mMousePosX -= 400;
	mMousePosY = 300 - mMousePosY;

	mSpeedY += GLAVITY;
	mPosition.mY += mSpeedY;

	if (mPlayerHp >= 0){
		//スペースキーでジャンプ
		if (CKey::Once(VK_SPACE) && mJump == true){
			mSpeedY = JUMPPOWER;
			mJumpTimer = JUMPRECHARGE;
			mJump = false;
		}

		//shiftキーでダッシュ
		//if (CKey::Once(VK_SHIFT)){
		//	if (CKey::Push('W')){
		//		//Z軸の+移動
		//		mSpeedZ = STEPSPEED;
		//	}


		//CTransformの更新
		CTransform::Update();

		//移動
		if (CKey::Push('A') && mSpeedX < SPEEDREMIT){
			//X軸の+移動
			mSpeedX += VELOCITY;
		}
		if (CKey::Push('D') && mSpeedX > -SPEEDREMIT){
			//X軸の-移動
			mSpeedX -= VELOCITY;
		}
		if (CKey::Push('S') && mSpeedZ > -SPEEDREMIT){
			//Z軸の-移動
			mSpeedZ -= VELOCITY;
		}
		if (CKey::Push('W') && mSpeedZ < SPEEDREMIT + 0.3f){
			//Z軸の+移動
			mSpeedZ += VELOCITY;
		}



		//ここからマウスによる操作
		//移動量
		mMouseMoveX = mMousePosX - mBeforMouseX;
		mMouseMoveY = mMousePosY - mBeforMouseY;

		//視点操作
		mRotation.mX -= mMouseMoveY / mMouseSpeedX;
		mRotation.mY -= mMouseMoveX / mMouseSpeedY;

		if (mRotation.mX < -90)
			mRotation.mX = -89;

		if (mRotation.mX > 85)
			mRotation.mX = 84;




		//左クリックで弾を発射
		if (CKey::Push(VK_LBUTTON) && mReloadTime < 0) {
			CBullet* bullet = new CBullet();
			bullet->mTag = CCharacter::EBULLETPLAYER;
			bullet->Set(0.5f, 4.0f);
			bullet->mPosition = CVector(-3.0f, 3.0f, 10.0f) * mMatrix;
			bullet->mRotation = mRotation;
			bullet->Update();
			mReloadTime = RELOAD;
		}
		if (mReloadTime > -1) {
			mReloadTime--;
		}

		if (CKey::Once(VK_RBUTTON)){
			mStep = 5;
		}
		if (mStep > 0){
			mSpeedZ += 12;
		}
		else if (mStep == 0) {
			mSpeedZ = 0;
		}
		mStep--;


		//ここまでマウスの操作
	}

	//位置の移動
	mPosition = CVector(mSpeedX,0.0f,mSpeedZ) * mMatrix;

	//慣性擬き
	if (mPosition.mY < 5){
		//X
		if (mSpeedX >= 0.01){
			mSpeedX -= VELOCITY / SUBERI;
		}
		else if (mSpeedX <= -0.01){
			mSpeedX += VELOCITY / SUBERI;
		}
		//Z
		if (mSpeedZ >= 0.01){
			mSpeedZ -= VELOCITY / SUBERI;
		}
		else if (mSpeedZ <= -0.01){
			mSpeedZ += VELOCITY / SUBERI;
		}
	}

	mBeforMouseX = mMousePosX;
	mBeforMouseY = mMousePosY;

	if (mJumpTimer >= 0)
	mJumpTimer--;

}

//接触判定
void CPlayer::Collision(CCollider *m, CCollider *o){
	//自身のコライダタイプで判定
	switch (m->mType){
	case CCollider::ELINE: //線分コライダ

		//相手のコライダが三角コライダの時
		if (o->mType == CCollider::ETRIANGLE){
			CVector adjust; //	調整用ベクトル
			//三角形と線分の衝突判定
			CCollider::CollisionTriangleLine(o, m, &adjust);
			//位置の更新(mPosition + adjust)
			mPosition = mPosition - adjust * -1;
			//疑似着地
			if (mPosition.mY < 1.6f && mJumpTimer < 0){
				mJump = true;
				if (mPosition.mY < 0.5f)
					mSpeedY += 0.002f;
			}
			CTransform::Update();
			break;
		}

	case CCollider::ESPHERE:
		if (CCollider::Collision(m, o)){
			if (o->mpParent->mTag == EBULLETENEMY){
				mPlayerHp--;
				new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
				break;
			}
		}
		
	}
}

//画面上2D描画
void CPlayer::Render(){
	//親の描画処理
	CCharacter::Render();

	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);
	//描画色の設定
	glColor4f(0.1f, 0.8f, 0.1f, 1.0f);
	//文字列編集エリアの作成
	char buf[64];

	////速度表示
	////文字列の設定
	//sprintf(buf, "PY:%5f", mPosition.mY);
	////文字列の描画
	//mText.DrawString(buf, -300, 200, 8, 16);

	////速度表示
	////文字列の設定
	//sprintf(buf, "VX:%f", mSpeedX);
	////文字列の描画
	//mText.DrawString(buf, -300, 200, 8, 16);

	////文字列の設定
	//sprintf(buf, "VY:%f", mSpeedY);
	////文字列の描画
	//mText.DrawString(buf, -300, 150, 8, 16);

	////文字列の設定
	//sprintf(buf, "VZ:%f", mSpeedZ);
	////文字列の描画
	//mText.DrawString(buf, -300, 100, 8, 16);


	//文字列の設定
	sprintf(buf, "HP:%d", mPlayerHp);
	//文字列の描画
	mText.DrawString(buf, -100, 250, 20, 20);


	//照準(仮)
	//文字列の設定
	sprintf(buf, "[+]");
	//文字列の描画
	mText.DrawString(buf, -30, 20, 15, 15);

	//終了判定
	

	//2D描画終了
	CUtil::End2D();
}

//衝突処理
void CPlayer::TaskCollision(){
	//コライダの優先度変更
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	mLine4.ChangePriority();
	mLine5.ChangePriority();
	mCollider.ChangePriority();
	//衝突処理 実行
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine4, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine5, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}