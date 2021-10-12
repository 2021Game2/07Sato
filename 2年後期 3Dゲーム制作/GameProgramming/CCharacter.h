#ifndef CCHARACTER_H
#define CCHARACTER_H
//変換行列クラスのインクルード
#include"CTransform.h"
//モデルクラスのインクルード
#include"CModel.h"
#include"CTask.h"
/*キャラクタークラス
　ゲームキャラクタの基本的な機能を定義する*/
class CCollider;

class CCharacter : public CTransform,public CTask{
public:
	enum ETag{
		EZERO,
		EPLAYER,		//プレイヤー本体
		EBULLETPLAYER,	//プレイヤーの弾
		EMAP,			//地面
		ESCOREBLOCK1,	//的型
		ESCOREBLOCK2,	//接触型
		EBLOCK,			//障害物
		EDAMAGEBLOCK,	//ダメージ有の障害物
		EGOAL,			//ゴール
	};
	ETag mTag;

	CModel *mpModel;	//モデルのポインタ

	//デフォルトコンストラクタ
	CCharacter();
	//デストラクタ
	~CCharacter();

	//描画処理
	void Render();

	virtual void Collision(CCollider *m, CCollider *o){}
};


#endif