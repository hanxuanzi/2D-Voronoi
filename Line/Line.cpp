
#include "Line.h"
#include <algorithm>
Line::Line() {

}
//���캯��
Line::Line(const Point& p1, const Point& p2) {
	this->pA = p1;
	this->pB = p2;
}
Line::Line(float x1, float y1, float x2, float y2) {
	this->pA = Point(x1, y1);//������ʵ����󣬷���PA
	this->pB = Point(x2, y2);
}
//�������캯��
Line::Line(const Line& l) {
	this->pA = l.pA;
	this->pB = l.pB;
}
//��Ա�������ڼ����е��
Point Line::getmidPoint() {
	return Point((this->pA.x + this->pB.x) / 2, (this->pA.y + this->pB.y) / 2);//���㲢����point����
}
//��ֵ��������غ���
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
//�жϹ���(δ�ã���
bool Line::IfconLine(const Point& p) {
	Point v1 = this->pA - p;
	Point v2 = this->pA - this->pB;
	float costheta = (v1.dot(v2) / (v1.dis() * v2.dis()));//�����н�
	const double epsilon = 1e-6;
	//��1���д�С�Ƚ�
	if (abs(1 - costheta) < epsilon || abs(1 + costheta) < epsilon) {
		return true;
	}
	else {
		return false;
	}
		
	
}

//�жϱ��Ƿ���������(��
bool Line::isinVector(std::vector<Line> commonEdges, Line L1) {
	std::vector<Line>::iterator ret;
	ret = find(commonEdges.begin(), commonEdges.end(),L1);
	if (ret == commonEdges.end()) {
		return true;
	}
	else
		return false;
}

//������������һ��ָ�����������(
Line Line::produceRayLine(const Point& point1, const Point& point2) {
	 Point vector(point2.x - point1.x, point2.y - point1.y);//ָ��point2������
	 float length = (point1.dis(point2));//ģ��
	 float x1 = vector.x / length;
	 float y1 = vector.y / length;
	 Point vector1(x1 , y1);//��1����Ϊ��������
	 Point endpoint = point1 + vector1 * 2;
	 Line rayLine(point1, endpoint);
	 return rayLine;
	//Point end;
	//if (direction.x > startpoint.x  ) {
	//	end.x = std::numeric_limits<double>::max();//x�������޴󣬱�ʾ��������ĳ�������޵�����
	//}
	//else {
	//	end.x = -std::numeric_limits<double>::max();
	//}
	//end.y = (direction.y - startpoint.y) * (end.x - startpoint.x) / (direction.x - startpoint.x) + startpoint.y;//�ó�y����

	//return Line(startpoint, end);
}
 //�ж���ֱ���Ƿ��ཻ(��
bool Line:: iftwoLineCross( Line& l) {
	//�����ų�ʵ��
	if (std::max(this->pA.x, this->pB.x) < std::min(l.pA.x, l.pB.x) || 
		std::max(l.pA.x,l.pB.x) < std::min(this->pA.x, this->pB.x) || 
		std::max(this->pA.y,this->pB.y)<std::min(l.pA.y,l.pB.y) ||
		std::max(l.pA.y, l.pB.y) < std::min(this->pA.y, this->pB.y)) {
		return false;

	}
	//����ʵ��??  �˷��� ���������
	if ((l.pA - this->pA).cross(this->pB - this->pA).dot(
		(l.pB - this->pA).cross(this->pB - this->pA)) > 0 || 
		(this->pA - l.pB ).cross (l.pA - l.pB).dot(
		(this->pB - l.pB).cross(l.pA - l.pB)) > 0) {


	}
	return true;
}
//���ֱཻ�߷��ؽ���(��)
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
//��֪������ͼ���н�����߶Σ���������
Point Line::findstartPoint(Line& rayLine) {
	Point pA(-1, 1); Point pB(1, 1); Point pC(1, -1); Point pD(-1, -1);
	if (-1 < rayLine.pA.x < 1 && -1 < rayLine.pA.y < 1) {
		return rayLine.pA;
	}
	else {
		return rayLine.pB;
	}
}
//�õ��ü�������Χ���߱�
std::vector<Line> Line::endRayLine( std::vector<Line>& RecLine, std::vector<Line>& rayLine) {
	std::vector<Line> rayLine_swap(rayLine);//����һ���������в�������Ӱ�������
	
	for (int i = 0; i < RecLine.size(); i++) {
		for (int j = 0; j < rayLine.size(); j++) {
			if (RecLine[i].iftwoLineCross(rayLine[j])) {
				Point crossPoint = RecLine[i].getCrossPoint(rayLine[j]);//�ҵ���������
				Line endrayLine = produceRayLine(findstartPoint(rayLine[j]), crossPoint);//���ݽ������깹���µ����ߣ��ü���
				//����߿��н��������ɾ��
				for (auto it = rayLine_swap.begin(); it != rayLine_swap.end(); ++it) {
					if (*it == rayLine[j]) {
						rayLine_swap.erase(it);
					}
				}
				//�������߲�����������
				rayLine_swap.push_back(endrayLine);
			}
		}
	}
	//�����������õ��ü��������Χ���߱�����
	rayLine = rayLine_swap;
	return rayLine;
}

Line::~Line() {

}
