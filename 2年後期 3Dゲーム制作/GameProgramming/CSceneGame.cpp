#include "CSceneGame.h"
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
#include"CBarricade.h"
#include"CPillar.h"

#include"CInput.h"
#include"CKey.h"
#include"CCamera.h"
#include"CSound.h"

CVector mEye;

int CSceneGame::mScore = 0;

bool CSceneGame::mStartFlag = true;


	//CSound Bgm;

	CSound Fire;
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

void CSceneGame::Init()
{
	mScene = EGAME;

	//Bgm.Load("bgm.wav");
	//Bgm.Repeat();

	//SE
	Fire.Load("Fire.wav");
	Bomb.Load("Bomb.wav");
	Reloaded.Load("Reloaded.wav");
	ScoreAdd.Load("ScoreAdd.wav");
	Start.Load("Start.wav");
	Noise.Load("Noise.wav");
	Jump.Load("Jump.wav");
	Step.Load("Step.wav");
	Clear.Load("Clear.wav");
	Faild.Load("Faild.wav");
	Moving.Load("Moving.wav");

	Noise.Repeat();


	//モデルファイルの入力
	mBackGround.Load("Load.obj", "Load.mtl");

	mModel.Load("Character.obj", "Character.mtl");
	mPillar.Load("Pillar.obj","Pillar.mtl");
	mBarricade.Load("barricade.obj", "barricade.mtl");
	mBlock.Load("Block.obj", "Block.mtl");
	mDamageBlock.Load("DamageBlock.obj", "DamageBlock.mtl");
	mTarget.Load("Target.obj", "Target.mtl");
	mGoal.Load("Goal.obj", "Goal.mtl");
	mTargetTouch.Load("ScoreBlock.obj", "ScoreBlock.mtl");
	//mGun.Load("Gun.obj", "Gun.mtl");

	CMatrix matrix;
	matrix.Print();

	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.0f);

	//プレイヤー
	mPlayer.mpModel = &mModel;
	mPlayer.mScale = CVector(0.5f, 0.5f, 0.5f);
	mPlayer.mPosition = CVector(0.0f, 10.0f, -215.0f) * mBackGroundMatrix;
	mPlayer.mRotation = CVector(0.0f, 0.0f, 0.0f);



	//的
	new CTarget(&mTarget,
		CVector(5.0f, 5.0f, -50.0f) * mBackGroundMatrix,
		CVector(0.0f,90.0f,0.0f),
		CVector(1.0f, 1.0f, 1.0f));

	//左右に動く的
	new CTargetRL(&mTarget,
		CVector(-20.0f, 50.0f, 30.0f) * mBackGroundMatrix,
		CVector(0.0f, 90.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f));

	//上下に動く的
	new CTargetUD(&mTarget,
		CVector(-30.0f, 50.0f, -90.0f) * mBackGroundMatrix,
		CVector(0.0f, 90.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f));

	//接触型
	new CTargetTouch(&mTargetTouch,
		CVector(0.0f, 7.0f, 50.0f) * mBackGroundMatrix,
		CVector(0.0f,0.0f,0.0f),
		CVector(3.0f, 3.0f, 3.0f));

	//ブロック
	new CBlock(&mBlock, 
		CVector(0.0f, 30.0f, 0.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(3.0f, 3.0f, 3.0f));

	//ブロック
	new CBlock(&mBlock,
		CVector(40.0f, 0.0f, 60.0f) * mBackGroundMatrix,
		CVector(-60.0f, 0.0f, 0.0f),
		CVector(3.0f, 2.0f, 3.0f));

	//動くブロック
	new CMoveBlock(&mBlock,
		CVector(-50.0f, 40.0f, -40.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(3.0f, 3.0f, 3.0f));

	//ダメージを受けるブロック
	new CDamageBlock(&mDamageBlock,
		CVector(0.0f, 20.0f, -150.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(2.0f, 2.0f, 2.0f));
	new CDamageBlock(&mDamageBlock,
		CVector(20.0f, 20.0f, -150.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(2.0f, 2.0f, 2.0f));
	new CDamageBlock(&mDamageBlock,
		CVector(0.0f, 5.0f, -150.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(2.0f, 2.0f, 2.0f));
	new CDamageBlock(&mDamageBlock,
		CVector(20.0f, 5.0f, -150.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(2.0f, 2.0f, 2.0f));
	new CDamageBlock(&mDamageBlock,
		CVector(0.0f, 20.0f, -100.0f) * mBackGroundMatrix,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(2.0f, 2.0f, 2.0f));

	//ゴール
	new CGoal(&mGoal,
		CVector(45.0f, 1.0f, 900.0f) * mBackGroundMatrix,
		CVector(0.0f, 90.0f, 0.0f),
		CVector(20.0f, 20.0f, 20.0f));


	mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);


	//カメラ位置
	mCamX = 0.0f;
	mCamY = 13.0f;
	mCamZ = -15.0f;
	
	mFcamX = 0.0f;
	mFcamY = 8.5f;
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
			mStartFlag = false;
		}
	}

	//ゴール時スコア表示
	/*if (CGoal::mTouchGoal == true) {
		mClearScore = mScore;
		mClearTime = CPlayer::mTime;
		mResultTimer--;
	}*/

	//ゲームオーバー時
	if (CPlayer::mPlayerHp == 0) {
		if (CKey::Once('R')) {
			CPlayer::mPlayerHp = 5;
			Init();

			mStartFlag = true;
		}
		if (CKey::Once('T')) {
			CPlayer::mPlayerHp = 5;
			mStartFlag = true;
		}
	}

	//描画
	CTaskManager::Get()->Render();
	CCollisionManager::Get()->Render();
}

//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}