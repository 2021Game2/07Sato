#ifndef CAIM_H
#define CAIM_H

#include"CInput.h"
#include"CPlayer.h"

class CAim{
private:

	float mBeforMouseX;	//直前マウス位置
	float mBeforMouseY;
	float mMouseMoveX;	//マウス移動量
	float mMouseMoveY;
	float mMouseSpeedX;	//マウス感度
	float mMouseSpeedY;

public:

	static float mRotateCamX;
	static float mRotateCamY;

	CAim();

	void Update();

};
#endif