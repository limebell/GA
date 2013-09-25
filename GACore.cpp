#include <stack>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include"GACore.h"
using namespace std;

#define FIXED_VALUE 128;

/*
초기화 -> 랜덤으로 생성
유전알고리즘에서 필요한것? -> 교차, 교배, 돌연변이
*/
int GACore::smaller(int x,int y){return x<y?x:y;}
void GACore::generate(int generation,int**vals,int size,int num,int numLeg)
{
	srand((unsigned)time(NULL));
	int i,j,numleg=numLeg;
	if(generation==1){
		for(i=0;i<num;i++){
			for(j=0;j<numleg-1;j++){
				vals[i][j]=rand()%2048;
			}
			vals[i][numleg-1] = FIXED_VALUE;
		}
	}
	else{
		for(i=num-1;i>49;i--){
			for(j=0;j<numleg-1;j++){
				vals[i][j]=0;
			}
			vals[i][numleg-1] = FIXED_VALUE;
		}
		
		GACore::crossover(vals, size, numLeg);
		GACore::mutation(vals, size, numLeg);
		
		for(i=0;i<num;i++){
			for(j=0;j<numleg-1;j++){
				vals[i][j]=vals[i%50][j]*(0.95+0.1/num*i);
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
				for(t=1; (int)small/t==0; t*=2, maxsize++);
				cut=rand()%(maxsize+1);                        //이 사이즈는 0101010101의 사이즈다
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
				cut=rand()%(maxsize+1);                        //이 사이즈는 0101010101의 사이즈다
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
				cut=rand()%(maxsize+1);                        //이 사이즈는 0101010101의 사이즈다
				temp[k]=vals[p1][k]%(int)pow(2.0,cut);
				vals[p1][k]=vals[p1][k]-(vals[p1][k]%(int)pow(2.0,cut))+(vals[p2][k]%(int)pow(2.0,cut));
				vals[p2][k]=vals[p2][k]-(vals[p2][k]%(int)pow(2.0,cut))+temp[k];
			}
		}
	}
}

void GACore::mutation(int**vals,int size,int numLeg)
{
	/*int i,j,k,temp1,temp2=0;
	for(i=0;i<20;i++){
		for(j=0;j<numLeg-1;j++){
			for(k=0;k<size;k++){
				temp1=rand()%100;
				if(temp1<k*k/sqrt(k))
					temp2=(vals[i][j]/(int)pow(2.0,size-k-1))%2;
				if(temp2==0)
					vals[i][j]=vals[i][j]+(int)pow(2.0,size-k);
				if(temp2==1)
					vals[i][j]=vals[i][j]-(int)pow(2.0,size-k);
			}
		}
	}*/
}