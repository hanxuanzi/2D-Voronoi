
#include "Line.h"
#include <algorithm>
Line::Line() {

}
//构造函数
Line::Line(const Point& p1, const Point& p2) {
	this->pA = p1;
	this->pB = p2;
}
Line::Line(float x1, float y1, float x2, float y2) {
	this->pA = Point(x1, y1);//创造无实体对象，放入PA
	this->pB = Point(x2, y2);
}
//拷贝构造函数
Line::Line(const Line& l) {
	this->pA = l.pA;
	this->pB = l.pB;
}
//成员函数用于计算中点√
Point Line::getmidPoint() {
	return Point((this->pA.x + this->pB.x) / 2, (this->pA.y + this->pB.y) / 2);//计算并返回point对象
}
//赋值运算符重载函数
Line& Line::operator=(const Line& l) {
	this->pA = l.pA;
	this->pB = l.pB;
	return *this;
}
bool Line::operator==(const Line& l)const {
	if (
		(this->pA == l.pA && this->pB == l.pB) ||
		(this->pA == l.pB && this->pB == l.pA)
		)
		return true;
	return false;
}
bool Line::isPointInLine(const Point& p) {
	return(this->pA == p || this->pB == p);
}
//判断共线(未用）√
bool Line::IfconLine(const Point& p) {
	Point v1 = this->pA - p;
	Point v2 = this->pA - this->pB;
	float costheta = (v1.dot(v2) / (v1.dis() * v2.dis()));//向量夹角
	const double epsilon = 1e-6;
	//与1进行大小比较
	if (abs(1 - costheta) < epsilon || abs(1 + costheta) < epsilon) {
		return true;
	}
	else {
		return false;
	}
		
	
}

//判断边是否不在容器中(√
bool Line::isinVector(std::vector<Line> commonEdges, Line L1) {
	std::vector<Line>::iterator ret;
	ret = find(commonEdges.begin(), commonEdges.end(),L1);
	if (ret == commonEdges.end()) {
		return true;
	}
	else
		return false;
}

//根据两点生成一条指定方向的射线(
Line Line::produceRayLine(const Point& point1, const Point& point2) {
	 Point vector(point2.x - point1.x, point2.y - point1.y);//指向point2的向量
	 float length = (point1.dis(point2));//模长
	 float x1 = vector.x / length;
	 float y1 = vector.y / length;
	 Point vector1(x1 , y1);//归1化成为方向向量
	 Point endpoint = point1 + vector1 * 2;
	 Line rayLine(point1, endpoint);
	 return rayLine;
	//Point end;
	//if (direction.x > startpoint.x  ) {
	//	end.x = std::numeric_limits<double>::max();//x坐标无限大，表示射线沿着某方向无限的延申
	//}
	//else {
	//	end.x = -std::numeric_limits<double>::max();
	//}
	//end.y = (direction.y - startpoint.y) * (end.x - startpoint.x) / (direction.x - startpoint.x) + startpoint.y;//得出y坐标

	//return Line(startpoint, end);
}
 //判断两直线是否相交(√
bool Line:: iftwoLineCross( Line& l) {
	//快速排斥实验
	if (std::max(this->pA.x, this->pB.x) < std::min(l.pA.x, l.pB.x) || 
		std::max(l.pA.x,l.pB.x) < std::min(this->pA.x, this->pB.x) || 
		std::max(this->pA.y,this->pB.y)<std::min(l.pA.y,l.pB.y) ||
		std::max(l.pA.y, l.pB.y) < std::min(this->pA.y, this->pB.y)) {
		return false;

	}
	//跨立实验??  乘法？ 叉积正负？
	if ((l.pA - this->pA).cross(this->pB - this->pA).dot(
		(l.pB - this->pA).cross(this->pB - this->pA)) > 0 || 
		(this->pA - l.pB ).cross (l.pA - l.pB).dot(
		(this->pB - l.pB).cross(l.pA - l.pB)) > 0) {


	}
	return true;
}
//两相交直线返回交点(√)
Point Line::getCrossPoint(Line& l) {
	float x0;
	float y0;
	float b1 = (this->pB.y - this->pA.y) * (this->pA.x) + (this->pA.x - this->pB.x) * (this->pA.y);
	float b2 = (l.pB.y - l.pA.y) * l.pA.x + (l.pA.x - l.pB.x) * l.pA.y;
	float D = (this->pB.x - this->pA.x) * (l.pB.y - l.pA.y) - (l.pB.x - l.pA.x) * (this->pB.y - this->pA.y);
	float D1 = b2 * (this->pB.x - this->pA.x) - b1 * (l.pB.x - l.pA.x);
	float D2 = b2 * (this->pB.y - this->pA.y) - b1 * (l.pB.y - l.pA.y);
	x0 = D1 / D;
	y0 = D2 / D;
	return Point(x0, y0);

}
//已知是与视图框有交点的线段，返回起点√
Point Line::findstartPoint(Line& rayLine) {
	Point pA(-1, 1); Point pB(1, 1); Point pC(1, -1); Point pD(-1, -1);
	if (-1 < rayLine.pA.x < 1 && -1 < rayLine.pA.y < 1) {
		return rayLine.pA;
	}
	else {
		return rayLine.pB;
	}
}
//得到裁剪的最外围射线边
std::vector<Line> Line::endRayLine( std::vector<Line>& RecLine, std::vector<Line>& rayLine) {
	std::vector<Line> rayLine_swap(rayLine);//定义一个副本进行操作，不影响迭代器
	
	for (int i = 0; i < RecLine.size(); i++) {
		for (int j = 0; j < rayLine.size(); j++) {
			if (RecLine[i].iftwoLineCross(rayLine[j])) {
				Point crossPoint = RecLine[i].getCrossPoint(rayLine[j]);//找到交点坐标
				Line endrayLine = produceRayLine(findstartPoint(rayLine[j]), crossPoint);//根据交点坐标构建新的射线（裁剪）
				//将与边框有交点的射线删掉
				for (auto it = rayLine_swap.begin(); it != rayLine_swap.end(); ++it) {
					if (*it == rayLine[j]) {
						rayLine_swap.erase(it);
					}
				}
				//将新射线插入容器副本
				rayLine_swap.push_back(endrayLine);
			}
		}
	}
	//操作容器，得到裁剪后的最外围射线边容器
	rayLine = rayLine_swap;
	return rayLine;
}

Line::~Line() {

}
