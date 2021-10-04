#ifndef CMAP_H
#define CMAP_H

#include "CCharacter.h"
#include "CColliderMesh.h"

class CMap : public CCharacter {
private:
	CModel mStage;
	CColliderMesh mColliderMesh;
	CMatrix mBackGroundMatrix;

public:
	CMap();

};

#endif
