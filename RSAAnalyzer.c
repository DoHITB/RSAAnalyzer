/*
 * RSAAnalyzer.c
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
#include "math.h"

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
  //General values
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
  struct BigInteger* one = (struct BigInteger*)malloc(sizeof(struct BigInteger));
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

  //Execution pool
  char* pool;
  int plen;
  int pi;
  int ppi;
  int px;

  FILE* fl;
  FILE* fl2;
  int efl;

  //Tracing aux vars
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
  int rf;
  int ri = 0;

  //Equation solving
  struct BigInteger* sols = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 2);

  //Iteration solving
  struct BigInteger* dist = (struct BigInteger*)malloc(sizeof(struct BigInteger) * 3);
  int exr = -1;
  int ext = 0;

  //Beacon signal
  FILE* bcs; //send
  FILE* bcr; //receive
  int bcsl;
  int bcrl;
  char* out = (char*)malloc(sizeof(char) * 5000);

  //debug
  int debug = 0;

  //TODO => memchk

  //temporal
  if (debug == 2) {
    testing();
  }

  iniStr(&st1);
  iniStr(&st2);
  iniStr(&st3);

  //inis
  BImemcpy(ten, 10);
  BImemcpy(zro, 0);
  BImemcpy(one, 1);

  //start tracing
  if(argc == 1) {
    activateLog(INFORMATIONAL);
  }else{
    name = (char*)malloc(sizeof(char) * 5000);

    //num_arr_s.dat
    snprintf(name, 5000, "%s_%s_%s.log", argv[1], argv[2], argv[3]);
    setFile(name);
    activateLog(INFORMATIONAL);
  }

  setShowTime(0);

  //get number
  if (argc == 1) {
    printf("Number to analyse: ");
    gets_s(number, 4096);
  }else {
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

    //delete previous files
    system("del.bat 2>nul");

    _log("", INFORMATIONAL);
    _log("Base execution. Generating execution pool", INFORMATIONAL);
    inFunction();

    _log("Starting waitlist...", INFORMATIONAL);
    efl = fopen_s(&fl2, "waitlist.bat", "w+");

    if (efl < 0)
      exit(-103);

    fputs("@echo off\n", fl2);
    fputs("start /B RSAWaitList", fl2);
    fflush(fl2);
    fclose(fl2);

    _log("RSAWaitlist.exe started!", INFORMATIONAL);
    system("waitlist.bat");

    /*
     * Params Table
     *
     * S will be downgraded by 1 as then it's upgraded
     * When S = 1 (arr[0] == arr[1]) we will move arr[1] - 1 as it's better for calculation
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
      _log("First pair pool: ", INFORMATIONAL);
      inFunction();
      //arr1 have data. Possible combinations:
      //{1, 1}, {1, 3}, {1, 7}, {1, 9} => S = arr1[1]
      for (pi = 0; pi < arr1[1]; pi++) {
        ppi = pi;

        if (ppi == 0)
          ppi = arr1[1];

        snprintf(pool, plen, "RSAAnalyzer.exe %s %i %i", st1, 1, ppi);
        _log("Command: %s", INFORMATIONAL, pool);
        fputs("START /B ", fl);
        fputs(pool, fl);
        fputs("\n", fl);
      }

      outFunction();
    }

    if (arr2[0] > 0) {
      _log("Second pair pool: ", INFORMATIONAL);
      inFunction();
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
        ppi = pi;

        if (ppi == 0)
          ppi = px;

        snprintf(pool, plen, "RSAAnalyzer.exe %s %i %i", st1, 2, ppi);
        _log("Command: %s", INFORMATIONAL, pool);
        fputs("START /B ", fl);
        fputs(pool, fl);
        fputs("\n", fl);
      }

      outFunction();
    }

    if (arr3[0] > 0) {
      _log("Third pair pool: ", INFORMATIONAL);
      inFunction();
      //arr3 have data. Possible combinations:
      //{9, 9}, {7, 7} => S = 1
      snprintf(pool, plen, "RSAAnalyzer.exe %s %i %i", st1, 3, arr3[1]);
      _log("Command: %s", INFORMATIONAL, pool);
      fputs("START /B ", fl);
      fputs(pool, fl);
      fputs("\n", fl);
    }

    outFunction();
    outFunction();

    fflush(fl);
    fclose(fl);

    _log("Execution pool generated (main.bat)", INFORMATIONAL);
    _log("Do not close this window. It will run on background and show the result on screen once done!", INFORMATIONAL);
    _log("Starting the pool right now", INFORMATIONAL);

    //start the pool
    system("main.bat");

    outFunction();
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
      //Debug Override
      op = 2;
      s = 1;
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

    //get Y  and Z Factor
    y = getY(arr);
    zf = getZF(arr);
    axisFactor(sq);
    rf = relativeFactor(getS(arr), arr);
    ri = relativeFactorResult(getS(arr), sq);

    //dump data
    _log("Selected data {%i}:", INFORMATIONAL, op);

    inFunction();
    toString(sqrtAprox, st1);
    toString(sq, st2);

    _log("arr: <%i, %i>", INFORMATIONAL, arr[0], arr[1]);
    _log("k: %i", INFORMATIONAL, k);
    _log("z: %i", INFORMATIONAL, z);
    _log("sqrtAprox: %s", INFORMATIONAL, st1);
    _log("Axis Factor: %s", INFORMATIONAL, st2);
    _log("y: %i", INFORMATIONAL, y);
    _log("z factor: %i", INFORMATIONAL, zf);
    _log("s: %i", INFORMATIONAL, s);
    _log("rf: %i", INFORMATIONAL, rf);
    _log("ri: %i", INFORMATIONAL, ri);
    _log("", INFORMATIONAL);

    outFunction();

    _log("Gathering data...", INFORMATIONAL);

    /* Data Gathering - START */
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

    //if rf = -1 means always store (arr[0] = arr[1])
    //if rf > 0 means that we have some "s" data.
    if (rf == -1 || ri % rf == (s - 1)) {
      //data[count] = chk
      memcpy(&data[count], chk, sizeof(struct BigInteger));

      //aixs[count] = sq
      memcpy(&axis[count], sq, sizeof(struct BigInteger));

      ++count;
    }

    //ri holds a counter to check congruency with rf mod s
    ++ri;

    while (done == 1) {
      //ant = chk
      memcpy(ant, chk, sizeof(struct BigInteger));

      //sqrtAprox1 += 10;
      add(sqrtAprox, ten);

      //get next value
      getPonderated(num, arr[0], sqrtAprox, k, z, n, tempVal);

      //n = tempVal[2]
      memcpy(n, &tempVal[2], sizeof(struct BigInteger));

      //res = tempVal[0] * tempVal[1];
      memcpy(res, &tempVal[0], sizeof(struct BigInteger));
      mul(res, &tempVal[1]);

      //chk = res - num
      memcpy(chk, res, sizeof(struct BigInteger));
      sub(chk, num);

      //if rf = -1 means always store (arr[0] = arr[1])
      //if rf > 0 means that we have some "s" data.
      if (rf == -1 || ri % rf == (s - 1)) {
        add(sq, one);

        //data[count] = chk
        memcpy(&data[count], chk, sizeof(struct BigInteger));

        //aixs[count] = sq
        memcpy(&axis[count], sq, sizeof(struct BigInteger));

        ++count;
      }else {
        //rf > 0 || rs % s != 0 => that means, have subseries and not time to store values
        if (count == 0) {
          //whereas we don't store any value, we keep treating sq as an auto-increment
          add(sq, one);
        }
      }

      equals(chk, zro, eq);

      if (*eq == 0) { //if(chk == 0)
        toString(&tempVal[0], st1);
        toString(&tempVal[1], st2);
        _log("DONE! <%s, %s>", INFORMATIONAL, st1, st2);

        done = 0;
        exr = 0;
        ext = 0;

        //copy it to sols to get printed
        memcpy(&sols[0], &tempVal[0], sizeof(struct BigInteger));
        memcpy(&sols[1], &tempVal[1], sizeof(struct BigInteger));
      }

      //we only need 3 data samples
      if (count == 3) {
        _log("Data gathered", INFORMATIONAL);
        done = 0;
      }

      ++ri;
    }

    _log("", INFORMATIONAL);
    _log("Gathered data: ", INFORMATIONAL);

    inFunction();

    //dump data
    for (possi = 0; possi < count; possi++) {
      toString(&data[possi], st1);
      toString(&axis[possi], st2);

      _log("Data[%i]: %s", INFORMATIONAL, possi, st1);
      _log("Axis[%i]: %s", INFORMATIONAL, possi, st2);

      _log("---------------------------------", INFORMATIONAL);
    }

    outFunction();
    /* Data Gathering - END */

    //it may be found while gathering data
    if (exr != 0) {
      regression(data, axis, dif);
      distance(dif, zf, y, s, dist);

      toString(&dif[0], st1);
      toString(&dif[1], st2);
      toString(&dif[2], st3);
      _log("dif: <%s, %s, %s>", INFORMATIONAL, st1, st2, st3);
      _log("Associated equation: %sx^2 + %sx + %s = 0", INFORMATIONAL, st1, st2, st3);

      toString(&dist[0], st1);
      toString(&dist[1], st2);
      toString(&dist[2], st3);
      _log("dist: <%s, %s, %s>", INFORMATIONAL, st1, st2, st3);

      inFunction();
      _log("Solving x...", INFORMATIONAL);

      solve(dif, sols);

      toString(&sols[0], st1);
      toString(&sols[1], st2);
      _log("Solutions: <%s, %s>", INFORMATIONAL, st1, st2);

      outFunction();

      //sols[0] * sols[1] = num?
      exr = checkSolution(&sols[0], arr[1], num);
    }

    //iterate until a solution is found on any thread
    while (exr != 0) {
      //look for another threads' solution
      bcrl = fopen_s(&bcr, "RSAWL.dat", "r");

      if (bcrl == 0) {
        //a thread found a solution!
        ext = 1; //external = 1
        exr = 0; //stop iterate

        //close the file
        if(bcr != NULL)
          fclose(bcr);
      }else {
        //no thread found a solution. Keep searching
        toString(&dif[0], st1);
        toString(&dif[1], st2);
        toString(&dif[2], st3);
        _log("Invalid value for dif: <%s, %s, %s>", INFORMATIONAL, st1, st2, st3);
        _log("Searching for new values...", INFORMATIONAL);

        //get new values for dif
        add(&dif[0], &dist[0]);
        add(&dif[1], &dist[1]);
        add(&dif[2], &dist[2]);

        toString(&dif[0], st1);
        toString(&dif[1], st2);
        toString(&dif[2], st3);
        _log("dif: <%s, %s, %s>", INFORMATIONAL, st1, st2, st3);
        _log("Associated equation: %sx^2 + %sx + %s = 0", INFORMATIONAL, st1, st2, st3);

        inFunction();
        _log("Solving x...", INFORMATIONAL);

        //solve new equation
        solve(dif, sols);

        toString(&sols[0], st1);
        toString(&sols[1], st2);
        _log("Solutions: <%s, %s>", INFORMATIONAL, st1, st2);

        outFunction();

        //sols[0] * sols[1] = num?
        exr = checkSolution(&sols[0], arr[1], num);
      }
    }

    //on this point, a solution has been found
    if (ext == 0) {
      //found on this thread!
      //prepare text
      st1 = printSolution(&sols[0], arr[1], num);
      snprintf(out, 5000, "%s_%s_%s.log: Solution %s", argv[1], argv[2], argv[3], st1);

      //write it on RSAWL.dat (open with w+ to avoid error during testing)
      bcsl = fopen_s(&bcs, "RSAWL.dat", "w+");

      if (bcsl < 0 || bcs == NULL)
        exit(-109);

      fputs(out, bcs);
      fflush(bcs);
      fclose(bcs);
    }

    outFunction();
    deactivateLog();
  }

  return 0;
}

//Load k Table
void loadK(int* kt) {
    int i = 0;
    int kti[16] = { 11, 13, 17, 19, 31, 33, 37, 39, 71, 73, 77, 79, 91, 93, 97, 99 };
    int ktk[16] = { 1,  7,  3,  9,  3,  1,  9,  7,  7,  9,  1,  3,  9,  3,  7,  1 };

    for (; i < 16; i++)
        kt[kti[i]] = ktk[i];

    //avoid undefined if any funcion returns a 0 value
    kt[0] = 0;
}

//Get the ending of a BigInteger
int getEnd(void* va) {
    return ((struct BigInteger*)va)->n[0];
}

//Return relative arr values
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

//Return relative kt value
int getK(int* arr) {
    return kt[(arr[0] * 10) + arr[1]];
}

//Return BigInteger % 100 (two lasts digits)
int getModulus(void* va) {
    if (((struct BigInteger*)va)->count == 0)
        return ((struct BigInteger*)va)->n[0];

    return (((struct BigInteger*)va)->n[1] * 10) +
           (((struct BigInteger*)va)->n[0]);
}

//Get Z value
int getZ(int* n, int num) {
    int i = 0;

    for (i = 0; i < 10; i++)
        if ((((10 * i) + n[0]) * n[1]) % 100 == num)
            return i;

    return 0;
}

//Get ponderated SQRT value for num
void getSqrt(void* num, int* arr, void* res) {
    int gsEnd;
    int s;
    struct BigInteger* ten = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* aux = (struct BigInteger*)malloc(sizeof(struct BigInteger));

    int mmi = 2;
    int mm;

    mm = memchk(mmi, ten, aux);

    if (mm < 0)
      exit(-109);
    
    if (arr[1] == 0) {
        BImemcpy(res, 0);
        return;
    }

    //initialize values
    BImemcpy(ten, 10);
    BImemcpy(aux, 0);

    //get sqrt
    memcpy(res, num, sizeof(struct BigInteger));
    nqrt(res, 2);

    //get S factor
    s = getS(arr);

    //get sqrt(s), only if there are subseries
    if (relativeFactor(s, arr) > 0) {
      s = (int)(sqrt((double)s));

      //if s == 3, sqrt(s) will be 1, so we add an unit
      if (s == 1)
        ++s;
    }else
      s = 1;

    //convert s to BI
    aux->n[0] = s;
    aux->count = 0;

    //res *= aux
    mul(res, aux);

    //get the ending
    gsEnd = getEnd(res);

    //the ending is bigger? then skip to the next
    if (gsEnd > arr[1])
        add(res, ten); //res += 10;

    //override ending with specific number
    ((struct BigInteger*)res)->n[0] = arr[1];

    free(ten);
    free(aux);
}

//Get Y value
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

//Get Z Factor
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
  }else if (arr[0] == 7) {
    //{7, 9}
    return 7;
  }

  return -1;
}

//Get S value
int getS(int* arr) {
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
    //1x => S = arr[1]
    return arr[1];
  }

  if (arr[0] == arr[1]) {
    //xx => S = x
    return arr[1];
  }

  if (arr[0] == 3) {
    //3x ({3, 7}, {3, 9})
    if (arr[1] == 7) {
      //37 => S = 9
      return 9;
    }else {
      //39 => S = 3
      return 3;
    }
  }

  if (arr[0] == 7) {
    //79 => S = 7
    return 7;
  }

  return -1;
}

//Retrieve relative value based on axis data
void axisFactor(void* a) {
  struct BigInteger* ten = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* one = (struct BigInteger*)malloc(sizeof(struct BigInteger));

  int mmi = 2;
  int mm;

  mm = memchk(mmi, ten, one);

  if (mm < 0)
    exit(-404);


  BImemcpy(ten, 10);                                                              //ten = 10;
  BImemcpy(one, 1);                                                               //one = 1;

  dvs(a, ten);                                                                    //a /= ten;
  add(a, one);                                                                    //a++;

  free(ten);
  free(one);
}

//Returns quantity of data to skip
int relativeFactor(int s, int* arr) {
  if (arr[0] == arr[1]) {
    return -1;
  }

  return s;
}

//Returns sq%s
int relativeFactorResult(int s, void* sq) {
  struct BigInteger* tmp = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* org = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  int ret;

  if (tmp == NULL || org == NULL)
    exit(-602);

  BImemcpy(tmp, 0);                             //tmp = 0;
  tmp->n[0] = s;                                //tmp = s;
  memcpy(org, sq, sizeof(struct BigInteger));   //org = sq;

  dvs(org, tmp);                                //org /= tmp;
  mul(org, tmp);                                //org *= tmp;
  memcpy(tmp, sq, sizeof(struct BigInteger));   //tmp = sq;
  sub(tmp, org);                                //tmp -= org;

  ret = tmp->n[0];                              //ret = org;

  free(tmp);
  free(org);

  return ret;
}

//Return ponderated value based on David Sole's Theoreme
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
    //VERSION 1. Do not delete yet
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

//Returns BigInteger.equals(va * vb, n)
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

//Performs QR regression, then solve it via Gauss
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
  int mmi = 22;
  int mm;

  mm = memchk(mmi, sxi1, sxi2, sxi3, sxi4, axisn, syi, sxi1yi, sxi2yi, eq1, eq2, eq3, three, f1, f2, f3, a, b, c, st1, st2, st3, st4);

  if (mm < 0)
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

//Return absolute value for n
void absolute(void* n) {
  struct BigInteger* z = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* m = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  int* r = (int*)malloc(sizeof(int));

  int mmi = 3;
  int mm;

  mm = memchk(mmi, z, m, r);

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

//Return signum distinctive
void gsignum(void* a, void* b, void* res) {
  struct BigInteger* z = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* o = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* m = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  int* k1 = (int*)malloc(sizeof(int));
  int* k2 = (int*)malloc(sizeof(int));

  int mmi = 5;
  int mm;

  mm = memchk(mmi, z, o, m, k1, k2);

  if (mm < 0)
    exit(-132);

  BImemcpy(z, 0);                     //z = 0;
  BImemcpy(o, 1);                     //o = 1;
  BImemcpy(m, -1);                    //m = -1;

  equals(a, z, k1);                   ////¿a < z? => k1
  equals(b, z, k2);                   ////¿b < z? => k2

  if (*k1 == 2 && *k2 == 2) {         //if(a < 0 && b < 0){
    BImemcpy(res, -1);                //  res = -1;
  }else if (*k1 == 1 && *k2 == 1) {   //}else if(a > 0 && b > 0){
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

//Performs factor * equation for each equation[i]
void gaussM(void* factor, void* equation) {
  int i = 0;

  for (i = 0; i < 4; i++)                               //for (i = 0; i < 3; i++) 
    mul(&((struct BigInteger*)equation)[i], factor);    //  equation[i] *= factor;
}

//Correlatively performs equation1[i] += equation2[i]
void gaussS(void* equation1, void* equation2) {
  int i = 0;

  for (i = 0; i < 4; i++)                                                             //for (i = 0; i < 3; i++) 
    add(&((struct BigInteger*)equation1)[i], &((struct BigInteger*)equation2)[i]);    //  equation1[i] += equation2[i];
}

//Solves a 2-degree equation (ax^2 + bx + c = 0)
void solve(void* dif, void* sols) {
  struct BigInteger* min = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* two = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* four = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* b2 = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* zro = (struct BigInteger*)malloc(sizeof(struct BigInteger));

  int mmi = 5;
  int mm;
  int ret;

  mm = memchk(mmi, min, two, four, b2, zro);

  if (mm < 0)
    exit(-301);

  //initialize data                                                               ////initialize data
  BImemcpy(min, -1);                                                              //min = -1;
  BImemcpy(two, 1);                                                               //two = 1;
  BImemcpy(zro, 0);                                                               //zro = 0;
  add(two, two);                                                                  //two++; (two = 2)

  memcpy(four, two, sizeof(struct BigInteger));                                   //four = two;
  add(four, four);                                                                //four = four + four; (four = 4)

  memcpy(b2, &((struct BigInteger*)dif)[1], sizeof(struct BigInteger));           //b2 = b;


  //b^2                                                                           ////b^2
  bipow(b2, 2);                                                                   //  pow(b2, 2);

  //4ac                                                                           ////4ac
  mul(four, &((struct BigInteger*)dif)[0]);                                       //  four *= a;
  mul(four, &((struct BigInteger*)dif)[2]);                                       //  four *= c;

  //b^2 - 4ac                                                                     ////b^2 - 4ac
  sub(b2, four);                                                                  //  b2 -= four;

  //sqrt(b^2 - 4ac)                                                               ////sqrt(b^2 - 4ac)
  nqrt(b2, 2);                                                                    //  b2 = sqrt(min);

  //2a                                                                            ////2a
  mul(two, &((struct BigInteger*)dif)[0]);                                        //  two *= a;

  //-b                                                                            ////-b
  mul(min, &((struct BigInteger*)dif)[1]);                                        //  min *= b;

  memcpy(&((struct BigInteger*)sols)[0], min, sizeof(struct BigInteger));         //sols[0] = min;
  memcpy(&((struct BigInteger*)sols)[1], min, sizeof(struct BigInteger));         //sols[1] = min;

  //-b + sqrt(b^2 - 4ac)                                                          ////-b + sqrt(b^2 - 4ac)
  add(&((struct BigInteger*)sols)[0], b2);                                        //  sols[0] += b2;

  //-b - sqrt(b^2 - 4ac)                                                          ////-b - sqrt(b^2 - 4ac)
  sub(&((struct BigInteger*)sols)[1], b2);                                        //  sols[1] -= b2;

  //(-b + sqrt(b^2 - 4ac)) / 2a                                                   ////(-b + sqrt(b^2 - 4ac)) / 2a
  dvs(&((struct BigInteger*)sols)[0], two);                                       //  sols[0] /= two;

  //(-b - sqrt(b^2 - 4ac)) / 2a                                                   ////(-b - sqrt(b^2 - 4ac)) / 2a
  dvs(&((struct BigInteger*)sols)[1], two);                                       //  sols[1] /= two;

  equals(&((struct BigInteger*)sols)[0], zro, &ret);

  free(min);
  free(two);
  free(four);
  free(b2);
  free(zro);

  if (ret == 0 || ret == 2) {
    //x1 solution <= 0
    _log("A solution reached 0 or below. Exiting thread", INFORMATIONAL);
    exit(0);
  }
}

//Calculate the distance of the CPC based on David Sole's CPC Theoreme
void distance(void* base, int z, int y, int s, void* res) {
  struct BigInteger* one = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* ten = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* hun = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* tho = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* biz = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* biy = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* bis = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* tmp = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  char* chz = (char*)malloc(sizeof(char) * 2);
  char* chy = (char*)malloc(sizeof(char) * 2);
  char* chs = (char*)malloc(sizeof(char) * 2);
  char* cmp;

  int mmi = 11;
  int mm;

  mm = memchk(mmi, ten, biz, biy, bis, tmp, chz, chy, chz, one, hun, tho);

  if (mm < 0)
    exit(-111);

  //initializations                                                               ////initializations
  BImemcpy(ten, 10);                                                              //ten = 10;
  BImemcpy(one, 1);                                                               //one = 1;
  BImemcpy(hun, 100);                                                             //hun = 100;
  BImemcpy(tho, 100);                                                             //tho = 100;

  iniStr(&cmp);

  mul(tho, ten);                                                                  //tho *= 10; (1000)

  //convert int to BI                                                             ////convert int to BI
  //z                                                                             ////z
  _itoa_s(z, chz, 2, 10);                                                         //z.toString();
  newBI(biz, chz, 0);                                                             //z.toBI();

  //y                                                                             ////y
  _itoa_s(y, chy, 2, 10);                                                         //y.toString();
  newBI(biy, chy, 0);                                                             //y.toBI();

  //s                                                                             ////s
  _itoa_s(s, chs, 2, 10);                                                         //s.toString();
  newBI(bis, chs, 0);                                                             //s.toBI();
  //add(bis, one);                                                                //bis += one;

  //a increase: 0                                                                 ////a increase: 0
  BImemcpy(&((struct BigInteger*)res)[0], 0);                                     //res[0] = 0;

  //b increase: 1000Z                                                             ////b increase: 10Z
  memcpy(&((struct BigInteger*)res)[1], biz, sizeof(struct BigInteger));          //res[1] = biz;
  mul(&((struct BigInteger*)res)[1], tho);                                        //res[1] *= tho;

  //c increase: ((Y * 100) - 1000) - (1000 * (Z - S))                             ////c increase: ((Y * 100) - 1000) - (1000 * (Z - S))
  //  Z - S                                                                       ////  Z - S
  memcpy(tmp, biz, sizeof(struct BigInteger));                                    //tmp = biz;
  sub(tmp, bis);                                                                  //tmp -= bis;

  toString(biz, cmp);
  _log("Z = %s", INFORMATIONAL, cmp);

  toString(bis, cmp);
  _log("S = %s", INFORMATIONAL, cmp);

  toString(tmp, cmp);
  _log("Z - S = %s", INFORMATIONAL, cmp);

  //  1000 * (Z - S)                                                              ////  1000 * (Z - S)
  mul(tmp, tho);                                                                  //tmp *= tho; 

  toString(tmp, cmp);
  _log("1000 * (Z - S) = %s", INFORMATIONAL, cmp);

  //  Y * 100                                                                     ////  Y * 100
  memcpy(&((struct BigInteger*)res)[2], biy, sizeof(struct BigInteger));          //res[2] = biy;
  mul(&((struct BigInteger*)res)[2], hun);                                        //res[2] *= hun

  toString(&((struct BigInteger*)res)[2], cmp);
  _log("Y * 100 = %s", INFORMATIONAL, cmp);

  //  (Y * 100) - 1000                                                            ////  (Y * 100) - 1000
  sub(&((struct BigInteger*)res)[2], tho);                                        //res[2] -= tho;

  toString(&((struct BigInteger*)res)[2], cmp);
  _log("(Y * 100) - 1000 = %s", INFORMATIONAL, cmp);

  //  ((Y * 100) - 1000) - (1000 * (Z - S))                                       ////  ((Y * 100) - 1000) - (1000 * (Z - S))
  sub(&((struct BigInteger*)res)[2], tmp);                                        //res[2] -= tmp;

  toString(&((struct BigInteger*)res)[2], cmp);
  _log("((Y * 100) - 1000) - (1000 * (Z - S)) = %s", INFORMATIONAL, cmp);

  free(one);
  free(ten);
  free(biz);
  free(biy);
  free(bis);
  free(tmp);
  free(chz);
  free(chs);
  free(chy);
  free(hun);
  free(tho);
}

//Check if given solutions fits for a * b = num, as initial x1 and x2 are axis-based data
int checkSolution(void* factor, int ending, void* num) {
  struct BigInteger* one = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* ten = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* fac = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* a = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* b = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* bending = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  int* pres = (int*)malloc(sizeof(int));
  char* ch = (char*)malloc(sizeof(char) * 2);
  char* str;
  int res;

  int mmi = 8;
  int mm;

  mm = memchk(mmi, one, ten, a, b, fac, pres, ch, bending);

  if (mm < 0)
    exit(-405);

  iniStr(&str);

  //inis                                                                          ////inis
  BImemcpy(one, 1);                                                               //one = 1;
  BImemcpy(ten, 10);                                                              //ten = 10;

  //conversion
  _itoa_s(ending, ch, 2, 10);                                                     //ending.toString();
  newBI(bending, ch, 0);                                                          //ending.toBI();


  memcpy(fac, factor, sizeof(struct BigInteger));                                 //fac = factor;
  memcpy(b, num, sizeof(struct BigInteger));                                      //b = num;

  sub(fac, one);                                                                  //--fac;
  mul(fac, ten);                                                                  //fac *= 10;
  add(fac, bending);                                                              //fac += ending;
  memcpy(a, fac, sizeof(struct BigInteger));                                      //a = fac;

  toString(fac, str);
  _log("factor: %s", INFORMATIONAL, str);

  dvs(b, fac);                                                                    //b /= fac;
  mul(b, a);                                                                      //b *= a;

  equals(b, num, pres);                                                           //pres = b.equals(num);

  memcpy(&res, pres, sizeof(int));

  free(one);
  free(ten);
  free(a);
  free(b);
  free(fac);
  free(pres);
  free(ch);
  free(bending);

  return res;
}

//Makes a printable String for the equation solution based on axis-data based
char* printSolution(void* factor, int ending, void* num) {
  struct BigInteger* one = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* ten = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* fac = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* a = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* b = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* bending = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  char* ret = (char*)malloc(sizeof(char) * 5000);
  char* xt1 = (char*)malloc(sizeof(char) * 5000);
  char* xt2 = (char*)malloc(sizeof(char) * 5000);
  char* ch = (char*)malloc(sizeof(char) * 2);

  int mmi = 10;
  int mm;

  mm = memchk(mmi, one, ten, a, b, fac, ch, bending, ret, xt1, xt2);

  if (mm < 0)
    exit(-405);

  //inis                                                                          ////inis
  BImemcpy(one, 1);                                                               //one = 1;
  BImemcpy(ten, 10);                                                              //ten = 10;

  //conversion
  _itoa_s(ending, ch, 2, 10);                                                     //ending.toString();
  newBI(bending, ch, 0);                                                          //ending.toBI();


  memcpy(fac, factor, sizeof(struct BigInteger));                                 //fac = factor;
  memcpy(b, num, sizeof(struct BigInteger));                                      //b = num;

  sub(fac, one);                                                                  //--fac;
  mul(fac, ten);                                                                  //fac *= 10;
  add(fac, bending);                                                              //fac += ending;
  memcpy(a, fac, sizeof(struct BigInteger));                                      //a = fac;
  dvs(b, fac);                                                                    //b /= fac;

  toString(a, xt1);
  toString(b, xt2);
  snprintf(ret, 5000, "<%s, %s>", xt1, xt2);

  free(one);
  free(ten);
  free(a);
  free(b);
  free(fac);
  free(ch);
  free(xt1);
  free(xt2);
  free(bending);

  return ret;
}

//Massive memory checking
int memchk(int n, ...) {
    va_list pa;
    va_start(pa, n);

    for (; n > 0; n--)
        if ((void*)va_arg(pa, size_t) == NULL)
            return -1 * n;

    return 0;
}

void testing() {
  exit(0);
}
