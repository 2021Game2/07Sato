#ifndef CAIM_H
#define CAIM_H

#include"CInput.h"
#include"CPlayer.h"

class CAim{
private:

	float mBeforMouseX;	//���O�}�E�X�ʒu
	float mBeforMouseY;
	float mMouseMoveX;	//�}�E�X�ړ���
	float mMouseMoveY;
	float mMouseSpeedX;	//�}�E�X���x
	float mMouseSpeedY;

public:

	static float mRotateCamX;
	static float mRotateCamY;

	CAim();

	void Update();

};
#endif