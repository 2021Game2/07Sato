#include "CDamageBlock.h"
#include"CCollisionManager.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CSound.h"



extern CSound Bomb;

CDamageBlock::CDamageBlock(CModel* model, CVector position, CVector rotation, CVector scale)
:mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),5.0f)
{
	
	//モデル,位置,回転,拡縮を設定
	mpModel = model;		//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;			//拡縮の設定
	
	mTag = EDAMAGEBLOCK;

	mPriority = 1; //優先度1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CDamageBlock::Update() {
	CTransform::Update();
	if (CSceneGame::mStartFlag == true && mEnabled == false) {
		mEnabled = true;
	}
}

void CDamageBlock::Collision(CCollider* m, CCollider* o) {
	if (CCollider::Collision(m, o)) {
		if (o->mpParent->mTag == EBULLET) {
			new CEffect(m->mpParent->mPosition, 10.0f, 10.0f, "tga/exp.tga", 4, 4, 2);
			Bomb.Play();
			mEnabled = false;
		}
	}
}

void CDamageBlock::TaskCollision(){
	//コライダの優先度変更
//Z軸の面
	mCollider.ChangePriority();

	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
