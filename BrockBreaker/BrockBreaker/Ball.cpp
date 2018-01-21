#include "DxLib.h"
#include "GlobalVariable.h"
//
//struct BODY_ball_t {
//	int x, y, range, flag, mx, my;
//};
//BODY_ball_t Ball;

BODY_Ball_c Ball;

void BallMove() {
	//左右
	if (Ball.ballCP.cPoint.x <= 0 + Ball.ballCP.r || Ball.ballCP.cPoint.x >= DISPLAY_SIZE_X - Ball.ballCP.r )
	{
		Ball.movePoint.x *= -1;
	}
	//上
	if (Ball.ballCP.cPoint.y <= 0 + Ball.ballCP.r)
	{
		Ball.movePoint.y *= -1;
	}
	//Player上面にあたった判定
	if (BallToBoxCollision(Player.pcp,Ball.ballCP))
	{
		Ball.movePoint = MovePoint(Player.centerPoint.x, Player.centerPoint.y, Ball.ballCP.cPoint.x, Ball.ballCP.cPoint.y);
	}
	//if (Ball.y > Player.y && Ball.y < Player.y + Player.height)//Ballがプレイヤーの高さの時
	//{
	//	if (Ball.x < Player.pcp.p[0].x  && Ball.x >= Player.pcp.p[0].x  - Ball.range) // Ballが左側かつ端に当たる
	//	{
	//		Ball.mx = -1;
	//	}
	//	else if(Ball.x > Player.pcp.p[0].x  + Player.width && Ball.x <= Player.pcp.p[0].x  + Player.width + Ball.range) // 右側
	//	{
	//		Ball.mx = 1;
	//	}
	//	DrawBox(0, 0, 100, 100, color_red, TRUE);
	//}
	//落ちたらRESULT
	if (Ball.ballCP.cPoint.y >= DISPLAY_SIZE_Y)
	{
		gameState = RESULT;
	}

	Ball.ballCP.cPoint.x += Ball.movePoint.x * BALL_SPEED;
	Ball.ballCP.cPoint.y += Ball.movePoint.y * BALL_SPEED;

	DrawCircle(Ball.ballCP.cPoint.x, Ball.ballCP.cPoint.y, Ball.ballCP.r, color_red, TRUE);
	DrawFormatString(0, 0, color_red, "%d", Ball.ballCP.r);
}