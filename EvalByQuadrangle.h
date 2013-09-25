#include<vector>
using namespace std;

/*
This header includes function get_eval(*func,*def_func) that returns eval.
Get eval by three point of triangle, and middle point of each point.
*/


#ifndef __EVAL_H__
#define __EVAL_H__

class EvalByQuadrangle
{
public:
	double get_eval(pair<double,double>*func, pair<double,double>*def_func, int _size);
	double getDist(pair<double,double> a,pair<double,double> b);
};

#endif