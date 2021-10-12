#ifndef CGOAL_H
#define CGOAL_H

#include "CCharacter.h"

//ゴール判定用ブロック
class CGoal : public CCharacter {
private:



public:

	static bool mTouchGoal;

	CGoal();

	void Update();


};

#endif