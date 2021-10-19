#include"CAim.h"

#define MOUSESPEEDX 1.2f	//マウス横感度
#define MOUSESPEEDY 1.2f	//マウス縦感度

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
	//マウス設定
	float mMousePosX, mMousePosY;	//マウスカーソル座標取得用
	//マウスカーソル座標の取得
	CInput::GetMousePos(&mMousePosX, &mMousePosY);

	//ゲーム画面中心からの座標へ変換
	mMousePosX -= 400;
	mMousePosY = 300 - mMousePosY;

	//マウスの移動量
	mMouseMoveX = mMousePosX - mBeforMouseX;
	mMouseMoveY = mMousePosY - mBeforMouseY;

	//視点操作
	mRotateCamX -= mMouseMoveY / mMouseSpeedX;
	mRotateCamY -= mMouseMoveX / mMouseSpeedY;

	if (mRotateCamX < -80)
		mRotateCamX = -79;

	if (mRotateCamX > 75)
		mRotateCamX = 74;

	mBeforMouseX = mMousePosX;
	mBeforMouseY = mMousePosY;
}