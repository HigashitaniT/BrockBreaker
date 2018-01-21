#include "DxLib.h"
#include "GlobalVariable.h"

char Key[256]; //�L�[����

//struct BODY_player_t {
//	double x, y;
//	int height, width, color;
//};
BODY_Player_c Player; //Player���
bool PlayerDamage();
int damageTimer;

/// <summary>
/// Player�ړ�����
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

// Player���G�Ɠ������Ă��邩�`�F�b�N
bool HitEnemyBody() {
	// �G�̐���
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].enemyConer.p[2].y <= Player.pcp.p[0].y) continue; // ���̍����܂ł͌v�Z�����Ȃ��B
		if (enemy[i].flag == 0) continue; // �o�ĂȂ��G�͔�΂��B
		//�@�l����
		for (int j = 0; j < 4; j++)
		{
			if ((int)Player.pcp.p[0].x < (int)enemy[i].enemyConer.p[j].x &&
				(int)Player.pcp.p[1].x > (int)enemy[i].enemyConer.p[j].x &&
				(int)Player.pcp.p[0].y < (int)enemy[i].enemyConer.p[j].y &&
				(int)Player.pcp.p[2].y > (int)enemy[i].enemyConer.p[j].y) {
				return true;
			}
		}
		// Player�̏�ʂ̐��ƓG�̗��T�C�h�̐����������Ă��邩����
		if (Intersection(Player.pcp.p[0], Player.pcp.p[1], enemy[i].enemyConer.p[0], enemy[i].enemyConer.p[2]) ||
			Intersection(Player.pcp.p[0], Player.pcp.p[1], enemy[i].enemyConer.p[1], enemy[i].enemyConer.p[3])) {
			return true;
		}
	}
	return false;
}

// �_���[�W�_�Œ����̃`�F�b�N
bool PlayerDamage() {
	// �_���[�W��H����Ă����莞�Ԃ�������0�ɂ���False
	if (damageTimer >= 1200) {
		damageTimer = 0;
		return false;
	}
	else if(HitEnemyBody())
	{
		DrawBox(0, 0, 10, 10, color_white, TRUE);
		// HP�����������������ɂ����
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

