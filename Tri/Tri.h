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
	Tri(Point p1,Point p2,Point p3);//�����㹹��������
	bool operator==(const Tri& TA)const;//�ж��������������
	bool isEdgeOnTri(const Line& L);//�жϱ��Ƿ�����������
	static std::vector<Tri> delaunayTriangulation(const std::vector<Point>& points);//����Delaunay
	
    bool isPointInCir(const Point& point);//�жϵ��Ƿ���Բ��
	bool isPointInTri(const Point& point)const;//�жϵ��Ƿ�����������
	//bool isPoinrInTriEdge(const Point& point);//�жϵ��Ƿ��������α���
	bool isPointOnTri(const Point& point);//�жϵ��Ƿ���������������
	static void addNewTri( std::vector<Tri>& newTri,Tri badTri, Point point);// ��������Ӱ������������������
	static void findCommonEdge( Tri T1,Tri T2,std::vector<Line>&L1);//Ѱ���������ι�����
	static void findbadTriCommonEdges(std::vector<Tri>& badTri , std::vector<Line>& commonEdges);//�ҳ�Ӱ�������εĹ�����
	static void deleteConnectSuperTriByPoints(std::vector<Tri>& triangulation , Tri& superTri);//ɾ���볬��������������������
	static void removenewTriByEdges(std::vector<Tri>& newTri, std::vector<Line>& Edges);//������������������ɾ������Ӱ�������ι����ߵ�������
	static void localOptimization(std::vector<Tri>& newTri);//LOP�Ż�
	static void swapD(Tri tri1, Tri tri2, const Line & commonedge, std::vector<Tri>& triangulation_swap);//�Ե��Խ���
	Point findFourthVertex(const Line& commonedge);//Ѱ�����������ε��ĸ�����
	static Point findMidPoint(const Line& L);//�ҳ�����е�����
    static std::vector<Line>VoronoiDiagramEdges(const std::vector<Tri>& delaunayTriangulation, std::vector<Line>& voronoiEdgesList);//����Delaunay������άŵͼ��
	static void creatVoronoiEdgeForOne(Tri delaunayTriangulation, std::vector<Line>neighborEdge,std::vector<Line> &voronoiEdgesList);//Ϊ�߽��������������߱�
	

	~Tri();
};

