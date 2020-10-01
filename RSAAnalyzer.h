/*
 * RSAAnalyzer.h
 *
 *  Created on: 25 ene. 2020
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
void getSqrt(void* num, int* arr, void* res);
void getPonderated(void* num, int a, void* b, int k, int z, void* n, void* res);
int isEqual(void* va, void* vb, void* n);
void regression(void* data, void* axis, void* dif);
void absolute(void* n);
void gsignum(void* a, void* b, void* res);
void gaussM(void* factor, void* equation);
void gaussS(void* equation1, void* equation2);
int getY(int* arr);
int getZF(int* arr);
void solve(void* dif, void* sols);

int memchk(int n, ...);

#endif /* ANALYZER_H_ */
