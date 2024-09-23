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

//���
float Point::dot(const Point& p) {
	return this->x * p.x + this->y * p.y;
	
}
//���
Point Point::cross(const Point& p)
{
	return Point(this->x * p.y, this->y * p.x);
}
//����
float Point:: dis(const Point& p) const {
	return sqrt((this->x - p.x) * (this->x - p.x) + (this->y - p.y) * (this->y - p.y));
}


Point::~Point() {

}
//������
bool Point::cmp(const Point &p1, const Point &p2) {
	if (p1.y < p2.y) { // ���Ȱ��� y ������ϵ�������
		return true;
	}
	else if (p1.y == p2.y) { // ��� y ������ȣ����� x �������������
		return p1.x < p2.x;
	}
	else {
		return false;
	}
}

//ָ����Χ�����������
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
	sort(m_pt.begin(), m_pt.end(), Point::cmp);//����������
	return m_pt;
}

