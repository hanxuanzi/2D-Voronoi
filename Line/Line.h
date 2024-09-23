#pragma once

#include "Point.h"
#include<cmath>
class Line
{
public:
	
	Point pA;
	Point pB;
	Line();
	Line(const Point& p1, const Point& p2);//����������յ�
	Line(float x1, float y1, float x2, float y2);//����ͨ����������
	Line(const Line& l);//���Ѵ��ڵ�ֱ�߶����ʼ���µ�ֱ�߶��󣨿������캯����
	Point getmidPoint();
	Line& operator = (const Line& l);
	bool IfconLine(const Point& p);//�жϹ���
	~Line();
	bool operator == (const Line& l)const;
	bool isPointInLine(const Point& p);//���Ƿ�������
	static bool isinVector(std::vector<Line> commonEdges, Line L1);
	static Line produceRayLine(const Point& point1, const Point& point2);//������������һ��ָ�����������
	bool iftwoLineCross( Line& L1);//�ж����߶��Ƿ��ཻ
	Point getCrossPoint(Line& l);//����֪�ཻ�������߶��з���һ���ཻ��
	static std::vector<Line> endRayLine(std::vector<Line> &RecLine, std::vector<Line> &rayLine);//���زü������߱ߵļ���
	static Point findstartPoint(Line& rayLine);//�ҵ��߶��������޶���Χ�ڵĵ�
};



