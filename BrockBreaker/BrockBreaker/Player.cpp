#include "DxLib.h"
#include "GlobalVariable.h"

char Key[256]; //キー入力

//struct BODY_player_t {
//	double x, y;
//	int height, width, color;
//};
BODY_Player_c Player; //Player情報
bool PlayerDamage();
int damageTimer;

/// <summary>
/// Player移動処理
/// </summary>
void PlayerMove() {
	if (Key[KEY_INPUT_LEFT] == 1) {
		Player.pcp.p[0].x -= 10.0f;
		if (Player.pcp.p[0].x < 0)
			Player.pcp.p[0].x = 0;
	}

	if (Key[KEY_INPUT_RIGHT] == 1) {
		Player.pcp.p[0].x += 10.0f;
		if (Player.pcp.p[0].x  > DISPLAY_SIZE_X - Player.width)
			Player.pcp.p[0].x = DISPLAY_SIZE_X - Player.width;
	}
	Player.pcp = MathCornerPoint(Player.pcp.p[0].x, Player.pcp.p[0].y, PLATER_Width, PLATER_Height);
	Player.centerPoint = Point(Player.pcp.p[0].x + Player.width / 2, Player.pcp.p[0].y);
	if (PlayerDamage())
	{
		if (damageTimer % 10 == 0) DrawBox((int)Player.pcp.p[0].x, (int)Player.pcp.p[0].y, (int)Player.pcp.p[3].x, (int)Player.pcp.p[3].y, color_white, FALSE);
		else DrawBox((int)Player.pcp.p[0].x, (int)Player.pcp.p[0].y, (int)Player.pcp.p[3].x, (int)Player.pcp.p[3].y, color_white, TRUE);
	}
	else
	{
		DrawBox((int)Player.pcp.p[0].x, (int)Player.pcp.p[0].y, (int)Player.pcp.p[3].x, (int)Player.pcp.p[3].y, color_white, TRUE);
	}
}

// Playerが敵と当たっているかチェック
bool HitEnemyBody() {
	// 敵の数分
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].enemyConer.p[2].y <= Player.pcp.p[0].y) continue; // 一定の高さまでは計算をしない。
		if (enemy[i].flag == 0) continue; // 出てない敵は飛ばす。
		//　四隅分
		for (int j = 0; j < 4; j++)
		{
			if ((int)Player.pcp.p[0].x < (int)enemy[i].enemyConer.p[j].x &&
				(int)Player.pcp.p[1].x > (int)enemy[i].enemyConer.p[j].x &&
				(int)Player.pcp.p[0].y < (int)enemy[i].enemyConer.p[j].y &&
				(int)Player.pcp.p[2].y > (int)enemy[i].enemyConer.p[j].y) {
				return true;
			}
		}
		// Playerの上面の線と敵の両サイドの線が交差しているか見る
		if (Intersection(Player.pcp.p[0], Player.pcp.p[1], enemy[i].enemyConer.p[0], enemy[i].enemyConer.p[2]) ||
			Intersection(Player.pcp.p[0], Player.pcp.p[1], enemy[i].enemyConer.p[1], enemy[i].enemyConer.p[3])) {
			return true;
		}
	}
	return false;
}

// ダメージ点滅中かのチェック
bool PlayerDamage() {
	// ダメージを食らってから一定時間たったら0にしてFalse
	if (damageTimer >= 1200) {
		damageTimer = 0;
		return false;
	}
	else if(HitEnemyBody())
	{
		DrawBox(0, 0, 10, 10, color_white, TRUE);
		// HPを引く処理をここにいれる
		return true;
	}
	else if (damageTimer > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

