#pragma once
#include "Line.h"
#include "Circle.h"


class Tri
{
public:
	Point pA;
	Point pB;
	Point pC;
	Line lAB;
	Line lAC;
	Line lBC;
	Circle outCircle;
	Tri();
	Tri(Point p1,Point p2,Point p3);//三个点构造三角形
	bool operator==(const Tri& TA)const;//判断两个三角形相等
	bool isEdgeOnTri(const Line& L);//判断边是否属于三角形
	static std::vector<Tri> delaunayTriangulation(const std::vector<Point>& points);//绘制Delaunay
	
    bool isPointInCir(const Point& point);//判断点是否在圆内
	bool isPointInTri(const Point& point)const;//判断点是否在三角形内
	//bool isPoinrInTriEdge(const Point& point);//判断点是否在三角形边上
	bool isPointOnTri(const Point& point);//判断点是否在三角形三点上
	static void addNewTri( std::vector<Tri>& newTri,Tri badTri, Point point);// 将点与受影响三角形三个点连接
	static void findCommonEdge( Tri T1,Tri T2,std::vector<Line>&L1);//寻找两三角形公共边
	static void findbadTriCommonEdges(std::vector<Tri>& badTri , std::vector<Line>& commonEdges);//找出影响三角形的公共边
	static void deleteConnectSuperTriByPoints(std::vector<Tri>& triangulation , Tri& superTri);//删除与超级三角形相连的三角形
	static void removenewTriByEdges(std::vector<Tri>& newTri, std::vector<Line>& Edges);//从新三角形容器里面删除带有影响三角形公共边的三角形
	static void localOptimization(std::vector<Tri>& newTri);//LOP优化
	static void swapD(Tri tri1, Tri tri2, const Line & commonedge, std::vector<Tri>& triangulation_swap);//对调对角线
	Point findFourthVertex(const Line& commonedge);//寻找两个三角形第四个顶点
	static Point findMidPoint(const Line& L);//找出点的中点坐标
    static std::vector<Line>VoronoiDiagramEdges(const std::vector<Tri>& delaunayTriangulation, std::vector<Line>& voronoiEdgesList);//根据Delaunay来生成维诺图边
	static void creatVoronoiEdgeForOne(Tri delaunayTriangulation, std::vector<Line>neighborEdge,std::vector<Line> &voronoiEdgesList);//为边界三角形生成射线边
	

	~Tri();
};

