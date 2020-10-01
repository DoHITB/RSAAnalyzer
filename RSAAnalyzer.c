/*
 * RSA.c
 *
 *  Created on: 27 sep. 2020
 *      Author: DoHITB
 */
#include "conio.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "BigInteger.h"
#include "RSAAnalyzer.h"
#include "Logging.h"
#include "stdarg.h"


 /* if num ends on...
  *            0, 1, 2, 3, 4, 5, 6, 7, 8, 9*/
int n1[10] = { 0, 1, 0, 1, 0, 0, 0, 1, 0, 1 };
int n2[10] = { 0, 1, 0, 3, 0, 0, 0, 7, 0, 9 };

int n3[10] = { 0, 3, 0, 7, 0, 0, 0, 3, 0, 3 };
int n4[10] = { 0, 7, 0, 9, 0, 0, 0, 9, 0, 3 };

int n5[10] = { 0, 9, 0, 0, 0, 0, 0, 0, 0, 7 };
int n6[10] = { 0, 9, 0, 0, 0, 0, 0, 0, 0, 7 };
int kt[100];

int INFORMATIONAL = 0;
int SEVERE = 1;
int ERROR = 2;
int MAX = 3;

int main(int argc, char* argv[]) {
  char number[4097];
  struct BigInteger* num = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* n = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sqrtAprox1 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sqrtAprox2 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sqrtAprox3 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sq1 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sq2 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sq3 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* chk = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* res = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* ant = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* ten = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* zro = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  int* arr1 = (int*)malloc(sizeof(int) * 2);
  int* arr2 = (int*)malloc(sizeof(int) * 2);
  int* arr3 = (int*)malloc(sizeof(int) * 2);
  int* eq = (int*)malloc(sizeof(int));
  struct BigInteger* tempVal = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 3);
  struct BigInteger* data = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 3);
  struct BigInteger* axis = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 3);
  struct BigInteger* dif = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 3);
  int k1;
  int k2;
  int k3;
  int z1;
  int z2;
  int z3;
  int mod;
  int end;
  int done = 0;
  int count;

  //data
  char* pool;
  int plen;
  int pi;
  int px;

  FILE* fl;
  FILE* fl2;
  int efl;

  //tracing aux vars
  char* st1;
  char* st2;
  char* st3;
  int possi;

  //logging
  char* name;

  //Gather & calculate
  struct BigInteger* sqrtAprox = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sq = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  int* arr = (int*)malloc(sizeof(int) * 2);
  int k;
  int z;
  int s;
  int op;
  int y;
  int zf;

  //equation solving
  struct BigInteger* sols = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 2);

  //debug
  int debug = 0;

  //TODO => memchk

  iniStr(&st1);
  iniStr(&st2);
  iniStr(&st3);

  //inis
  BImemcpy(ten, 10);
  BImemcpy(zro, 0);

  //start tracing
  if (argc == 1) {
    activateLog(INFORMATIONAL);
  }
  else {
    name = (char*)malloc(sizeof(char) * 5000);

    //num_arr_s.dat
    snprintf(name, 5000, "%s_%s_%s.log", argv[1], argv[2], argv[3]);
    setFile(name);
    activateLog(INFORMATIONAL);
  }

  //get number
  if (argc == 1) {
    printf("Number to analyse: ");
    gets_s(number, 4096);
  }
  else {
    strcpy_s(number, 4096, argv[1]);
  }

  _log("number: %s", INFORMATIONAL, number);

  //convert it to BigInteger
  newBI(num, number, 0);

  //load K-Table
  loadK(kt);

  //get ending of the number
  end = getEnd(num);

  toString(num, st1);

  _log("Searching for: %s", INFORMATIONAL, st1);
  _log("Initial data: ", INFORMATIONAL);

  inFunction();
  _log("getEnd: %i", INFORMATIONAL, end);

  //get possible multiplies
  poss(1, end, arr1);
  poss(2, end, arr2);
  poss(3, end, arr3);

  _log("arr Values: ", INFORMATIONAL);

  inFunction();
  _log("arr1: <%i, %i>", INFORMATIONAL, arr1[0], arr1[1]);
  _log("arr2: <%i, %i>", INFORMATIONAL, arr2[0], arr2[1]);
  _log("arr3: <%i, %i>", INFORMATIONAL, arr3[0], arr3[1]);
  outFunction();

  //get associated k's
  k1 = getK(arr1);
  k2 = getK(arr2);
  k3 = getK(arr3);

  _log("k Values: ", INFORMATIONAL);

  inFunction();
  _log("k1: %i", INFORMATIONAL, k1);
  _log("k2: %i", INFORMATIONAL, k2);
  _log("k3: %i", INFORMATIONAL, k3);
  outFunction();

  //get z's
  mod = getModulus(num);

  _log("mod: %i", INFORMATIONAL, mod);

  z1 = getZ(arr1, mod);
  z2 = getZ(arr2, mod);
  z3 = getZ(arr3, mod);

  _log("z Values: ", INFORMATIONAL);

  inFunction();
  _log("z1: %i", INFORMATIONAL, z1);
  _log("z2: %i", INFORMATIONAL, z2);
  _log("z3: %i", INFORMATIONAL, z3);
  outFunction();

  getSqrt(num, arr1, sqrtAprox1);
  getSqrt(num, arr2, sqrtAprox2);
  getSqrt(num, arr3, sqrtAprox3);

  memcpy(sq1, sqrtAprox1, sizeof(struct BigInteger));
  memcpy(sq2, sqrtAprox2, sizeof(struct BigInteger));
  memcpy(sq3, sqrtAprox3, sizeof(struct BigInteger));

  toString(sq1, st1);
  toString(sq2, st2);
  toString(sq3, st3);

  _log("sqrt Values: ", INFORMATIONAL);

  inFunction();
  _log("sq1: %s", INFORMATIONAL, st1);
  _log("sq2: %s", INFORMATIONAL, st2);
  _log("sq3: %s", INFORMATIONAL, st3);
  outFunction();
  outFunction();

  //debug override
  if(debug == 1) {
    argc = 2;
  }

  if(argc == 1) {
    /*************************************
     *******POOL GENERATION SECTION*******
     *************************************/

    //only an argument ==> generate pool
    //0               1   2    3
    //RSAAnalyzer.exe num #arr #S
    _log("", INFORMATIONAL);
    _log("Base execution. Generating execution pool", INFORMATIONAL);
    inFunction();

    _log("Starting waitlist...", INFORMATIONAL);
    efl = fopen_s(&fl2, "waitlist.bat", "w+");

    if (efl < 0)
      exit(-103);

    fputs("start /B RSAWaitList", fl2);
    fflush(fl2);
    fclose(fl2);

    system("waitlist.bat");
    _log("RSAWaitlist.exe started!", INFORMATIONAL);

    /*
     * Params Table
     *
     * ----------------------------------------
     *| arr[0] |  arr[1]  |  Z  |   Y  |   S   |
     *|--------+----------+-----+------+-------|
     *|      1 |       1  |  1  |   1  |   1   |
     *|      1 |       3  |  3  |   3  |   3   |
     *|      1 |       7  |  7  |   7  |   7   |
     *|      1 |       9  |  9  |   9  |   9   |
     *|      3 |       3  |  3  |   3  |   1   |
     *|      3 |       7  |  9  |   7  |   9   |
     *|      3 |       9  |  3  |   9  |   3   |
     *|      7 |       7  |  7  |   7  |   1   |
     *|      7 |       9  |  7  |   9  |   7   |
     *|      9 |       9  |  9  |   9  |   1   |
     * ----------------------------------------
     */

    plen = num->count; //num
    plen += 1; // \0 char
    plen += 4; // _#_#
    plen += 50; //exe name + extra space

    pool = (char*)malloc(sizeof(char) * plen);
    efl = fopen_s(&fl, "main.bat", "w+");

    if (efl < 0)
      exit(-102);

    fputs("@echo off\n", fl);

    //num
    toString(num, st1);

    if (arr1[0] > 0) {
      //arr1 have data. Possible combinations:
      //{1, 1}, {1, 3}, {1, 7}, {1, 9} => S = arr1[1]
      for (pi = 0; pi < arr1[1]; pi++) {
        snprintf(pool, plen, "ConsoleApplication1.exe %s %i %i", st1, 1, pi);
        _log("Command: %s", INFORMATIONAL, pool);
        fputs("START /B ", fl);
        fputs(pool, fl);
        fputs("\n", fl);
      }
    }

    if (arr2[0] > 0) {
      //arr2 have data. Possilbe combinations:
      //{3, 7}, {7, 9}, {3, 9}, {3, 3}
      if (arr2[0] == 3)
        //3x
        if (arr2[1] == 3)
          //{3, 3} => S = 1
          px = 1;
        else if (arr2[1] == 7)
          //{3, 7} => S = 9
          px = 9;
        else
          //{3, 9} => S = 3
          px = 3;
      else
        //{7, 9} => S = 7
        px = 7;

      for (pi = 0; pi < px; pi++) {
        snprintf(pool, plen, "ConsoleApplication1.exe %s %i %i", st1, 2, pi);
        _log("Command: %s", INFORMATIONAL, pool);
        fputs("START /B ", fl);
        fputs(pool, fl);
        fputs("\n", fl);
      }
    }

    if (arr3[0] > 0) {
      //arr3 have data. Possible combinations:
      //{9, 9}, {7, 7} => S = 1
      snprintf(pool, plen, "ConsoleApplication1.exe %s %i %i", st1, 3, 0);
      _log("Command: %s", INFORMATIONAL, pool);
      fputs("START /B ", fl);
      fputs(pool, fl);
      fputs("\n", fl);
    }

    outFunction();

    fflush(fl);
    fclose(fl);

    _log("Execution pool generated (main.bat)", INFORMATIONAL);
    _log("Do not close this window. It will run on background and show the result on screen once done!", INFORMATIONAL);
    _log("Starting the pool right now", INFORMATIONAL);

    //start the pool
    system("main.bat");

    inFunction();
    _log("Pool successfully launched.", INFORMATIONAL);
  }else{
    /************************************
     *****GATHER & CALCULATE SECTION*****
     ************************************/

    //Gather and calculate
    //0               1   2    3
    //RSAAnalyzer.exe num #arr #S
    BImemcpy(n, -1);

    if(debug == 0) {
      _log("", INFORMATIONAL);
      _log("Index: %s, Serie: %s", INFORMATIONAL, argv[2], argv[3]);

      op = atoi(argv[2]);
      s = atoi(argv[3]);
    }else {
      op = 1;
      s = 0;
    }

    if (op == 1) {
      memcpy(arr, arr1, sizeof(int) * 2);
      k = k1;
      z = z1;
      memcpy(sqrtAprox, sqrtAprox1, sizeof(struct BigInteger));
      memcpy(sq, sq1, sizeof(struct BigInteger));
    }else if (op == 2) {
      memcpy(arr, arr2, sizeof(int) * 2);
      k = k2;
      z = z2;
      memcpy(sqrtAprox, sqrtAprox2, sizeof(struct BigInteger));
      memcpy(sq, sq2, sizeof(struct BigInteger));
    }else if (op == 3) {
      memcpy(arr, arr3, sizeof(int) * 2);
      k = k3;
      z = z3;
      memcpy(sqrtAprox, sqrtAprox3, sizeof(struct BigInteger));
      memcpy(sq, sq3, sizeof(struct BigInteger));
    }else {
      exit(-2);
    }

    y = getY(arr);
    zf = getZF(arr);

    _log("Selected data {%i}:", INFORMATIONAL, op);
    inFunction();
    _log("arr: <%i, %i>", INFORMATIONAL, arr[0], arr[1]);
    _log("k: %i", INFORMATIONAL, k);
    _log("z: %i", INFORMATIONAL, z);

    toString(sqrtAprox, st1);
    _log("sqrtAprox: %s", INFORMATIONAL, st1);
    _log("y: %i", INFORMATIONAL, y);
    _log("z factor: %i", INFORMATIONAL, zf);
    _log("s: %i", INFORMATIONAL, s);
    _log("", INFORMATIONAL);
    outFunction();

    _log("Gathering data...", INFORMATIONAL);

    getPonderated(num, arr[0], sqrtAprox, k, z, n, tempVal);

    //res = tempVal[0] * tempVal[1];
    memcpy(res, &tempVal[0], sizeof(struct BigInteger));
    mul(res, &tempVal[1]);

    //chk = res - num
    memcpy(chk, res, sizeof(struct BigInteger));
    sub(chk, num);

    //done = true;
    done = 1;
    count = 0;

    //n = tempVal[2]
    memcpy(n, &tempVal[2], sizeof(struct BigInteger));

    //data[count] = chk
    memcpy(&data[count], chk, sizeof(struct BigInteger));

    //aixs[count] = sqrtAprox1
    memcpy(&axis[count], sqrtAprox, sizeof(struct BigInteger));

    ++count;

    while (done == 1) {
      //ant = chk
      memcpy(ant, chk, sizeof(struct BigInteger));

      //sqrtAprox1 += 10;
      add(sqrtAprox, ten);

      getPonderated(num, arr[0], sqrtAprox, k, z, n, tempVal);

      //n = tempVal[2]
      memcpy(n, &tempVal[2], sizeof(struct BigInteger));

      //res = tempVal[0] * tempVal[1];
      memcpy(res, &tempVal[0], sizeof(struct BigInteger));
      mul(res, &tempVal[1]);

      //chk = res - num
      memcpy(chk, res, sizeof(struct BigInteger));
      sub(chk, num);

      //data[count] = chk
      memcpy(&data[count], chk, sizeof(struct BigInteger));

      //aixs[count] = sqrtAprox1
      memcpy(&axis[count], sqrtAprox, sizeof(struct BigInteger));

      ++count;

      equals(chk, zro, eq);

      if (*eq == 0) { //if(chk == 0)
        toString(&tempVal[0], st1);
        toString(&tempVal[1], st2);
        _log("DONE! <%s, %s>", INFORMATIONAL, st1, st2);

        done = 0;
      }

      if (count == 3) {
        _log("Data gathered", INFORMATIONAL);
        done = 0;
      }
    }

    _log("", INFORMATIONAL);
    _log("Gathered data: ", INFORMATIONAL);

    inFunction();

    for (possi = 0; possi < count; possi++) {
      toString(&data[possi], st1);
      toString(&axis[possi], st2);

      _log("Data[%i]: %s", INFORMATIONAL, possi, st1);
      _log("Axis[%i]: %s", INFORMATIONAL, possi, st2);

      _log("---------------------------------", INFORMATIONAL);
    }

    outFunction();

    regression(data, axis, dif);

    toString(&dif[0], st1);
    toString(&dif[1], st2);
    toString(&dif[2], st3);
    _log("dif: <%s, %s, %s>", INFORMATIONAL, st1, st2, st3);
    _log("Associated equation: %sx^2 + %sx + %s = 0", INFORMATIONAL, st1, st2, st3);

    inFunction();
    _log("Solving x...", INFORMATIONAL);

    solve(dif, sols);

    toString(&sols[0], st1);
    toString(&sols[1], st2);
    _log("Solutions: <%s, %s>", INFORMATIONAL, st1, st2);

    //isEqual
    /*
Distancia a	0
Distancia b	Z * 1000
Distancia c	(Y * 100) - 1000 - (1000 * Z - S)
    */

    outFunction();


    deactivateLog();
  }

  return 0;
}

void loadK(int* kt) {
    int i = 0;
    int kti[16] = { 11, 13, 17, 19, 31, 33, 37, 39, 71, 73, 77, 79, 91, 93, 97, 99 };
    int ktk[16] = { 1,  7,  3,  9,  3,  1,  9,  7,  7,  9,  1,  3,  9,  3,  7,  1 };

    for (; i < 16; i++)
        kt[kti[i]] = ktk[i];

    //avoid undefined if any funcion returns a 0 value
    kt[0] = 0;
}

int getEnd(void* va) {
    return ((struct BigInteger*)va)->n[0];
}

void poss(int ind, int num, int* arr) {
    if (ind == 1) {
        arr[0] = n1[num];
        arr[1] = n2[num];
    }else if (ind == 2) {
        arr[0] = n3[num];
        arr[1] = n4[num];
    }else if (ind == 3) {
        arr[0] = n5[num];
        arr[1] = n6[num];
    }else {
        arr[0] = 0;
        arr[1] = 0;
    }
}

int getK(int* arr) {
    return kt[(arr[0] * 10) + arr[1]];
}

int getModulus(void* va) {
    if (((struct BigInteger*)va)->count == 0)
        return ((struct BigInteger*)va)->n[0];

    return (((struct BigInteger*)va)->n[1] * 10) +
           (((struct BigInteger*)va)->n[0]);
}

int getZ(int* n, int num) {
    int i = 0;

    for (i = 0; i < 10; i++)
        if ((((10 * i) + n[0]) * n[1]) % 100 == num)
            return i;

    return 0;
}

void getSqrt(void* num, int* arr, void* res) {
    int gsEnd;
    struct BigInteger* ten = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    
    if (arr[1] == 0) {
        BImemcpy(res, 0);
        return;
    }

    //initialize values
    BImemcpy(ten, 10);

    //get sqrt
    memcpy(res, num, sizeof(struct BigInteger));
    nqrt(res, 2);

    //get the ending
    gsEnd = getEnd(res);

    //the ending is bigger? then skip to the next
    if (gsEnd > arr[1])
        add(res, ten); //res += 10;

    //override ending with specific number
    ((struct BigInteger*)res)->n[0] = arr[1];

    free(ten);
}

int getY(int* arr) {
  /*
   * Params Table
   *
   * ----------------------------------------
   *| arr[0] |  arr[1]  |  Z  |   Y  |   S   |
   *|--------+----------+-----+------+-------|
   *|      1 |       1  |  1  |   1  |   1   |
   *|      1 |       3  |  3  |   3  |   3   |
   *|      1 |       7  |  7  |   7  |   7   |
   *|      1 |       9  |  9  |   9  |   9   |
   *|      3 |       3  |  3  |   3  |   1   |
   *|      3 |       7  |  9  |   7  |   9   |
   *|      3 |       9  |  3  |   9  |   3   |
   *|      7 |       7  |  7  |   7  |   1   |
   *|      7 |       9  |  7  |   9  |   7   |
   *|      9 |       9  |  9  |   9  |   1   |
   * ----------------------------------------
   */
  return arr[1];
}

int getZF(int* arr) {
  /*
   * Params Table
   *
   * ----------------------------------------
   *| arr[0] |  arr[1]  |  Z  |   Y  |   S   |
   *|--------+----------+-----+------+-------|
   *|      1 |       1  |  1  |   1  |   1   |
   *|      1 |       3  |  3  |   3  |   3   |
   *|      1 |       7  |  7  |   7  |   7   |
   *|      1 |       9  |  9  |   9  |   9   |
   *|      3 |       3  |  3  |   3  |   1   |
   *|      3 |       7  |  9  |   7  |   9   |
   *|      3 |       9  |  3  |   9  |   3   |
   *|      7 |       7  |  7  |   7  |   1   |
   *|      7 |       9  |  7  |   9  |   7   |
   *|      9 |       9  |  9  |   9  |   1   |
   * ----------------------------------------
   */
  if (arr[0] == 1) {
    //1x => Z = arr[1]
    return arr[1];
  }

  if (arr[0] == arr[1]) {
    //xx => Z = x
    return arr[1];
  }

  if (arr[0] == 3) {
    //{3, 7}, {3, 9}
    if (arr[1] == 7) {
      //{3, 7}
      return 9;
    }else {
      return 3;
    }
  }else if (arr[1] == 7) {
    //{7, 9}
    return 7;
  }
}

void getPonderated(void* num, int ia, void* b, int k, int z, void* n, void* res) {
    int ipR;
    int ipR0;
    struct BigInteger* pN = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* min = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* one = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* ten = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* hun = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* a = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* pTR = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* pR0 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* pR = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* pNH = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* pRT = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* pA0 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* pA1 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* stk0 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* stk1 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* stk2 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    int* ires = (int*)malloc(sizeof(int));
    int mm;
    int mmi = 17;
    //int isEq;

    //temp
    char* st1;
    char* st2;

    iniStr(&st1);
    iniStr(&st2);

    mm = memchk(mmi, pN, min, one, ten, hun, a, pTR, pR0, pR, pNH, pRT, pA0, pA1, stk0, stk1, stk2, ires);

    if (mm < 0)
        exit(-101);

    //initialize data                                                               ////iniitalize data
    BImemcpy(min, -1);                                                              //min = -1;
    BImemcpy(one, 1);                                                               //one = 1;
    BImemcpy(ten, 10);                                                              //ten = 10;
    BImemcpy(hun, 100);                                                             //hun = 100;
    BImemcpy(a, 0);                                                                 //a = 0;
    BImemcpy(pR0, 0);                                                               //pR0 = 0;
    BImemcpy(pR, 0);                                                                //pR = 0;

    ipR = z;                                                                        //iPR = z;
    ipR0 = 10 - k;                                                                  //ipR0 = 10 - k;

    equals(n, min, ires);                                                           ////¿n = -1? => res

    if (*ires == 0) {                                                               //if(n == -1){
        memcpy(pN, num, sizeof(struct BigInteger));                                 //  pN = num;
        dvs(pN, b);                                                                 //  pN = pN / b;
        dvs(pN, hun);                                                               //  pN = pN / hun (100);
    }else {                                                                         //}else{
        memcpy(pN, n, sizeof(struct BigInteger));                                   //  pN = n;
    }                                                                               //}

    a->n[0] = ia;                                                                   //a = ia;
    pR0->n[0] = ipR0;                                                               //pR0 = ipR0;
    pR->n[0] = ipR;                                                                 //pR = ipR;

    memcpy(pTR, b, sizeof(struct BigInteger));                                      //pTR = b;
    sub(pTR, a);                                                                    //pTR = pTR - a;
    dvs(pTR, ten);                                                                  //pTR = pTR / ten (10);
    mul(pTR, pR0);                                                                  //pTR = pTR * pR0;

    add(pR, pTR);                                                                   //pR = pR + pTR;

    memcpy(pNH, pN, sizeof(struct BigInteger));                                     //pNH = pN;
    mul(pNH, hun);                                                                  //pNH = pNH * hun (100);

    memcpy(pRT, pR, sizeof(struct BigInteger));                                     //pRT = pR;
    mul(pRT, ten);                                                                  //pRT = pRT * ten (10);

    memcpy(pA0, a, sizeof(struct BigInteger));                                      //pA0 = a;
    add(pA0, pNH);                                                                  //pA0 = pA0 + pNH;
    add(pA0, pRT);                                                                  //pA0 = pA0 + pRT;

    memcpy(pA1, b, sizeof(struct BigInteger));                                      //pA1 = b;

/*VERSION 2*/
    //stk1 = ((((10 * pN--) + pR) * 10) + a)                                        //stk1 = ((((10 * pN--) + pR) * 10) + a)
    memcpy(stk1, pN, sizeof(struct BigInteger));                                    //  stk1 = pN;
    mul(stk1, ten);                                                                 //  stk1 = pA0 * ten (10);
    add(stk1, pR);                                                                  //  stk1 = pA0 * pR;
    mul(stk1, ten);                                                                 //  stk1 = pA0 * ten (10);
    add(stk1, a);                                                                   //  stk1 = pA0 + a;
    sub(pN, one);                                                                   //  pN--;

    //stk2 = ((((10 * pN) + pR) * 10) + a)                                          //  stk2 = ((((10 * pN) + pR) * 10) + a)
    memcpy(stk2, pN, sizeof(struct BigInteger));                                    //      stk2 = pN;
    mul(stk2, ten);                                                                 //      stk2 = pA0 * ten (10);
    add(stk2, pR);                                                                  //      stk2 = pA0 * pR;
    mul(stk2, ten);                                                                 //      stk2 = pA0 * ten (10);
    add(stk2, a);                                                                   //      stk2 = pA0 + a;

    add(pN, one);                                                                   //pN++;

    mul(stk1, pA1);                                                                 //stk1 *= pA1; {n0}
    mul(stk2, pA1);                                                                 //stk2 *= pA1; {n1}

    //pN = (pN - ((num - n0) / (n0 - n1)))
    memcpy(stk0, stk1, sizeof(struct BigInteger));                                  //stk0 = stk1;

    sub(stk1, stk2);                                                                //stk1 -= stk2;
    sub(stk0, num);                                                                 //stk1 -= num;
    dvs(stk0, stk1);                                                                //stk0 /= stk1;
    sub(pN, stk0);                                                                  //pN -= stk0
/*VERSION 2*/

/*
    isEq = isEqual(pA0, pA1, num);                                                  //¿pA0 * pA1 > num? => isEq

    if (isEq == 1) {                                                                //if(pA0 * pA1 > num){
        //pA0 = ((((10 * pN--) + pR) * 10) + a)                                     //  pA0 = ((((10 * pN--) + pR) * 10) + a)
        memcpy(pA0, pN, sizeof(struct BigInteger));                                 //      pA0 = pN;
        mul(pA0, ten);                                                              //      pA0 = pA0 * ten (10);
        add(pA0, pR);                                                               //      pA0 = pA0 * pR;
        mul(pA0, ten);                                                              //      pA0 = pA0 * ten (10);
        add(pA0, a);                                                                //      pA0 = pA0 + a;
        sub(pN, one);                                                               //      pN--;

        isEq = isEqual(pA0, pA1, num);                                              //  ¿pA0 * pA1 > num? => isEq

        while (isEq == 1) {                                                         //  while((((10 * (pN--) + pR) * 10) + a) * pA1 > num){
            //pA0 = ((((10 * pN--) + pR) * 10) + a)                                 //      pA0 = ((((10 * pN--) + pR) * 10) + a)
            memcpy(pA0, pN, sizeof(struct BigInteger));                             //          pA0 = pN;
            mul(pA0, ten);                                                          //          pA0 = pA0 * ten (10);
            add(pA0, pR);                                                           //          pA0 = pA0 * pR;
            mul(pA0, ten);                                                          //          pA0 = pA0 * ten (10);
            add(pA0, a);                                                            //          pA0 = pA0 + a;
            sub(pN, one);                                                           //          pN--;

            isEq = isEqual(pA0, pA1, num);                                          //      ¿pA0 * pA1 > num? => isEq
        }                                                                           //  }

        add(pN, one);                                                               //  pN++;
        //pA0 = ((((10 * pN) + pR) * 10) + a)                                       //  pA0 = ((((10 * pN) + pR) * 10) + a)
        memcpy(pA0, pN, sizeof(struct BigInteger));                                 //      pA0 = pN;
        mul(pA0, ten);                                                              //      pA0 = pA0 * ten (10);
        add(pA0, pR);                                                               //      pA0 = pA0 * pR;
        mul(pA0, ten);                                                              //      pA0 = pA0 * ten (10);
        add(pA0, a);                                                                //      pA0 = pA0 + a;

        isEq = isEqual(pA0, pA1, num);                                              //  ¿pA0 * pA1 > num? => isEq

        if (isEq == 2)                                                              //  if((((10 * (++pN) + pR) * 10) + a) * pA1 < num)
            add(pN, one);                                                           //      pN++;
    }else {                                                                         //}else{
        //pA0 = ((((10 * ++pN) + pR) * 10) + a)                                     //  pA0 = ((((10 * ++pN) + pR) * 10) + a)
        add(pN, one);                                                               //      pN++
        memcpy(pA0, pN, sizeof(struct BigInteger));                                 //      pA0 = pN;
        mul(pA0, ten);                                                              //      pA0 = pA0 * ten (10);
        add(pA0, pR);                                                               //      pA0 = pA0 * pR;
        mul(pA0, ten);                                                              //      pA0 = pA0 * ten (10);
        add(pA0, a);                                                                //      pA0 = pA0 + a;

        isEq = isEqual(pA0, pA1, num);                                              //  ¿pA0 * pA1 > num? => isEq

        while (isEq == 2) {                                                         //  while((((10 * (++pN) + pR) * 10) + a) * pA1 < num){
            //pA0 = ((((10 * ++pN) + pR) * 10) + a)                                 //      pA0 = ((((10 * ++pN) + pR) * 10) + a)
            add(pN, one);                                                           //          pN++
            memcpy(pA0, pN, sizeof(struct BigInteger));                             //          pA0 = pN;
            mul(pA0, ten);                                                          //          pA0 = pA0 * ten (10);
            add(pA0, pR);                                                           //          pA0 = pA0 * pR;
            mul(pA0, ten);                                                          //          pA0 = pA0 * ten (10);
            add(pA0, a);                                                            //          pA0 = pA0 + a;

            isEq = isEqual(pA0, pA1, num);                                          //      ¿pA0 * pA1 > num? => isEq
        }                                                                           //  }

        sub(pN, one);                                                               //  pN--;
    }                                                                               //}

*/
    //pA0 = (((10 * pN + pR) * 10) + a);                                            //pA0 = (((10 * pN + pR) * 10) + a);
    memcpy(pA0, pN, sizeof(struct BigInteger));                                     //  pA0 = pN;
    mul(pA0, ten);                                                                  //  pA0 = pA0 * ten (10);
    add(pA0, pR);                                                                   //  pA0 = pA0 * pR;
    mul(pA0, ten);                                                                  //  pA0 = pA0 * ten (10);
    add(pA0, a);                                                                    //  pA0 = pA0 + a;

    memcpy(&((struct BigInteger*)res)[0], pA0, sizeof(struct BigInteger));          //res[0] = pA0;
    memcpy(&((struct BigInteger*)res)[1], pA1, sizeof(struct BigInteger));          //res[1] = pA1;
    memcpy(&((struct BigInteger*)res)[2], pN, sizeof(struct BigInteger));           //res[2] = pN;

    free(pN);
    free(min);
    free(one);
    free(ten);
    free(hun);
    free(a);
    free(pTR);
    free(pR0);
    free(pR);
    free(ires);
    free(pNH);
    free(pRT);
    free(pA0);
    free(pA1);
    free(stk0);
    free(stk1);
    free(stk2);
}

int isEqual(void* va, void* vb, void* n) {
    struct BigInteger* r = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    int* k = (int*)malloc(sizeof(int));
    int x;
    int mm;

    mm = memchk(2, r, k);

    if (mm < 0) {
        _log("Error", INFORMATIONAL);
        exit(-110);
    }

    memcpy(r, va, sizeof(struct BigInteger));   //r = va;

    mul(r, vb);                                 //r = r * vb;
    equals(r, n, k);                            // ¿r = n? => k

    memcpy(&x, k, sizeof(int));                 //x = k

    free(r);
    free(k);

    return x;
}

void regression(void* data, void* axis, void* dif) {
  struct BigInteger* sxi1 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sxi2 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sxi3 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sxi4 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* syi = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sxi1yi = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* sxi2yi = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* axisn = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* three = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* eq1 = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 4);
  struct BigInteger* eq2 = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 4);
  struct BigInteger* eq3 = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 4);
  struct BigInteger* f1 = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 4);
  struct BigInteger* f2 = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 4);
  struct BigInteger* f3 = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 4);
  struct BigInteger* a = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 4);
  struct BigInteger* b = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 4);
  struct BigInteger* c = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 4);

  //logging
  char* st1;
  char* st2;
  char* st3;
  char* st4;

  iniStr(&st1);
  iniStr(&st2);
  iniStr(&st3);
  iniStr(&st4);

  int i = 0;
  int mmc = 22;

  memchk(mmc, sxi1, sxi2, sxi3, sxi4, axisn, syi, sxi1yi, sxi2yi, eq1, eq2, eq3, three, f1, f2, f3, a, b, c, st1, st2, st3, st4);

  if (mmc < 0)
    exit(-121);

  //initialise data                                                               ////initialise data
  BImemcpy(sxi1, 0);                                                              //sxi1 = 0;
  BImemcpy(sxi2, 0);                                                              //sxi2 = 0;
  BImemcpy(sxi3, 0);                                                              //sxi3 = 0;
  BImemcpy(sxi4, 0);                                                              //sxi4 = 0;
  BImemcpy(syi, 0);                                                               //syi = 0;
  BImemcpy(sxi1yi, 0);                                                            //sxi1yi = 0;
  BImemcpy(sxi2yi, 0);                                                            //sxi2yi = 0;
  BImemcpy(axisn, 0);                                                             //axisn = 0;
  BImemcpy(three, 1);                                                             //axisn = 1;

  for (; i < 3; i++) {                                                            //for (; i < 3; i++) {
    //sxin: sum of i^n                                                            //  //sxin: sum of i^n
    //syi: sum of f(x)                                                            //  //syi: sum of f(x)
    //sxinyi: sum of i^n + yi                                                     //  //sxinyi: sum of i^n + yi
    add(sxi1, &((struct BigInteger*)axis)[i]);                                    //  sxi1 += axis[i];
    add(syi, &((struct BigInteger*)data)[i]);                                     //  syi += data[i];

    memcpy(axisn, &((struct BigInteger*)axis)[i], sizeof(struct BigInteger));     //  axisn = axis[i];

    mul(axisn, &((struct BigInteger*)axis)[i]);                                   //  axisn *= axis[i] (axisn^2);
    add(sxi2, axisn);                                                             //  sxi2 += axisn;

    mul(axisn, &((struct BigInteger*)axis)[i]);                                   //  axisn *= axis[i] (axisn^3);
    add(sxi3, axisn);                                                             //  sxi3 += axisn;

    mul(axisn, &((struct BigInteger*)axis)[i]);                                   //  axisn *= axis[i] (axisn^4);
    add(sxi4, axisn);                                                             //  sxi4 += axisn;

    memcpy(axisn, &((struct BigInteger*)axis)[i], sizeof(struct BigInteger));     //  axisn = axis[i];
    mul(axisn, &((struct BigInteger*)data)[i]);                                   //  axisn *= data[i];
    add(sxi1yi, axisn);                                                           //  sxi1yi += axisn;

    mul(axisn, &((struct BigInteger*)axis)[i]);                                   //  axisn *= axis[i] (axisn^2);
    add(sxi2yi, axisn);                                                           //  sxi2yi += axisn;
  }                                                                               //}

  BImemcpy(axisn, 1);                                                             //axisn = 1;
  add(three, axisn);                                                              // three++;
  add(three, axisn);                                                              // three++;

  //build equations                                                               ////build equations
  //equation 1                                                                    ////equation 1
  memcpy(&eq1[0], three, sizeof(struct BigInteger));                              //eq1[0] = 3;
  memcpy(&eq1[1], sxi1, sizeof(struct BigInteger));                               //eq1[1] = sxi1;
  memcpy(&eq1[2], sxi2, sizeof(struct BigInteger));                               //eq1[2] = sxi2;
  memcpy(&eq1[3], syi, sizeof(struct BigInteger));                                //eq1[3] = syi;

  //equation 2
  memcpy(&eq2[0], sxi1, sizeof(struct BigInteger));                               //eq2[0] = sxi1;
  memcpy(&eq2[1], sxi2, sizeof(struct BigInteger));                               //eq2[1] = sxi2;
  memcpy(&eq2[2], sxi3, sizeof(struct BigInteger));                               //eq2[2] = sxi3;
  memcpy(&eq2[3], sxi1yi, sizeof(struct BigInteger));                             //eq2[3] = sxi1yi;

  //equation 3
  memcpy(&eq3[0], sxi2, sizeof(struct BigInteger));                               //eq3[0] = sxi2;
  memcpy(&eq3[1], sxi3, sizeof(struct BigInteger));                               //eq3[1] = sxi3;
  memcpy(&eq3[2], sxi4, sizeof(struct BigInteger));                               //eq3[2] = sxi4;
  memcpy(&eq3[3], sxi2yi, sizeof(struct BigInteger));                             //eq3[3] = sxi2yi;

  toString(&eq1[0], st1);                                                         ///*
  toString(&eq1[1], st2);                                                         // * Display eq1
  toString(&eq1[2], st3);                                                         // *
  toString(&eq1[3], st4);                                                         // *

  _log("Equation 1: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq2[0], st1);                                                         ///*
  toString(&eq2[1], st2);                                                         // * Display eq2
  toString(&eq2[2], st3);                                                         // *
  toString(&eq2[3], st4);                                                         // *

  _log("Equation 2: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq3[0], st1);                                                         ///*
  toString(&eq3[1], st2);                                                         // * Display eq3
  toString(&eq3[2], st3);                                                         // *
  toString(&eq3[3], st4);                                                         // *

  _log("Equation 3: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  //Gauss                                                                         ////Gauss
  //eliminate x-factor on eq2                                                     ////eliminate x-factor on eq2
  gsignum(&eq1[0], &eq2[0], f1);                                                  //f1 = gsignum(eq1[0], eq2[0]);
  memcpy(f3, &eq1[0], sizeof(struct BigInteger));                                 //f3 = eq1[0];
  absolute(f3);                                                                   //f3 = absolute(f3);
  mul(f1, f3);                                                                    //f1 *= f3;

  memcpy(f2, &eq2[0], sizeof(struct BigInteger));                                 //f2 = eq2[0];
  absolute(f2);                                                                   //f2 = absolute(f2);

  gaussM(f1, eq2);                                                                //gaussM(f1, eq2);
  gaussM(f2, eq1);                                                                //gaussM(f2, eq1);
  gaussS(eq2, eq1);                                                               //gaussS(eq2, eq1);

  _log("------------- x on eq2 -------------", INFORMATIONAL);                    ////Display header
  toString(&eq1[0], st1);                                                         ///*
  toString(&eq1[1], st2);                                                         // *  Display eq1
  toString(&eq1[2], st3);                                                         // *
  toString(&eq1[3], st4);                                                         // *

  _log("Equation 1: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq2[0], st1);                                                         ///*
  toString(&eq2[1], st2);                                                         // *  Display eq2
  toString(&eq2[2], st3);                                                         // *
  toString(&eq2[3], st4);                                                         // *

  _log("Equation 2: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq3[0], st1);                                                         ///*
  toString(&eq3[1], st2);                                                         // *  Display eq3
  toString(&eq3[2], st3);                                                         // *
  toString(&eq3[3], st4);                                                         // *

  _log("Equation 3: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  //eliminate x-factor on eq3                                                     ////eliminate x-factor on eq3
  gsignum(&eq1[0], &eq3[0], f1);                                                  //f1 = gsignum(eq1[0], eq3[0]);
  memcpy(f3, &eq1[0], sizeof(struct BigInteger));                                 //f3 = eq1[0];
  absolute(f3);                                                                   //f3 = absolute(f3);
  mul(f1, f3);                                                                    //f1 *= f3;

  memcpy(f2, &eq3[0], sizeof(struct BigInteger));                                 //f2 = eq3[0];
  absolute(f2);                                                                   //f2 = absolute(f2);

  gaussM(f1, eq3);                                                                //gaussM(f1, eq3);
  gaussM(f2, eq1);                                                                //gaussM(f2, eq1);
  gaussS(eq3, eq1);                                                               //gaussS(eq3, eq1);

  _log("------------- x on eq3 -------------", INFORMATIONAL);                    ////Display header
  toString(&eq1[0], st1);                                                         ///*
  toString(&eq1[1], st2);                                                         // *  Display eq1
  toString(&eq1[2], st3);                                                         // *
  toString(&eq1[3], st4);                                                         // *

  _log("Equation 1: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq2[0], st1);                                                         ///*
  toString(&eq2[1], st2);                                                         // *  Display eq2
  toString(&eq2[2], st3);                                                         // *
  toString(&eq2[3], st4);                                                         // *

  _log("Equation 2: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq3[0], st1);                                                         ///*
  toString(&eq3[1], st2);                                                         // *  Display eq3
  toString(&eq3[2], st3);                                                         // *
  toString(&eq3[3], st4);                                                         // *

  _log("Equation 3: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  //eliminate y-factor on eq1                                                     ////eliminate y-factor on eq1
  gsignum(&eq2[1], &eq1[1], f1);                                                  //f1 = gsignum(eq2[1], eq1[1]);
  memcpy(f3, &eq2[1], sizeof(struct BigInteger));                                 //f3 = eq2[1];
  absolute(f3);                                                                   //f3 = absolute(f3);
  mul(f1, f3);                                                                    //f1 *= f3;

  memcpy(f2, &eq1[1], sizeof(struct BigInteger));                                 //f2 = eq1[1];
  absolute(f2);                                                                   //f2 = absolute(f2);

  gaussM(f1, eq1);                                                                //gaussM(f1, eq1);
  gaussM(f2, eq2);                                                                //gaussM(f2, eq2);
  gaussS(eq1, eq2);                                                               //gaussS(eq1, eq2);

  _log("------------- y on eq1 -------------", INFORMATIONAL);                    ////Display header
  toString(&eq1[0], st1);                                                         ///*
  toString(&eq1[1], st2);                                                         // *  Display eq1
  toString(&eq1[2], st3);                                                         // *
  toString(&eq1[3], st4);                                                         // *

  _log("Equation 1: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq2[0], st1);                                                         ///*
  toString(&eq2[1], st2);                                                         // *  Display eq2
  toString(&eq2[2], st3);                                                         // *
  toString(&eq2[3], st4);                                                         // *

  _log("Equation 2: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq3[0], st1);                                                         ///*
  toString(&eq3[1], st2);                                                         // *  Display eq3
  toString(&eq3[2], st3);                                                         // *
  toString(&eq3[3], st4);                                                         // *

  _log("Equation 3: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  //eliminate y-factor on eq3                                                     ////eliminate y-factor on eq3
  gsignum(&eq2[1], &eq3[1], f1);                                                  //f1 = gsignum(eq2[1], eq3[1]);
  memcpy(f3, &eq2[1], sizeof(struct BigInteger));                                 //f3 = eq2[1];
  absolute(f3);                                                                   //f3 = absolute(f3);
  mul(f1, f3);                                                                    //f1 *= f3;

  memcpy(f2, &eq3[1], sizeof(struct BigInteger));                                 //f2 = eq3[1];
  absolute(f2);                                                                   //f2 = absolute(f2);

  gaussM(f1, eq3);                                                                //gaussM(f1, eq3);
  gaussM(f2, eq2);                                                                //gaussM(f2, eq2);
  gaussS(eq3, eq2);                                                               //gaussS(eq3, eq2);

  _log("------------- y on eq3 -------------", INFORMATIONAL);                    ////Display header
  toString(&eq1[0], st1);                                                         ///*
  toString(&eq1[1], st2);                                                         // *  Display eq1
  toString(&eq1[2], st3);                                                         // *
  toString(&eq1[3], st4);                                                         // *

  _log("Equation 1: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq2[0], st1);                                                         ///*
  toString(&eq2[1], st2);                                                         // *  Display eq2
  toString(&eq2[2], st3);                                                         // *
  toString(&eq2[3], st4);                                                         // *

  _log("Equation 2: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq3[0], st1);                                                         ///*
  toString(&eq3[1], st2);                                                         // *  Display eq3
  toString(&eq3[2], st3);                                                         // *
  toString(&eq3[3], st4);                                                         // *

  _log("Equation 3: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  //eliminate z-factor on eq1                                                     ////eliminate z-factor on eq1
  gsignum(&eq3[2], &eq1[2], f1);                                                  //f1 = gsignum(eq3[2], eq1[2]);
  memcpy(f3, &eq3[2], sizeof(struct BigInteger));                                 //f3 = eq3[2];
  absolute(f3);                                                                   //f3 = absolute(f3);
  mul(f1, f3);                                                                    //f1 *= f3;

  memcpy(f2, &eq1[2], sizeof(struct BigInteger));                                 //f2 = eq1[2];
  absolute(f2);                                                                   //f2 = absolute(f2);

  gaussM(f1, eq1);                                                                //gaussM(f1, eq1);
  gaussM(f2, eq3);                                                                //gaussM(f2, eq3);
  gaussS(eq1, eq3);                                                               //gaussS(eq1, eq3);

  _log("------------- z on eq1 -------------", INFORMATIONAL);                    ////Display header
  toString(&eq1[0], st1);                                                         ///*
  toString(&eq1[1], st2);                                                         // *  Display eq1
  toString(&eq1[2], st3);                                                         // *
  toString(&eq1[3], st4);                                                         // *

  _log("Equation 1: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq2[0], st1);                                                         ///*
  toString(&eq2[1], st2);                                                         // *  Display eq2
  toString(&eq2[2], st3);                                                         // *
  toString(&eq2[3], st4);                                                         // *

  _log("Equation 2: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq3[0], st1);                                                         ///*
  toString(&eq3[1], st2);                                                         // *  Display eq3
  toString(&eq3[2], st3);                                                         // *
  toString(&eq3[3], st4);                                                         // *

  _log("Equation 3: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  //eliminate z-factor on eq2                                                     ////eliminate z-factor on eq2
  gsignum(&eq3[2], &eq2[2], f1);                                                  //f1 = gsignum(eq3[2], eq2[2]);
  memcpy(f3, &eq3[2], sizeof(struct BigInteger));                                 //f3 = eq3[2];
  absolute(f3);                                                                   //f3 = absolute(f3);
  mul(f1, f3);                                                                    //f1 *= f3;

  memcpy(f2, &eq2[2], sizeof(struct BigInteger));                                 //f2 = eq2[2];
  absolute(f2);                                                                   //f2 = absolute(f2);

  gaussM(f1, eq2);                                                                //gaussM(f1, eq2);
  gaussM(f2, eq3);                                                                //gaussM(f2, eq3);
  gaussS(eq2, eq3);                                                               //gaussS(eq2, eq3);

  _log("------------- z on eq2 -------------", INFORMATIONAL);                    ////Display header
  toString(&eq1[0], st1);                                                         ///*
  toString(&eq1[1], st2);                                                         // *  Display eq1
  toString(&eq1[2], st3);                                                         // *
  toString(&eq1[3], st4);                                                         // *

  _log("Equation 1: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq2[0], st1);                                                         ///*
  toString(&eq2[1], st2);                                                         // *  Display eq2
  toString(&eq2[2], st3);                                                         // *
  toString(&eq2[3], st4);                                                         // *

  _log("Equation 2: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  toString(&eq3[0], st1);                                                         ///*
  toString(&eq3[1], st2);                                                         // *  Display eq3
  toString(&eq3[2], st3);                                                         // *
  toString(&eq3[3], st4);                                                         // *

  _log("Equation 3: <%s, %s, %s, %s>", INFORMATIONAL, st1, st2, st3, st4);        // */

  memcpy(c, &eq1[3], sizeof(struct BigInteger));                                  //c = eq1[3];
  memcpy(b, &eq2[3], sizeof(struct BigInteger));                                  //b = eq2[3];
  memcpy(a, &eq3[3], sizeof(struct BigInteger));                                  //a = eq3[3];

  dvs(c, &eq1[0]);                                                                //c /= eq1[0];
  dvs(b, &eq2[1]);                                                                //b /= eq2[1];
  dvs(a, &eq3[2]);                                                                //a /= eq3[2];

  toString(a, st1);                                                               ///*
  toString(b, st2);                                                               // * Display a, b, c
  toString(c, st3);                                                               // *
  _log("a: %s", INFORMATIONAL, st1);                                              // *
  _log("b: %s", INFORMATIONAL, st2);                                              // *
  _log("c: %s", INFORMATIONAL, st3);                                              // */

  memcpy(&((struct BigInteger*)dif)[0], a, sizeof(struct BigInteger));            //dif[0] = a;
  memcpy(&((struct BigInteger*)dif)[1], b, sizeof(struct BigInteger));            //dif[1] = b;
  memcpy(&((struct BigInteger*)dif)[2], c, sizeof(struct BigInteger));            //dif[2] = c;

  free(sxi1);
  free(sxi2);
  free(sxi3);
  free(sxi4);
  free(syi);
  free(sxi1yi);
  free(sxi2yi);
  free(axisn);
  free(three);
  free(eq1);
  free(eq2);
  free(eq3);
  free(f1);
  free(f2);
  free(f3);
  free(a);
  free(b);
  free(c);
  free(st1);
  free(st2);
  free(st3);
  free(st4);
}

void absolute(void* n) {
  struct BigInteger* z = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* m = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  int* r = (int*)malloc(sizeof(int));

  int mm = 3;

  memchk(mm, z, m, r);

  if (mm < 0)
    exit(-131);

  BImemcpy(z, 0);     //z = 0;
  BImemcpy(m, -1);    //m = -1;

  equals(n, z, r);    ////¿n < z? => r

  if (*r == 2)        //if(n < z)
    mul(n, m);        //  n *= m;

  free(z);
  free(m);
  free(r);
}

void gsignum(void* a, void* b, void* res) {
  struct BigInteger* z = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* o = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* m = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  int* k1 = (int*)malloc(sizeof(int));
  int* k2 = (int*)malloc(sizeof(int));

  int mm = 5;

  memchk(mm, z, o, m, k1, k2);

  BImemcpy(z, 0);                     //z = 0;
  BImemcpy(o, 1);                     //o = 1;
  BImemcpy(m, -1);                    //m = -1;

  equals(a, z, k1);                   ////¿a < z? => k1
  equals(b, z, k2);                   ////¿b < z? => k2

  if (*k1 == 2 && *k2 == 2) {          //if(a < 0 && b < 0){
    BImemcpy(res, -1);                //  res = -1;
  }else if (*k1 == 1 && *k2 == 1) {    //}else if(a > 0 && b > 0){
    BImemcpy(res, -1);                //  res = -1;
  }else {                             //}else{
    BImemcpy(res, 1);                 //  res = 1;
  }                                   //}

  free(z);
  free(o);
  free(m);
  free(k1);
  free(k2);
}

void gaussM(void* factor, void* equation) {
  int i = 0;

  for (i = 0; i < 4; i++)                               //for (i = 0; i < 3; i++) 
    mul(&((struct BigInteger*)equation)[i], factor);    //  equation[i] *= factor;
}

void gaussS(void* equation1, void* equation2) {
  int i = 0;

  for (i = 0; i < 4; i++)                                                             //for (i = 0; i < 3; i++) 
    add(&((struct BigInteger*)equation1)[i], &((struct BigInteger*)equation2)[i]);    //  equation1[i] += equation2[i];
}

void solve(void* dif, void* sols) {
  struct BigInteger* min = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* two = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* four = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* b2 = (struct BigInteger*)malloc(sizeof(struct BigInteger));

  int mm = 4;
  int m;

  m = memchk(mm, min, two, four, b2);

  if (m < 0)
    exit(-301);

  //initialize data
  BImemcpy(min, -1); //min = -1;
  BImemcpy(two, 1); //two = 1;
  add(two, two); //two++; (two = 2)

  memcpy(four, two, sizeof(struct BigInteger)); //four = two;
  add(four, four); //four = four + four; (four = 4)

  memcpy(b2, &((struct BigInteger*)dif)[1], sizeof(struct BigInteger)); //b2 = b;


  //b^2
  mul(b2, b2); //b2 *= b2;

  //4ac
  mul(four, &((struct BigInteger*)dif)[0]); //four *= a;
  mul(four, &((struct BigInteger*)dif)[2]); //four *= c;

  //b^2 - 4ac
  sub(b2, four); //b2 -= four;

  //sqrt(b^2 - 4ac)
  nqrt(b2, 2); //b2 = sqrt(min);

  //2a
  mul(two, &((struct BigInteger*)dif)[0]); //two *= a;

  //-b
  mul(min, &((struct BigInteger*)dif)[1]); //min *= b;

  memcpy(&((struct BigInteger*)sols)[0], min, sizeof(struct BigInteger)); //sols[0] = min;
  memcpy(&((struct BigInteger*)sols)[1], min, sizeof(struct BigInteger)); //sols[1] = min;

  //-b + sqrt(b^2 - 4ac)
  add(&((struct BigInteger*)sols)[0], b2); //sols[0] += b2;

  //-b - sqrt(b^2 - 4ac)
  sub(&((struct BigInteger*)sols)[1], b2); //sols[1] -= b2;

  //(-b + sqrt(b^2 - 4ac)) / 2a
  dvs(&((struct BigInteger*)sols)[0], two); //sols[0] /= two;

  //(-b - sqrt(b^2 - 4ac)) / 2a
  dvs(&((struct BigInteger*)sols)[1], two); //sols[1] /= two;

  free(min);
  free(two);
  free(four);
  free(b2);
}

int memchk(int n, ...) {
    va_list pa;
    va_start(pa, n);

    for (; n > 0; n--)
        if ((void*)va_arg(pa, size_t) == NULL)
            return -1;

    return 0;
}
