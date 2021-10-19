#include"CAim.h"

#define MOUSESPEEDX 1.2f	//�}�E�X�����x
#define MOUSESPEEDY 1.2f	//�}�E�X�c���x

float CAim::mRotateCamX;
float CAim::mRotateCamY;


CAim::CAim() {
	mBeforMouseX = 0;
	mBeforMouseY = 0;
	mMouseMoveX = 0;
	mMouseMoveY = 0;

	mMouseSpeedX = MOUSESPEEDX;
	mMouseSpeedY = MOUSESPEEDY;

}

void CAim::Update() {
	//�}�E�X�ݒ�
	float mMousePosX, mMousePosY;	//�}�E�X�J�[�\�����W�擾�p
	//�}�E�X�J�[�\�����W�̎擾
	CInput::GetMousePos(&mMousePosX, &mMousePosY);

	//�Q�[����ʒ��S����̍��W�֕ϊ�
	mMousePosX -= 400;
	mMousePosY = 300 - mMousePosY;

	//�}�E�X�̈ړ���
	mMouseMoveX = mMousePosX - mBeforMouseX;
	mMouseMoveY = mMousePosY - mBeforMouseY;

	//���_����
	mRotateCamX -= mMouseMoveY / mMouseSpeedX;
	mRotateCamY -= mMouseMoveX / mMouseSpeedY;

	if (mRotateCamX < -80)
		mRotateCamX = -79;

	if (mRotateCamX > 75)
		mRotateCamX = 74;

	mBeforMouseX = mMousePosX;
	mBeforMouseY = mMousePosY;
}