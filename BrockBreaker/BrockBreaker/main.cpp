#include "DxLib.h"
#include "GlobalVariable.h"

GameState gameState = TITLE;
int counter = 0;

int startTime = 0;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	int RefreshTime;

	ChangeWindowMode(TRUE);
	SetGraphMode(DISPLAY_SIZE_X, DISPLAY_SIZE_Y, 32);
	if (DxLib_Init() == -1) return -1;

	SetDrawScreen(DX_SCREEN_BACK);                  //裏画面を使用する。

	SetColor();
	SetFontHandle();
	startTime = GetNowCount();
	//gameState = TITLE;

	while (ProcessMessage() == 0 && GetHitKeyStateAll(Key) == 0) {
		RefreshTime = GetNowCount();  //今の時間を取得
		ClearDrawScreen();  //裏画面のデータを全て削除
		
		if (gameState == TITLE) {
			if (Key[KEY_INPUT_SPACE] == 1) {
				gameState = GAME;
				StageInitialize();
			}
		}

		if (gameState == GAME) {
			StageSystem();
			BallMove();
			EnemyUpdata();
			PlayerMove();
		}

		if (gameState == RESULT) {
			if (Key[KEY_INPUT_SPACE] == 1) {
				Ball.ballCP.cPoint.x = DISPLAY_SIZE_X / 2;
				Ball.ballCP.cPoint.y =DISPLAY_SIZE_Y / 2;
				Ball.movePoint.y = -1;
				for (int i = 0; i < ENEMY_MAX; i++)
				{
					enemy[i].flag = 0;
					enemy[i].counter = 0;
				}
				gameState = TITLE;
			}
		}
		counter = (GetNowCount() - startTime) / 1000;
		DxLib::DrawFormatString(640, 0, GetColor(255, 255, 255), "%d", counter);

		ScreenFlip();                             //裏画面データを表画面へ反映

		if (Key[KEY_INPUT_ESCAPE] == 1)    break;     //Escapeが押されたら終了
		while (GetNowCount() - RefreshTime < 17);   //1周の処理が17ミリ秒になるまで待つ
		
		
	}

	DxLib_End();
	return 0;
}