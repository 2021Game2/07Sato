#include "CInput.h"

GLFWwindow* CInput::mpWindow = 0;

void CInput::Init(GLFWwindow* w){
	mpWindow = w;
}

void CInput::GetMousePos(float *px, float *py){
	double xpos, ypos;
	glfwGetCursorPos(mpWindow, &xpos, &ypos);
	*px = xpos;
	*py = ypos;
	return;
}

//bool CInput::SetMousePos(float *setX,float *setY) {
//	double xp, yp;
//	glfwSetCursorPos(mpWindow, &xp, &yp);
//	
//	return;
//}
//
//int CInput::ShowCursor(bool bShow) {
//
//	return;
//}
