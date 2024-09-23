#pragma once
#include "Point.h"
class Circle
{
public:
	Point centerPoint;
	float R;
	Circle();
	Circle(const Point& p, float r);
	bool IfInCircle(const Point& p1);
};



