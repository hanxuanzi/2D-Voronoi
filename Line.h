#pragma once

#include "Point.h"
#include<cmath>
class Line
{
public:
	
	Point pA;
	Point pB;
	Line();
	Line(const Point& p1, const Point& p2);//接受起点与终点
	Line(float x1, float y1, float x2, float y2);//接受通过给定坐标
	Line(const Line& l);//用已存在的直线对象初始化新的直线对象（拷贝构造函数）
	Point getmidPoint();
	Line& operator = (const Line& l);
	bool IfconLine(const Point& p);//判断共线
	~Line();
	bool operator == (const Line& l)const;
	bool isPointInLine(const Point& p);//点是否在线上
	static bool isinVector(std::vector<Line> commonEdges, Line L1);
	static Line produceRayLine(const Point& point1, const Point& point2);//根据两点生成一条指定方向的射线
	bool iftwoLineCross( Line& L1);//判断两线段是否相交
	Point getCrossPoint(Line& l);//从已知相交的两个线段中返回一个相交点
	static std::vector<Line> endRayLine(std::vector<Line> &RecLine, std::vector<Line> &rayLine);//返回裁剪后射线边的集合
	static Point findstartPoint(Line& rayLine);//找到线段两端在限定范围内的点
};



