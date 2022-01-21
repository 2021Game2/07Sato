#include"CBullet.h"
#include"CCollisionManager.h"
#include"CEffect.h"

int CBullet::mDamage;

//デフォルトコンストラクタ
CBullet::CBullet()
:mLife(50)
,mCollider(this,&mMatrix,CVector(0.0f,0.0f,5.0f),1.5f)
,mCollider2(this, &mMatrix, CVector(0.0f, 0.0f, -2.0f), 1.5f)
{
	mTag = CCharacter::EBULLET;
}

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

//攻撃力
void CBullet::Damage(int damage) {
	mDamage = damage;
}

//更新
void CBullet::Update(){
	//生存時間の判定
	if (mLife-- > 0){
		CTransform::Update();
		//位置更新
		mPosition = CVector(0.0f, 0.0f, 19.0f) * mMatrix;
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
	if (CCollider::Collision(m, o)) {
		if (o->mpParent->mTag == EPLAYER) {
			return;
		}
	}
	//コライダのmとoが衝突しているか判定
	if (CCollider::Collision(m, o)) {
		if (o->mType == CCollider::ESPHERE) {
			new CEffect(m->mpParent->mPosition, 2.0f, 2.0f, "tga/exp.tga", 4, 4, 2);
			//相手がゴールの時は戻る
			if (o->mpParent->mTag == EGOAL) {
				return;
			}
			mEnabled = false;
		}
	}
	if (o->mpParent != nullptr) {
		if (o->mpParent->mTag == EBLOCK || o->mpParent->mTag == EMOVEBLOCK) {
			CVector adjust;		//調整用ベクトル
			//三角形と線分の衝突判定
			return;

		}
	}
}

//衝突処理
void CBullet::TaskCollision(){
	//コライダの優先度変更
	mCollider.ChangePriority();
	mCollider2.ChangePriority();
	//衝突処理 実行
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider2, COLLISIONRANGE);
}