#pragma once
#include <cmath>
#include<vector>
#include<iostream>

class Point
{
public:
	float x;
	float y;
	float z;
	Point();
	Point(float x, float y);
	Point(const Point& p);
	Point& operator=(const Point& p);
	Point operator-(const Point& p);
	Point operator+(const Point& p) const;
	Point operator/(float L);
	Point operator * (float a)const;
	bool operator==(const Point& p)const;
	bool operator!=(const Point& p)const;
	bool operator<(const Point& p)const;//����С�ں�����set����ȥ��
	float dot(const Point& p);//���
	Point cross(const Point& p);//���
    float dis(const Point& p = Point(0, 0)) const;//ģ��
	void  out();
	~Point();
	
	 static std::vector <Point> SetPoint(int num);//���������
	 static bool cmp(const Point &p1, const Point &p2);//���õ�Ĳ���˳����
	 

	 
};


//while (nums < seeds)
//{
//	Point<> RandomP(0, 0, 0);
//	RandomP.x = static_cast<float>(rand()) / (float)RAND_MAX * (TopRight[0] - BottomLeft[0]) + BottomLeft[0];
//	RandomP.y = static_cast<float>(rand()) / (float)RAND_MAX * (TopRight[1] - BottomLeft[1]) + BottomLeft[1];
//
//	if ()
//	{
//		RP[nums] = RandomP;
//		++nums;
//	}
//}
