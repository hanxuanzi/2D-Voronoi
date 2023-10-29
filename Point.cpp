#include "Point.h"
#include <algorithm>

Point::Point() {
	this->x = 0;
	this->y = 0;
}

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

Point::Point(const Point& p) {
	this->x = p.x;
	this->y = p.y;
}

void  Point::out() {
	std::cout << "(" << this->x << "," << this->y << ")" << std::endl;
}
//
Point& Point::operator=(const Point& p) {
	this->x = p.x;
	this->y = p.y;
	return *this;
}

Point Point:: operator/(float L) {
	return Point(this->x / L, this->y / L);
}
Point Point::operator - (const Point& p) {
	return Point(this->x - p.x, this->y - p.y);
}

Point Point::operator + (const Point& p) const {
	
	return Point(this->x + p.x, this->y + p.y);
}

Point Point::operator * (float a) const{
	return Point(this->x * a, this->y * a);
}

bool Point::operator == (const Point& p)const {
	return this->x == p.x && this->y == p.y;
}

bool Point::operator != (const Point& p)const {
	return this->x != p.x || this->y != p.y;
}

bool Point::operator < (const Point& p)const{
	if (this->x < p.x)return true;
	else if (this->x == p.x) {
		if (this->y < p.y)return true;
	}
	return false;
}

//Point Point::operator + (const Point& p) {
//
//	return Point(this->x + p.x, this->y + p.y);
//}

//点乘
float Point::dot(const Point& p) {
	return this->x * p.x + this->y * p.y;
	
}
//叉乘
Point Point::cross(const Point& p)
{
	return Point(this->x * p.y, this->y * p.x);
}
//距离
float Point:: dis(const Point& p) const {
	return sqrt((this->x - p.x) * (this->x - p.x) + (this->y - p.y) * (this->y - p.y));
}


Point::~Point() {

}
//排序函数
bool Point::cmp(const Point &p1, const Point &p2) {
	if (p1.y < p2.y) { // 首先按照 y 坐标从上到下排序
		return true;
	}
	else if (p1.y == p2.y) { // 如果 y 坐标相等，则按照 x 坐标从左到右排序
		return p1.x < p2.x;
	}
	else {
		return false;
	}
}

//指定范围内生成随机点
std::vector<Point> Point::SetPoint(int num) {
	std::vector<Point> m_pt;
	srand(time(NULL));
	for (int i = 0; i < num; i++)
	{
		float random1 = rand() % 2000 / 1000.0 -1.0;
		float random2 = rand() % 2000 / 1000.0 -1.0;
		Point r_pt;
		r_pt.x = random1;
		r_pt.y = random2;
		m_pt.push_back(r_pt);

	}
	sort(m_pt.begin(), m_pt.end(), Point::cmp);//进行排序处理
	return m_pt;
}

