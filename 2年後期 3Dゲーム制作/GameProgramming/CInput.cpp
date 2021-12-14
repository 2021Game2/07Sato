#include "CInput.h"
#include<windows.h>

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

void CInput::SetMousePos(float setx, float sety) {
	double setX, setY;
	setX = 1200 / 2;
	setY = 800 / 2;
	setx = setX;
	sety = setY;
	glfwSetCursorPos(mpWindow, setX, setY);
}