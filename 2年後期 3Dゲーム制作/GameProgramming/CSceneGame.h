#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include"CScene.h"
#include"CModel.h"
#include"CCharacter.h"
#include"CPlayer.h"
#include"CColliderTriangle.h"
#include"CColliderMesh.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
private:

	float mCamX;
	float mCamY;
	float mCamZ;

	float mFcamX;
	float mFcamY;
	float mFcamZ;

public:
	//モデルクラスのインスタンス作成
	CModel mModel;

	CMatrix mBackGroundMatrix;
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;


	CModel mBackGround; //背景
	CModel mPillar;
	CModel mBarricade;
	CModel mTarget;
	CModel mTargetTouch;
	CModel mGoal;

	CPlayer mPlayer;

	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
