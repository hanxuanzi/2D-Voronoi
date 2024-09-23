#include "Tri.h"
#include<cmath>
Tri::Tri(Point p1, Point p2, Point p3) {
	this->pA = p1;
	this->pB = p2;
	this->pC = p3;
	this->lAB = Line(p1, p2);//创造无实体对象
	this->lAC = Line(p1, p3);
	this->lBC = Line(p2, p3);
	//外心与半径计算√
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

//判断为三角形相等(未用）
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

//判断点在外接圆内√
bool Tri::isPointInCir(const Point& point) {
	return (this->outCircle.centerPoint.dis(point) < this->outCircle.R);
}
//判断点在三角形内√（未用）
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
//连接插入点与三角形顶点-添加

//判断边是否属于三角形
bool Tri::isEdgeOnTri(const Line& L)
{
	return (this->lAB == L || this->lAC == L || this->lBC == L);
}

//判断点是否在三角形上
bool Tri::isPointOnTri(const Point& point) {
	return (this->pA == point || this->pB == point || this->pC == point);
}
//将插入点与受影响三角形三个点连接√
void Tri::addNewTri( std::vector<Tri>& newTri,Tri badTri, Point point) {
	Tri tri1(badTri.pA, badTri.pB, point);
	Tri tri2(badTri.pB, badTri.pC, point);
	Tri tri3(badTri.pA, badTri.pC, point);

	newTri.push_back(tri1);
	newTri.push_back(tri2);
	newTri.push_back(tri3);
}

//找出两三角形的公共边√
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

//找出影响三角形的公共边并将其放入容器中√
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

//删除新三角形容器中带有影响三角形公共边的三角形√
void Tri::removenewTriByEdges(std::vector<Tri>&newTri, std::vector<Line>&Edges) {
	for (const auto& edge : Edges) {
		for (auto it = newTri.begin(); it != newTri.end();) {
			if(it->isEdgeOnTri(edge)) {
				it = newTri.erase(it);//判断删除
			}else {
				++it;
			}
		}
	}
}


//删除与超级三角形相连的三角形√
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
//进行翻边操作√
void Tri::swapD(Tri tri1, Tri tri2, const Line & commonedge,std::vector<Tri>& triangulation_swap) {
	Point A = tri1.findFourthVertex(commonedge);
	Point B = tri2.findFourthVertex(commonedge);
	Point a = commonedge.pA;
	Point b = commonedge.pB;
	Tri newTri1(A, B, a);
	Tri newTri2(A, B, b);
	//寻找-替换
	auto it1 = std::find(triangulation_swap.begin(), triangulation_swap.end(), tri1);
	auto it2 = std::find(triangulation_swap.begin(), triangulation_swap.end(), tri2);
	if (it1 != triangulation_swap.end() && it2 != triangulation_swap.end()) {
		*it1 = newTri1;
		*it2 = newTri2;
	}

}
//得到两三角形非公共边上顶点√
Point Tri::findFourthVertex(const Line& commonedge) {
	//检查第一个三角形
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
//找到边的中点坐标(未用）
Point Tri::findMidPoint(const Line& L) {
	return Point((L.pA.x + L.pB.x) / 2, (L.pA.y + L.pB.y) / 2);
}

//LOP优化√
void Tri::localOptimization(std::vector<Tri>& newTri) {
	for (int i = 0; i < newTri.size()-1; i++) {
		for (int j = 1+i; j < newTri.size(); j++) {
			//检查两个三角形是否有公共边
			std::vector<Line> L1;
			findCommonEdge(newTri[i], newTri[j], L1);
			/*std::cout << L1[0].pA.x << "     " << L1[0].pA.y << std::endl;
			std::cout << L1[0].pB.x << "     " << L1[0].pB.y << std::endl;*/
			if (L1.size() > 0) {
				//找到两个三角形第四个顶点
				//Point fourthPoint2 = newTri[j].findFourthVertex(newTri[i], newTri[j], L1[0]);
				
				//判断第四顶点是否在另一三角形外接圆内
				bool IfInCircle1 = newTri[j].isPointInCir(newTri[i].findFourthVertex(L1[0]));
				bool IfInCircle2 = newTri[i].isPointInCir(newTri[j].findFourthVertex(L1[0]));
				
				//翻边操作
				if (IfInCircle1 || IfInCircle2) {
					swapD(newTri[i], newTri[j], L1[0],newTri);

				}
				

			}
		}
	}
}

//为边界三角形生成射线边
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
		//lAB对向角为钝角
		if ((delaunayTriangulation.pA - delaunayTriangulation.pC).dot(delaunayTriangulation.pB - delaunayTriangulation.pC) < 0) {
			//生成射线边并放入维诺边列表中
			if (-1 < delaunayTriangulation.outCircle.centerPoint.x < 1 && -1 < delaunayTriangulation.outCircle.centerPoint.y < 1) {
				Line rayLine(delaunayTriangulation.lAB.getmidPoint(), delaunayTriangulation.outCircle.centerPoint);
				voronoiEdgesList.push_back(rayLine);
			}
			/*else {
				Line rayLine = Line::produceRayLine(delaunayTriangulation.lAB.getmidPoint(), delaunayTriangulation.outCircle.centerPoint);
				voronoiEdgesList.push_back(rayLine);
			}*/
			
		}
		//锐角
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


//绘制Delaunay Triangle
   std:: vector<Tri> Tri::delaunayTriangulation(const std::vector<Point>& points) {
	//绘制超级三角形并放入vector
	Point p1(-1.0, 1.0);
	Point p2(-1.0, -3.0);
	Point p3(3.0, 1.0);
	Tri SuperTri(p1, p2, p3);
	std::vector<Tri>triangulation;//Delaunay Triangle（最终）
	triangulation.push_back(SuperTri);
	std::vector<Tri> badTri;//存放与此点相关的影响三角形(每次进入循环建一个新的容器储存，防止干涉）
	std::vector<Tri> newTri;//新形成的三角形
	std::vector<Line> commonEdges;//受影响三角形公共边
	std::vector<Tri> triangulation_swap(triangulation);
	for (auto& point: points) {
        commonEdges.clear();
		newTri.clear();
		badTri.clear();
		//旧 有问题
		//for (auto it = triangulation.begin(); it != triangulation.end(); ) {
		//	 if (it->isPointInCir(point)) {
		//		badTri.push_back(*it);  // 将影响三角形放入容器
		//		it = triangulation.erase(it);  // 删除当前迭代器指向的元素，并返回指向下一个元素的迭代器
		//	 }else {
		//		 ++it;
		//	 }
		//	 for (int i = 0; i < badTri.size(); ++i)
		//	 {
		//		 addNewTri(newTri, badTri[i], point);//将新三角形放入容器newTri中
		//		 findbadTriCommonEdges(badTri, commonEdges);//找出影响三角形公共边并放入commonEdges中
		//		 removenewTriByEdges(newTri, commonEdges);//将带有影响三角形公共边的新三角形删除
		//	 }
		//	
		//	 //将处理好的newTri塞给triangulation
		//	 triangulation.insert(triangulation.end(), newTri.begin(), newTri.end());
		//
		//}
		for (int i = 0; i<triangulation.size();i++) {
			if (triangulation[i].isPointInCir(point)) {
				badTri.push_back(triangulation[i]);  // 将影响三角形放入容器
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
			addNewTri(newTri, badTri[j], point);//将新三角形放入容器newTri中
		}
		
		findbadTriCommonEdges(badTri, commonEdges);//找出影响三角形公共边并放入commonEdges中
		removenewTriByEdges(newTri, commonEdges);//将带有影响三角形公共边的新三角形删除
		//将处理好的newTri塞给triangulation_swap
		triangulation_swap.insert(triangulation_swap.end(), newTri.begin(), newTri.end());
		//进行LOP优化
		localOptimization(triangulation_swap);
		//赋值给最终容器
		triangulation=triangulation_swap;

		
		

		//===修改
		////清除容器triangulation中与badTri共有部分，即清除这一循环开始时被检索出的影响三角形
		//triangulation.erase(std::remove_if(triangulation.begin(), triangulation.end(),[&badTri](const Tri& triangle) {
		//			return std::find(badTri.begin(), badTri.end(), triangle) != badTri.end();
		//		}), triangulation.end());

	}
	////删除triangulation中与SuperTri连接的三角形
	deleteConnectSuperTriByPoints(triangulation, SuperTri);
	return triangulation;
}

   //根据Delaunay来生成维诺图边
   std::vector<Line>Tri:: VoronoiDiagramEdges(const std::vector<Tri>& delaunayTriangulation, std::vector<Line>& voronoiEdgesList) {
	   std::vector<Line> voronoiRayEdge;//外围射线边
	   voronoiEdgesList.clear();//维诺图的边
	   std::vector<Line> neighborEdge;//三角形所有的邻接边
	   std::vector<Line>neighborOneEdge;//三角形一个邻接边
	   std::vector<Line> rayLine;//储存外界射线边
	   for (int i = 0; i < delaunayTriangulation.size(); i++) {
		   neighborEdge.clear();
		   
		   for (int j = 0; j < delaunayTriangulation.size(); j++) {
			   if (j != 1) {
				   neighborOneEdge.clear();
				   findCommonEdge(delaunayTriangulation[i], delaunayTriangulation[j], neighborOneEdge);
				   //若找到邻接三角形，构造维诺边
				   if (neighborOneEdge.size() > 0) {
					   Line voronoiEdge = Line(delaunayTriangulation[i].outCircle.centerPoint, delaunayTriangulation[j].outCircle.centerPoint);//连接这两个三角形外接圆的圆心
					   //检查维诺边是否已经在容器中
					   if (Line::isinVector(voronoiEdgesList, voronoiEdge)) {
						   //插入维诺边列表
						   voronoiEdgesList.push_back(voronoiEdge);
					   }
					   //将 此三角形 的所有有邻接边的边放入容器
					   neighborEdge.push_back(neighborOneEdge[0]);

				   }
			   }
		   }
		   //判断 此三角形 是否是边界三角形(若是进行最外围维诺边的生成)
		   if (neighborEdge.size() < 3) {

			   //太繁琐，进行函数抽象============================
			   ////判断 此三角形 中的无邻接边
			   //if (Line::isinVector(neighborEdge, delaunayTriangulation[i].lAB)) {
				  // Point midpoint = findMidPoint(delaunayTriangulation[i].lAB);//中点
				  //// Line RayEdge = Line(midpoint, delaunayTriangulation[i].outCircle.centerPoint);//最外围边
				  // Line RayEdge = Line::produceRayLine(delaunayTriangulation[i].outCircle.centerPoint , midpoint);//射线
				  // voronoiEdgesList.push_back(RayEdge);//放入维诺边链表
			   //}
			   //if (Line::isinVector(neighborEdge, delaunayTriangulation[i].lAC)) {
				  // Point midpoint = findMidPoint(delaunayTriangulation[i].lAC);//中点
				  // //Line RayEdge = Line(midpoint, delaunayTriangulation[i].outCircle.centerPoint);//最外围边
				  // Line RayEdge = Line::produceRayLine(delaunayTriangulation[i].outCircle.centerPoint, midpoint);
				  // voronoiEdgesList.push_back(RayEdge);//放入维诺边链表
			   //}
			   //if (Line::isinVector(neighborEdge, delaunayTriangulation[i].lBC)) {
				  // Point midpoint = findMidPoint(delaunayTriangulation[i].lBC);//中点
				  // //Line RayEdge = Line(midpoint, delaunayTriangulation[i].outCircle.centerPoint);//最外围边
				  // Line RayEdge = Line::produceRayLine(delaunayTriangulation[i].outCircle.centerPoint, midpoint);
				  // voronoiEdgesList.push_back(RayEdge);//放入维诺边链表
			   //}
			   //======================================
			   //通过对那个边界三角形的边进行判断并生成维诺边(外界射线），放入容器
			  
			   creatVoronoiEdgeForOne(delaunayTriangulation[i] , neighborEdge ,  rayLine);

		   }
	   }
	   //裁剪边界
	   Point pA(-1, 1); Point pB(1, 1); Point pC(1, -1); Point pD(-1, -1);
	   Line lAB(pA, pB); Line lBC(pB, pC); Line lCD(pC, pD); Line lDA(pD, pA);
	   std::vector<Line> RecLine;
	   RecLine.push_back(lAB);
	   RecLine.push_back(lBC);
	   RecLine.push_back(lCD);
	   RecLine.push_back(lDA);
	   std::vector<Line> endRayLine = Line::endRayLine(RecLine,rayLine );
	   //得到最终的维诺链表
	   voronoiEdgesList.insert(voronoiEdgesList.end(),endRayLine.begin(),endRayLine.end());
	  
	   return voronoiEdgesList;
	   
   }


Tri::~Tri() {

}

