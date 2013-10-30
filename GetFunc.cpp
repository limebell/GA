#include<vector>
#include<math.h>
#include<malloc.h>
#include"GetFunc.h"
using namespace std;

#define PI 3.141592;

double GetFunc::f_distance(pair<double,double> a, pair<double,double> b)
{
	return sqrt( (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second) );
}
	

bool GetFunc::get_func(int *size, pair<double,double> *func, int num)
{
	double pi = PI;
	double GAP = 2*pi / num;
	
	pair<double,double> point[8];
	pair<double,double> ppoint[8];
	pair<bool, pair<double,double>> temp1;
	pair<bool, pair<double,double>> temp2;
	pair<bool, pair<double,double>> temp;

	double theta = 0;

	point[0].first = point[0].second = 0;
	
	for(int i=0; i < num; theta += GAP, i++)
	{
		point[1].first = point[0].first - size[0];
		point[1].second = point[0].second + size[11];
	
		point[2].first = point[0].first + size[12]*cos(theta);
		point[2].second = point[0].second + size[12]*sin(theta);

		//3
		temp1 = GetFunc::getPoint1(point[1], point[2], size[1], size[9]);
		temp2 = GetFunc::getPoint2(point[1], point[2], size[1], size[9]);
		if( temp1.first == false ) return false;
		else if( i == 0 ){
			if((point[2].second-point[1].second)*(temp1.second.first-point[1].first)/(point[2].first-point[1].first)+point[1].second-temp1.second.second>0){
				point[3] = temp1.second;
			} else point[3] = temp2.second;
			ppoint[3] = point[3];
		} else {
			point[3] = (GetFunc::f_distance(temp1.second, ppoint[3])<GetFunc::f_distance(temp2.second, ppoint[3]))?temp1.second:temp2.second;
			ppoint[3] = point[3];
		}
	
		//4
		temp1 = GetFunc::getPoint1(point[1], point[3], size[3], size[4]);
		temp2 = GetFunc::getPoint2(point[1], point[3], size[3], size[4]);
		if( temp1.first == false ) return false;
		else if( i == 0 ){
			if( GetFunc::isOpposite(point[1], point[3], point[2], temp1.second) ) point[4] = temp1.second;
			else point[4] = temp2.second;
			ppoint[4] = point[4];
		} else {
			point[4] = (GetFunc::f_distance(temp1.second, ppoint[4])<GetFunc::f_distance(temp2.second, ppoint[4]))?temp1.second:temp2.second;
			ppoint[4] = point[4];
		}
	
		//5
		temp1 = GetFunc::getPoint1(point[1], point[2], size[2], size[10]);
		temp2 = GetFunc::getPoint2(point[1], point[2], size[2], size[10]);
		if( temp1.first == false ) return false;
		else if( i == 0 ){
			if( GetFunc::isOpposite(point[1], point[2], point[3], temp1.second) ) point[5] = temp1.second;
			else point[5] = temp2.second;
			ppoint[5] = point[5];
		} else {
			point[5] = (GetFunc::f_distance(temp1.second, ppoint[5])<GetFunc::f_distance(temp2.second, ppoint[5]))?temp1.second:temp2.second;
			ppoint[5] = point[5];
		}
	
		//6
		temp1 = GetFunc::getPoint1(point[4], point[5], size[5], size[6]);
		temp2 = GetFunc::getPoint2(point[4], point[5], size[5], size[6]);
		if( temp1.first == false ) return false;
		else if( i == 0 ){
			if( GetFunc::isOpposite(point[4], point[5], point[1], temp1.second) ) point[6] = temp1.second;
			else point[6] = temp2.second;
			ppoint[6] = point[6];
		} else {
			point[6] = (GetFunc::f_distance(temp1.second, ppoint[6])<GetFunc::f_distance(temp2.second, ppoint[6]))?temp1.second:temp2.second;
			ppoint[6] = point[6];
		}
	
		//7
		temp1 = GetFunc::getPoint1(point[5], point[6], size[8], size[7]);
		temp2 = GetFunc::getPoint2(point[5], point[6], size[8], size[7]);
		if( temp1.first == false ) return false;
		else if( i == 0 ){
			if( temp1.second.second > point[5].second && temp1.second.second > point[6].second ){
				point[7] = temp1.second;
				ppoint[7] = point[7];
			} else if( temp2.second.second > point[5].second && temp2.second.second > point[6].second ){
				point[7] = temp2.second;
				ppoint[7] = point[7];
			} else return false;
		} else {
			point[7] = (GetFunc::f_distance(temp1.second, ppoint[7])<GetFunc::f_distance(temp2.second, ppoint[7]))?temp1.second:temp2.second;
			ppoint[7] = point[7];
		}

		func[i] = point[7];
	}

	return true;
}

// +
pair<bool, pair<double,double>> GetFunc::getPoint1(pair<double,double> p1, pair<double,double> p2, int l1,int l2)
{
	pair<bool, pair<double,double>> R;
	pair<double,double> p3;
	double x1, x2, y1, y2;
	x1=p1.first, x2=p2.first, y1=p1.second, y2=p2.second;
	double A, B, a, b, c;
	if(x1 == x2 && y1 == y2)
	{
		R.first = false;
		return R;
	} else if(x1 != x2 && y1 == y2) {
		p3.first = (x1*x1-x2*x2-l1*l1+l2*l2)/(2*(x1-x2));
		if( l1*l1 - (x1-p3.first)*(x1-p3.first) <= 0 ){
			R.first = false;
			return R;
		} else {
			R.first = true;
			p3.first = y1 + sqrt(l1*l1 - (x1-p3.first)*(x1-p3.first));
			R.second = p3;
			return R;
		}
	} else if(x1 == x2 && y1 != y2) {
		p3.second = (y1*y1-y2*y2-l1*l1+l2*l2)/(2*(y1-y2));
		if( l1*l1-(y1-p3.second)*(y1-p3.second) <= 0 ){
			R.first = false;
			return R;
		} else {
			R.first = true;
			p3.first = x1 + sqrt(l1*l1-(y1-p3.second)*(y1-p3.second));
			R.second = p3;
			return R;
		}
	} else {
		A = (x1-x2)/(y2-y1);
		B = (x1*x1-x2*x2+y1*y1-y2*y2-l1*l1+l2*l2)/(2*(y1-y2));
		a = 1+A*A;
		b = -2*x1-2*y1*A+2*A*B;
		c = x1*x1+y1*y1+B*B-2*y1*B-l1*l1;
		if(b*b-4*a*c <= 0){
			R.first = false;
			return R;
		} else {
			R.first = true;
			p3.first = (-b+sqrt(b*b-4*a*c))/(2*a);
			p3.second = A*p3.first+B;
			R.second = p3;
			return R;
		}
	}
}

// -
pair<bool, pair<double,double>> GetFunc::getPoint2(pair<double,double> p1, pair<double,double> p2, int l1, int l2)
{
	pair<bool, pair<double,double>> R;
	pair<double,double> p3;
	double x1, x2, y1, y2;
	x1=p1.first, x2=p2.first, y1=p1.second, y2=p2.second;
	double A, B, a, b, c;
	if(x1 == x2 && y1 == y2)
	{
		R.first = false;
		return R;
	} else if(x1 != x2 && y1 == y2) {
		p3.first = (x1*x1-x2*x2-l1*l1+l2*l2)/(2*(x1-x2));
		if( l1*l1 - (x1-p3.first)*(x1-p3.first) <= 0 ){
			R.first = false;
			return R;
		} else {
			R.first = true;
			p3.first = y1 - sqrt(l1*l1 - (x1-p3.first)*(x1-p3.first));
			R.second = p3;
			return R;
		}
	} else if(x1 == x2 && y1 != y2) {
		p3.second = (y1*y1-y2*y2-l1*l1+l2*l2)/(2*(y1-y2));
		if( l1*l1-(y1-p3.second)*(y1-p3.second) <= 0 ){
			R.first = false;
			return R;
		} else {
			R.first = true;
			p3.first = x1 - sqrt(l1*l1-(y1-p3.second)*(y1-p3.second));
			R.second = p3;
			return R;
		}
	} else {
		A = (x1-x2)/(y2-y1);
		B = (x1*x1-x2*x2+y1*y1-y2*y2-l1*l1+l2*l2)/(2*(y1-y2));
		a = 1+A*A;
		b = -2*x1-2*y1*A+2*A*B;
		c = x1*x1+y1*y1+B*B-2*y1*B-l1*l1;
		if(b*b-4*a*c <= 0){
			R.first = false;
			return R;
		} else {
			R.first = true;
			p3.first = (-b-sqrt(b*b-4*a*c))/(2*a);
			p3.second = A*p3.first+B;
			R.second = p3;
			return R;
		}
	}
}

bool GetFunc::isOpposite(pair<double,double> s1, pair<double,double> s2, pair<double,double> p1, pair<double,double> p2)
{
	if(s1.first != s2.first && s1.second != s2.second){
		return ((s2.second-s1.second)*(p1.first-s1.first)/(s2.first-s1.first)+s1.second-p1.second)*((s2.second-s1.second)*(p2.first-s1.first)/(s2.first-s1.first)+s1.second-p2.second)<0;
	} else if(s1.first == s2.first){
		return (s1.first-p1.first)*(s1.first-p2.first)<0;
	} else if(s1.second == s2.second){
		return (s1.second-p1.second)*(s1.second-p2.second)<0;
	}
	return false;
}

double f_distance(pair<double,double> a, pair<double,double> b)
{
	return sqrt( (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second) );
}