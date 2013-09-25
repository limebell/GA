#include<vector>
using namespace std;

#ifndef __GETFUNC_H__
#define __GETFUNC_H__

class GetFunc
{

private:
	double f_distance(pair<double,double> a, pair<double,double> b);

public:
	bool get_func(int *size, pair<double,double> *func, int num);
	pair<bool, pair<double,double>> getPoint1(pair<double,double> p1, pair<double,double> p2, int l1, int l2);
	pair<bool, pair<double,double>> getPoint2(pair<double,double> p1, pair<double,double> p2, int l1, int l2);
	bool isOpposite(pair<double,double> s1, pair<double,double> s2, pair<double,double> p1, pair<double,double> p2);

};

#endif