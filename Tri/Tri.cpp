#include "Tri.h"
#include<cmath>
Tri::Tri(Point p1, Point p2, Point p3) {
	this->pA = p1;
	this->pB = p2;
	this->pC = p3;
	this->lAB = Line(p1, p2);//������ʵ�����
	this->lAC = Line(p1, p3);
	this->lBC = Line(p2, p3);
	//������뾶�����
	float d1 = (p2.x * p2.x + p2.y * p2.y) - (p1.x * p1.x + p1.y * p1.y);
	float d2 = (p3.x * p3.x + p3.y * p3.y) - (p2.x * p2.x + p2.y * p2.y);
	float fm = 2 * ((p3.y - p2.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p3.x - p2.x));
	float center_x = ((p3.y - p2.y) * d1 - (p2.y - p1.y) * d2) / fm;
	float center_y = ((p2.x - p1.x) * d2 - (p3.x - p2.x) * d1) / fm;
	Point centerPoint(center_x, center_y);
	float r = centerPoint.dis(p1);
	this->outCircle = Circle(centerPoint, r);



}
Tri::Tri() {

}

//�ж�Ϊ���������(δ�ã�
bool Tri:: operator==(const Tri& TA)const {
	int a = 0;
	if (this->lAB == TA.lAB || this->lAB == TA.lAC || this->lAB == TA.lBC)
		a++;
	if (this->lAC == TA.lAB || this->lAC == TA.lAC || this->lAC == TA.lBC)
		a++;
	if (this->lBC == TA.lAB || this->lBC == TA.lAC || this->lBC == TA.lBC)
		a++;
	if (a == 3)
		return true;
	return false;
}

//�жϵ������Բ�ڡ�
bool Tri::isPointInCir(const Point& point) {
	return (this->outCircle.centerPoint.dis(point) < this->outCircle.R);
}
//�жϵ����������ڡ̣�δ�ã�
bool Tri::isPointInTri(const Point& point)const {
	double S1 = (this->pB.x - this->pA.x) * (point.y - this->pA.y) - (this->pB.y - this->pA.y) * (point.x - this->pA.x);
	double S2 = (this->pC.x - this->pB.x) * (point.y - this->pB.y) - (this->pC.y - this->pB.y) * (point.x - this->pB.x);
	double S3 = (this->pA.x - this->pC.x) * (point.y - this->pC.y) - (this->pA.y - this->pC.y) * (point.x - this->pC.x);
	if ((S1 > 0 && S2 > 0 && S3 > 0) || (S1 < 0 && S2 < 0 && S3 < 0)) {
		return true;
	}
		return false;
	
	/*return (S1 > 0 && S2 > 0 && S3 > 0) || (S1 < 0 && S2 < 0 && S3 < 0);*/
   
}
//bool Tri::isPoinrInTriEdge(const Point& point) {
//
//}
//���Ӳ�����������ζ���-���

//�жϱ��Ƿ�����������
bool Tri::isEdgeOnTri(const Line& L)
{
	return (this->lAB == L || this->lAC == L || this->lBC == L);
}

//�жϵ��Ƿ�����������
bool Tri::isPointOnTri(const Point& point) {
	return (this->pA == point || this->pB == point || this->pC == point);
}
//�����������Ӱ�����������������ӡ�
void Tri::addNewTri( std::vector<Tri>& newTri,Tri badTri, Point point) {
	Tri tri1(badTri.pA, badTri.pB, point);
	Tri tri2(badTri.pB, badTri.pC, point);
	Tri tri3(badTri.pA, badTri.pC, point);

	newTri.push_back(tri1);
	newTri.push_back(tri2);
	newTri.push_back(tri3);
}

//�ҳ��������εĹ����ߡ�
void Tri::findCommonEdge( Tri T1,Tri T2,std::vector<Line> &L1) {
	std::vector<Point>commonSites;
	if (T1.pA == T2.pA || T1.pA == T2.pB || T1.pA == T2.pC) {
		commonSites.push_back(T1.pA);
		}
	if (T1.pB == T2.pA || T1.pB == T2.pB || T1.pB == T2.pC) {
		commonSites.push_back(T1.pB);
	}
	if(T1.pC == T2.pA || T1.pC == T2.pB || T1.pC == T2.pC) {
		commonSites.push_back(T1.pC);
	}
	if (commonSites.size() == 2) {
		Line m_edge(commonSites[0], commonSites[1]);
		L1.push_back(m_edge);
	}
}

//�ҳ�Ӱ�������εĹ����߲�������������С�
void Tri::findbadTriCommonEdges(std::vector<Tri>& badTri , std::vector<Line>& commonEdges) {

	if (badTri.size() <= 1) {
		return;  
	}
		for (int i = 0; i < badTri.size()-1; i++) {

			for (int j = i + 1; j < badTri.size(); j++) {
				findCommonEdge(badTri[i], badTri[j], commonEdges);
			}
		}
}

//ɾ���������������д���Ӱ�������ι����ߵ������Ρ�
void Tri::removenewTriByEdges(std::vector<Tri>&newTri, std::vector<Line>&Edges) {
	for (const auto& edge : Edges) {
		for (auto it = newTri.begin(); it != newTri.end();) {
			if(it->isEdgeOnTri(edge)) {
				it = newTri.erase(it);//�ж�ɾ��
			}else {
				++it;
			}
		}
	}
}


//ɾ���볬�������������������Ρ�
void  Tri::deleteConnectSuperTriByPoints(std::vector<Tri>& triangulation , Tri & superTri) {
	std::vector<Point> superPoint{ superTri.pA,superTri.pB,superTri.pC };
	for (auto& point : superPoint) {
		for (auto it = triangulation.begin(); it != triangulation.end();) {
			if (it->isPointOnTri(point)) {
				it = triangulation.erase(it);
			}else {
				++it;
			}
		}
	}
}
//���з��߲�����
void Tri::swapD(Tri tri1, Tri tri2, const Line & commonedge,std::vector<Tri>& triangulation_swap) {
	Point A = tri1.findFourthVertex(commonedge);
	Point B = tri2.findFourthVertex(commonedge);
	Point a = commonedge.pA;
	Point b = commonedge.pB;
	Tri newTri1(A, B, a);
	Tri newTri2(A, B, b);
	//Ѱ��-�滻
	auto it1 = std::find(triangulation_swap.begin(), triangulation_swap.end(), tri1);
	auto it2 = std::find(triangulation_swap.begin(), triangulation_swap.end(), tri2);
	if (it1 != triangulation_swap.end() && it2 != triangulation_swap.end()) {
		*it1 = newTri1;
		*it2 = newTri2;
	}

}
//�õ��������ηǹ������϶����
Point Tri::findFourthVertex(const Line& commonedge) {
	//����һ��������
	if ((this->pA != commonedge.pA) && (this->pA != commonedge.pB)) {
		return this->pA;
	}
	else if ((this->pB != commonedge.pA) && (this->pB != commonedge.pB)) {
		return this->pB;
	}
	else if ((this->pC != commonedge.pA )&& (this->pC != commonedge.pB)) {
		return this->pC;
	}
	else
		return Point();
}
//�ҵ��ߵ��е�����(δ�ã�
Point Tri::findMidPoint(const Line& L) {
	return Point((L.pA.x + L.pB.x) / 2, (L.pA.y + L.pB.y) / 2);
}

//LOP�Ż���
void Tri::localOptimization(std::vector<Tri>& newTri) {
	for (int i = 0; i < newTri.size()-1; i++) {
		for (int j = 1+i; j < newTri.size(); j++) {
			//��������������Ƿ��й�����
			std::vector<Line> L1;
			findCommonEdge(newTri[i], newTri[j], L1);
			/*std::cout << L1[0].pA.x << "     " << L1[0].pA.y << std::endl;
			std::cout << L1[0].pB.x << "     " << L1[0].pB.y << std::endl;*/
			if (L1.size() > 0) {
				//�ҵ����������ε��ĸ�����
				//Point fourthPoint2 = newTri[j].findFourthVertex(newTri[i], newTri[j], L1[0]);
				
				//�жϵ��Ķ����Ƿ�����һ���������Բ��
				bool IfInCircle1 = newTri[j].isPointInCir(newTri[i].findFourthVertex(L1[0]));
				bool IfInCircle2 = newTri[i].isPointInCir(newTri[j].findFourthVertex(L1[0]));
				
				//���߲���
				if (IfInCircle1 || IfInCircle2) {
					swapD(newTri[i], newTri[j], L1[0],newTri);

				}
				

			}
		}
	}
}

//Ϊ�߽��������������߱�
void Tri::creatVoronoiEdgeForOne( Tri  delaunayTriangulation, std::vector<Line>neighborEdge, std::vector<Line>& voronoiEdgesList) {
	/*std::vector<Line> Triline;
	Triline.push_back(delaunayTriangulation.lAB);
	Triline.push_back(delaunayTriangulation.lAC);
	Triline.push_back(delaunayTriangulation.lBC);
	for (int i = 0; i < Triline.size(); i++) {
		if (Line::isinVector(neighborEdge, Triline[i])) {

		}
	}*/
	
	if (Line::isinVector(neighborEdge, delaunayTriangulation.lAB)) {
		//lAB�����Ϊ�۽�
		if ((delaunayTriangulation.pA - delaunayTriangulation.pC).dot(delaunayTriangulation.pB - delaunayTriangulation.pC) < 0) {
			//�������߲߱�����άŵ���б���
			if (-1 < delaunayTriangulation.outCircle.centerPoint.x < 1 && -1 < delaunayTriangulation.outCircle.centerPoint.y < 1) {
				Line rayLine(delaunayTriangulation.lAB.getmidPoint(), delaunayTriangulation.outCircle.centerPoint);
				voronoiEdgesList.push_back(rayLine);
			}
			/*else {
				Line rayLine = Line::produceRayLine(delaunayTriangulation.lAB.getmidPoint(), delaunayTriangulation.outCircle.centerPoint);
				voronoiEdgesList.push_back(rayLine);
			}*/
			
		}
		//���
		else if((delaunayTriangulation.pA - delaunayTriangulation.pC).dot(delaunayTriangulation.pB - delaunayTriangulation.pC) > 0) {
			Line rayLine = Line::produceRayLine(delaunayTriangulation.outCircle.centerPoint, delaunayTriangulation.lAB.getmidPoint());
			voronoiEdgesList.push_back(rayLine);
		}
	}

	if (Line::isinVector(neighborEdge, delaunayTriangulation.lAC)) {
		if ((delaunayTriangulation.pA - delaunayTriangulation.pB).dot(delaunayTriangulation.pC - delaunayTriangulation.pB) < 0) {
			if (-1 < delaunayTriangulation.outCircle.centerPoint.x < 1 && -1 < delaunayTriangulation.outCircle.centerPoint.y < 1) {
				Line rayLine(delaunayTriangulation.lAC.getmidPoint(), delaunayTriangulation.outCircle.centerPoint);
				voronoiEdgesList.push_back(rayLine);
			}
			/*else {
				Line rayLine = Line::produceRayLine(delaunayTriangulation.lAC.getmidPoint(), delaunayTriangulation.outCircle.centerPoint);
				voronoiEdgesList.push_back(rayLine);
			}*/
			
		}
		else if ((delaunayTriangulation.pA - delaunayTriangulation.pB).dot(delaunayTriangulation.pC - delaunayTriangulation.pB) > 0) {
			Line rayLine = Line::produceRayLine(delaunayTriangulation.outCircle.centerPoint, delaunayTriangulation.lAC.getmidPoint());
			voronoiEdgesList.push_back(rayLine);
		}
	}

	if (Line::isinVector(neighborEdge, delaunayTriangulation.lBC)) {
		if ((delaunayTriangulation.pB - delaunayTriangulation.pA).dot(delaunayTriangulation.pC - delaunayTriangulation.pA) < 0) {
			if (-1 < delaunayTriangulation.outCircle.centerPoint.x < 1 && -1 < delaunayTriangulation.outCircle.centerPoint.y < 1) {
				Line rayLine(delaunayTriangulation.lBC.getmidPoint(), delaunayTriangulation.outCircle.centerPoint);
				voronoiEdgesList.push_back(rayLine);
			}
			/*else {
				Line rayLine = Line::produceRayLine(delaunayTriangulation.lBC.getmidPoint(), delaunayTriangulation.outCircle.centerPoint);
				voronoiEdgesList.push_back(rayLine);
			}*/
			
		}
		else if ((delaunayTriangulation.pB - delaunayTriangulation.pA).dot(delaunayTriangulation.pC - delaunayTriangulation.pA) > 0){
			Line rayLine = Line::produceRayLine(delaunayTriangulation.outCircle.centerPoint, delaunayTriangulation.lBC.getmidPoint());
			voronoiEdgesList.push_back(rayLine);
		}
	}
}


//����Delaunay Triangle
   std:: vector<Tri> Tri::delaunayTriangulation(const std::vector<Point>& points) {
	//���Ƴ��������β�����vector
	Point p1(-1.0, 1.0);
	Point p2(-1.0, -3.0);
	Point p3(3.0, 1.0);
	Tri SuperTri(p1, p2, p3);
	std::vector<Tri>triangulation;//Delaunay Triangle�����գ�
	triangulation.push_back(SuperTri);
	std::vector<Tri> badTri;//�����˵���ص�Ӱ��������(ÿ�ν���ѭ����һ���µ��������棬��ֹ���棩
	std::vector<Tri> newTri;//���γɵ�������
	std::vector<Line> commonEdges;//��Ӱ�������ι�����
	std::vector<Tri> triangulation_swap(triangulation);
	for (auto& point: points) {
        commonEdges.clear();
		newTri.clear();
		badTri.clear();
		//�� ������
		//for (auto it = triangulation.begin(); it != triangulation.end(); ) {
		//	 if (it->isPointInCir(point)) {
		//		badTri.push_back(*it);  // ��Ӱ�������η�������
		//		it = triangulation.erase(it);  // ɾ����ǰ������ָ���Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
		//	 }else {
		//		 ++it;
		//	 }
		//	 for (int i = 0; i < badTri.size(); ++i)
		//	 {
		//		 addNewTri(newTri, badTri[i], point);//���������η�������newTri��
		//		 findbadTriCommonEdges(badTri, commonEdges);//�ҳ�Ӱ�������ι����߲�����commonEdges��
		//		 removenewTriByEdges(newTri, commonEdges);//������Ӱ�������ι����ߵ���������ɾ��
		//	 }
		//	
		//	 //������õ�newTri����triangulation
		//	 triangulation.insert(triangulation.end(), newTri.begin(), newTri.end());
		//
		//}
		for (int i = 0; i<triangulation.size();i++) {
			if (triangulation[i].isPointInCir(point)) {
				badTri.push_back(triangulation[i]);  // ��Ӱ�������η�������
				for (auto it = triangulation_swap.begin(); it != triangulation_swap.end();++it) {
					if (*it == triangulation[i]) {
						triangulation_swap.erase(it);
						break;
					}
				}
			}
		}
		for (int j = 0; j < badTri.size(); ++j)
		{
			addNewTri(newTri, badTri[j], point);//���������η�������newTri��
		}
		
		findbadTriCommonEdges(badTri, commonEdges);//�ҳ�Ӱ�������ι����߲�����commonEdges��
		removenewTriByEdges(newTri, commonEdges);//������Ӱ�������ι����ߵ���������ɾ��
		//������õ�newTri����triangulation_swap
		triangulation_swap.insert(triangulation_swap.end(), newTri.begin(), newTri.end());
		//����LOP�Ż�
		localOptimization(triangulation_swap);
		//��ֵ����������
		triangulation=triangulation_swap;

		
		

		//===�޸�
		////�������triangulation����badTri���в��֣��������һѭ����ʼʱ����������Ӱ��������
		//triangulation.erase(std::remove_if(triangulation.begin(), triangulation.end(),[&badTri](const Tri& triangle) {
		//			return std::find(badTri.begin(), badTri.end(), triangle) != badTri.end();
		//		}), triangulation.end());

	}
	////ɾ��triangulation����SuperTri���ӵ�������
	deleteConnectSuperTriByPoints(triangulation, SuperTri);
	return triangulation;
}

   //����Delaunay������άŵͼ��
   std::vector<Line>Tri:: VoronoiDiagramEdges(const std::vector<Tri>& delaunayTriangulation, std::vector<Line>& voronoiEdgesList) {
	   std::vector<Line> voronoiRayEdge;//��Χ���߱�
	   voronoiEdgesList.clear();//άŵͼ�ı�
	   std::vector<Line> neighborEdge;//���������е��ڽӱ�
	   std::vector<Line>neighborOneEdge;//������һ���ڽӱ�
	   std::vector<Line> rayLine;//����������߱�
	   for (int i = 0; i < delaunayTriangulation.size(); i++) {
		   neighborEdge.clear();
		   
		   for (int j = 0; j < delaunayTriangulation.size(); j++) {
			   if (j != 1) {
				   neighborOneEdge.clear();
				   findCommonEdge(delaunayTriangulation[i], delaunayTriangulation[j], neighborOneEdge);
				   //���ҵ��ڽ������Σ�����άŵ��
				   if (neighborOneEdge.size() > 0) {
					   Line voronoiEdge = Line(delaunayTriangulation[i].outCircle.centerPoint, delaunayTriangulation[j].outCircle.centerPoint);//�������������������Բ��Բ��
					   //���άŵ���Ƿ��Ѿ���������
					   if (Line::isinVector(voronoiEdgesList, voronoiEdge)) {
						   //����άŵ���б�
						   voronoiEdgesList.push_back(voronoiEdge);
					   }
					   //�� �������� ���������ڽӱߵı߷�������
					   neighborEdge.push_back(neighborOneEdge[0]);

				   }
			   }
		   }
		   //�ж� �������� �Ƿ��Ǳ߽�������(���ǽ�������Χάŵ�ߵ�����)
		   if (neighborEdge.size() < 3) {

			   //̫���������к�������============================
			   ////�ж� �������� �е����ڽӱ�
			   //if (Line::isinVector(neighborEdge, delaunayTriangulation[i].lAB)) {
				  // Point midpoint = findMidPoint(delaunayTriangulation[i].lAB);//�е�
				  //// Line RayEdge = Line(midpoint, delaunayTriangulation[i].outCircle.centerPoint);//����Χ��
				  // Line RayEdge = Line::produceRayLine(delaunayTriangulation[i].outCircle.centerPoint , midpoint);//����
				  // voronoiEdgesList.push_back(RayEdge);//����άŵ������
			   //}
			   //if (Line::isinVector(neighborEdge, delaunayTriangulation[i].lAC)) {
				  // Point midpoint = findMidPoint(delaunayTriangulation[i].lAC);//�е�
				  // //Line RayEdge = Line(midpoint, delaunayTriangulation[i].outCircle.centerPoint);//����Χ��
				  // Line RayEdge = Line::produceRayLine(delaunayTriangulation[i].outCircle.centerPoint, midpoint);
				  // voronoiEdgesList.push_back(RayEdge);//����άŵ������
			   //}
			   //if (Line::isinVector(neighborEdge, delaunayTriangulation[i].lBC)) {
				  // Point midpoint = findMidPoint(delaunayTriangulation[i].lBC);//�е�
				  // //Line RayEdge = Line(midpoint, delaunayTriangulation[i].outCircle.centerPoint);//����Χ��
				  // Line RayEdge = Line::produceRayLine(delaunayTriangulation[i].outCircle.centerPoint, midpoint);
				  // voronoiEdgesList.push_back(RayEdge);//����άŵ������
			   //}
			   //======================================
			   //ͨ�����Ǹ��߽������εı߽����жϲ�����άŵ��(������ߣ�����������
			  
			   creatVoronoiEdgeForOne(delaunayTriangulation[i] , neighborEdge ,  rayLine);

		   }
	   }
	   //�ü��߽�
	   Point pA(-1, 1); Point pB(1, 1); Point pC(1, -1); Point pD(-1, -1);
	   Line lAB(pA, pB); Line lBC(pB, pC); Line lCD(pC, pD); Line lDA(pD, pA);
	   std::vector<Line> RecLine;
	   RecLine.push_back(lAB);
	   RecLine.push_back(lBC);
	   RecLine.push_back(lCD);
	   RecLine.push_back(lDA);
	   std::vector<Line> endRayLine = Line::endRayLine(RecLine,rayLine );
	   //�õ����յ�άŵ����
	   voronoiEdgesList.insert(voronoiEdgesList.end(),endRayLine.begin(),endRayLine.end());
	  
	   return voronoiEdgesList;
	   
   }


Tri::~Tri() {

}

