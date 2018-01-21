#include "DxLib.h"
#include "GlobalVariable.h"

typedef Point Vector;

//�@p->q�̃x�N�g��
Vector CreateVector(const Point &p, const Point &q) { 
	Vector v = Vector(q.x - p.x, q.y - p.y);
	return v;
}

//�@�x�N�g���̓���
double InnerProduct(const Vector &a, const Vector &b) {
	return(a.x*b.x + a.y*b.y);
}

//�@�x�N�g���̊O��
double OuterProduct(const Vector &a, const Vector &b) {
	return(a.x*b.y - a.y*b.x);
}

// �x�N�g���̓�{��Ԃ�
double VectorLength2(const Vector &v) {
	return InnerProduct(v, v);//v�Ev=|v|^2
}

//�@�~���m�̓����蔻��
bool CircleCollision(const CirclePoint &Cp1, const CirclePoint &Cp2) {
	double dx, dy, r;
	dx = Cp2.cPoint.x - Cp1.cPoint.x;
	dy = Cp2.cPoint.y - Cp1.cPoint.y;
	r = Cp1.r + Cp2.r;
	return ((dx*dx) + (dy*dy) < (r*r)); // �������Ă����True
}

// �l�p�̎l���Ɖ~�̓�����
bool BoxCornerCollider(const CirclePoint &B, const CornerPoint &Corp) {
	CirclePoint cornerCricleP; // �l�p��4�_���ꎞ�I�ɔ��a�O�̉~�Ɖ��肷��
	for (int i = 0; i < 4; i++) // �l�p��4�_�ƃ{�[�����ׂ�
	{
		cornerCricleP.cPoint.x = Corp.p[i].x;
		cornerCricleP.cPoint.y = Corp.p[i].y;
		if (CircleCollision(B, cornerCricleP)) // �~����𗬗p
		{
			return true;
		}
	}
	return false;
}

// �l�p�̕ӂƉ~�̓����蔻��
bool BoxLineCollider(const CornerPoint &box, const CirclePoint &m) {
	Vector pq, pm;								// �x�N�g��p->q p->m
	float inner, k, pqd2, pmd2, phd2, d2;		// ���ρ@

	const int n[][4] = { { 0,1,3,2 },{ 1,3,2,0 } };
	for (int i = 0; i<4; i++) {
		pq = CreateVector(box.p[n[0][i]], box.p[n[1][i]]);//0.1.3.2:1.3.2.0
		pm = CreateVector(box.p[n[0][i]], (Point)m.cPoint);

		inner = InnerProduct(pq, pm);//����
		pqd2 = VectorLength2(pq);  //�傫����2��
		pmd2 = VectorLength2(pm);  //�傫����2��

		k = inner / pqd2;

		if (k<0 || 1<k)continue;//h������ pq ��ɂ��邩�ǂ���

		phd2 = (inner*inner) / pqd2;  //ph�̑傫����2��

		d2 = pmd2 - phd2;  //�����̑傫����2��

		if (d2<m.r*m.r)return true;//��r
	}

	return false;
}

// �{�[���̒��˕Ԃ�̕��������߂�֐�
Point MovePoint(double x, double y, double x2, double y2) {
	double angle = atan2(y2 - y, x2 - x); //* 180.0f / M_PI;
	double ry = sin(angle);
	double rx = cos(angle);
	return Point(rx, ry);
}


// �~�Ǝl�p�̓����蔻��
bool BallToBoxCollision(const CornerPoint &box, const CirclePoint &m) {
	if (BoxCornerCollider(m,box) || BoxLineCollider(box,m) )
	{
		//if(m.cPoint.x < box.p[0].x) // �~���l�p�̍��p��荶�ɓ�����

		return true;
	}
	return false;
}
//�l�p�̊p��Ԃ�
CornerPoint MathCornerPoint(double &_x, double &_y, int _w, int _h) {
	CornerPoint cp;
	//����
	cp.p[0].x = _x;
	cp.p[0].y = _y;
	//�E��
	cp.p[1].x = _x + _w;
	cp.p[1].y = _y;
	//����
	cp.p[2].x = _x;
	cp.p[2].y = _y + _h;
	//�E��
	cp.p[3].x = _x + _w;
	cp.p[3].y = _y + _h;

	return cp;
}
// �������Ă��邩��Ԃ�
bool Intersection(Point &lineA1, Point &lineA2, Point &lineB1, Point &lineB2) {
	
	double ta = (lineB1.x - lineB2.x) * (lineA1.y - lineB1.y) + (lineB1.y - lineB2.y) * (lineB1.x - lineA1.x);
	double tb = (lineB1.x - lineB2.x) * (lineA2.y - lineB1.y) + (lineB1.y - lineB2.y) * (lineB1.x - lineA2.x);
	double tc = (lineA1.x - lineA2.x) * (lineB1.y - lineA1.y) + (lineA1.y - lineA2.y) * (lineA1.x - lineB1.x);
	double td = (lineA1.x - lineA2.x) * (lineB2.y - lineA1.y) + (lineA1.y - lineA2.y) * (lineA1.x - lineB2.x);

	return tc * td < 0 && ta * tb < 0;

	//��_���W�����߂�����̂��ꉞ�u���Ă���
	/*double	z1, z2;
	Point i;

	z1 = (lineA2.y - lineA1.y) / (lineA2.x - lineA1.x);
	z2 = (lineB2.y - lineB1.y) / (lineB2.x - lineB1.x);

	i.x = (z1*lineA1.x - lineA1.y - z2*lineB1.x + lineB1.y) / (z1 - z2);
	i.y = (lineA2.y - lineA1.y) / (lineA2.x - lineA1.x)*(i.x - lineA1.x) + lineA1.y;
	return i;*/
}