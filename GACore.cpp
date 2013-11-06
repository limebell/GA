#include <stack>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include"GACore.h"
using namespace std;

#define FIXED_VALUE 128;

/*
�ʱ�ȭ -> �������� ����
�����˰��򿡼� �ʿ��Ѱ�? -> ����, ����, ��������
*/
int GACore::smaller(int x,int y){return x<y?x:y;}
void GACore::generate(int regenerate,int**vals,int size,int num,int numLeg)
{
	srand((unsigned)time(NULL));
	int i,j,numleg=numLeg;
	if(regenerate==0){
		printf("restart!");
		for(i=0;i<num;i++){
			for(j=0;j<numleg-1;j++){
				vals[i][j]=rand()%2048;
			}
			vals[i][numleg-1] = FIXED_VALUE;
		}
		/*vals[0][0] = 324;
		vals[0][1] = 354;
		vals[0][2] = 335;
		vals[0][3] = 342;
		vals[0][4] = 476;
		vals[0][5] = 336;
		vals[0][6] = 313;
		vals[0][7] = 561;
		vals[0][8] = 418;
		vals[0][9] = 427;
		vals[0][10] = 528;
		vals[0][11] = 67;
		vals[0][12] = 128;*/
	}
	else{
		for(i=num-1;i>49;i--){
			for(j=0;j<numleg-1;j++){
				vals[i][j]=0;
			}
			vals[i][numleg-1] = FIXED_VALUE;
		}
		
		//GACore::crossover(vals, size, numLeg);
		//GACore::mutation(vals, size, numLeg);
		
		for(i=50;i<num;i++){
			for(j=0;j<numleg-1;j++){
				vals[i][j] = vals[i % 50][j] * (0.7+double(rand() % 600)/1000);
			}
		}
	}
}

void GACore::crossover(int**vals,int size,int numLeg)
{
	int small,maxsize=0,cut,i,j=0,k=0,p1,p2=0,temp[30000],t;
	stack<int> chosen;
	int save[50];
	for(i=0;i<50;i++){
		save[i]=rand()%100;
		if(save[i]<25){
			chosen.push(i);
			j++;
		}
	}
	if(j%2==0){
		while(!chosen.empty()){
			p1=chosen.top();
			chosen.pop();
			p2=chosen.top();
			chosen.pop();
			for(k=0;k<numLeg-1;k++)
			{
				small=smaller(vals[p1][k],vals[p2][k]);
				for(t=1; small<t; t*=2, maxsize++);
				cut=rand()%(maxsize+1);                        //�� ������� 0101010101�� �������
				temp[k]=vals[p1][k]%(int)pow(2.0,cut);
				vals[p1][k]=vals[p1][k]-(vals[p1][k]%(int)pow(2.0,cut))+(vals[p2][k]%(int)pow(2.0,cut));
				vals[p2][k]=vals[p2][k]-(vals[p2][k]%(int)pow(2.0,cut))+temp[k];
			}
		}
	}
	else{
		for(i=0;i<j-1;i++){
			if(!chosen.empty()){
				p1=chosen.top();
				chosen.pop();
			}
			if(!chosen.empty()){
				p2=chosen.top();
				chosen.pop();
			}
			for(k=0;k<numLeg-1;k++)
			{
				small=smaller(vals[p1][k],vals[p2][k]);
				for(t = 1; small<t; t*=2, maxsize++);
				cut=rand()%(maxsize+1);                        //�� ������� 0101010101�� �������
				temp[k]=vals[p1][k]%(int)pow(2.0,cut);
				vals[p1][k]=vals[p1][k]-(vals[p1][k]%(int)pow(2.0,cut))+(vals[p2][k]%(int)pow(2.0,cut));
				vals[p2][k]=vals[p2][k]-(vals[p2][k]%(int)pow(2.0,cut))+temp[k];
			}
		}
		if(!chosen.empty()){
			p1=chosen.top();
			chosen.pop();
		}
		if(p2!=0){
			for(k=0;k<numLeg-1;k++)
			{
				small=smaller(vals[p1][k],vals[p2][k]);
				for(t = 1; small<t; t*=2, maxsize++);
				cut=rand()%(maxsize+1);                        //�� ������� 0101010101�� �������
				temp[k]=vals[p1][k]%(int)pow(2.0,cut);
				vals[p1][k]=vals[p1][k]-(vals[p1][k]%(int)pow(2.0,cut))+(vals[p2][k]%(int)pow(2.0,cut));
				vals[p2][k]=vals[p2][k]-(vals[p2][k]%(int)pow(2.0,cut))+temp[k];
			}
		}
	}
}

void GACore::mutation(int**vals,int size,int numLeg)
{
	int i,j,k,temp1,temp2=0,maxsize=0;
	for(i=0;i<20;i++){
		for(j=0;j<numLeg-1;j++){
			for (k = 1; k < size; k=k * 2){
				maxsize++;
			}
			for(k=0;k<maxsize;k++){
				temp1=rand()%100;
				if (temp1<k*k / sqrt(k)){
					temp2 = (vals[i][j] / (int)pow(2.0, maxsize - k - 1)) % 2;
					if (temp2 == 0)
						vals[i][j] = vals[i][j] + (int)pow(2.0, maxsize - k);
					if (temp2 == 1)
						vals[i][j] = vals[i][j] - (int)pow(2.0, maxsize - k);
				}
			}
		}
	}
}