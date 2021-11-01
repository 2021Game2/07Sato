#include"CBullet.h"
#include"CCollisionManager.h"

//デフォルトコンストラクタ
CBullet::CBullet()
:mLife(50)
,mCollider(this,&mMatrix,CVector(0.0f,0.0f,5.0f),1.0f)
{}

//幅と奥行きの設定
//Set(幅,奥行き)
void CBullet::Set(float w, float d){
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定
	mT.SetVertex(CVector(-w, 0.0, 0.0),CVector(w, 0.0, 0.0),CVector(0.0, 0.0, d));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CBullet::Update(){
	//生存時間の判定
	if (mLife-- > 0){
		CTransform::Update();
		//位置更新
		mPosition = CVector(0.0f, 0.0f, 15.0f) * mMatrix;
		mRotation.mZ += 240;
	}
	else{
		//無効にする
		mEnabled = false;
	}
}

//描画
void CBullet::Render(){
	//DIFFUSE黄色設定
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画
	mT.Render(mMatrix);
}

//衝突処理
//Collision(コライダ1,コライダ2)
void CBullet::Collision(CCollider* m, CCollider* o) {
	//コライダのmとoが衝突しているか判定
	if (CCollider::Collision(m, o)) {
		if (o->mType == CCollider::ESPHERE) {
			//相手がゴールの時は戻る
			if (o->mpParent->mTag == EGOAL) {
				return;
			}
			mEnabled = false;
		}
	}
}

//衝突処理
void CBullet::TaskCollision(){
	//コライダの優先度変更
	mCollider.ChangePriority();
	//衝突処理 実行
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}