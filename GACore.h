#include<malloc.h>
#include<stdlib.h>
#include<time.h>

#ifndef __GACORE_H__
#define __GACORE_H__


//genetic algorthm

class  GACore
{
	
public:
	int smaller(int x,int y);
	void generate(int generation, int**vals,int size,int num,int numLeg);
	void crossover(int**vals,int size,int numLeg);
	void mating();
	void mutation(int**vals,int size,int numLeg);

};

#endif