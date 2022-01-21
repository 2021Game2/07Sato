#include "CSceneGame.h"
#include "CSceneManager.h"
//OpenGL
#include"glut.h"
#include"CVector.h"
#include"CTriangle.h"
#include"CMatrix.h"
#include"CTransform.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CColliderTriangle.h"

#include"CPlayer.h"
#include"CTarget.h"
#include"CTargetRL.h"
#include"CTargetUD.h"
#include"CTargetTouch.h"
#include"CGoal.h"
#include"CBlock.h"
#include"CMoveBlock.h"
#include"CDamageBlock.h"
#include"CBillBoard.h"
#include"CSphere.h"

#include"CInput.h"
#include"CKey.h"
#include"CCamera.h"
#include"CSound.h"

CVector mEye;

int CSceneGame::mScore = 0;

bool CSceneGame::mStartFlag = true;


	CSound Bgm;

	CSound Fire;
	CSound FireMg;
	CSound Bomb;
	CSound Reloaded;
	CSound ScoreAdd;
	CSound Start;
	CSound Noise;	//駆動音
	CSound Jump;
	CSound Step;
	CSound Clear;
	CSound Faild;
	CSound Moving;
	CSound ChangeMode;
	CSound ChangeMode2;
	CSound Hit;


	void CSceneGame::SetStage() {
		mDamageBlock.Load("obj,mtl/DamageBlock.obj", "obj,mtl/DamageBlock.mtl");
		mTarget.Load("obj,mtl/Target.obj", "obj,mtl/Target.mtl");
		mTargetTouch.Load("obj,mtl/ScoreBlock.obj", "obj,mtl/ScoreBlock.mtl");

		//的
		new CTarget(&mTarget,
			CVector(15.0f, 5.0f, -1000.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTarget(&mTarget,
			CVector(35.0f, 25.0f, -920.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTarget(&mTarget,
			CVector(-22.0f, 30.0f, -580.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTarget(&mTarget,
			CVector(5.0f, 5.0f, -50.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTarget(&mTarget,
			CVector(-15.0f, 20.0f, 120.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTarget(&mTarget,
			CVector(11.0f, 16.0f, 320.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTarget(&mTarget,
			CVector(-25.0f, 13.0f, 550.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTarget(&mTarget,
			CVector(4.0f, 10.0f, 750.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTarget(&mTarget,
			CVector(-5.0f, 46.0f, 800.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));

		//左右に動く的
		new CTargetRL(&mTarget,
			CVector(-20.0f, 50.0f, -340.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetRL(&mTarget,
			CVector(20.0f, 20.0f, -640.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetRL(&mTarget,
			CVector(-20.0f, 50.0f, 30.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetRL(&mTarget,
			CVector(-70.0f, 5.0f, 85.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetRL(&mTarget,
			CVector(-70.0f, 20.0f, 180.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetRL(&mTarget,
			CVector(0.0f, 10.0f, 320.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetRL(&mTarget,
			CVector(-14.0f, 8.0f, 620.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetRL(&mTarget,
			CVector(12.0f, 29.0f, 800.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));

		//上下に動く的
		new CTargetUD(&mTarget,
			CVector(5.0f, 30.0f, -820.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetUD(&mTarget,
			CVector(35.0f, 30.0f, -550.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetUD(&mTarget,
			CVector(-30.0f, 40.0f, -90.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetUD(&mTarget,
			CVector(30.0f, 50.0f, 210.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetUD(&mTarget,
			CVector(-30.0f, 30.0f, 460.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));
		new CTargetUD(&mTarget,
			CVector(-20.0f, 40.0f, 580.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(1.0f, 1.0f, 1.0f));

		//接触型
		new CTargetTouch(&mTargetTouch,
			CVector(5.0f, 18.0f, -900.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(3.0f, 3.0f, 3.0f));
		new CTargetTouch(&mTargetTouch,
			CVector(-20.0f, 30.0f, -700.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(3.0f, 3.0f, 3.0f));
		new CTargetTouch(&mTargetTouch,
			CVector(0.0f, 7.0f, 50.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(3.0f, 3.0f, 3.0f));
		new CTargetTouch(&mTargetTouch,
			CVector(15.0f, 13.0f, 150.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(3.0f, 3.0f, 3.0f));
		new CTargetTouch(&mTargetTouch,
			CVector(-25.0f, 25.0f, 260.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(3.0f, 3.0f, 3.0f));

		//ダメージを受けるブロック
		new CDamageBlock(&mDamageBlock,
			CVector(-25.0f, 15.0f, -750.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(2.0f, 2.0f, 2.0f));
		new CDamageBlock(&mDamageBlock,
			CVector(-10.0f, 5.0f, -700.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(2.0f, 2.0f, 2.0f));
		new CDamageBlock(&mDamageBlock,
			CVector(10.0f, 20.0f, -580.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(2.0f, 2.0f, 2.0f));
		new CDamageBlock(&mDamageBlock,
			CVector(25.0f, 5.0f, -600.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(2.0f, 2.0f, 2.0f));
		new CDamageBlock(&mDamageBlock,
			CVector(-25.0f, 15.0f, 50.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(2.0f, 2.0f, 2.0f));
		new CDamageBlock(&mDamageBlock,
			CVector(15.0f, 5.0f, 56.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(2.0f, 2.0f, 2.0f));
		new CDamageBlock(&mDamageBlock,
			CVector(-5.0f, 5.0f, -150.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(2.0f, 2.0f, 2.0f));
		new CDamageBlock(&mDamageBlock,
			CVector(-10.0f, 20.0f, 130.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(2.0f, 2.0f, 2.0f));

	}

	void CSceneGame::Init()
	{
		mScene = EGAME;

		Bgm.Load("wav/bgm.wav");
		Bgm.Repeat();

		//SE
		Fire.Load("wav/Fire.wav");
		FireMg.Load("wav/Fire-Mg.wav");
		Bomb.Load("wav/Bomb.wav");
		Reloaded.Load("wav/Reloaded.wav");
		ScoreAdd.Load("wav/ScoreAdd.wav");
		Start.Load("wav/Start.wav");
		Noise.Load("wav/Noise.wav");
		Jump.Load("wav/Jump.wav");
		Step.Load("wav/Step.wav");
		Clear.Load("wav/Clear.wav");
		Faild.Load("wav/Faild.wav");
		Moving.Load("wav/Moving.wav");
		ChangeMode.Load("wav/ChangeMode.wav");
		ChangeMode2.Load("wav/ChangeMode2.wav");
		Hit.Load("wav/hit.wav");

		Noise.Repeat();

		//モデルファイルの入力
		mBackGround.Load("obj,mtl/Load.obj", "obj,mtl/Load.mtl");
		mModel.Load("obj,mtl/Player.obj", "obj,mtl/Player.mtl");
		mBlock.Load("obj,mtl/Block.obj", "obj,mtl/Block.mtl");
		mGoal.Load("obj,mtl/Goal.obj", "obj,mtl/Goal.mtl");

		CMatrix matrix;
		matrix.Print();

		mBackGroundMatrix.Translate(0.0f, 0.0f, 0.0f);

		//プレイヤー
		mPlayer.mpModel = &mModel;
		mPlayer.mScale = CVector(0.5f, 0.5f, 0.5f);
		mPlayer.mPosition = CVector(15.0f, 10.0f, -1100.0f) * mBackGroundMatrix;
		mPlayer.mRotation = CVector(0.0f, 0.0f, 0.0f);

		//ゴール
		new CGoal(&mGoal,
			CVector(45.0f, 1.0f, 900.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(20.0f, 20.0f, 20.0f));

		//ブロック
		new CBlock(&mBlock,
			CVector(-2.0f, 0.0f, -890.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(5.0f, 3.0f, 7.0f));
		new CBlock(&mBlock,
			CVector(-60.0f, 12.0f, -240.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(5.0f, 2.0f, 8.0f));
		new CBlock(&mBlock,
			CVector(-80.0f, 12.0f, -200.0f) * mBackGroundMatrix,
			CVector(0.0f, -30.0f, 0.0f),
			CVector(5.0f, 2.0f, 8.0f));
		new CBlock(&mBlock,
			CVector(40.0f, 35.0f, -140.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(5.0f, 2.0f, 8.0f));
		new CBlock(&mBlock,
			CVector(0.0f, 20.0f, 3.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(3.5f, 2.0f, 3.5f));
		new CBlock(&mBlock,
			CVector(-70.0f, 0.0f, 60.0f) * mBackGroundMatrix,
			CVector(-60.0f, 0.0f, 0.0f),
			CVector(5.0f, 3.0f, 6.0f));

		//動くブロック
		new CMoveBlock(&mBlock,
			CVector(-50.0f, 20.0f, -750.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(3.0f, 3.0f, 3.0f));
		new CMoveBlock(&mBlock,
			CVector(-20.0f, 40.0f, -750.0f) * mBackGroundMatrix,
			CVector(0.0f, 90.0f, 0.0f),
			CVector(3.0f, 3.0f, 3.0f));
		new CMoveBlock(&mBlock,
			CVector(-50.0f, 40.0f, -40.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(3.0f, 3.0f, 3.0f));
		new CMoveBlock(&mBlock,
			CVector(-25.0f, 20.0f, 670.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(5.0f, 2.0f, 4.0f));
		new CMoveBlock(&mBlock,
			CVector(-70.0f, 40.0f, 720.0f) * mBackGroundMatrix,
			CVector(0.0f, 0.0f, 0.0f),
			CVector(5.0f, 2.0f, 4.0f));

		SetStage();

		mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);


		//カメラ位置
		mCamX = 0.0f;
		mCamY = 8.0f;
		mCamZ = -15.0f;

		mFcamX = 0.0f;
		mFcamY = 5.0f;
		mFcamZ = 50.0f;


}


void CSceneGame::Update() {

	CTaskManager::Get()->Update();
	//コリジョンマネージャの衝突処理
	CTaskManager::Get()->TaskCollision();

	//頂点1,頂点2,頂点3,法線データの作成
	CVector v0, v1, v2, n;
	//法線を上向きで設定
	n.mX = 0.0f; n.mY = 1.0f; n.mZ = 0.0f;
	//頂点1の座標を設定
	v0.mX = 0.0f; v0.mY = 0.0f; v0.mZ = 0.5f;
	//頂点2の座標を設定
	v1.mX = 1.0f; v1.mY = 0.0f; v1.mZ = 0.0f;
	//頂点3の座標を設定
	v2.mX = 0.0f; v2.mY = 0.0f; v2.mZ = -0.5f;

	//カメラのパラメータを作成する
	CVector e, c, u;	//視点,注視点,上方向

	//視点を求める
	e = CVector(mCamX, mCamY, mCamZ) * mPlayer.mMatrix;
	//注視点を求める
	c = CVector(mFcamX, mFcamY, mFcamZ) * mPlayer.mMatrix;
	//上方向を求める
	u = CVector(0, 1, 0);

	//カメラクラスの設定
	Camera.Set(e, c, u);
	Camera.Render();

	mBackGround.Render();

	//タスクリストの削除
	CTaskManager::Get()->Delete();

	//スタート時一時ストップ
	if (mStartFlag == true) {
		if (CKey::Once(VK_SPACE)) {
			Start.Play();
			mStartFlag = false;
		}
	}

	//ゴール時スコア表示
	if (CGoal::mTouchGoal == true) {
		mClearScore = mScore;
		mClearTime = CPlayer::mTime;
	}
	if (CGoal::mTouchGoal == true) {
		if (CKey::Once('R')) {
			CPlayer::mPlayerHp = 3;
			CPlayer::mScore = 0;
			CPlayer::mTime = 0;
			mPlayer.mPosition = CVector(15.0f, 10.0f, -1100.0f) * mBackGroundMatrix;
			mPlayer.mRotation = CVector(0.0f, 0.0f, 0.0f);
			SetStage();
			CGoal::mTouchGoal = false;
			mStartFlag = true;
		}
	}

	//ゲームオーバー時
	if (CPlayer::mPlayerHp == 0) {
		if (CKey::Once('R')) {
			CPlayer::mPlayerHp = 3;
			CPlayer::mScore = 0;
			CPlayer::mTime = 0;
			mPlayer.mPosition = CVector(15.0f, 10.0f, -1100.0f) * mBackGroundMatrix;
			mPlayer.mRotation = CVector(0.0f, 0.0f, 0.0f);
			SetStage();
			mStartFlag = true;
		}
		if (CKey::Once('T')) {
			CPlayer::mPlayerHp = 1;
			mStartFlag = true;
		}
	}
	
	//描画
	CTaskManager::Get()->Render();
	//CCollisionManager::Get()->Render();
}

//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}