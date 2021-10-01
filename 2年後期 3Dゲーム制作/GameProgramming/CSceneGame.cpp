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
#include"CColliderMesh.h"

#include"CPlayer.h"
#include"CBillBoard.h"
#include"CSphere.h"
#include"CBarricade.h"
#include"CPillar.h"

#include"CInput.h"
#include"CKey.h"
#include"CCamera.h"
#include"CSound.h"

CVector mEye;

//CSound Bgm;

CModel mBackGround; //背景

CModel mPillar;
CModel mBarricade;

//モデルからコライダを生成
CColliderMesh mColliderMesh;

CMatrix mBackGroundMatrix;

void CSceneGame::Init() {

	//モデルファイルの入力
	mModel.Load("Character.obj", "Character.mtl");
	mPillar.Load("Pillar.obj","Pillar.mtl");
	mBarricade.Load("barricade.obj", "barricade.mtl");
	mBackGround.Load("sky.obj", "sky.mtl");

	//wav読み込み
	//Bgm.Load(".wav");

	CMatrix matrix;
	matrix.Print();

	mBackGroundMatrix.Translate(0.0f, -2.0f, 500.0f);

	mPlayer.mpModel = &mModel;
	mPlayer.mScale = CVector(0.7f, 0.7f, 0.7f);
	mPlayer.mPosition = CVector(0.0f, 5.0f, -60.0f) * mBackGroundMatrix;
	mPlayer.mRotation = CVector(0.0f, 0.0f, 0.0f);


	//背景モデルから三角コライダを生成
	//親インスタンスと親行列は無し
	mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);

	//カメラ位置
	mCamX = 0.0f;
	mCamY = 15.0f;
	mCamZ = -20.0f;
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

	mBackGround.Render(mBackGroundMatrix);

	//タスクリストの削除
	CTaskManager::Get()->Delete();
	//描画
	CTaskManager::Get()->Render();

	//CCollisionManager::Get()->Render();
}