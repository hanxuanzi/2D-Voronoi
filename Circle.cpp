#include "Circle.h"


Circle::Circle(){

}
Circle::Circle(const Point& p, float r) {
	this->centerPoint = p;
	this->R = r;
}

bool Circle::IfInCircle(const Point& p1) {
	return this->centerPoint.dis(p1) < this->R;//判断任意一点是否在圆内
}
