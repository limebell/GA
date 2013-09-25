#include<stdio.h>
#include<vector>
#include<malloc.h>
#include<algorithm>
#include"GACore.h"
#include"EvalByQuadrangle.h"
#include"GetFunc.h"
using namespace std;

/*
목표함수의 입력은 input.txt 파일에 적되 다음의 형식으로 적는다.
목표함수의 점들의 개수를 먼저 입력하고, 다음줄부터 각 점의 좌표가 줄바꿈으로 구분되어 입력된다.
단 각 점의 x, y 좌표는 공백으로 구분한다.
*/

#define LEG_SIZE 10
#define NUM_LEGS 13
#define NUM_PER_GENERATION 1000
#define MAX_GENERATION 100

int qsortByEval(double* eval, int** len, int left, int right);
	
int main()
{
	GetFunc function;
	GACore CoreFunction;
	EvalByQuadrangle Evaluate;
	int NumFuncPoints;
	pair<double,double>*def_func;
	pair<double,double>*func;
	int **len;
	double *evals;
	
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	scanf("%d\n",&NumFuncPoints);
	def_func = (pair<double,double>*)malloc(NumFuncPoints*sizeof(pair<double,double>));
	func = (pair<double,double>*)malloc(NumFuncPoints*sizeof(pair<double,double>));
	evals = (double*)malloc(NUM_PER_GENERATION*sizeof(double));
	
	for(int i=0;i<NumFuncPoints;i++) scanf("%f %f\n",&def_func[i].first,&def_func[i].second);
	
	len = (int**)malloc(NUM_PER_GENERATION*sizeof(int*));
	for(int i = 0; i < NUM_PER_GENERATION;i++)
	{
		*(len+i) = (int*)malloc(NUM_LEGS*sizeof(int));
	}
	
	/*for(int i=0;i<NUM_LEGS;i++)
	{
		len[i] = (double*)malloc(LEG_SIZE*sizeof(char));
	}*/

	for(int i=1;i<=MAX_GENERATION;i++)
	{
		CoreFunction.generate(i,len,LEG_SIZE,NUM_PER_GENERATION,NUM_LEGS);
		printf("\n%d번째 세대\n",i);
		for(int j=0;j<NUM_PER_GENERATION;j++)
		{
			//printf("%d ",j);
			if(function.get_func(len[j],func,140))
			{
				evals[j] = int(Evaluate.get_eval(func,def_func, 140)*100000);
			} else {
				evals[j] = 2147483647;
			}
		}
		qsortByEval(evals, len, 0, NUM_PER_GENERATION-1);
		for(int j=0;j<20;j++)
		{
			printf("%d : ",j+1);
			for(int k=0;k<NUM_LEGS;k++)
			{
				printf("%d, ",len[j][k]);
			}
			printf("\n");
		}
	}
	for(int i=0;i<NUM_PER_GENERATION;i++)
	{
		for(int j=0;j<NUM_LEGS;j++)
		{
			printf("%d, ", len[i][j]);
		}
		printf("\n-----------------------------------------------\n");
	}
}

int qsortByEval(double* eval, int** len, int left, int right){
	int pivot = left, nleft = left, nright = right;
	double temp;
	int *ttemp;
	if(nleft >= nright) return 0;
	while(1){
		while(1){
			if(eval[left] > eval[pivot]) break;
			if(left > right) break;
			left++;
		}
		while(1){
			if(eval[right] < eval[pivot]) break;
			if(right < left) break;
			right--;
		}
		if(left > right){
			temp = eval[right];
			eval[right] = eval[pivot];
			eval[pivot] = temp;
			ttemp = len[right];
			len[right] = len[pivot];
			len[pivot] = ttemp;
			break;
		}
		temp = eval[left];
		eval[left] = eval[right];
		eval[right] = temp;
		ttemp = len[left];
		len[left] = len[right];
		len[right] = ttemp;
	}
	return qsortByEval(eval, len, nleft, right-1) + qsortByEval(eval, len, left, nright);
}