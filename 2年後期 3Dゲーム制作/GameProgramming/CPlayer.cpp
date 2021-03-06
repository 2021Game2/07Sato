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
#include"CSceneGame.h"
#include"stdlib.h"

#define GLAVITY -0.07f //重力
#define JUMPPOWER 3.0f	//ジャンプ力
#define JUMPRECHARGE 70	//次ジャンプまでの待ち時間

#define STEPSPEED 17
#define STEPMOVE 5
#define STEPRECHARGE 120

#define VELOCITY 0.065f	//移動力
#define SPEEDREMIT 0.9	//速度制限
#define SUBERI 2	//滑り易さ

#define RELOAD -50

#define PHP 3	//HP

#define MOUSESPEEDX 4.0f	//マウス横感度
#define MOUSESPEEDY 4.0f	//マウス縦感度

int CPlayer::mPlayerHp = PHP;

float CPlayer::mSpeedX = NULL;
float CPlayer::mSpeedY = NULL;
float CPlayer::mSpeedZ = NULL;

CText mText;

int CPlayer::mScore;

float CPlayer::mTime;

//音声
extern CSound Fire;
extern CSound Reloaded;
extern CSound Bomb;
extern CSound Jump;
extern CSound Step;
extern CSound Faild;
extern CSound Moving;
extern CSound FireMg;
extern CSound ChangeMode;
extern CSound ChangeMode2;



CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 0.0f, -8.0f), CVector(0.0f, 0.0f, 8.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 8.0f, 0.0f), CVector(0.0f, -8.0f, 0.0f))
, mLine3(this, &mMatrix, CVector(8.0f, 0.0f, 0.0f), CVector(-8.0f, 0.0f, 0.0f))
, mCollider(this, &mMatrix, CVector(0.0f,0.0f,0.0f),3.5f)
//, mSearchLine(this, &mMatrix, CVector(0.0f, 0.0f, 80.0f), CVector(0.0f, 0.0f, -80.0f))
{
	mText.LoadTexture("tga/FontWhite.tga", 1, 64);
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

	mFaildSound = true;

	mMachineGun = false;

	mMouseSetX = 600;
	mMouseSetY = 400;

	mBeforMouseX = 0;
	mBeforMouseY = 0;
	mMouseMoveX = 0;
	mMouseMoveY = 0;

	mFreeCursor = false;
	CInput::SetMousePos(mMouseSetX, mMouseSetY);

}

//更新処理
void CPlayer::Update() {
	if (mPosition.mY < 0) {
		mPosition.mY = 0.1f;
	}

	//CTransformの更新
	CTransform::Update();

	if (mPlayerHp > 0) {
		if (CSceneGame::mStartFlag == false) {	//スタート前の行動制限

			//時間加算
			if (CGoal::mTouchGoal == false) {
				mTime++;
			}

			//shiftキーでダッシュ
			if (CKey::Push(VK_SHIFT) && mSpeedZ < SPEEDREMIT + 3.0f) {
				if (CKey::Push('W'))
					mSpeedZ += VELOCITY + 0.4f;
				Moving.Play();
			}
			//移動
			if (CKey::Push('W') && mSpeedZ < SPEEDREMIT + 1.1f) {
				//Z軸の+移動
				mSpeedZ += VELOCITY + 0.2f;
				Moving.Play();
			}
			if (CKey::Push('S') && mSpeedZ > -SPEEDREMIT - 0.3f) {
				//Z軸の-移動
				mSpeedZ -= VELOCITY;
				Moving.Play();
			}
			if (CKey::Push('A') && mSpeedX < SPEEDREMIT) {
				//X軸の+移動
				mSpeedX += VELOCITY;
				Moving.Play();
			}
			if (CKey::Push('D') && mSpeedX > -SPEEDREMIT) {
				//X軸の-移動
				mSpeedX -= VELOCITY;
				Moving.Play();
			}

			//スペースキーでジャンプ
			if (CKey::Once(VK_SPACE) && mJump == true) {
				mSpeedY = JUMPPOWER;
				mJumpTimer = JUMPRECHARGE;
				Jump.Play();
				mJump = false;
			}

			//ここからマウスによる操作
			//左クリックで弾を発射
			if (mMachineGun == false) {
				if (CKey::Once(VK_LBUTTON) && mReloadTime > 0) {
					CBullet* bullet = new CBullet();
					bullet->Set(1.5f, 14.0f);
					bullet->Damage(15);
					bullet->mPosition = CVector(-3.0f, 3.0f, 10.0f) * mMatrix;
					new CEffect(bullet->mPosition, 2.0f, 2.0f, "tga/flash.tga", 1,1, 2);
					bullet->mRotation = mRotation;
					bullet->Update();
					Fire.Play();
					mReloadTime = RELOAD;
				}
				if (mReloadTime < 1) {
					mReloadTime++;
				}
				if (mReloadTime == 0) {
					Reloaded.Play();
				}
			}
			else {
				if (CKey::Push(VK_LBUTTON) && mReloadTime > 0) {
					CBullet* bullet = new CBullet();
					bullet->Set(1.5f, 14.0f);
					bullet->Damage(1);
					bullet->mPosition = CVector(-3.0f, 4.0f, 4.0f) * mMatrix;
					new CEffect(bullet->mPosition, 1.2f, 1.2f, "tga/flash.tga", 1, 1, 2);
					bullet->mRotation = mRotation;
					bullet->Update();
					FireMg.Play();
					mReloadTime = -6;
				}
				if (mReloadTime < 1) {
					mReloadTime++;
				}
			}
			//右クリックで瞬間移動
			if (CKey::Once(VK_RBUTTON) && mStepRecharge < 0) {
				mStep = STEPMOVE;
				Step.Play();
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
		}	//ここまでがスタート前の動作制限
		else {	//スタート前限定操作
		//マシンガンモード
			if (CKey::Once('M')) {
				if (mMachineGun == true) {
					mMachineGun = false;
				}
				else {
					mMachineGun = true;
				}
				ChangeMode.Play();
				ChangeMode2.Play();
			}
		}

			//視点上下角制限
			if (mRotation.mX < -80)
				mRotation.mX = -79;

			if (mRotation.mX > 75)
				mRotation.mX = 74;



			//マウス設定
			//マウスカーソル座標の取得
			CInput::GetMousePos(&mMousePosX, &mMousePosY);

			//ゲーム画面中心からの座標へ変換
			mMousePosX -= 600;
			mMousePosY = 400 - mMousePosY;

			//マウスの現在の座標を取得する
			//マウスの位置を固定
			if (mMousePosX > 600 || mMousePosX < -600 ||
				mMousePosY > 400 || mMousePosY < -400) {
				if (mFreeCursor == false) {
					mBeforMouseX = 0;
					mBeforMouseY = 0;
					CInput::SetMousePos(mMouseSetX, mMouseSetY);
				}
			}
			else {
				//視点操作
				mMouseMoveX = mMousePosX - mBeforMouseX;
				mMouseMoveY = mMousePosY - mBeforMouseY;

				mRotation.mX -= mMouseMoveY / MOUSESPEEDX;
				mRotation.mY -= mMouseMoveX / MOUSESPEEDY;

				mBeforMouseX = mMousePosX;
				mBeforMouseY = mMousePosY;
			}
			if (CKey::Push('F')) {
				mFreeCursor = true;
				ShowCursor(true);
			}
			else {
				mFreeCursor = false;
				ShowCursor(false);
			}
			//ここまでマウスの操作

		}	//ここまでがif(mPlayerHp > 0)




	else {
		if (mFaildSound == true) {
			Faild.Play();
			mFaildSound = false;
		}
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

	//無敵時間減算
	mNotHit--;

	if (mPosition.mZ > 920.0f) {
		mPosition.mZ = 920.0f;
	}

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
				//着地
				if (mPosition.mY < 1.0f && mSpeedY < 0) {
					mSpeedY += 0.009f;
				}
			}
			CTransform::Update();
		}
		
		//ダメージブロック接触時
		if(o->mpParent != nullptr){
		if(CCollider::Collision(m,o)){
			if (o->mpParent->mTag == EDAMAGEBLOCK) {
				if (mNotHit < 0) {
					mPlayerHp--;
				}
				mNotHit = 30;
				new CEffect(o->mpParent->mPosition, 10.0f, 10.0f, "tga/exp.tga", 4, 4, 2);
				Bomb.Play();
				o->mpParent->mEnabled = false;
			}
			}
		}
		break;

	case CCollider::ELINE:
		if (o->mpParent != nullptr) {
			if (o->mType == CCollider::ETRIANGLE) {
				if (o->mpParent->mTag == EBLOCK || o->mpParent->mTag == EMOVEBLOCK) {
					CVector adjust;		//調整用ベクトル
					//三角形と線分の衝突判定
					CCollider::CollisionTriangleLine(o, m, &adjust);
					//位置の更新(mPosition + adjust)
					mPosition = mPosition - adjust * -1;
					if (mSpeedY < -4.0) {
						mSpeedY += 0.006f;
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
	//sprintf(buf, "PY:%5f", mPosition.mZ);
	//文字列の描画
	//mText.DrawString(buf, -300, 200, 8, 16);

	//速度表示
	//文字列の設定
	//sprintf(buf, "VX:%f", mSpeedX);
	//文字列の描画
	//mText.DrawString(buf, -300, 200, 8, 16);

	//文字列の設定
	//sprintf(buf, "VY:%f", mSpeedY);
	//文字列の描画
	//mText.DrawString(buf, -300, 150, 8, 16);

	//文字列の設定
	//sprintf(buf, "VZ:%f", mSpeedZ);
	//文字列の描画
	//mText.DrawString(buf, -300, 100, 8, 16);


	//HP表示
	sprintf(buf, "HP:", mPlayerHp);
	mText.DrawString(buf, -350, -250, 20, 20);

	for (int h = 0; mPlayerHp > h; h++) {
		sprintf(buf, "I");
		mText.DrawString(buf, (-250 + (h * 20)), -250, 20, 20);
	}

	//スコア
	sprintf(buf, "SCORE:%d",mScore);
	mText.DrawString(buf, 150, 250, 13, 13);

	sprintf(buf, "TIME:%5.1f", mTime/60);
	mText.DrawString(buf, 100, 210, 13, 13);


	if (mMachineGun == true) {
		sprintf(buf, "M:MACHINE GUN");
		mText.DrawString(buf, -300, 280, 12, 12);
	}
	else {
		sprintf(buf, "M:RIFLE");
		mText.DrawString(buf, -300, 280, 12, 12);
	}

	//リロード状況
	if (mMachineGun == false) {
		if (mReloadTime < 0) {
			sprintf(buf, ":RELOADING");
			mText.DrawString(buf, 150, -220, 10, 10);

			for (int r = -80; mReloadTime > r; r += 20) {
				sprintf(buf, "[]");
				mText.DrawString(buf, 40 - r, -220, 12, 12);
			}
		}
	}

	//スタート前
	if (CSceneGame::mStartFlag == true) {
		sprintf(buf, "READY");
		mText.DrawString(buf, -130, 0, 35, 35);
		sprintf(buf, "START TO SPACE");
		mText.DrawString(buf, -220, -50, 18, 18);
	}
	//ゴール
	else if (CGoal::mTouchGoal == true) {
		glColor4f(0.1f, 0.3f, 0.8f, 1.0f);
		sprintf(buf, "GOAL");
		mText.DrawString(buf, -120, 0, 35, 35);
		glColor4f(0.5f, 0.6f, 0.8f, 1.0f);
		sprintf(buf, "RESTART TO R");
		mText.DrawString(buf, -220, -50, 20, 20);
	}
	//ゲームオーバー
	else if (mPlayerHp == 0) {
		mScore = 0;
		glColor4f(0.5f, 0.3f, 0.3f, 1.0f);
		sprintf(buf, "FAILED");
		mText.DrawString(buf, -150, 0, 35, 35);
		glColor4f(0.5f, 0.6f, 0.8f, 1.0f);
		sprintf(buf, "RESTART TO R");
		mText.DrawString(buf, -220, -50, 20, 20);
		sprintf(buf, "CONTINUE TO T");
		mText.DrawString(buf, -260, -100, 20, 20);
	}
	//照準(仮)
	else if (CGoal::mTouchGoal != true) {
		//文字列の設定
		sprintf(buf, "[+]");
		//文字列の描画
		mText.DrawString(buf, -30, 20, 15, 15);
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
	//mSearchLine.ChangePriority();
	//衝突処理 実行
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	//CCollisionManager::Get()->Collision(&mSearchLine, COLLISIONRANGE);
}