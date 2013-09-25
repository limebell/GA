#include<vector>
#include"EvalByQuadrangle.h"
using namespace std;


double EvalByQuadrangle::get_eval(pair<double,double>*func, pair<double,double>*def_func, int _size)
{
	double eval=0;
	int mxX=0, mxY=0, mnX=0, mnY=0;
	int fmxX=0, fmxY=0, fmnX=0, fmnY=0;
	double a[4], b[4];
	//int p1[7], p2[7];
	for(int i=0;i<_size;i++)
	{
		if(func[i].first>func[mxX].first) mxX = i;
		else if(func[i].second>func[mxY].second) mxY = i;
		else if(func[i].first<func[mnX].first) mnX = i;
		else if(func[i].second<func[mnY].second) mnY = i;

		if(def_func[i].first>def_func[fmxX].first) fmxX = i;
		else if(def_func[i].second>def_func[fmxY].second) fmxY = i;
		else if(def_func[i].first<def_func[fmnX].first) fmnX = i;
		else if(def_func[i].second<def_func[fmnY].second) fmnY = i;
	}
	
	a[0] = EvalByQuadrangle::getDist(func[mnX], func[mxY]);
	a[1] = EvalByQuadrangle::getDist(func[mxY], func[mxX]);
	a[2] = EvalByQuadrangle::getDist(func[mxX], func[mnY]);
	a[3] = EvalByQuadrangle::getDist(func[mnY], func[mnX]);

	b[0] = EvalByQuadrangle::getDist(def_func[fmnX], def_func[fmxY]);
	b[1] = EvalByQuadrangle::getDist(def_func[fmxY], def_func[fmxX]);
	b[2] = EvalByQuadrangle::getDist(def_func[fmxX], def_func[fmnY]);
	b[3] = EvalByQuadrangle::getDist(def_func[fmnY], def_func[fmnX]);

	for(int i=0;i<4;i++)
	{
		if(a[i]==0) a[i]++;
		if(b[i]==0) b[i]++;
	}

	for(int i=1;i<4;i++)
	{
		eval += abs(a[i]/a[0]-b[i]/b[0]);
	}

	return eval;
}

double EvalByQuadrangle::getDist(pair<double,double> a, pair<double,double> b)
{
	return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}