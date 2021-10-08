#include "CCharacter.h"
#include "CMap.h"

CMap::CMap()
{
	mPosition = CVector(0.0f, 0.0f, 0.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();

	mStage.Load("stage.obj", "stage.mtl");
	mpModel = &mStage;

	//�w�i���f������O�p�R���C�_�𐶐�
	//�e�C���X�^���X�Ɛe�s��͖���
	mColliderMesh.Set(NULL, &mBackGroundMatrix, &mStage);
}
