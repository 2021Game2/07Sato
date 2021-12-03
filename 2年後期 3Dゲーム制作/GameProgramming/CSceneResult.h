#ifndef CSCENERESULT_H
#define CSCENERESULT_H
#include"CScene.h"
#include"CSceneGame.h"

class CSceneResult : public CScene{
private:
	int mScores[10];
	float mTimes[10];


public:

	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//次のシーンの取得
	EScene GetNextScene();
};
#endif