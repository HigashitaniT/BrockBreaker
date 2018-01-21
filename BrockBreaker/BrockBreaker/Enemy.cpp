#include "DxLib.h"
#include "GlobalVariable.h"

BODY_Enemy_c enemy[ENEMY_MAX];

//空いているenemyを探してフラグを入れる
void EnemySpawn(double _x, double _y , int _hp, int _pattern, double _sizeX, double _sizeY ) {
	int i = 0;
	for (i = 0; i < ENEMY_MAX; i++) { // エネミー最大数分
		if (enemy[i].flag == 0) break; // 出てないエネミーの番号をもってbreak
	}
	enemy[i].flag = 1;
	enemy[i].hp = _hp;
	enemy[i].enemyConer.p[0].x = _x;
	enemy[i].enemyConer.p[0].y = _y;
	enemy[i].pattern = _pattern;
	enemy[i].sizeX = _sizeX;
	enemy[i].sizeY = _sizeY;
	enemy[i].counter = 0;
}

void EnemyPattern(int &i, int &pattern) {
	
	switch (pattern)
	{
	case 1:
		enemy[i].enemyConer.p[0].y += 1.5;
		break;
	case 2:
		double ay = -1.5;
		if (enemy[i].counter % 50 >= 40) ay *= -1;
		enemy[i].enemyConer.p[0].y -= ay;
		enemy[i].enemyConer.p[0].x += sin(M_PI*enemy[i].counter / 40.0f)*5.0f;
		break;
	}
}

void EnemyUpdata() {
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].flag == 1) {
			EnemyPattern(i, enemy[i].pattern);
			enemy[i].counter++;
			enemy[i].enemyConer = MathCornerPoint(enemy[i].enemyConer.p[0].x,enemy[i].enemyConer.p[0].y,
							enemy[i].sizeX, enemy[i].sizeY
							);
			
			if (BallToBoxCollision(enemy[i].enemyConer, Ball.ballCP))
			{
				if (enemy[i].enemyConer.p[0].x > Ball.ballCP.cPoint.x || enemy[i].enemyConer.p[3].x < Ball.ballCP.cPoint.x) Ball.movePoint.x *= -1;
				if (enemy[i].enemyConer.p[0].y > Ball.ballCP.cPoint.y || enemy[i].enemyConer.p[3].y < Ball.ballCP.cPoint.y) Ball.movePoint.y *= -1;
				enemy[i].flag = 0;
			}

			DrawBox(enemy[i].enemyConer.p[0].x,enemy[i].enemyConer.p[0].y,
					enemy[i].enemyConer.p[3].x,enemy[i].enemyConer.p[3].y, 
					color_white, TRUE
					);
		}
	}
}


