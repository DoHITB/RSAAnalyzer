/*
 * RSAAnalyzer.h
 *
 *  Created on: 27 sep. 2020
 *      Author: DoHITB
 */
#ifndef ANALYZER_H_
#define ANALYZER_H_
void loadK(int* kt);
int getEnd(void* va);
void poss(int ind, int num, int* arr);
int getK(int* arr);
int getModulus(void* va);
int getZ(int* n, int num);
void getSqrt(void* num, int* arr, void* res, void* m);
void getPonderated(void* num, int a, void* b, int k, int z, void* n, void* res, void* m);
int isEqual(void* va, void* vb, void* n, void* m);
void regression(void* data, void* axis, void* dif, void* m);
void absolute(void* n, void* m);
void gsignum(void* a, void* b, void* res);
void gaussM(void* factor, void* equation, void* m);
void gaussS(void* equation1, void* equation2, void* m);
int getY(int* arr);
int getZF(int* arr);
int getS(int* arr);
void solve(void* dif, void* sols, int check, void* m);
void distance(void* base, int z, int y, int s, void* res, void* m);
void axisFactor(void* a, void* m);
int checkSolution(void* factor, int *ending, void* num, void* m, int *arrp);
char* printSolution(void* factor, int *ending, void* num, void* m, int *arrp);
int relativeFactor(int s, int* arr);
int relativeFactorResult(int s, void* sq, void* m);
void lowerLimit(void* dif, void* dist, void* m);
void hbBolzano(void* dif, void* dist, void* bist, void* m, void* baxis, void* bvalue);
static void cudaMode(void* dif, void* dist, int* arr, void* num, void* baxis, void* bvalue);

//temporal
void testing();

int memchk(int n, ...);

#endif /* ANALYZER_H_ */
