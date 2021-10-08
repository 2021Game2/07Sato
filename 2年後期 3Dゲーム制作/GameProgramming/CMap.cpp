#include "CCharacter.h"
#include "CMap.h"

CMap::CMap()
{
	mPosition = CVector(0.0f, 0.0f, 0.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();

	mStage.Load("stage.obj", "stage.mtl");
	mpModel = &mStage;

	//背景モデルから三角コライダを生成
	//親インスタンスと親行列は無し
	mColliderMesh.Set(NULL, &mBackGroundMatrix, &mStage);
}
