/*
 * RSAAnalyzer.c
 *
 *  Created on: 27 sep. 2020
 *      Author: DoHITB under MIT Liscense
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

int CUDA_ON =
#if IS_CUDA_ON == 1
1;
#else
0;
#endif


int main(int argc, char* argv[]) {
  //General values
  char number[4097];
  BigInteger* num = malloc(sizeof(BigInteger));
  BigInteger* n = malloc(sizeof(BigInteger));
  BigInteger* sqrtAprox1 = malloc(sizeof(BigInteger));
  BigInteger* sqrtAprox2 = malloc(sizeof(BigInteger));
  BigInteger* sqrtAprox3 = malloc(sizeof(BigInteger));
  BigInteger* sq1 = malloc(sizeof(BigInteger));
  BigInteger* sq2 = malloc(sizeof(BigInteger));
  BigInteger* sq3 = malloc(sizeof(BigInteger));
  BigInteger* chk = malloc(sizeof(BigInteger));
  BigInteger* res = malloc(sizeof(BigInteger));
  BigInteger* ant = malloc(sizeof(BigInteger));
  BigInteger* ten = malloc(sizeof(BigInteger));
  BigInteger* zro = malloc(sizeof(BigInteger));
  BigInteger* one = malloc(sizeof(BigInteger));
  int* arr1 = malloc(sizeof(int) * 2);
  int* arr2 = malloc(sizeof(int) * 2);
  int* arr3 = malloc(sizeof(int) * 2);
  int* eq = malloc(sizeof(int));
  BigInteger* tempVal = malloc(sizeof(BigInteger) * 3);
  BigInteger* data = malloc(sizeof(BigInteger) * 3);
  BigInteger* axis = malloc(sizeof(BigInteger) * 3);
  BigInteger* dif = malloc(sizeof(BigInteger) * 3);
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
  char* st4;
  char* st5;
  char* st6;
  int possi;

  //logging
  char* name;

  //Gather & calculate
  BigInteger* sqrtAprox = malloc(sizeof(BigInteger));
  BigInteger* sq = malloc(sizeof(BigInteger));
  int* arr = malloc(sizeof(int) * 2);
  int k;
  int z;
  int s;
  int op;
  int y;
  int zf;
  int rf;
  int ri = 0;

  //Equation solving
  BigInteger* sols = malloc(sizeof(BigInteger) * 2);

  //Iteration solving
  BigInteger* dist = malloc(sizeof(BigInteger) * 3);
  BigInteger* bist = malloc(sizeof(BigInteger) * 3);
  int exr = -1;
  int ext = 0;
  int* arrp = malloc(sizeof(int));

  //Beacon signal
  FILE* bcs; //send
  FILE* bcr; //receive
  int bcsl;
  int bcrl;
  char* out = malloc(sizeof(char) * 5000);

  //settings
  FILE* set;
  int setl;
  char setc;

  //debug
  int debug = 1;

  //counting
  BigInteger* i = malloc(sizeof(BigInteger));

  //memory pool
  struct memory* m = malloc(getMemorySize());

  //memory checking
  int mm;
  int mmi = 32;

  mm = memchk(mmi, num, n, sqrtAprox1, sqrtAprox2, sqrtAprox3, sq1, sq2, sq3, chk, res, ant, ten, zro, one, arr1, arr2, arr3,
    eq, tempVal, data, axis, dif, sqrtAprox, sq, arr, sols, dist, bist, out, i, m, arrp);

  if (mm < 0)
    exit(mm);

  //temporal
  if (debug == 2) {
    testing();
  }

  iniStr(&st1);
  iniStr(&st2);
  iniStr(&st3);
  iniStr(&st4);
  iniStr(&st5);
  iniStr(&st6);
  init(m);

  //inis
  BImemcpy(ten, 10);
  BImemcpy(zro, 0);
  BImemcpy(one, 1);
  BImemcpy(i, 0);

  //start tracing
  if (argc == 1) {
    activateLog(ERROR);
  } else {
    name = malloc(sizeof(char) * 5000);

    //num_arr_s.dat
    snprintf(name, 5000, "%s_%s_%s.log", argv[1], argv[2], argv[3]);

    if (debug == 0)
      setFile(name);

    activateLog(ERROR);
  }

  if (debug > 0)
    activateLog(INFORMATIONAL);

  setShowTime(1);

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

  _log("Searching for: %s", ERROR, st1);
  _log("Initial data: ", ERROR);

  inFunction();
  _log("getEnd: %i", ERROR, end);

  //get possible multiplies
  poss(1, end, arr1);
  poss(2, end, arr2);
  poss(3, end, arr3);

  _log("arr Values: ", ERROR);

  inFunction();
  _log("arr1: <%i, %i>", ERROR, arr1[0], arr1[1]);
  _log("arr2: <%i, %i>", ERROR, arr2[0], arr2[1]);
  _log("arr3: <%i, %i>", ERROR, arr3[0], arr3[1]);
  outFunction();

  //get associated k's
  k1 = getK(arr1);
  k2 = getK(arr2);
  k3 = getK(arr3);

  _log("k Values: ", ERROR);

  inFunction();
  _log("k1: %i", ERROR, k1);
  _log("k2: %i", ERROR, k2);
  _log("k3: %i", ERROR, k3);
  outFunction();

  //get z's
  mod = getModulus(num);

  _log("mod: %i", ERROR, mod);

  z1 = getZ(arr1, mod);
  z2 = getZ(arr2, mod);
  z3 = getZ(arr3, mod);

  _log("z Values: ", ERROR);

  inFunction();
  _log("z1: %i", ERROR, z1);
  _log("z2: %i", ERROR, z2);
  _log("z3: %i", ERROR, z3);
  outFunction();

  getSqrt(num, arr1, sqrtAprox1, m);
  getSqrt(num, arr2, sqrtAprox2, m);
  getSqrt(num, arr3, sqrtAprox3, m);

  memcpy(sq1, sqrtAprox1, sizeof(BigInteger));
  memcpy(sq2, sqrtAprox2, sizeof(BigInteger));
  memcpy(sq3, sqrtAprox3, sizeof(BigInteger));

  toString(sq1, st1);
  toString(sq2, st2);
  toString(sq3, st3);

  _log("sqrt Values: ", ERROR);

  inFunction();
  _log("sq1: %s", ERROR, st1);
  _log("sq2: %s", ERROR, st2);
  _log("sq3: %s", ERROR, st3);
  outFunction();
  outFunction();

  //debug override
  if (debug == 1) {
    argc = 2;
  }

  if (argc == 1) {
    /*************************************
     *******POOL GENERATION SECTION*******
     *************************************/

     //only an argument ==> generate pool
     //0               1   2    3
     //RSAAnalyzer.exe num #arr #S

     //delete previous files
    system("del.bat 2>nul");

    _log("", ERROR);
    _log("Base execution. Generating execution pool", ERROR);
    inFunction();

    _log("Starting waitlist...", ERROR);
    efl = fopen_s(&fl2, "waitlist.bat", "w+");

    if (efl < 0)
      exit(-103);

    fputs("@echo off\n", fl2);
    fputs("start /B RSAWaitList", fl2);
    fflush(fl2);
    fclose(fl2);

    _log("RSAWaitlist.exe started!", ERROR);
    system("waitlist.bat");

    /*
     * Params Table
     *
     * S will be downgraded by 1 as then it's upgraded
     * When S = 1 (arr[0] == arr[1]) we will move arr[1] - 1 as it's better for calculation
     *
     *+----------------------------------------+
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
     *+----------------------------------------+
     */

    plen = num->count; //num
    plen += 1; // \0 char
    plen += 4; // _#_#
    plen += 50; //exe name + extra space

    pool = malloc(sizeof(char) * plen);
    efl = fopen_s(&fl, "main.bat", "w+");

    if (efl < 0)
      exit(-102);

    fputs("@echo off\n", fl);

    //num
    toString(num, st1);

    if (arr1[0] > 0) {
      _log("First pair pool: ", ERROR);
      inFunction();
      //arr1 have data. Possible combinations:
      //{1, 1}, {1, 3}, {1, 7}, {1, 9} => S = arr1[1]
      for (pi = 0; pi < arr1[1]; pi++) {
        ppi = pi;

        if (ppi == 0)
          ppi = arr1[1];

        snprintf(pool, plen, "RSAAnalyzer.exe %s %i %i", st1, 1, ppi);
        _log("Command: %s", ERROR, pool);
        fputs("START /B ", fl);
        fputs(pool, fl);
        fputs("\n", fl);
      }

      outFunction();
    }

    if (arr2[0] > 0) {
      _log("Second pair pool: ", ERROR);
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
        _log("Command: %s", ERROR, pool);
        fputs("START /B ", fl);
        fputs(pool, fl);
        fputs("\n", fl);
      }

      outFunction();
    }

    if (arr3[0] > 0) {
      _log("Third pair pool: ", ERROR);
      inFunction();
      //arr3 have data. Possible combinations:
      //{9, 9}, {7, 7} => S = 1
      snprintf(pool, plen, "RSAAnalyzer.exe %s %i %i", st1, 3, arr3[1]);
      _log("Command: %s", ERROR, pool);
      fputs("START /B ", fl);
      fputs(pool, fl);
      fputs("\n", fl);
    }

    outFunction();
    outFunction();

    fflush(fl);
    fclose(fl);

    _log("Execution pool generated (main.bat)", ERROR);
    _log("Do not close this window. It will run on background and show the result on screen once done!", ERROR);
    _log("Starting the pool right now", ERROR);

    //start the pool
    system("main.bat");

    outFunction();
  } else {
    /************************************
     *****GATHER & CALCULATE SECTION*****
     ************************************/

     //Gather and calculate
     //0               1   2    3
     //RSAAnalyzer.exe num #arr #S
    BImemcpy(n, -1);

    if (debug == 0) {
      _log("", ERROR);
      _log("Index: %s, Serie: %s", ERROR, argv[2], argv[3]);

      op = atoi(argv[2]);
      s = atoi(argv[3]);
    } else {
      //Debug Override
      op = 1;
      s = 1;
    }

    if (op == 1) {
      memcpy(arr, arr1, sizeof(int) * 2);
      k = k1;
      z = z1;
      memcpy(sqrtAprox, sqrtAprox1, sizeof(BigInteger));
      memcpy(sq, sq1, sizeof(BigInteger));
    } else if (op == 2) {
      memcpy(arr, arr2, sizeof(int) * 2);
      k = k2;
      z = z2;
      memcpy(sqrtAprox, sqrtAprox2, sizeof(BigInteger));
      memcpy(sq, sq2, sizeof(BigInteger));
    } else if (op == 3) {
      memcpy(arr, arr3, sizeof(int) * 2);
      k = k3;
      z = z3;
      memcpy(sqrtAprox, sqrtAprox3, sizeof(BigInteger));
      memcpy(sq, sq3, sizeof(BigInteger));
    } else {
      exit(-2);
    }

    //get Y  and Z Factor
    y = getY(arr);
    zf = getZF(arr);
    axisFactor(sq, m);
    rf = relativeFactor(getS(arr), arr);
    ri = relativeFactorResult(getS(arr), sq, m);

    //dump data
    _log("Selected data {%i}:", ERROR, op);

    inFunction();
    toString(sqrtAprox, st1);
    toString(sq, st2);

    _log("arr: <%i, %i>", ERROR, arr[0], arr[1]);
    _log("k: %i", ERROR, k);
    _log("z: %i", ERROR, z);
    _log("sqrtAprox: %s", ERROR, st1);
    _log("Axis Factor: %s", ERROR, st2);
    _log("y: %i", ERROR, y);
    _log("z factor: %i", ERROR, zf);
    _log("s: %i", ERROR, s);
    _log("rf: %i", ERROR, rf);
    _log("ri: %i", ERROR, ri);
    _log("", ERROR);

    outFunction();

    _log("Gathering data...", ERROR);

    /* Data Gathering - START */
    getPonderated(num, arr[0], sqrtAprox, k, z, n, tempVal, m);

    //res = tempVal[0] * tempVal[1];
    memcpy(res, &tempVal[0], sizeof(BigInteger));
    mul(res, &tempVal[1], m);

    //chk = res - num
    memcpy(chk, res, sizeof(BigInteger));
    sub(chk, num, m);

    //done = true;
    done = 1;
    count = 0;

    //n = tempVal[2]
    memcpy(n, &tempVal[2], sizeof(BigInteger));

    //if rf = -1 means always store (arr[0] = arr[1])
    //if rf > 0 means that we have some "s" data.
    if (rf == -1 || ri % rf == (s - 1)) {
      //data[count] = chk
      memcpy(&data[count], chk, sizeof(BigInteger));

      //aixs[count] = sq
      memcpy(&axis[count], sq, sizeof(BigInteger));

      equals(&data[count], zro, m, eq);

      if (*eq == 0) {
        _log("That's a perfect square!", ERROR);
        exit(0);
      }

      ++count;
    }

    //ri holds a counter to check congruency with rf mod s
    ++ri;

    while (done == 1) {
      //ant = chk
      memcpy(ant, chk, sizeof(BigInteger));

      //sqrtAprox1 += 10;
      add(sqrtAprox, ten, m);

      //get next value
      getPonderated(num, arr[0], sqrtAprox, k, z, n, tempVal, m);

      //n = tempVal[2]
      memcpy(n, &tempVal[2], sizeof(BigInteger));

      //res = tempVal[0] * tempVal[1];
      memcpy(res, &tempVal[0], sizeof(BigInteger));
      mul(res, &tempVal[1], m);

      //chk = res - num
      memcpy(chk, res, sizeof(BigInteger));
      sub(chk, num, m);

      //if rf = -1 means always store (arr[0] = arr[1])
      //if rf > 0 means that we have some "s" data.
      if (rf == -1 || ri % rf == (s - 1)) {
        add(sq, one, m);

        //data[count] = chk
        memcpy(&data[count], chk, sizeof(BigInteger));

        //aixs[count] = sq
        memcpy(&axis[count], sq, sizeof(BigInteger));

        ++count;
      } else {
        //rf > 0 || rs % s != 0 => that means, have subseries and not time to store values
        if (count == 0) {
          //whereas we don't store any value, we keep treating sq as an auto-increment
          add(sq, one, m);
        }
      }

      equals(chk, zro, m, eq);

      if (*eq == 0) { //if(chk == 0)
        toString(&tempVal[0], st1);
        toString(&tempVal[1], st2);
        _log("DONE! <%s, %s>", ERROR, st1, st2);

        done = 0;
        exr = 0;
        ext = -1;

        //copy it to sols to get printed
        memcpy(&sols[0], &tempVal[0], sizeof(BigInteger));
        memcpy(&sols[1], &tempVal[1], sizeof(BigInteger));
      }

      //we only need 3 data samples
      if (count == 3) {
        _log("Data gathered", ERROR);
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
      regression(data, axis, dif, m);
      distance(dif, zf, y, s, dist, m);

      //dif holds "a", "b", and "c" params
      toString(&dif[0], st1);
      toString(&dif[1], st2);
      toString(&dif[2], st3);
      _log("dif: <%s, %s, %s>", INFORMATIONAL, st1, st2, st3);
      _log("Associated initial equation: %sx^2 + %sx + %s = 0", INFORMATIONAL, st1, st2, st3);

      toString(&dist[0], st1);
      toString(&dist[1], st2);
      toString(&dist[2], st3);
      _log("dist: <%s, %s, %s>", INFORMATIONAL, st1, st2, st3);

      _log("checking for lower limit", INFORMATIONAL);
      lowerLimit(dif, dist, m);

      toString(&dif[0], st1);
      toString(&dif[1], st2);
      toString(&dif[2], st3);
      _log("after lowerLimit...", INFORMATIONAL);
      _log("dif: <%s, %s, %s>", INFORMATIONAL, st1, st2, st3);

      _log("Hyperbolic-Potential limit...", INFORMATIONAL);
      hbBolzano(dif, dist, bist, m);

      inFunction();
      _log("Solving x...", INFORMATIONAL);

      solve(dif, sols, 1, m);

      toString(&sols[0], st4);
      toString(&sols[1], st5);
      _log("Solutions: <%s, %s>", INFORMATIONAL, st4, st5);

      _log("%s\t%s\t%s\t%s\t%s", INFORMATIONAL, st1, st2, st3, st4, st5);

      outFunction();

      //sols[0] * sols[1] = num?
      exr = checkSolution(&sols[0], arr, num, m, arrp);
    }

    //close log to make it accesible
    closeFile();

    add(i, one, m);

    if (CUDA_ON == 0) {
      //CPU mode. Iterate until a solution is found on any thread
      while (exr != 0) {
        //look for another threads' solution
        bcrl = fopen_s(&bcr, "RSAWL.dat", "r");

        if (bcrl == 0) {
          //a thread found a solution!
          ext = 1; //external = 1
          exr = 0; //stop iterate

          //close the file
          if (bcr != NULL)
            fclose(bcr);
        } else {
          //no thread found a solution. Keep searching
          toString(&dif[0], st1);
          toString(&dif[1], st2);
          toString(&dif[2], st3);
          _log("Invalid value for dif: <%s, %s, %s>", INFORMATIONAL, st1, st2, st3);
          _log("Searching for new values...", INFORMATIONAL);

          //get new values for dif
          add(&dif[0], &dist[0], m);
          add(&dif[1], &dist[1], m);
          add(&dif[2], &dist[2], m);

          toString(&dif[0], st1);
          toString(&dif[1], st2);
          toString(&dif[2], st3);
          _log("dif: <%s, %s, %s>", INFORMATIONAL, st1, st2, st3);
          _log("Associated equation: %sx^2 + %sx + %s = 0", INFORMATIONAL, st1, st2, st3);

          inFunction();
          _log("Solving x...", INFORMATIONAL);

          //solve new equation
          solve(dif, sols, 1, m);

          toString(&sols[0], st4);
          toString(&sols[1], st5);
          _log("Solutions: <%s, %s>", INFORMATIONAL, st4, st5);

          _log("%s\t%s\t%s\t%s\t%s", INFORMATIONAL, st1, st2, st3, st4, st5);

          outFunction();

          //sols[0] * sols[1] = num?
          exr = checkSolution(&sols[0], arr, num, m, arrp);

          //increase counter
          add(i, one, m);

          //finally, check for any settings:
          toString(i, st6);
          _log("%s\t%s\t%s\t%s\t%s\t{%s}", ERROR, st1, st2, st3, st4, st5, st6);

          setl = fopen_s(&set, "settings.txt", "r");

          if (setl == 0) {
            setc = fgetc(set);

            if (setc == 'p') {
              //p = print status
              toString(i, st6);
              _log("%s\t%s\t%s\t%s\t%s\t{%s}", ERROR, st1, st2, st3, st4, st5, st6);
            }
            else if (setc == 'x') {
              //x = quit
              toString(i, st6);
              _log("%s\t%s\t%s\t%s\t%s\t{%s}", ERROR, st1, st2, st3, st4, st5, st6);
              _log("Quitting as per user requirement", ERROR);

              //force remove
              remove("settings.txt");

              exit(0);
            }

            //close the file
            fclose(set);

            //then delete it
            remove("settings.txt");

            //close log file to make it accessible
            closeFile();
          }
        }
      }
    } else {
      //GPU mode.
      cudaMode(dif, dist, arr, num);

      exit(0);
    }

    //on this point, a solution has been found 
    if (ext == 0) {
      //found on this thread (on the loop)!
      //prepare text
      st1 = printSolution(&sols[0], arr, num, m, arrp);

      if (debug == 0) {
        snprintf(out, 5000, "%s_%s_%s.log: Solution %s", argv[1], argv[2], argv[3], st1);
        _log("%s", ERROR, out);
      }

      //write it on RSAWL.dat (open with w+ to avoid error during testing)
      bcsl = fopen_s(&bcs, "RSAWL.dat", "w+");

      if (bcsl < 0 || bcs == NULL)
        exit(-109);

      fputs(out, bcs);
      fflush(bcs);
      fclose(bcs);
    }
    else if (ext == -1) {
      //found on this thread (while gathering data)!
      //prepare text
      toString(&sols[0], st1);
      toString(&sols[1], st2);
      snprintf(out, 5000, "%s_%s_%s.log: Solution <%s, %s>", argv[1], argv[2], argv[3], st1, st2);
      _log("%s", ERROR, out);

      //write it on RSAWL.dat (open with w+ to avoid error during testing)
      bcsl = fopen_s(&bcs, "RSAWL.dat", "w+");

      if (bcsl < 0 || bcs == NULL)
        exit(-108);

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
  return ((BigInteger*)va)->n[0];
}

//Return relative arr values
void poss(int ind, int num, int* arr) {
  if (ind == 1) {
    arr[0] = n1[num];
    arr[1] = n2[num];
  }
  else if (ind == 2) {
    arr[0] = n3[num];
    arr[1] = n4[num];
  }
  else if (ind == 3) {
    arr[0] = n5[num];
    arr[1] = n6[num];
  }
  else {
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
  if (((BigInteger*)va)->count == 0)
    return ((BigInteger*)va)->n[0];

  return (((BigInteger*)va)->n[1] * 10) +
    (((BigInteger*)va)->n[0]);
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
void getSqrt(void* num, int* arr, void* res, void* m) {
  int gsEnd;
  int s;
  BigInteger* ten = malloc(sizeof(BigInteger));
  BigInteger* aux = malloc(sizeof(BigInteger));

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
  memcpy(res, num, sizeof(BigInteger));
  nqrt(res, 2, m);

  //get S factor
  s = getS(arr);

  //get sqrt(s), only if there are subseries
  if (relativeFactor(s, arr) > 0) {
    s = (int)(sqrt((double)s));

    //if s == 3, sqrt(s) will be 1, so we add an unit
    if (s == 1)
      ++s;
  }
  else
    s = 1;

  //convert s to BI
  aux->n[0] = s;
  aux->count = 0;

  //res *= aux
  mul(res, aux, m);

  //get the ending
  gsEnd = getEnd(res);

  //the ending is bigger? then skip to the next
  if (gsEnd > arr[1])
    add(res, ten, m); //res += 10;

//override ending with specific number
  ((BigInteger*)res)->n[0] = arr[1];

  free(ten);
  free(aux);
}

//Get Y value
int getY(int* arr) {
  /*
   * Params Table
   *
   *+----------------------------------------+
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
   *+----------------------------------------+
   */
  return arr[1];
}

//Get Z Factor
int getZF(int* arr) {
  /*
   * Params Table
   *
   *+----------------------------------------+
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
   *+----------------------------------------+
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
    }
    else {
      return 3;
    }
  }
  else if (arr[0] == 7) {
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
   *+----------------------------------------+
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
   *+----------------------------------------+
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
    }
    else {
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
void axisFactor(void* a, void* m) {
  BigInteger* ten = malloc(sizeof(BigInteger));
  BigInteger* one = malloc(sizeof(BigInteger));

  int mmi = 2;
  int mm;

  mm = memchk(mmi, ten, one);

  if (mm < 0)
    exit(-404);


  BImemcpy(ten, 10);                                                              //ten = 10;
  BImemcpy(one, 1);                                                               //one = 1;

  dvs(a, ten, m);                                                                 //a /= ten;
  add(a, one, m);                                                                 //a++;

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

//Returns sq % s
int relativeFactorResult(int s, void* sq, void* m) {
  BigInteger* tmp = malloc(sizeof(BigInteger));
  BigInteger* org = malloc(sizeof(BigInteger));
  int ret;

  if (tmp == NULL || org == NULL)
    exit(-602);

  BImemcpy(tmp, 0);                             //tmp = 0;
  tmp->n[0] = s;                                //tmp = s;
  memcpy(org, sq, sizeof(BigInteger));          //org = sq;

  dvs(org, tmp, m);                             //org /= tmp;
  mul(org, tmp, m);                             //org *= tmp;
  memcpy(tmp, sq, sizeof(BigInteger));          //tmp = sq;
  sub(tmp, org, m);                             //tmp -= org;

  ret = tmp->n[0];                              //ret = org;

  free(tmp);
  free(org);

  return ret;
}

//Return ponderated value based on David Sole's Theoreme
void getPonderated(void* num, int ia, void* b, int k, int z, void* n, void* res, void* m) {
  int ipR;
  int ipR0;
  BigInteger* pN = malloc(sizeof(BigInteger));
  BigInteger* min = malloc(sizeof(BigInteger));
  BigInteger* one = malloc(sizeof(BigInteger));
  BigInteger* ten = malloc(sizeof(BigInteger));
  BigInteger* hun = malloc(sizeof(BigInteger));
  BigInteger* a = malloc(sizeof(BigInteger));
  BigInteger* pTR = malloc(sizeof(BigInteger));
  BigInteger* pR0 = malloc(sizeof(BigInteger));
  BigInteger* pR = malloc(sizeof(BigInteger));
  BigInteger* pNH = malloc(sizeof(BigInteger));
  BigInteger* pRT = malloc(sizeof(BigInteger));
  BigInteger* pA0 = malloc(sizeof(BigInteger));
  BigInteger* pA1 = malloc(sizeof(BigInteger));
  BigInteger* stk0 = malloc(sizeof(BigInteger));
  BigInteger* stk1 = malloc(sizeof(BigInteger));
  BigInteger* stk2 = malloc(sizeof(BigInteger));
  int* ires = malloc(sizeof(int));
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

  equals(n, min, m, ires);                                                        ////¿n = -1? => res

  if (*ires == 0) {                                                               //if(n == -1){
    memcpy(pN, num, sizeof(BigInteger));                                          //  pN = num;
    dvs(pN, b, m);                                                                //  pN = pN / b;
    dvs(pN, hun, m);                                                              //  pN = pN / hun (100);
  }
  else {                                                                          //} else {
    memcpy(pN, n, sizeof(BigInteger));                                            //  pN = n;
  }                                                                               //}

  a->n[0] = ia;                                                                   //a = ia;
  pR0->n[0] = ipR0;                                                               //pR0 = ipR0;
  pR->n[0] = ipR;                                                                 //pR = ipR;

  memcpy(pTR, b, sizeof(BigInteger));                                             //pTR = b;
  sub(pTR, a, m);                                                                 //pTR = pTR - a;
  dvs(pTR, ten, m);                                                               //pTR = pTR / ten (10);
  mul(pTR, pR0, m);                                                               //pTR = pTR * pR0;

  add(pR, pTR, m);                                                                //pR = pR + pTR;

  memcpy(pNH, pN, sizeof(BigInteger));                                            //pNH = pN;
  mul(pNH, hun, m);                                                               //pNH = pNH * hun (100);

  memcpy(pRT, pR, sizeof(BigInteger));                                            //pRT = pR;
  mul(pRT, ten, m);                                                               //pRT = pRT * ten (10);

  memcpy(pA0, a, sizeof(BigInteger));                                             //pA0 = a;
  add(pA0, pNH, m);                                                               //pA0 = pA0 + pNH;
  add(pA0, pRT, m);                                                               //pA0 = pA0 + pRT;

  memcpy(pA1, b, sizeof(BigInteger));                                             //pA1 = b;

  //stk1 = ((((10 * pN--) + pR) * 10) + a)                                        //stk1 = ((((10 * pN--) + pR) * 10) + a)
  memcpy(stk1, pN, sizeof(BigInteger));                                           //  stk1 = pN;
  mul(stk1, ten, m);                                                              //  stk1 = pA0 * ten (10);
  add(stk1, pR, m);                                                               //  stk1 = pA0 * pR;
  mul(stk1, ten, m);                                                              //  stk1 = pA0 * ten (10);
  add(stk1, a, m);                                                                //  stk1 = pA0 + a;
  sub(pN, one, m);                                                                //  pN--;

  //stk2 = ((((10 * pN) + pR) * 10) + a)                                          //stk2 = ((((10 * pN) + pR) * 10) + a)
  memcpy(stk2, pN, sizeof(BigInteger));                                           //  stk2 = pN;
  mul(stk2, ten, m);                                                              //  stk2 = pA0 * ten (10);
  add(stk2, pR, m);                                                               //  stk2 = pA0 * pR;
  mul(stk2, ten, m);                                                              //  stk2 = pA0 * ten (10);
  add(stk2, a, m);                                                                //  stk2 = pA0 + a;

  add(pN, one, m);                                                                //pN++;

  mul(stk1, pA1, m);                                                              //stk1 *= pA1; {n0}
  mul(stk2, pA1, m);                                                              //stk2 *= pA1; {n1}

  //pN = (pN - ((num - n0) / (n0 - n1)))
  memcpy(stk0, stk1, sizeof(BigInteger));                                         //stk0 = stk1;

  sub(stk1, stk2, m);                                                             //stk1 -= stk2;
  sub(stk0, num, m);                                                              //stk1 -= num;
  dvs(stk0, stk1, m);                                                             //stk0 /= stk1;
  sub(pN, stk0, m);                                                               //pN -= stk0

  //pA0 = (((10 * pN + pR) * 10) + a);                                            //pA0 = (((10 * pN + pR) * 10) + a);
  memcpy(pA0, pN, sizeof(BigInteger));                                            //  pA0 = pN;
  mul(pA0, ten, m);                                                               //  pA0 = pA0 * ten (10);
  add(pA0, pR, m);                                                                //  pA0 = pA0 * pR;
  mul(pA0, ten, m);                                                               //  pA0 = pA0 * ten (10);
  add(pA0, a, m);                                                                 //  pA0 = pA0 + a;

  memcpy(&((BigInteger*)res)[0], pA0, sizeof(BigInteger));                       //res[0] = pA0;
  memcpy(&((BigInteger*)res)[1], pA1, sizeof(BigInteger));                       //res[1] = pA1;
  memcpy(&((BigInteger*)res)[2], pN, sizeof(BigInteger));                        //res[2] = pN;

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
int isEqual(void* va, void* vb, void* n, void* m) {
  BigInteger* r = malloc(sizeof(BigInteger));
  int* k = malloc(sizeof(int));
  int x;
  int mm;

  mm = memchk(2, r, k);

  if (mm < 0) {
    _log("Error", ERROR);
    exit(-110);
  }

  memcpy(r, va, sizeof(BigInteger));          //r = va;

  mul(r, vb, m);                              //r = r * vb;
  equals(r, n, m, k);                         // ¿r = n? => k

  memcpy(&x, k, sizeof(int));                 //x = k

  free(r);
  free(k);

  return x;
}

//Performs QR regression, then solve it via Gauss
void regression(void* data, void* axis, void* dif, void* m) {
  BigInteger* sxi1 = malloc(sizeof(BigInteger));
  BigInteger* sxi2 = malloc(sizeof(BigInteger));
  BigInteger* sxi3 = malloc(sizeof(BigInteger));
  BigInteger* sxi4 = malloc(sizeof(BigInteger));
  BigInteger* syi = malloc(sizeof(BigInteger));
  BigInteger* sxi1yi = malloc(sizeof(BigInteger));
  BigInteger* sxi2yi = malloc(sizeof(BigInteger));
  BigInteger* axisn = malloc(sizeof(BigInteger));
  BigInteger* three = malloc(sizeof(BigInteger));
  BigInteger* eq1 = malloc(sizeof(BigInteger) * 4);
  BigInteger* eq2 = malloc(sizeof(BigInteger) * 4);
  BigInteger* eq3 = malloc(sizeof(BigInteger) * 4);
  BigInteger* f1 = malloc(sizeof(BigInteger) * 4);
  BigInteger* f2 = malloc(sizeof(BigInteger) * 4);
  BigInteger* f3 = malloc(sizeof(BigInteger) * 4);
  BigInteger* a = malloc(sizeof(BigInteger) * 4);
  BigInteger* b = malloc(sizeof(BigInteger) * 4);
  BigInteger* c = malloc(sizeof(BigInteger) * 4);

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
    add(sxi1, &((BigInteger*)axis)[i], m);                                        //  sxi1 += axis[i];
    add(syi, &((BigInteger*)data)[i], m);                                         //  syi += data[i];

    memcpy(axisn, &((BigInteger*)axis)[i], sizeof(BigInteger));                   //  axisn = axis[i];

    mul(axisn, &((BigInteger*)axis)[i], m);                                       //  axisn *= axis[i] (axisn^2);
    add(sxi2, axisn, m);                                                          //  sxi2 += axisn;

    mul(axisn, &((BigInteger*)axis)[i], m);                                       //  axisn *= axis[i] (axisn^3);
    add(sxi3, axisn, m);                                                          //  sxi3 += axisn;

    mul(axisn, &((BigInteger*)axis)[i], m);                                       //  axisn *= axis[i] (axisn^4);
    add(sxi4, axisn, m);                                                          //  sxi4 += axisn;

    memcpy(axisn, &((BigInteger*)axis)[i], sizeof(BigInteger));                   //  axisn = axis[i];
    mul(axisn, &((BigInteger*)data)[i], m);                                       //  axisn *= data[i];
    add(sxi1yi, axisn, m);                                                        //  sxi1yi += axisn;

    mul(axisn, &((BigInteger*)axis)[i], m);                                       //  axisn *= axis[i] (axisn^2);
    add(sxi2yi, axisn, m);                                                        //  sxi2yi += axisn;
  }                                                                               //}

  BImemcpy(axisn, 1);                                                             //axisn = 1;
  add(three, axisn, m);                                                           // three++;
  add(three, axisn, m);                                                           // three++;

  //build equations                                                               ////build equations
  //equation 1                                                                    ////equation 1
  memcpy(&eq1[0], three, sizeof(BigInteger));                                     //eq1[0] = 3;
  memcpy(&eq1[1], sxi1, sizeof(BigInteger));                                      //eq1[1] = sxi1;
  memcpy(&eq1[2], sxi2, sizeof(BigInteger));                                      //eq1[2] = sxi2;
  memcpy(&eq1[3], syi, sizeof(BigInteger));                                       //eq1[3] = syi;

  //equation 2
  memcpy(&eq2[0], sxi1, sizeof(BigInteger));                                      //eq2[0] = sxi1;
  memcpy(&eq2[1], sxi2, sizeof(BigInteger));                                      //eq2[1] = sxi2;
  memcpy(&eq2[2], sxi3, sizeof(BigInteger));                                      //eq2[2] = sxi3;
  memcpy(&eq2[3], sxi1yi, sizeof(BigInteger));                                    //eq2[3] = sxi1yi;

  //equation 3
  memcpy(&eq3[0], sxi2, sizeof(BigInteger));                                      //eq3[0] = sxi2;
  memcpy(&eq3[1], sxi3, sizeof(BigInteger));                                      //eq3[1] = sxi3;
  memcpy(&eq3[2], sxi4, sizeof(BigInteger));                                      //eq3[2] = sxi4;
  memcpy(&eq3[3], sxi2yi, sizeof(BigInteger));                                    //eq3[3] = sxi2yi;

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
  memcpy(f3, &eq1[0], sizeof(BigInteger));                                        //f3 = eq1[0];
  absolute(f3, m);                                                                //f3 = absolute(f3);
  mul(f1, f3, m);                                                                 //f1 *= f3;

  memcpy(f2, &eq2[0], sizeof(BigInteger));                                        //f2 = eq2[0];
  absolute(f2, m);                                                                //f2 = absolute(f2);

  gaussM(f1, eq2, m);                                                             //gaussM(f1, eq2);
  gaussM(f2, eq1, m);                                                             //gaussM(f2, eq1);
  gaussS(eq2, eq1, m);                                                            //gaussS(eq2, eq1);

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
  memcpy(f3, &eq1[0], sizeof(BigInteger));                                        //f3 = eq1[0];
  absolute(f3, m);                                                                //f3 = absolute(f3);
  mul(f1, f3, m);                                                                 //f1 *= f3;

  memcpy(f2, &eq3[0], sizeof(BigInteger));                                        //f2 = eq3[0];
  absolute(f2, m);                                                                //f2 = absolute(f2);

  gaussM(f1, eq3, m);                                                             //gaussM(f1, eq3);
  gaussM(f2, eq1, m);                                                             //gaussM(f2, eq1);
  gaussS(eq3, eq1, m);                                                            //gaussS(eq3, eq1);

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
  memcpy(f3, &eq2[1], sizeof(BigInteger));                                        //f3 = eq2[1];
  absolute(f3, m);                                                                //f3 = absolute(f3);
  mul(f1, f3, m);                                                                 //f1 *= f3;

  memcpy(f2, &eq1[1], sizeof(BigInteger));                                        //f2 = eq1[1];
  absolute(f2, m);                                                                //f2 = absolute(f2);

  gaussM(f1, eq1, m);                                                             //gaussM(f1, eq1);
  gaussM(f2, eq2, m);                                                             //gaussM(f2, eq2);
  gaussS(eq1, eq2, m);                                                            //gaussS(eq1, eq2);

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
  memcpy(f3, &eq2[1], sizeof(BigInteger));                                        //f3 = eq2[1];
  absolute(f3, m);                                                                //f3 = absolute(f3);
  mul(f1, f3, m);                                                                 //f1 *= f3;

  memcpy(f2, &eq3[1], sizeof(BigInteger));                                        //f2 = eq3[1];
  absolute(f2, m);                                                                //f2 = absolute(f2);

  gaussM(f1, eq3, m);                                                             //gaussM(f1, eq3);
  gaussM(f2, eq2, m);                                                             //gaussM(f2, eq2);
  gaussS(eq3, eq2, m);                                                            //gaussS(eq3, eq2);

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
  memcpy(f3, &eq3[2], sizeof(BigInteger));                                        //f3 = eq3[2];
  absolute(f3, m);                                                                //f3 = absolute(f3);
  mul(f1, f3, m);                                                                 //f1 *= f3;

  memcpy(f2, &eq1[2], sizeof(BigInteger));                                        //f2 = eq1[2];
  absolute(f2, m);                                                                //f2 = absolute(f2);

  gaussM(f1, eq1, m);                                                             //gaussM(f1, eq1);
  gaussM(f2, eq3, m);                                                             //gaussM(f2, eq3);
  gaussS(eq1, eq3, m);                                                            //gaussS(eq1, eq3);

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
  memcpy(f3, &eq3[2], sizeof(BigInteger));                                        //f3 = eq3[2];
  absolute(f3, m);                                                                //f3 = absolute(f3);
  mul(f1, f3, m);                                                                 //f1 *= f3;

  memcpy(f2, &eq2[2], sizeof(BigInteger));                                        //f2 = eq2[2];
  absolute(f2, m);                                                                //f2 = absolute(f2);

  gaussM(f1, eq2, m);                                                             //gaussM(f1, eq2);
  gaussM(f2, eq3, m);                                                             //gaussM(f2, eq3);
  gaussS(eq2, eq3, m);                                                            //gaussS(eq2, eq3);

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

  memcpy(c, &eq1[3], sizeof(BigInteger));                                         //c = eq1[3];
  memcpy(b, &eq2[3], sizeof(BigInteger));                                         //b = eq2[3];
  memcpy(a, &eq3[3], sizeof(BigInteger));                                         //a = eq3[3];

  dvs(c, &eq1[0], m);                                                             //c /= eq1[0];
  dvs(b, &eq2[1], m);                                                             //b /= eq2[1];
  dvs(a, &eq3[2], m);                                                             //a /= eq3[2];

  toString(a, st1);                                                               ///*
  toString(b, st2);                                                               // * Display a, b, c
  toString(c, st3);                                                               // *
  _log("a: %s", INFORMATIONAL, st1);                                              // *
  _log("b: %s", INFORMATIONAL, st2);                                              // *
  _log("c: %s", INFORMATIONAL, st3);                                              // */

  memcpy(&((BigInteger*)dif)[0], a, sizeof(BigInteger));                          //dif[0] = a;
  memcpy(&((BigInteger*)dif)[1], b, sizeof(BigInteger));                          //dif[1] = b;
  memcpy(&((BigInteger*)dif)[2], c, sizeof(BigInteger));                          //dif[2] = c;

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
void absolute(void* n, void* y) {
  BigInteger* z = malloc(sizeof(BigInteger));
  BigInteger* m = malloc(sizeof(BigInteger));
  int* r = malloc(sizeof(int));

  int mmi = 3;
  int mm;

  mm = memchk(mmi, z, m, r);

  if (mm < 0)
    exit(-131);

  BImemcpy(z, 0);     //z = 0;
  BImemcpy(m, -1);    //m = -1;

  equals(n, z, m, r); ////¿n < z? => r

  if (*r == 2)        //if(n < z)
    mul(n, m, y);     //  n *= m;

  free(z);
  free(m);
  free(r);
}

//Return signum distinctive
void gsignum(void* a, void* b, void* res) {
  BigInteger* z = malloc(sizeof(BigInteger));
  BigInteger* o = malloc(sizeof(BigInteger));
  BigInteger* m = malloc(sizeof(BigInteger));
  int* k1 = malloc(sizeof(int));
  int* k2 = malloc(sizeof(int));

  int mmi = 5;
  int mm;

  mm = memchk(mmi, z, o, m, k1, k2);

  if (mm < 0)
    exit(-132);

  BImemcpy(z, 0);                     //z = 0;
  BImemcpy(o, 1);                     //o = 1;
  BImemcpy(m, -1);                    //m = -1;

  equals(a, z, m, k1);                ////¿a < z? => k1
  equals(b, z, m, k2);                ////¿b < z? => k2

  if (*k1 == 2 && *k2 == 2) {         //if(a < 0 && b < 0){
    BImemcpy(res, -1);                //  res = -1;
  }
  else if (*k1 == 1 && *k2 == 1) {    //}else if(a > 0 && b > 0){
    BImemcpy(res, -1);                //  res = -1;
  }
  else {                              //}else{
    BImemcpy(res, 1);                 //  res = 1;
  }                                   //}

  free(z);
  free(o);
  free(m);
  free(k1);
  free(k2);
}

//Performs factor * equation for each equation[i]
void gaussM(void* factor, void* equation, void* m) {
  int i = 0;

  for (i = 0; i < 4; i++)                               //for (i = 0; i < 3; i++) 
    mul(&((BigInteger*)equation)[i], factor, m);        //  equation[i] *= factor;
}

//Correlatively performs equation1[i] += equation2[i]
void gaussS(void* equation1, void* equation2, void* m) {
  int i = 0;

  for (i = 0; i < 4; i++)                                                             //for (i = 0; i < 3; i++) 
    add(&((BigInteger*)equation1)[i], &((BigInteger*)equation2)[i], m);               //  equation1[i] += equation2[i];
}

//Solves a 2-degree equation (ax^2 + bx + c = 0)
void solve(void* dif, void* sols, int check, void* m) {
  BigInteger* min = malloc(sizeof(BigInteger));
  BigInteger* two = malloc(sizeof(BigInteger));
  BigInteger* four = malloc(sizeof(BigInteger));
  BigInteger* b2 = malloc(sizeof(BigInteger));
  BigInteger* zro = malloc(sizeof(BigInteger));

  int mmi = 5;
  int mm;
  int ret;

  mm = memchk(mmi, min, two, four, b2, zro);

  if (mm < 0)
    exit(-301);

  //initialize data                                                               ////initialize data
  BImemcpy(min, -1);                                                              //min = -1;
  BImemcpy(two, 2);                                                               //two = 2;
  BImemcpy(zro, 0);                                                               //zro = 0;
  BImemcpy(four, 4);                                                              //four = 4;

  memcpy(b2, &((BigInteger*)dif)[1], sizeof(BigInteger));                         //b2 = b;


  //b^2                                                                           ////b^2
  bipow(b2, 2, m);                                                                //  pow(b2, 2);

  //4ac                                                                           ////4ac
  mul(four, &((BigInteger*)dif)[0], m);                                           //  four *= a;
  mul(four, &((BigInteger*)dif)[2], m);                                           //  four *= c;

  //b^2 - 4ac                                                                     ////b^2 - 4ac
  sub(b2, four, m);                                                               //  b2 -= four;

  //sqrt(b^2 - 4ac)                                                               ////sqrt(b^2 - 4ac)
  nqrt(b2, 2, m);                                                                 //  b2 = sqrt(min);

  //2a                                                                            ////2a
  mul(two, &((BigInteger*)dif)[0], m);                                            //  two *= a;

  //-b                                                                            ////-b
  mul(min, &((BigInteger*)dif)[1], m);                                            //  min *= b;

  memcpy(&((BigInteger*)sols)[0], min, sizeof(BigInteger));                       //sols[0] = min;
  memcpy(&((BigInteger*)sols)[1], min, sizeof(BigInteger));                       //sols[1] = min;

  //-b + sqrt(b^2 - 4ac)                                                          ////-b + sqrt(b^2 - 4ac)
  add(&((BigInteger*)sols)[0], b2, m);                                            //  sols[0] += b2;

  //-b - sqrt(b^2 - 4ac)                                                          ////-b - sqrt(b^2 - 4ac)
  sub(&((BigInteger*)sols)[1], b2, m);                                            //  sols[1] -= b2;

  //(-b + sqrt(b^2 - 4ac)) / 2a                                                   ////(-b + sqrt(b^2 - 4ac)) / 2a
  dvs(&((BigInteger*)sols)[0], two, m);                                           //  sols[0] /= two;

  //(-b - sqrt(b^2 - 4ac)) / 2a                                                   ////(-b - sqrt(b^2 - 4ac)) / 2a
  dvs(&((BigInteger*)sols)[1], two, m);                                           //  sols[1] /= two;

  equals(&((BigInteger*)sols)[0], zro, m, &ret);

  free(min);
  free(two);
  free(four);
  free(b2);
  free(zro);

  if (check > 0) {
    if (ret == 0 || ret == 2) {
      //x1 solution <= 0
      _log("A solution reached 0 or below. Exiting thread", ERROR);
      exit(0);
    }
  }
}

//Calculate the distance of the CPC based on David Sole's CPC Theoreme
void distance(void* base, int z, int y, int s, void* res, void* m) {
  BigInteger* one = malloc(sizeof(BigInteger));
  BigInteger* ten = malloc(sizeof(BigInteger));
  BigInteger* hun = malloc(sizeof(BigInteger));
  BigInteger* tho = malloc(sizeof(BigInteger));
  BigInteger* biz = malloc(sizeof(BigInteger));
  BigInteger* biy = malloc(sizeof(BigInteger));
  BigInteger* bis = malloc(sizeof(BigInteger));
  BigInteger* tmp = malloc(sizeof(BigInteger));
  char* chz = malloc(sizeof(char) * 2);
  char* chy = malloc(sizeof(char) * 2);
  char* chs = malloc(sizeof(char) * 2);

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

  mul(tho, ten, m);                                                               //tho *= 10; (1000)

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
  BImemcpy(&((BigInteger*)res)[0], 0);                                            //res[0] = 0;

  //b increase: 1000Z                                                             ////b increase: 10Z
  memcpy(&((BigInteger*)res)[1], biz, sizeof(BigInteger));                        //res[1] = biz;
  mul(&((BigInteger*)res)[1], tho, m);                                            //res[1] *= tho;

  //c increase: ((Y * 100) - 1000) - (1000 * (Z - S))                             ////c increase: ((Y * 100) - 1000) - (1000 * (Z - S))
  //  Z - S                                                                       ////  Z - S
  memcpy(tmp, biz, sizeof(BigInteger));                                           //tmp = biz;
  sub(tmp, bis, m);                                                               //tmp -= bis;

  //  1000 * (Z - S)                                                              ////  1000 * (Z - S)
  mul(tmp, tho, m);                                                               //tmp *= tho; 

  //  Y * 100                                                                     ////  Y * 100
  memcpy(&((BigInteger*)res)[2], biy, sizeof(BigInteger));                        //res[2] = biy;
  mul(&((BigInteger*)res)[2], hun, m);                                            //res[2] *= hun

  //  (Y * 100) - 1000                                                            ////  (Y * 100) - 1000
  sub(&((BigInteger*)res)[2], tho, m);                                            //res[2] -= tho;

  //  ((Y * 100) - 1000) - (1000 * (Z - S))                                       ////  ((Y * 100) - 1000) - (1000 * (Z - S))
  sub(&((BigInteger*)res)[2], tmp, m);                                            //res[2] -= tmp;

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
int checkSolution(void* factor, int* ending, void* num, void* m, int* arrp) {
  BigInteger* one = malloc(sizeof(BigInteger));
  BigInteger* ten = malloc(sizeof(BigInteger));
  BigInteger* fac = malloc(sizeof(BigInteger));
  BigInteger* a = malloc(sizeof(BigInteger));
  BigInteger* b = malloc(sizeof(BigInteger));
  BigInteger* bending = malloc(sizeof(BigInteger));
  int* pres = malloc(sizeof(int));
  char* ch = malloc(sizeof(char) * 2);
  int res;

  int mmi = 8;
  int mm;

  mm = memchk(mmi, one, ten, a, b, fac, pres, ch, bending);

  if (mm < 0)
    exit(-405);

  //First number                                                                  ////First number
  *arrp = 0;                                                                      //arrp = 0;

  //inis                                                                          ////inis
  BImemcpy(one, 1);                                                               //one = 1;
  BImemcpy(ten, 10);                                                              //ten = 10;

  //conversion
  _itoa_s(ending[0], ch, 2, 10);                                                  //ending[0].toString();
  newBI(bending, ch, 0);                                                          //ending[0].toBI();

  memcpy(fac, factor, sizeof(BigInteger));                                        //fac = factor;
  memcpy(b, num, sizeof(BigInteger));                                             //b = num;

  sub(fac, one, m);                                                               //--fac;
  mul(fac, ten, m);                                                               //fac *= 10;
  add(fac, bending, m);                                                           //fac += ending;
  memcpy(a, fac, sizeof(BigInteger));                                             //a = fac;

  dvs(b, fac, m);                                                                 //b /= fac;
  mul(b, a, m);                                                                   //b *= a;

  equals(b, num, m, pres);                                                        //pres = b.equals(num);

  if (*pres != 0) {                                                               //if (*pres != 0) {
    //first value did not satisfy the equation. Try second one                    //  //first value did not satisfy the equation. Try second one
    *arrp = 1;                                                                    //  arrp = 1;

    //conversion                                                                  //  //conversion
    _itoa_s(ending[1], ch, 2, 10);                                                //  ending[1].toString();
    newBI(bending, ch, 0);                                                        //  ending[1].toBI();

    memcpy(fac, factor, sizeof(BigInteger));                                      //  fac = factor;
    memcpy(b, num, sizeof(BigInteger));                                           //  b = num;

    sub(fac, one, m);                                                             //  --fac;
    mul(fac, ten, m);                                                             //  fac *= 10;
    add(fac, bending, m);                                                         //  fac += ending;
    memcpy(a, fac, sizeof(BigInteger));                                           //  a = fac;

    dvs(b, fac, m);                                                               //  b /= fac;
    mul(b, a, m);                                                                 //  b *= a;

    equals(b, num, m, pres);                                                      //  pres = b.equals(num);
  }                                                                               //}

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
char* printSolution(void* factor, int* ending, void* num, void* m, int* arrp) {
  BigInteger* one = malloc(sizeof(BigInteger));
  BigInteger* ten = malloc(sizeof(BigInteger));
  BigInteger* fac = malloc(sizeof(BigInteger));
  BigInteger* a = malloc(sizeof(BigInteger));
  BigInteger* b = malloc(sizeof(BigInteger));
  BigInteger* bending = malloc(sizeof(BigInteger));
  char* ret = malloc(sizeof(char) * 5000);
  char* xt1 = malloc(sizeof(char) * 5000);
  char* xt2 = malloc(sizeof(char) * 5000);
  char* ch = malloc(sizeof(char) * 2);

  int mmi = 10;
  int mm;

  mm = memchk(mmi, one, ten, a, b, fac, ch, bending, ret, xt1, xt2);

  if (mm < 0)
    exit(-405);

  //inis                                                                          ////inis
  BImemcpy(one, 1);                                                               //one = 1;
  BImemcpy(ten, 10);                                                              //ten = 10;

  //conversion
  _itoa_s(ending[*arrp], ch, 2, 10);                                              //ending[arrp].toString();
  newBI(bending, ch, 0);                                                          //ending[arrp].toBI();


  memcpy(fac, factor, sizeof(BigInteger));                                        //fac = factor;
  memcpy(b, num, sizeof(BigInteger));                                             //b = num;

  sub(fac, one, m);                                                               //--fac;
  mul(fac, ten, m);                                                               //fac *= 10;
  add(fac, bending, m);                                                           //fac += ending;
  memcpy(a, fac, sizeof(BigInteger));                                             //a = fac;
  dvs(b, fac, m);                                                                 //b /= fac;

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

//Modifies dif to get the lower limit, solving inequation b^2 < 4ac
void lowerLimit(void* dif, void* dist, void* m) {
  /*
   * "a" is a constant, we'll name it "k"
   *
   * "b" will depend on "m + nz" formula, on which:
   *    p = dif[1] ("b" value from initial equation)
   *    q = dist[1] (increment on "b" for each "z" value)
   *
   * so, "b = dif[1] + dist[1] * z"
   *
   * "c" will depend on "-o -pz" formula, on which:
   *    o = dif[2] ("c" value from initial equation)
   *    p = dist[2] (decrement on "c" for each "z" value)
   *
   * so, "c = dif[2] + dist[2] * z" (as both dif and dist are negative we can omit the sign)
   *
   *
   * To solve the inequation, first we make it an equation
   *
   *    b^2 = 4ac
   *
   * Then, replace "a", "b", and "c" for their formulas
   *
   *    (dif[1] + dist[1] * z)^2 = 4 * (k) * (dif[2] + dist[2] * z);
   *
   * We can simplfy 4 * k => q (also contract the "*" markers to make it easier
   *
   *    (dif[1] + dist[1]z)^2 = q * (dif[2] + dist[2]z);
   *
   * Now, expand both sides
   *
   *    dif[1]^2 + dist[1]^2z^2 + 2dif[1]dist[1]z = qdif[2] + qdist[2]z;
   *
   * We have a 2nd-degree equation. Arrange the things:
   *
   *    dif[1]^2 + dist[1]^2z^2 + 2dif[1]dist[1]z - qdif[2] - qdist[2]z = 0;
   *
   * Now simplify temrs and rearrange:
   *
   *    (dist[1]^2z^2) + (2dif[1]dist[1]z - qdist[2]z) + (dif[1]^2 - qdif[2]) = 0;
   *
   * Make new variables
   *
   *    j = dist[1]^2;
   *    l = (2 * dif[1] * dist[1]) - (q * dist[2])
   *    t = (dif[1]^2) - (q * dif[2])
   *
   * Now we have classical equation
   *
   *    jz^2 + lz + t = 0
   *
   * Only left to solve for "z".
   *
   * Exceptional case: this equation may lead to non-real solution.
   * In this case, both solutions will have a 0 value; then we will search
   * for the minimum value of (dif[1] + dist[1] * z)^2 by geting its derivative.
   *
   * f(x) = (dif[1] + dist[1] * z)^2;
   *
   * dif[1] = w;
   * dist[1] = y;
   *
   * f(x) = (w + yz)^2;
   * f(x) = w^2 + (y^2z^2) + 2wyz;
   * f'(x) = 2(y^2)z + 2wy;
   *
   * We search for f'(x) = 0, so
   *
   * 2y^2z = -2wy;
   * z = -2wy / 2(y^2)
   *
   */
  BigInteger* q = malloc(sizeof(BigInteger));
  BigInteger* j = malloc(sizeof(BigInteger));
  BigInteger* l = malloc(sizeof(BigInteger));
  BigInteger* t = malloc(sizeof(BigInteger));
  BigInteger* four = malloc(sizeof(BigInteger));
  BigInteger* two = malloc(sizeof(BigInteger));
  BigInteger* aux1 = malloc(sizeof(BigInteger));
  BigInteger* aux2 = malloc(sizeof(BigInteger));
  BigInteger* vals = malloc(sizeof(BigInteger) * 3);
  BigInteger* sols = malloc(sizeof(BigInteger) * 2);

  char* st;

  int mmi;
  int mm = 10;

  mmi = memchk(mm, q, j, four, two, l, aux1, t, aux2, vals, sols);

  if (mmi < 0)
    exit(-700);

  iniStr(&st);

  BImemcpy(four, 4);                                                              //four = 4;
  BImemcpy(two, 2);                                                               //two = 2;
  memcpy(q, &((BigInteger*)dif)[0], sizeof(BigInteger));                          //q = dif[0];

  //Calculate q = 4 * k                                                           ////Calculate q = 4 * k
  mul(q, four, m);                                                                //q *= four;

  //Calculate j = dist[1]^2                                                       ////Calculate j = dist[1]^2
  memcpy(j, &((BigInteger*)dist)[1], sizeof(BigInteger));                         //j = dist[1];
  bipow(j, 2, m);                                                                 //j = j^2;

  //Calculate l = (2 * dif[1] * dist[1]) - (q * dist[2])                          ////Calculate l = (2 * dif[1] * dist[1]) - (q * dist[2])
  memcpy(l, &((BigInteger*)dif)[1], sizeof(BigInteger));                          //l = dif[1];
  mul(l, two, m);                                                                 //l *= two;
  mul(l, &((BigInteger*)dist)[1], m);                                             //l *= dist[1];

  memcpy(aux1, q, sizeof(BigInteger));                                            //aux1 = q;
  mul(aux1, &((BigInteger*)dist)[2], m);                                          //aux1 *= dist[2];

  sub(l, aux1, m);                                                                //l -= aux1;

  //Calculate t = (dif[1]^2) - (q * dif[2])                                       ////Calculate t = (dif[1]^2) - (q * dif[2])
  memcpy(t, &((BigInteger*)dif)[1], sizeof(BigInteger));                          //t = dif[1];
  bipow(t, 2, m);                                                                 //t = t^2;

  memcpy(aux2, q, sizeof(BigInteger));                                            //aux2 = q;
  mul(aux2, &((BigInteger*)dif)[2], m);                                           //aux2 *= dif[2];

  sub(t, aux2, m);                                                                //t -= aux2;

  //solve the equation                                                            ////solve the equation
  memcpy(&vals[0], j, sizeof(BigInteger));                                        //vals[0] = j;
  memcpy(&vals[1], l, sizeof(BigInteger));                                        //vals[1] = l;
  memcpy(&vals[2], t, sizeof(BigInteger));                                        //vals[2] = t;

  solve(vals, sols, 0, m);                                                        //solve(vals, sols, 0);

  toString(&((BigInteger*)sols)[0], st);
  _log("sol 1: %s", INFORMATIONAL, st);

  toString(&((BigInteger*)sols)[1], st);
  _log("sol 2: %s", INFORMATIONAL, st);

  /*
   * The optimal value will be on sols[0].
   * We step back sols[1] steps, as:
   *   * dif[0] = dif[0];
   *   * dif[1] = dif[1] + sols[1] * dist[1];
   *   * dif[2] = dif[2] + sols[1] * dist[2];
   *
   * We use "+" as sols[1] will always be 0 or lower.
   */

   //dif[1] offset                                                                ////dif[1] offset
  memcpy(aux1, &((BigInteger*)sols)[0], sizeof(BigInteger));                      //aux1 = sols[0];
  mul(aux1, &((BigInteger*)dist)[1], m);                                          //aux1 *= dist[1];
  add(&((BigInteger*)dif)[1], aux1, m);                                           //dif[1] += aux1;

  //dif[2] offset                                                                 ////dif[2] offset
  memcpy(aux2, &((BigInteger*)sols)[0], sizeof(BigInteger));                      //aux2 = sols[0];
  mul(aux2, &((BigInteger*)dist)[2], m);                                          //aux2 *= dist[2];
  add(&((BigInteger*)dif)[2], aux2, m);                                           //dif[2] += aux;


  free(q);
  free(j);
  free(four);
  free(two);
  free(l);
  free(aux1);
  free(t);
  free(aux2);
  free(vals);
  free(sols);
}

//Gets the hyperbolic jump limit using Bolzano aproximation
void hbBolzano(void* dif, void* dist, void* bist, void* m) {
  /*
   * The consecutive solutions for quadratic equation works on a hpyerbolic-potential way.
   * So, there's a point on which ceiling values for solutions begin to repeat; at first
   * they repeat twice, then three times, and each new value have more repetition count.
   *
   * The goal of this function is to get the first repeated value, which means the end of
   * hyperbolic-potential function.
   *
   * To achieve this, we'll perform Bolzano's approach. That means, we will start increasing
   * values until we found a repeated one, then get back 10^n-1 values until we don't found
   * any repeated values.
   *
   * On this point, we get forward 10^n-1 values to ensuer we're after the hyperbolic-potential
   * loop, and then perform the same with 10^n-2 values (and so on).
   */
  BigInteger* offset = malloc(sizeof(BigInteger));
  BigInteger* base = malloc(sizeof(BigInteger));
  BigInteger* ten = malloc(sizeof(BigInteger));
  BigInteger* one = malloc(sizeof(BigInteger));
  BigInteger* zero = malloc(sizeof(BigInteger));
  BigInteger* aux1 = malloc(sizeof(BigInteger));
  BigInteger* aux2 = malloc(sizeof(BigInteger));
  BigInteger* fst = malloc(sizeof(BigInteger));
  BigInteger* scd = malloc(sizeof(BigInteger));
  BigInteger* trd = malloc(sizeof(BigInteger));
  BigInteger* sols = malloc(sizeof(BigInteger) * 2);

  int* chk = malloc(sizeof(int));
  int cnt = 0;
  char* st1;

  int mmi = 12;
  int mm;

  mm = memchk(mmi, offset, base, ten, one, aux1, aux2, fst, scd, trd, sols, chk, zero);

  if (mm < 0)
    exit(-450);

  //inits
  BImemcpy(one, 1);                                                                                         //one = 1;
  BImemcpy(ten, 10);                                                                                        //ten = 10;
  BImemcpy(zero, 0);                                                                                        //zero = 0;

  iniStr(&st1);

  *chk = -1;                                                                                                //*chk = -1;

  _log("Bolzano starts", INFORMATIONAL);

  //Get the fisrt value that crosses hb-p part                                                              ////Get the fisrt value that crosses hb-p part
  memcpy(base, ten, sizeof(BigInteger));                                                                    //base = ten;

  //We need to get 3 consecutive values to check...                                                         ////We need to get 3 consecutive values to check...
  while (*chk != 0) {                                                                                       //while (*chk != 0){
    //copy values to bist                                                                                   //  //copy values to bist
    memcpy(&((BigInteger*)bist)[0], &((BigInteger*)dif)[0], sizeof(BigInteger));                            //  bist[0] = dif[0];
    memcpy(&((BigInteger*)bist)[1], &((BigInteger*)dif)[1], sizeof(BigInteger));                            //  bist[1] = dif[1];
    memcpy(&((BigInteger*)bist)[2], &((BigInteger*)dif)[2], sizeof(BigInteger));                            //  bist[2] = dif[2];

    //FIRST VALUE                                                                                           //  //FIRST VALUE
    //bist[1] offset                                                                                        //  //bist[1] offset                                                                
    memcpy(aux1, base, sizeof(BigInteger));                                                                 //  aux1 = base;
    mul(aux1, &((BigInteger*)dist)[1], m);                                                                  //  aux1 *= dist[1];
    add(&((BigInteger*)bist)[1], aux1, m);                                                                  //  bist[1] += aux1;

    //bist[2] offset                                                                                        //  //bist[2] offset                                                           
    memcpy(aux2, base, sizeof(BigInteger));                                                                 //  aux2 = base;
    mul(aux2, &((BigInteger*)dist)[2], m);                                                                  //  aux2 *= dist[2]
    add(&((BigInteger*)bist)[2], aux2, m);                                                                  //  bist[2] += aux2;

    //solve equation                                                                                        //  //solve equation
    solve(bist, sols, 0, m);                                                                                //  solve(bist, sols, 0);

    //Bolzano will be applied on the potential way (sols[0]).                                               //  //Bolzano will be applied on the potential way (sols[0]).
    memcpy(fst, &((BigInteger*)sols)[0], sizeof(BigInteger));                                               //  fst = sols[0];

    //SECOND VALUE                                                                                          //  //SECOND VALUE
    add(&((BigInteger*)bist)[1], &((BigInteger*)dist)[1], m);                                               //  bist[1] += dist[1];
    add(&((BigInteger*)bist)[2], &((BigInteger*)dist)[2], m);                                               //  bist[2] += dist[2];
    solve(bist, sols, 0, m);                                                                                //  solve(bist, sols, 0);
    memcpy(scd, &((BigInteger*)sols)[0], sizeof(BigInteger));                                               //  scd = sols[0];

    //THIRD VALUE                                                                                           //  //THIRD VALUE
    add(&((BigInteger*)bist)[1], &((BigInteger*)dist)[1], m);                                               //  bist[1] += dist[1];
    add(&((BigInteger*)bist)[2], &((BigInteger*)dist)[2], m);                                               //  bist[2] += dist[2];
    solve(bist, sols, 0, m);                                                                                //  solve(bist, sols, 0);
    memcpy(trd, &((BigInteger*)sols)[0], sizeof(BigInteger));                                               //  trd = sols[0];

    /*                                                                                                      //  /*
     * Now we compare the values                                                                            //   * Now we compare the values
     *                                                                                                      //   *
     * If a == b ==> n, n, ?                                                                                //   * If a == b ==> n, n, ?
     * If b == c ==> ?, n, n                                                                                //   * If b == c ==> ?, n, n
     */                                                                                                     //   */
    equals(fst, scd, m, chk);                                                                               //  fst = scd?

    if (*chk == 0) {                                                                                        //  if(fst == scd) {
      //fst == scd                                                                                          //    //fst == scd
      toString(base, st1);
      _log("Bolzano approach: %s", ERROR, st1);
    }
    else {                                                                                                  //  } else {
      equals(scd, trd, m, chk);                                                                             //    scd = trd?

      if (*chk == 0) {                                                                                      //    if(scd == trd) {
        //scd == trd                                                                                        //      //scd == trd
        toString(base, st1);
        _log("Bolzano approach: %s", ERROR, st1);
      }
      else {                                                                                                //    } else {
     //fst != scd != trd; increase base                                                                     //      //fst != scd != trd; increase base
        mul(base, ten, m);                                                                                  //      base *= ten;
      }                                                                                                     //    }
    }                                                                                                       //  }
  }                                                                                                         //}

  /*                                                                                                        ///*
   * Once got on this point, we have [base / 10 < n < base].                                                // * Once got on this point, we have [base / 10 < n < base].
   * We will get a more accurated range [base / 10 < n < (base / 10) + k * (base / 100)]                    // * We will get a more accurated range [base / 10 < n < (base / 10) + k * (base / 100)]
   *                                                                                                        // *
   * In other words, we will keep subtracting base / 10 from base until there's no equal values,            // * In other words, we will keep subtracting base / 10 from base until there's no equal values,
   * then add base / 10 to base.                                                                            // * then add base / 10 to base.
   */                                                                                                       // */
  memcpy(offset, base, sizeof(BigInteger));                                                                 //base = offset;

  //reduce the base                                                                                         ////reduce the base
  dvs(base, ten, m);                                                                                        //base /= ten;
  sub(offset, base, m);                                                                                     //offset -= base;

  while (cnt != 9) {                                                                                        //while (cnt != 9) {
    //restart counters                                                                                      //  //restart counters
    *chk = 0;                                                                                               //  *chk = 0;
    cnt = 0;                                                                                                //  cnt = 0;

    while (*chk == 0) {                                                                                     //  while (*chk == 0) {
      //copy values to bist                                                                                 //    //copy values to bist
      memcpy(&((BigInteger*)bist)[0], &((BigInteger*)dif)[0], sizeof(BigInteger));                          //    bist[0] = dif[0];
      memcpy(&((BigInteger*)bist)[1], &((BigInteger*)dif)[1], sizeof(BigInteger));                          //    bist[1] = dif[1];
      memcpy(&((BigInteger*)bist)[2], &((BigInteger*)dif)[2], sizeof(BigInteger));                          //    bist[2] = dif[2]; 

      //FIRST VALUE                                                                                         //    //FIRST VALUE
      //bist[1] offset                                                                                      //    //bist[1] offset     
      memcpy(aux1, offset, sizeof(BigInteger));                                                             //    aux1 = base;
      mul(aux1, &((BigInteger*)dist)[1], m);                                                                //    aux1 *= dist[1];
      add(&((BigInteger*)bist)[1], aux1, m);                                                                //    bist[1] += aux1;

      //bist[2] offset                                                                                      //    //bist[2] offset     
      memcpy(aux2, offset, sizeof(BigInteger));                                                             //    aux2 = base;
      mul(aux2, &((BigInteger*)dist)[2], m);                                                                //    aux2 *= dist[2]
      add(&((BigInteger*)bist)[2], aux2, m);                                                                //    bist[2] += aux2;

      //solve equation                                                                                      //    //solve equation
      solve(bist, sols, 0, m);                                                                              //    solve(bist, sols, 0);

      memcpy(fst, &((BigInteger*)sols)[0], sizeof(BigInteger));                                             //    fst = sols[0];

      //SECOND VALUE                                                                                        //    //SECOND VALUE
      add(&((BigInteger*)bist)[1], &((BigInteger*)dist)[1], m);                                             //    bist[1] += dist[1];
      add(&((BigInteger*)bist)[2], &((BigInteger*)dist)[2], m);                                             //    bist[2] += dist[2];
      solve(bist, sols, 0, m);                                                                              //    solve(bist, sols, 0);
      memcpy(scd, &((BigInteger*)sols)[0], sizeof(BigInteger));                                             //    scd = sols[0];

      //THIRD VALUE                                                                                         //    //THIRD VALUE
      add(&((BigInteger*)bist)[1], &((BigInteger*)dist)[1], m);                                             //    bist[1] += dist[1];
      add(&((BigInteger*)bist)[2], &((BigInteger*)dist)[2], m);                                             //    bist[2] += dist[2];
      solve(bist, sols, 0, m);                                                                              //    solve(bist, sols, 0);
      memcpy(trd, &((BigInteger*)sols)[0], sizeof(BigInteger));                                             //    trd = sols[0];

      /*                                                                                                    //    /*
       * Now we compare the values                                                                          //     * Now we compare the values
       *                                                                                                    //     *
       * If a == b ==> n, n, ?                                                                              //     * If a == b ==> n, n, ?
       * If b == c ==> ?, n, n                                                                              //     * If b == c ==> ?, n, n
       *                                                                                                    //     *
       * We keed decreasing until there're not equal values                                                 //     * We keed decreasing until there're not equal values
       */                                                                                                   //     */
      equals(fst, scd, m, chk);                                                                             //    fst == scd?

      if (*chk == 0) {                                                                                      //    if(fst == scd) {
        //fst == scd; decrease base                                                                         //      //fst == scd; decrease base
        sub(offset, base, m);                                                                               //      offset -= base;
      }
      else {                                                                                                //    } else {
        equals(scd, trd, m, chk);                                                                           //      scd == trd?

        if (*chk == 0) {                                                                                    //      if(scd == trd) {
          //scd == trd; decrease base                                                                       //        //scd == trd; decrease base
          sub(offset, base, m);                                                                             //        offset -= base;
        }
        else {                                                                                              //      } else {
       //fst != scd != trd; got it                                                                          //        //fst != scd != trd; got it
          toString(offset, st1);
          _log("Bolzano approach break: %s", ERROR, st1);
        }                                                                                                   //      }
      }                                                                                                     //    }

      //try count                                                                                           //    //try count
      ++cnt;                                                                                                //    ++cnt;

      //if we tried 9 times and no break found, we have the value                                           //    //if we tried 9 times and no break found, we have the value
      if (cnt == 9) {                                                                                       //    if (cnt == 9) {
        *chk = 0;                                                                                           //      *chk = 0;
      }                                                                                                     //    }
    }                                                                                                       //  }

    //jump to next value to ensure range                                                                    //  //jump to next value to ensure range
    add(offset, base, m);                                                                                   //  offset += base;
    dvs(base, ten, m);                                                                                      //  base /= ten;

    //restart offset                                                                                        //  //restart offset
    sub(offset, base, m);                                                                                   //  offset -= base;

    equals(base, zero, m, chk);                                                                             //  base == zero?

    //if base = one, we're done                                                                             //  //if base = one, we're done
    if (*chk == 0) {                                                                                        //  if (*chk == 0) {
      cnt = 9;                                                                                              //    cnt = 9;
    }                                                                                                       //  }
  }                                                                                                         //}

  toString(offset, st1);
  _log("Hyperbolic-Potential limit (axis): %s", ERROR, st1);

  toString(trd, st1);
  _log("Hyperbolic-Potential limit (value): %s", ERROR, st1);

  add(trd, offset, m);
  toString(trd, st1);
  _log("Theorical maximum iterations: %s", ERROR, st1);


  free(offset);
  free(base);
  free(ten);
  free(one);
  free(zero);
  free(aux1);
  free(aux2);
  free(fst);
  free(scd);
  free(trd);
  free(sols);
  free(chk);
  free(st1);
}

//dumps a file and starts cuda engine
static void cudaMode(void* dif, void* dist, int* arr, void* num) {
  FILE* f;
  int fl;
  char* st1;
  char* st2;
  char* st3;
  char* st4;
  char* st5;
  char* st6;
  char* st7;
  BigInteger* ha = malloc(sizeof(BigInteger));
  BigInteger* hb = malloc(sizeof(BigInteger));
  BigInteger* hc = malloc(sizeof(BigInteger));
  BigInteger* hd = malloc(sizeof(BigInteger));
  BigInteger* he = malloc(sizeof(BigInteger));
  BigInteger* hf = malloc(sizeof(BigInteger));
  BigInteger* min = malloc(sizeof(BigInteger));
  BigInteger* two = malloc(sizeof(BigInteger));
  BigInteger* four = malloc(sizeof(BigInteger));
  BigInteger* tmp = malloc(sizeof(BigInteger));
  struct memory* m = malloc(getMemorySize());

  iniStr(&st1);
  iniStr(&st2);
  iniStr(&st3);
  iniStr(&st4);
  iniStr(&st5);
  iniStr(&st6);
  iniStr(&st7);
  init(m);

  //dif[0] = k
  memcpy(ha, &((BigInteger*)dif)[0], sizeof(BigInteger));
  toString(ha, st1);
  printf("k: %s\n", st1);

  //dif[1] = p
  //dif[2] = r
  memcpy(ha, &((BigInteger*)dif)[2], sizeof(BigInteger));
  toString(ha, st1);
  printf("r: %s\n", st1);

  //dist[0] = -
  //dist[1] = q
  //dist[2] = s
  memcpy(ha, &((BigInteger*)dist)[2], sizeof(BigInteger));
  toString(ha, st1);
  printf("s: %s\n", st1);

  BImemcpy(min, -1);
  BImemcpy(two, 2);
  BImemcpy(four, 4);

  //ha = p
  memcpy(ha, &((BigInteger*)dif)[1], sizeof(BigInteger));

  //hb = -q
  memcpy(hb, &((BigInteger*)dist)[1], sizeof(BigInteger));
  mul(hb, min, m);

  //hc = q^2
  memcpy(hc, &((BigInteger*)dist)[1], sizeof(BigInteger));
  bipow(hc, 2, m);

  //hd = 2pq + 4ks
  memcpy(hd, &((BigInteger*)dist)[1], sizeof(BigInteger));
  mul(hd, &((BigInteger*)dif)[1], m);
  mul(hd, two, m); //2pq
  memcpy(tmp, &((BigInteger*)dif)[0], sizeof(BigInteger));
  mul(tmp, four, m);
  mul(tmp, &((BigInteger*)dist)[2], m);
  mul(tmp, min, m); //4ks
  add(hd, tmp, m); //2pq + 4ks

  //he = p^2 - 4kr
  memcpy(he, &((BigInteger*)dif)[1], sizeof(BigInteger));
  bipow(he, 2, m); //p^2

  memcpy(tmp, &((BigInteger*)dif)[0], sizeof(BigInteger));
  mul(tmp, four, m);
  mul(tmp, &((BigInteger*)dif)[2], m); //4kr

  sub(he, tmp, m); //p^2 - 4kr

  //hf = 2k
  memcpy(hf, &((BigInteger*)dif)[0], sizeof(BigInteger));
  mul(hf, two, m);

  /*
  toString(&((BigInteger*)dif)[0], st1);
  toString(&((BigInteger*)dif)[1], st2);
  toString(&((BigInteger*)dif)[2], st3);
  toString(&((BigInteger*)dist)[0], st4);
  toString(&((BigInteger*)dist)[1], st5);
  toString(&((BigInteger*)dist)[2], st6);
  toString(num, st7);
  */

  toString(ha, st1);
  toString(hb, st2);
  toString(hc, st3);
  toString(hd, st4);
  toString(he, st5);
  toString(hf, st6);
  toString(num, st7);

  fl = fopen_s(&f, "cuda_var.dat", "w+");

  if (fl != 0)
    exit(-905);

  fprintf_s(f, "%s %s %s %s %s %s %i %i %s", st1, st2, st3, st4, st5, st6, arr[0], arr[1], st7);
  fflush(f);
  fclose(f);

  free(st1);
  free(st2);
  free(st3);
  free(st4);
  free(st5);
  free(st6);
  free(st7);
  free(f);
  free(ha);
  free(hb);
  free(hc);
  free(hd);
  free(he);
  free(hf);
  free(min);
  free(two);
  free(four);
  free(tmp);
  free(m);
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
