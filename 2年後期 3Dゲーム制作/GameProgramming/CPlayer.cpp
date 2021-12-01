//プレイヤークラスのインクルード
#include"CPlayer.h"
#include"CGoal.h"
#include"CBlock.h"
#include"CKey.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CText.h"
#include"CUtil.h"
#include"CInput.h"
#include"CSound.h"

#define GLAVITY -0.07f //重力
#define JUMPPOWER 3.0f	//ジャンプ力
#define JUMPRECHARGE 70	//次ジャンプまでの待ち時間

#define STEPSPEED 17
#define STEPMOVE 5
#define STEPRECHARGE 120

#define VELOCITY 0.065f	//移動力
#define SPEEDREMIT 0.9	//速度制限
#define SUBERI 2	//滑り易さ

#define RELOAD 80

#define PHP 5	//HP

#define MOUSESPEEDX 1.2f	//マウス横感度
#define MOUSESPEEDY 1.2f	//マウス縦感度

int CPlayer::mPlayerHp = PHP;

float CPlayer::mSpeedX = NULL;
float CPlayer::mSpeedY = NULL;
float CPlayer::mSpeedZ = NULL;

CText mText;

int CPlayer::mScore;

float CPlayer::mTime;

CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 0.0f, -6.0f), CVector(0.0f, 0.0f, 6.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 8.0f, 0.0f), CVector(0.0f, -8.0f, 0.0f))
, mLine3(this, &mMatrix, CVector(6.0f, 0.0f, 0.0f), CVector(-6.0f, 0.0f, 0.0f))
, mCollider(this, &mMatrix, CVector(0.0f,0.0f,0.0f),3.5f)
, mSearchLine(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 20.0f))
{
	mText.LoadTexture("FontWhite.tga", 1, 64);
	CCharacter::mTag = EPLAYER; //タグの設定
	
	mJumpTimer = 0;
	mJump = true;

	mTimeCount = true;

	mStep = -1;
	mStepRecharge = 0;

	mReloadTime = 0;
	mNotHit = 0;

	mTime = 0;
	mScore = 0;


	mBeforMouseX = 0;
	mBeforMouseY = 0;
	mMouseMoveX = 0;
	mMouseMoveY = 0;

	mMouseSpeedX = MOUSESPEEDX;
	mMouseSpeedY = MOUSESPEEDY;

	mSearchLine.mTag = CCollider::ESEARCH;
}

//更新処理
void CPlayer::Update() {
	if (mPosition.mY < 0) {
		mPosition.mY = 0.1f;
	}

	//CTransformの更新
	CTransform::Update();

	if (mPlayerHp >= 0) {

		//shiftキーでダッシュ
		if (CKey::Push(VK_SHIFT) && mSpeedZ < SPEEDREMIT + 3.0f) {
			if (CKey::Push('W'))
				mSpeedZ += VELOCITY + 0.4f;
		}

		//移動
		if (CKey::Push('W') && mSpeedZ < SPEEDREMIT + 1.1f) {
			//Z軸の+移動
			mSpeedZ += VELOCITY + 0.2f;
		}
		if (CKey::Push('S') && mSpeedZ > -SPEEDREMIT - 0.3f) {
			//Z軸の-移動
			mSpeedZ -= VELOCITY;
		}
		if (CKey::Push('A') && mSpeedX < SPEEDREMIT) {
			//X軸の+移動
			mSpeedX += VELOCITY;
		}
		if (CKey::Push('D') && mSpeedX > -SPEEDREMIT) {
			//X軸の-移動
			mSpeedX -= VELOCITY;
		}


		//スペースキーでジャンプ
		if (CKey::Once(VK_SPACE) && mJump == true) {
			mSpeedY = JUMPPOWER;
			mJumpTimer = JUMPRECHARGE;
			mJump = false;
		}

		//一時的旋回キー
		if (CKey::Push(VK_RIGHT)) {
			mRotation.mY -= 1;
		}
		if (CKey::Push(VK_LEFT)) {
			mRotation.mY += 1;
		}

		if (CKey::Push(VK_UP)) {
			mRotation.mX -= 1;
		}
		if (CKey::Push(VK_DOWN)) {
			mRotation.mX += 1;
		}

		//視点上下角制限
		if (mRotation.mX < -80)
			mRotation.mX = -79;

		if (mRotation.mX > 75)
			mRotation.mX = 74;



		//ここからマウスによる操作
		//左クリックで弾を発射
		if (CKey::Once(VK_LBUTTON) && mReloadTime < 0) {
			CBullet* bullet = new CBullet();
			bullet->mTag = CCharacter::EBULLET;
			bullet->Set(1.5f, 14.0f);
			bullet->mPosition = CVector(-3.0f, 3.0f, 10.0f) * mMatrix;
			bullet->mRotation = mRotation;
			bullet->Update();
			mReloadTime = RELOAD;
		}
		if (mReloadTime > -1) {
			mReloadTime--;
		}

		//瞬間移動
		if (CKey::Once(VK_RBUTTON) && mStepRecharge < 0) {
			mStep = STEPMOVE;
			mStepRecharge = 60;
		}
		if (mStep > 0) {
			mSpeedZ += STEPSPEED;
		}
		if (mStep <= 0 && mStep >= -5 && mSpeedZ > 0.2f) {
			mSpeedZ -= 14.0f;
		}
		mStep--;
		mStepRecharge--;


		//マウス設定
		float mMousePosX, mMousePosY;	//マウスカーソル座標取得用
		//マウスカーソル座標の取得
		CInput::GetMousePos(&mMousePosX, &mMousePosY);

		//ゲーム画面中心からの座標へ変換
		mMousePosX -= 400;
		mMousePosY = 300 - mMousePosY;

		//マウスの移動量
		mMouseMoveX = mMousePosX - mBeforMouseX;
		mMouseMoveY = mMousePosY - mBeforMouseY;

		//視点操作
		mRotation.mX -= mMouseMoveY / mMouseSpeedX;
		mRotation.mY -= mMouseMoveX / mMouseSpeedY;

		mBeforMouseX = mMousePosX;
		mBeforMouseY = mMousePosY;

		//ここまでマウスの操作

	}

	//位置の移動
	mPosition = CVector(mSpeedX, 0.0f, mSpeedZ) * mMatrix;
	//重力
	mSpeedY += GLAVITY;
	mPosition.mY += mSpeedY;

	//慣性擬き
		//X
	if (mSpeedX >= 0.01) {
		mSpeedX -= VELOCITY / SUBERI;
	}
	else if (mSpeedX <= -0.01) {
		mSpeedX += VELOCITY / SUBERI;
	}
	//Z
	if (mSpeedZ >= 0.01) {
		mSpeedZ -= VELOCITY / SUBERI;
	}
	else if (mSpeedZ <= -0.01) {
		mSpeedZ += VELOCITY / SUBERI;
	}


	if (mJumpTimer >= 0)
		mJumpTimer--;

	//時間加算
	mTime++;

	//無敵時間減算
	mNotHit--;

}

//接触判定
void CPlayer::Collision(CCollider *m, CCollider *o){
	//自身のコライダタイプで判定
	switch (m->CCollider::mType) {
	case CCollider::ESPHERE:
		//相手のコライダが三角コライダの時
		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;		//調整用ベクトル
			//三角形と線分の衝突判定
			CCollider::CollisionTriangleSphere(o, m, &adjust);
			//位置の更新(mPosition + adjust)
			mPosition = mPosition - adjust * -1;

			if (mPosition.mY < 2.0f) {
				//ジャンプ再使用
				if (mJumpTimer < 0) {
					mJump = true;
				}
				//瞬間移動の減速
				//着地
				if (mPosition.mY < 1.0f && mSpeedY < 0) {
					mSpeedY += 0.009f;
				}
			}
			CTransform::Update();
		}

		//ダメージブロック接触時
		if(CCollider::Collision(m,o)){
			if (o->mpParent->mTag == EDAMAGEBLOCK) {
				if (mNotHit < 0) {
					mPlayerHp--;
					mNotHit = 5;
					new CEffect(o->mpParent->mPosition, 10.0f, 10.0f, "exp.tga", 4, 4, 2);
					o->mpParent->mEnabled = false;
				}
			}
		}
		break;

	case CCollider::ELINE:
		if (o->mpParent != nullptr) {
			if (o->mType == CCollider::ETRIANGLE) {
				if (o->mpParent->mTag == EBLOCK || o->mpParent->mTag == EMOVEBLOCK) {
					if (mSpeedY < -4.0) {
						mSpeedY += 0.005f;
					}
					if (mJumpTimer < 0) {
						mJump = true;
					}
					break;
				}
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

	//速度表示
	//文字列の設定
	sprintf(buf, "PY:%5f", mPosition.mY);
	//文字列の描画
	mText.DrawString(buf, -300, 200, 8, 16);

	//速度表示
	//文字列の設定
	//sprintf(buf, "VX:%f", mSpeedX);
	//文字列の描画
	//mText.DrawString(buf, -300, 200, 8, 16);

	//文字列の設定
	sprintf(buf, "VY:%f", mSpeedY);
	//文字列の描画
	mText.DrawString(buf, -300, 150, 8, 16);

	//文字列の設定
	sprintf(buf, "VZ:%f", mSpeedZ);
	//文字列の描画
	mText.DrawString(buf, -300, 100, 8, 16);


	//文字列の設定
	sprintf(buf, "HP:%d", mPlayerHp);
	//文字列の描画
	mText.DrawString(buf, -100, 250, 20, 20);

	//文字列の設定
	sprintf(buf, "SCORE:%d",mScore);
	//文字列の描画
	mText.DrawString(buf, 150, 250, 13, 13);

	//文字列の設定
	sprintf(buf, "TIME:%5.1f", mTime/60);
	//文字列の描画
	mText.DrawString(buf, 100, 210, 13, 13);

	//照準(仮)
	if (CGoal::mTouchGoal == false) {
		//文字列の設定
		sprintf(buf, "[+]");
		//文字列の描画
		mText.DrawString(buf, -30, 20, 15, 15);
	}
	//ゴール
	else if (CGoal::mTouchGoal == true) {
		glColor4f(0.1f, 0.3f, 0.8f, 1.0f);
		sprintf(buf, "GOAL");
		mText.DrawString(buf, -120, 0, 35, 35);
	}

	if (mPlayerHp == 0) {
		glColor4f(0.5f, 0.3f, 0.3f, 1.0f);
		sprintf(buf, "FAILED");
		mText.DrawString(buf, -150, 0, 35, 35);
	}

	//2D描画終了
	CUtil::End2D();
}

//衝突処理
void CPlayer::TaskCollision(){
	//コライダの優先度変更
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	mCollider.ChangePriority();
	mSearchLine.ChangePriority();
	//衝突処理 実行
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mSearchLine, COLLISIONRANGE);
}