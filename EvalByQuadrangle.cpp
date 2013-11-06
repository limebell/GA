#include<vector>
#include<stack>
#include"EvalByQuadrangle.h"
using namespace std;


double EvalByQuadrangle::get_eval(pair<double,double>*func, pair<double,double>*def_func, int _size)
{
	double eval=0;
	
	int i;

	int mxX=0, mxY=0, mnX=0, mnY=0;
	int XY=0, Xy=0, xY=0, xy=0;

	int fmxX=0, fmxY=0, fmnX=0, fmnY=0;
	int fXY=0, fXy=0, fxY=0, fxy=0;
	
	stack<pair<int, int>> order;
	stack<pair<int, int>> forder;
	
	pair<int, int> tObject;
	pair<int, int> aaa, bbb;
	
	double diff, midX;
	double a[10], b[10];

	double areaA=0, areaB=0;
	stack<pair<double, double>> pointsA;
	stack<pair<double, double>> pointsB;
	
	for(i=0;i<_size;i++)
	{
		if(func[i].first>func[mxX].first) mxX = i;
		if(func[i].second>func[mxY].second) mxY = i;
		if(func[i].first<func[mnX].first) mnX = i;
		if(func[i].second<func[mnY].second) mnY = i;
		
		if(def_func[i].first>def_func[fmxX].first) fmxX = i;
		if(def_func[i].second>def_func[fmxY].second) fmxY = i;
		if(def_func[i].first<def_func[fmnX].first) fmnX = i;
		if(def_func[i].second<def_func[fmnY].second) fmnY = i;
	}
	
	//mxX : 1, mnX : 2, mxY : 3, mnY : 4;

	for(i=_size-1;i>=0;i--)
	{
		if(i == mxX){
			pair<int, int> o;
			o.first = i;
			o.second = 1;
			order.push(o);
		}
		if(i == mxY){
			pair<int, int> o;
			o.first = i;
			o.second = 3;
			order.push(o);
		}
		if(i == mnX){
			pair<int, int> o;
			o.first = i;
			o.second = 2;
			order.push(o);
		}
		if(i == mnY){
			pair<int, int> o;
			o.first = i;
			o.second = 4;
			order.push(o);
		}
		
		if(i == fmxX){
			pair<int, int> o;
			o.first = i;
			o.second = 1;
			forder.push(o);
		}
		if(i == fmxY){
			pair<int, int> o;
			o.first = i;
			o.second = 3;
			forder.push(o);
		}
		if(i == fmnX){
			pair<int, int> o;
			o.first = i;
			o.second = 2;
			forder.push(o);
		}
		if(i == fmnY){
			pair<int, int> o;
			o.first = i;
			o.second = 4;
			forder.push(o);
		}
	}
	
	
	bbb = order.top();
	order.pop();
	tObject = aaa = bbb;
	bbb = order.top();
	order.pop();
	midX = (func[aaa.first].first+func[bbb.first].first)/2;
	diff = 2147483647;
	i = aaa.first;
	while(true)
	{
		i++;
		if(diff >= abs(midX-func[i%_size].first)){
			diff = abs(midX-func[i%_size].first);
			if(aaa.second==1){
				if(bbb.second==3) XY = i%_size;
				if(bbb.second==4) Xy = i%_size;
			}
			if(aaa.second==2){
				if(bbb.second==3) xY = i%_size;
				if(bbb.second==4) xy = i%_size;
			}
			if(aaa.second==3){
				if(bbb.second==1) XY = i%_size;
				if(bbb.second==2) xY = i%_size;
			}
			if(aaa.second==4){
				if(bbb.second==1) Xy = i%_size;
				if(bbb.second==2) xy = i%_size;
			}
		}
		if( (aaa.first>bbb.first&&i>=bbb.first+_size) || (aaa.first<=bbb.first&&i>=bbb.first) ){
			if(order.empty()){
				if(tObject.first == -2) break;
				else{
					order.push(tObject);
					tObject.first = -2;
				}
			}
			aaa = bbb;
			bbb = order.top();
			order.pop();
			midX = (func[aaa.first].first+func[bbb.first].first)/2;
			diff = 2147483647;
			i = aaa.first;
		}
	}
	
	bbb = forder.top();
	forder.pop();
	tObject = aaa = bbb;
	bbb = forder.top();
	forder.pop();
	midX = (def_func[aaa.first].first+def_func[bbb.first].first)/2;
	diff = 2147483647;
	i = aaa.first;
	while(true)
	{
		i++;
		if(diff >= abs(midX-def_func[i%_size].first)){
			diff = abs(midX-def_func[i%_size].first);
			if(aaa.second==1){
				if(bbb.second==3) fXY = i%_size;
				if(bbb.second==4) fXy = i%_size;
			}
			if(aaa.second==2){
				if(bbb.second==3) fxY = i%_size;
				if(bbb.second==4) fxy = i%_size;
			}
			if(aaa.second==3){
				if(bbb.second==1) fXY = i%_size;
				if(bbb.second==2) fxY = i%_size;
			}
			if(aaa.second==4){
				if(bbb.second==1) fXy = i%_size;
				if(bbb.second==2) fxy = i%_size;
			}
		}
		if( (aaa.first>bbb.first&&i>=bbb.first+_size) || (aaa.first<=bbb.first&&i>=bbb.first) ){
			if(forder.empty()){
				if(tObject.first == -2) break;
				else{
					forder.push(tObject);
					tObject.first = -2;
				}
			}
			aaa = bbb;
			bbb = forder.top();
			forder.pop();
			midX = (def_func[aaa.first].first+def_func[bbb.first].first)/2;
			diff = 2147483647;
			i = aaa.first;
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

	pointsA.push( func[mxX] );
	pointsA.push( func[XY] );
	pointsA.push( func[mxY] );
	pointsA.push( func[xY] );
	pointsA.push( func[mnX] );
	pointsA.push( func[xy] );
	pointsA.push( func[mnY] );
	pointsA.push( func[Xy] );
	pointsA.push( func[mxX] );

	pointsB.push( def_func[fmxX] );
	pointsB.push( def_func[fXY] );
	pointsB.push( def_func[fmxY] );
	pointsB.push( def_func[fxY] );
	pointsB.push( def_func[fmnX] );
	pointsB.push( def_func[fxy] );
	pointsB.push( def_func[fmnY] );
	pointsB.push( def_func[fXy] );
	pointsB.push( def_func[fmxX] );

	areaA = getArea(pointsA);
	areaB = getArea(pointsB);

	if(areaA==0||areaB==0) eval = 1000000000;
	else for(i=0;i<8;i++) eval += abs(a[i]*sqrt(areaB/areaA)-b[i]);
	return eval;
}

double EvalByQuadrangle::getDist(pair<double,double> a, pair<double,double> b)
{
	return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}

double EvalByQuadrangle::getArea(stack<pair<double, double>>points)
{
	double area = 0;
	pair<double, double> a, b;
	b = points.top();
	points.pop();
	while (points.size()>0){
		a = b;
		b = points.top();
		points.pop();
		area = area + a.first*b.second - b.first*a.second;
	}
	return abs(area) / 2;
}