#include "CTarget.h"
#include"CSound.h"
#include"CTaskManager.h"
#include"CEffect.h"
#include"CCollisionManager.h"

#define OBJ "Target.obj"	//モデルのファイル
#define MTL "Target.mtl"	//モデルのマテリアルファイル

CModel CTarget::mTarget;

CTarget::CTarget(CModel* model, CVector position, CVector rotation, CVector scale) {
	//モデル,位置,回転,拡縮を設定
	mpModel = model;		//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;			//拡縮の設定
	mTag = ESCOREBLOCK1;

	//モデルが無いときは読み込む
	if (mTarget.mTriangles.size() == 0) {
		mTarget.Load(OBJ, MTL);
	}

	mPriority = 1; //優先度1
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}
	

void CTarget::Update() {

}

void CTarget::Collision(CCollider* m, CCollider* o){

}

void CTarget::TaskCollision(){
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
