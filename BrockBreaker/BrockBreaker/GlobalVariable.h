#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define PLATER_STARTPOS_X 640
#define PLATER_STARTPOS_Y 850
#define PLATER_Width 120
#define PLATER_Height 40

#define DISPLAY_SIZE_X 1280
#define DISPLAY_SIZE_Y 960

#define BALL_SPEED 5

#define ENEMY_MAX 30

// ---------------------------------------------
// �ϐ��Q
// ---------------------------------------------
//�F
extern int color_white;
extern int color_red;

//font
extern int font_normal;

extern char Key[256]; 

extern int counter;
extern double stageCounter;

extern double time_stageStart; // �X�e�[�W���n�܂�������

// ---------------------------------------------
// enum class
// ---------------------------------------------
enum GameState {
	TITLE,
	GAME,
	RESULT,
};
extern GameState gameState;

class Point //���W�N���X
{
public: double
	x, y;
	Point() { x = y = 0.0; }
	Point(const double &_x, const double &_y) { x = _x; y = _y; }
};
class CornerPoint // �l�p��4�̊p�̍��W��ێ�
{
public:
	Point p[4];
};
class CirclePoint // �~�̍��W�Ɣ��a��ێ�
{
public:
	Point cPoint;	// ���S���W
	double r = 0.0; // ���a
	CirclePoint() {
		r = 0;
	}
};
CornerPoint MathCornerPoint(double &_x, double &_y, int _w, int _h);

class BODY_Player_c
{
public:

	int height, width, color;	//�@�����A���A�F
	Point centerPoint;			//�@Player�̒��S
	CornerPoint pcp;			//�@�v���C���[�R�[�i�[�|�C���g

	BODY_Player_c() {
		double px = PLATER_STARTPOS_X;
		double py = PLATER_STARTPOS_Y;
		width = PLATER_Width;
		height = PLATER_Height;
		pcp = MathCornerPoint(px, py, width, height);
		centerPoint.x = pcp.p[0].x + width / 2;
		centerPoint.y = pcp.p[0].y;
	}
};
extern BODY_Player_c Player; //Player���

class BODY_Ball_c
{
public:
	int flag;
	Point movePoint;
	CirclePoint ballCP;
	BODY_Ball_c() {
		ballCP.r = 20;
		ballCP.cPoint.x = PLATER_STARTPOS_X + PLATER_Width / 2;
		ballCP.cPoint.y = PLATER_STARTPOS_Y - ballCP.r * 2;
		movePoint = Point(1.0f,-1.0f);
	}
};
extern BODY_Ball_c Ball; //Ball���

//enemy��� x, y, hp, counter, pattern, sizeX, sizeY, flag
class BODY_Enemy_c 
{
public:
	double sizeX, sizeY;
	int hp, counter, pattern, flag;
	CornerPoint enemyConer;
	BODY_Enemy_c() {
		sizeX = 30.0;
		sizeY = 30.0;
		hp = 10;
		flag = 0;
	}
};
extern BODY_Enemy_c enemy[ENEMY_MAX]; //

// ---------------------------------------------
// �֐��Q
// ---------------------------------------------
// �F��t�H���g�̏����ݒ�
void SetColor();
void SetFontHandle();

void StageInitialize();	// �X�e�[�W������
void StageSystem();		// �X�e�[�W�Ǘ�

void PlayerMove();		// �v���C���[�̊Ǘ�
bool PlayerDamage();

void BallMove();		// �{�[���̊Ǘ�

// �G�̊Ǘ�
void EnemySpawn(double _x, double _y = -30, int _hp = 10, int _pattern = 1, double _sizeX = 100, double _sizeY = 100);
void EnemyUpdata();

// �{�[���Ǝl�p�̂����蔻���Ԃ�
bool BallToBoxCollision(const CornerPoint &box, const CirclePoint &m);

// �o�[�Ɠ����������̈ړ����Ԃ�
Point MovePoint(double x, double y, double x2, double y2);

// �������Ă��邩��Ԃ�
bool Intersection(Point &lineA1, Point &lineA2, Point &lineB1, Point &lineB2);
