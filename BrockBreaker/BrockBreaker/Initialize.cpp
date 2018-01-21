#include "GlobalVariable.h"
#include "DxLib.h"

int color_red;
int color_white;

void SetColor() {
	color_white = GetColor(255, 255, 255);
	color_red = GetColor(255, 0, 0);
}

void SetFontHandle() {
	SetFontSize(64);
	font_normal = CreateFontToHandle(NULL, 32, 3);
}