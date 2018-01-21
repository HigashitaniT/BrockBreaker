#include "DxLib.h"
#include "GlobalVariable.h"
#include <stdio.h>
#include <string>

using namespace std;

int stageNum = 0;
int font_normal = 0;

double fTime = 255;

double stageCounter = 0;
double time_stageStart = 0; // ステージが始まった時間

const string stringStage = "STAGE ";

void FadeDrawString(string);

void StageInitialize() {
	stageNum = 0;
	font_normal = 0;
	fTime = 255;
	stageCounter = 0;
	time_stageStart = 0;
}

void StageSchedule() {
	switch ((int)stageCounter)
	{
	case 10:
	case 20:
	case 30:
	case 40:
	case 100:
		EnemySpawn(stageCounter);
		break;
	default:
		break;
	}
}

void StageSystem() {
	string s = stringStage + to_string(stageNum);
	FadeDrawString(s);
	if (time_stageStart == 0) time_stageStart = counter;
	if (60.0f <= counter - time_stageStart) { //１ステージ60秒
		stageNum++;
		time_stageStart = 0;
		fTime = 255;
		stageCounter = 0;
	}
	StageSchedule();
	stageCounter++;
}

void FadeDrawString(string s) {
	fTime -= 1;
	if (fTime <= 0)
	{
		fTime = 0;
	}
	DrawStringToHandle(640, 300, s.c_str(), GetColor(fTime, fTime, fTime), font_normal);
	
}

