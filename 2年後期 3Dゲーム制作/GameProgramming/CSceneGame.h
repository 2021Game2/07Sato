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
	CModel mModel2;

	CMatrix mBackGroundMatrix;
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;

	static bool mStartFlag;

	static int mScore;

	int mClearScore;
	float mClearTime;


	CModel mBackGround; //背景
	CModel mPillar;
	CModel mBarricade;
	CModel mBlock;
	CModel mDamageBlock;
	CModel mTarget;
	CModel mTargetTouch;
	CModel mGoal;
	//CModel mGun;

	CPlayer mPlayer;

	//初期化処理のオーバーライド
	void Init();

	void SetStage();

	//更新処理のオーバーライド
	void Update();

	EScene GetNextScene();
};

#endif
