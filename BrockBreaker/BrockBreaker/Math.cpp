#include "DxLib.h"
#include "GlobalVariable.h"

typedef Point Vector;

//　p->qのベクトル
Vector CreateVector(const Point &p, const Point &q) { 
	Vector v = Vector(q.x - p.x, q.y - p.y);
	return v;
}

//　ベクトルの内積
double InnerProduct(const Vector &a, const Vector &b) {
	return(a.x*b.x + a.y*b.y);
}

//　ベクトルの外積
double OuterProduct(const Vector &a, const Vector &b) {
	return(a.x*b.y - a.y*b.x);
}

// ベクトルの二倍を返す
double VectorLength2(const Vector &v) {
	return InnerProduct(v, v);//v・v=|v|^2
}

//　円同士の当たり判定
bool CircleCollision(const CirclePoint &Cp1, const CirclePoint &Cp2) {
	double dx, dy, r;
	dx = Cp2.cPoint.x - Cp1.cPoint.x;
	dy = Cp2.cPoint.y - Cp1.cPoint.y;
	r = Cp1.r + Cp2.r;
	return ((dx*dx) + (dy*dy) < (r*r)); // 当たっていればTrue
}

// 四角の四隅と円の当たり
bool BoxCornerCollider(const CirclePoint &B, const CornerPoint &Corp) {
	CirclePoint cornerCricleP; // 四角の4点を一時的に半径０の円と仮定する
	for (int i = 0; i < 4; i++) // 四角の4点とボールを比べる
	{
		cornerCricleP.cPoint.x = Corp.p[i].x;
		cornerCricleP.cPoint.y = Corp.p[i].y;
		if (CircleCollision(B, cornerCricleP)) // 円判定を流用
		{
			return true;
		}
	}
	return false;
}

// 四角の辺と円の当たり判定
bool BoxLineCollider(const CornerPoint &box, const CirclePoint &m) {
	Vector pq, pm;								// ベクトルp->q p->m
	float inner, k, pqd2, pmd2, phd2, d2;		// 内積　

	const int n[][4] = { { 0,1,3,2 },{ 1,3,2,0 } };
	for (int i = 0; i<4; i++) {
		pq = CreateVector(box.p[n[0][i]], box.p[n[1][i]]);//0.1.3.2:1.3.2.0
		pm = CreateVector(box.p[n[0][i]], (Point)m.cPoint);

		inner = InnerProduct(pq, pm);//内積
		pqd2 = VectorLength2(pq);  //大きさの2乗
		pmd2 = VectorLength2(pm);  //大きさの2乗

		k = inner / pqd2;

		if (k<0 || 1<k)continue;//hが線分 pq 上にあるかどうか

		phd2 = (inner*inner) / pqd2;  //phの大きさの2乗

		d2 = pmd2 - phd2;  //垂線の大きさの2乗

		if (d2<m.r*m.r)return true;//比較
	}

	return false;
}

// ボールの跳ね返りの方向を決める関数
Point MovePoint(double x, double y, double x2, double y2) {
	double angle = atan2(y2 - y, x2 - x); //* 180.0f / M_PI;
	double ry = sin(angle);
	double rx = cos(angle);
	return Point(rx, ry);
}


// 円と四角の当たり判定
bool BallToBoxCollision(const CornerPoint &box, const CirclePoint &m) {
	if (BoxCornerCollider(m,box) || BoxLineCollider(box,m) )
	{
		//if(m.cPoint.x < box.p[0].x) // 円が四角の左角より左に当たる

		return true;
	}
	return false;
}
//四角の角を返す
CornerPoint MathCornerPoint(double &_x, double &_y, int _w, int _h) {
	CornerPoint cp;
	//左上
	cp.p[0].x = _x;
	cp.p[0].y = _y;
	//右上
	cp.p[1].x = _x + _w;
	cp.p[1].y = _y;
	//左下
	cp.p[2].x = _x;
	cp.p[2].y = _y + _h;
	//右下
	cp.p[3].x = _x + _w;
	cp.p[3].y = _y + _h;

	return cp;
}
// 交差しているかを返す
bool Intersection(Point &lineA1, Point &lineA2, Point &lineB1, Point &lineB2) {
	
	double ta = (lineB1.x - lineB2.x) * (lineA1.y - lineB1.y) + (lineB1.y - lineB2.y) * (lineB1.x - lineA1.x);
	double tb = (lineB1.x - lineB2.x) * (lineA2.y - lineB1.y) + (lineB1.y - lineB2.y) * (lineB1.x - lineA2.x);
	double tc = (lineA1.x - lineA2.x) * (lineB1.y - lineA1.y) + (lineA1.y - lineA2.y) * (lineA1.x - lineB1.x);
	double td = (lineA1.x - lineA2.x) * (lineB2.y - lineA1.y) + (lineA1.y - lineA2.y) * (lineA1.x - lineB2.x);

	return tc * td < 0 && ta * tb < 0;

	//交点座標を求められるものも一応置いておく
	/*double	z1, z2;
	Point i;

	z1 = (lineA2.y - lineA1.y) / (lineA2.x - lineA1.x);
	z2 = (lineB2.y - lineB1.y) / (lineB2.x - lineB1.x);

	i.x = (z1*lineA1.x - lineA1.y - z2*lineB1.x + lineB1.y) / (z1 - z2);
	i.y = (lineA2.y - lineA1.y) / (lineA2.x - lineA1.x)*(i.x - lineA1.x) + lineA1.y;
	return i;*/
}