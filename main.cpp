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
#define NUM_PER_GENERATION 2000
#define MAX_GENERATION 300
#define OPTIMUM_RADIUS 50
#define MAX_REPEAT 7

int qsortByEval(double* eval, int** len, int left, int right);
	
int main()
{
	GetFunc function;
	GACore CoreFunction;
	EvalByQuadrangle Evaluate;
	int NumFuncPoints;
	pair<double, double>*def_func;
	pair<double, double>*func;
	int **len;
	double *evals;

	int **optimalLen;
	bool flag;
	int index = 0;
	int count = MAX_REPEAT;
	double localMinimum[5] = { -1, };
	
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	scanf("%d\n", &NumFuncPoints);
	def_func = (pair<double, double>*)malloc(NumFuncPoints*sizeof(pair<double, double>));
	func = (pair<double, double>*)malloc(NumFuncPoints*sizeof(pair<double, double>));
	evals = (double*)malloc(NUM_PER_GENERATION*sizeof(double));

	for (int i = 0; i < NumFuncPoints; i++) scanf("%lf, %lf\n", &def_func[i].first, &def_func[i].second);
	
	len = (int**)malloc(NUM_PER_GENERATION*sizeof(int*));
	for (int i = 0; i < NUM_PER_GENERATION; i++)
	{
		*(len + i) = (int*)malloc(NUM_LEGS*sizeof(int));
	}

	optimalLen = (int**)malloc(MAX_GENERATION*sizeof(int*));
	for (int i = 0; i < MAX_GENERATION; i++)
	{
		*(optimalLen + i) = (int*)malloc(NUM_LEGS*sizeof(int));
	}

	evals[0] = OPTIMUM_RADIUS + 1;
	for (int i = 0; i < MAX_GENERATION; i++)
	{
		//최적화조건
		if (evals[0] < OPTIMUM_RADIUS){
			for (int j = 0; j < NUM_LEGS; j++){
				optimalLen[index][j] = len[0][j];
			}
			index++;
			break;
		}
		
		//유전 알고리즘
		CoreFunction.generate(count - MAX_REPEAT, len, LEG_SIZE, NUM_PER_GENERATION, NUM_LEGS);
		printf("%d번째 세대\n", i+1);
		for (int j = 0; j < NUM_PER_GENERATION; j++)
		{
			if (function.get_func(len[j], func, 140))
			{
				evals[j] = Evaluate.get_eval(func, def_func, 140);
			}
			else {
				evals[j] = 1000000000;
			}
			//printf("%lf\n",evals[j]);
		}
		qsortByEval(evals, len, 0, NUM_PER_GENERATION - 1);

		//극소탈출부분
		if (count == MAX_REPEAT){
			count = 0;
		}
		flag = true;
		for (int j = 0; j < 5; j++){
			if (evals[j] != localMinimum[j]) flag = false;
		}
		if (flag) count += 1;
		else{
			for (int j = 0; j < 5; j++) localMinimum[j] = evals[j];
			count = 0;
		}
		if (count == MAX_REPEAT){
			for (int j = 0; j < NUM_LEGS; j++){
				optimalLen[index][j] = len[0][j];
			}
			index += 1;
		}

		//출력부분
		for(int j=0;j<20;j++)
		{
			printf("%d : ",j+1);
			for(int k=0;k<NUM_LEGS;k++)
			{
				printf("%d, ",len[j][k]);
			}
			printf("EVAL : %lf\n",evals[j]);
		}
	}

	for (int j = 0; j < NUM_LEGS; j++){
		optimalLen[index][j] = len[0][j];
	}
	index++;

	/*for(int i=0;i<NUM_PER_GENERATION;i++)
	{
		printf("LENGH : ");
		for(int j=0;j<NUM_LEGS;j++)
		{
			printf("%d, ", len[i][j]);
		}
		printf("EVAL : %lf\n", evals[i]);
	}*/

	for (int i = 0; i < index; i++) {
		printf("LENGH : ");
		for (int j = 0; j < NUM_LEGS; j++){
			printf("%d, ", optimalLen[i][j]);
		}
		function.get_func(optimalLen[i], func, 140);
		printf("EVAL : %lf\n", Evaluate.get_eval(func, def_func, 140));
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