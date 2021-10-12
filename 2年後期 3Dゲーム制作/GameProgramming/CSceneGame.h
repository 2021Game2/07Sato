#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include"CScene.h"
#include"CModel.h"
#include"CMap.h"
#include"CCharacter.h"
#include"CPlayer.h"
#include"CColliderTriangle.h"


/*
ゲームのシーン
*/
class CSceneGame : public CScene {
private:
	CMap mMap;

	float mCamX;
	float mCamY;
	float mCamZ;

	float mFcamX;
	float mFcamY;
	float mFcamZ;

public:
	//モデルクラスのインスタンス作成
	CModel mModel;

	CModel mBackGround; //背景

	CModel mTarget;

	CModel mPillar;
	CModel mBarricade;

	CPlayer mPlayer;

	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
