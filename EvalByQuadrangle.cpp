#include<vector>
#include"EvalByQuadrangle.h"
using namespace std;


double EvalByQuadrangle::get_eval(pair<double,double>*func, pair<double,double>*def_func, int _size)
{
	double eval=0;
	int mxX=0, mxY=0, mnX=0, mnY=0;
	int XY=0, Xy=0, xY=0, xy=0;
	int fmxX=0, fmxY=0, fmnX=0, fmnY=0;
	int fXY=0, fXy=0, fxY=0, fxy=0;
	double delta;
	double midX;
	double a[8], b[8];
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
	
	midX = (func[mxX].first+func[mxY].first)/2;
	delta = 2147483647;
	for(int i = min(mxX, mxY); i < max(mxX, mxY); i++)
	{
		if(delta > abs(midX-func[i].first)){
			delta = abs(midX-func[i].first);
			XY = i;
		}
	}
	midX = (func[mnX].first+func[mxY].first)/2;
	delta = 2147483647;
	for(int i = min(mnX, mxY); i < max(mnX, mxY); i++)
	{
		if(delta > abs(midX-func[i].first)){
			delta = abs(midX-func[i].first);
			xY = i;
		}
	}
	midX = (func[mxX].first+func[mnY].first)/2;
	delta = 2147483647;
	for(int i = min(mxX, mnY); i < max(mxX, mnY); i++)
	{
		if(delta > abs(midX-func[i].first)){
			delta = abs(midX-func[i].first);
			Xy = i;
		}
	}
	midX = (func[mnX].first+func[mnY].first)/2;
	delta = 2147483647;
	for(int i = min(mnX, mnY); i < max(mnX, mnY); i++)
	{
		if(delta > abs(midX-func[i].first)){
			delta = abs(midX-func[i].first);
			xy = i;
		}
	}
	midX = (func[fmxX].first+func[fmxY].first)/2;
	delta = 2147483647;
	for(int i = min(fmxX, fmxY); i < max(fmxX, fmxY); i++)
	{
		if(delta > abs(midX-func[i].first)){
			delta = abs(midX-func[i].first);
			fXY = i;
		}
	}
	midX = (func[fmnX].first+func[fmxY].first)/2;
	delta = 2147483647;
	for(int i = min(fmnX, fmxY); i < max(fmnX, fmxY); i++)
	{
		if(delta > abs(midX-func[i].first)){
			delta = abs(midX-func[i].first);
			fxY = i;
		}
	}
	midX = (func[fmxX].first+func[fmnY].first)/2;
	delta = 2147483647;
	for(int i = min(fmxX, fmnY); i < max(fmxX, fmnY); i++)
	{
		if(delta > abs(midX-func[i].first)){
			delta = abs(midX-func[i].first);
			fXy = i;
		}
	}
	midX = (func[fmnX].first+func[fmnY].first)/2;
	delta = 2147483647;
	for(int i = min(fmnX, fmnY); i < max(fmnX, fmnY); i++)
	{
		if(delta > abs(midX-func[i].first)){
			delta = abs(midX-func[i].first);
			fxy = i;
		}
	}
	
	a[0] = EvalByQuadrangle::getDist(func[mxX], func[XY]);
	a[1] = EvalByQuadrangle::getDist(func[XY], func[mxY]);
	a[2] = EvalByQuadrangle::getDist(func[mxY], func[xY]);
	a[3] = EvalByQuadrangle::getDist(func[xY], func[mnX]);
	a[4] = EvalByQuadrangle::getDist(func[mnX], func[xy]);
	a[5] = EvalByQuadrangle::getDist(func[xy], func[mnY]);
	a[6] = EvalByQuadrangle::getDist(func[mnY], func[Xy]);
	a[7] = EvalByQuadrangle::getDist(func[Xy], func[mxX]);
	
	b[0] = EvalByQuadrangle::getDist(def_func[fmxX], def_func[fXY]);
	b[1] = EvalByQuadrangle::getDist(def_func[fXY], def_func[fmxY]);
	b[2] = EvalByQuadrangle::getDist(def_func[fmxY], def_func[fxY]);
	b[3] = EvalByQuadrangle::getDist(def_func[fxY], def_func[fmnX]);
	b[4] = EvalByQuadrangle::getDist(def_func[fmnX], def_func[fxy]);
	b[5] = EvalByQuadrangle::getDist(def_func[fxy], def_func[fmnY]);
	b[6] = EvalByQuadrangle::getDist(def_func[fmnY], def_func[fXy]);
	b[7] = EvalByQuadrangle::getDist(def_func[fXy], def_func[fmxX]);

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( i!=j ) eval += max( a[i]*b[j]/a[j]/b[i], a[j]*b[i]/a[i]/b[j] );
		}
	}
	
	return eval;
}

double EvalByQuadrangle::getDist(pair<double,double> a, pair<double,double> b)
{
	return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}