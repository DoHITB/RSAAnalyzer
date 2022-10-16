/*
 * EQSolver.cu
 *
 *  Created on: 30 nov. 2020
 *      Author: DoHITB under MIT Liscense
 * 
 *  CHANGELOG
 *    v1.1: General revision. Several bugs found, code identation, comments, etc.
 *          Added a small improvement on performance by checking remainder of sqrt.
 *          Use of BigInteger.cu (custom!)
 *          Added mcd usage
 *          Added hyperbolic axis limit
 *          Added memory check
 */
#include "conio.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "BigInteger.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

 /////////////////////////// FUNCTION DEFINITION ///////////////////////////
void mcd(void* a, void* b, void* m);
__global__ void kernelCal(void* x, void* y, void* n, void* a, void* b, void* c, void* d, void* e, void* f, void* xa, void* xb, void* o, void* m, void* ax, void* num, int* arr, volatile void* r);
__device__ int checkSolution(void* va, void* vb, void* xa, void* xb, int* arr, void* num);

int main(int argc, char* argv[]) {
  //////////// HOST DATA ////////////
  //file read
  FILE* fl;
  int efl;

  //kernel control
  int cn;
  int cm;

  if (argc > 1) {
    cn = atoi(argv[1]);
    cm = atoi(argv[2]);
  } else {
    cn = 32;
    cm = 4096;
  }

  //heap memory control
  size_t maxMem;

  //HOST data
  char* st1 = (char*)malloc(sizeof(char) * MAX_LENGTH);
  int* harr = (int*)malloc(sizeof(int) * 2);
  BigInteger* hnum = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* ho = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* ha = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* hb = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* hc = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* hd = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* he = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* hf = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* hn = (BigInteger*)malloc(sizeof(BigInteger) * cn * cm);
  BigInteger* zro = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* hr = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* hmcd = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* hmce = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* haxis = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* hvalue = (BigInteger*)malloc(sizeof(BigInteger));
  int hi = 0;
  cudaError_t cuerr;
  char* st = (char*)malloc(sizeof(char) * MAX_LENGTH);
  memory* hm = (memory*)malloc(getMemorySize());

  //////////// DEVICE DATA ////////////
  //BI Creation
  char* dst;
  BigInteger* a;
  BigInteger* b;
  BigInteger* c;
  BigInteger* d;
  BigInteger* e;
  BigInteger* f;
  BigInteger* n;
  BigInteger* o;
  BigInteger* x;
  BigInteger* y;
  BigInteger* m;
  BigInteger* ax;
  BigInteger* vl;
  BigInteger* num;
  int* arr;

  //AUX
  BigInteger* xa;
  BigInteger* xb;

  //Linkage
  BigInteger* r;

  init((void**)hm);
  newBI(zro, "0", 0);

  cudaDeviceGetLimit(&maxMem, cudaLimitMallocHeapSize);
  cudaDeviceSetLimit(cudaLimitMallocHeapSize, maxMem);
  printf("Heap memory set result: %s\n", cudaGetErrorString(cudaGetLastError()));
  printf("Kernel <<<%i, %i>>> will be launched\n", cn, cm);

  //get data from file
  efl = fopen_s(&fl, "cuda_var.dat", "r");

  if (efl != 0)
    exit(-1);

  //init DEVICE data
  cuerr = cudaMalloc(&dst, sizeof(char) * MAX_LENGTH);

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&arr, sizeof(int) * 2);

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&a, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&b, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&c, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&d, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&e, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&f, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&n, sizeof(BigInteger) * cn * cm);

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&o, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&x, sizeof(BigInteger) * cn * cm);

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&y, sizeof(BigInteger) * cn * cm);

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&num, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&xa, sizeof(BigInteger) * cn * cm);

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&xb, sizeof(BigInteger) * cn * cm);

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&r, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&m, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&ax, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMalloc(&vl, sizeof(BigInteger));

  if (cuerr != 0) {
    printf("Error on malloc: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  printf("CLOCKS PER SECOND: %i\n", CLOCKS_PER_SEC);
  printf("Data allocation - Start @%i\n", clock());
  printf("\t Allocated memory:\n");
  printf("\t\t%i BigInteger\n", (5 * cn * cm) + 12);
  printf("\t\t2-position int array\n");
  printf("\t\t1025-position char array\n");

  //a, b, c, d, e, f
  fscanf_s(fl, "%s", st1, MAX_LENGTH);
  newBI(ha, st1, 0);

  fscanf_s(fl, "%s", st1, MAX_LENGTH);
  newBI(hb, st1, 0);

  fscanf_s(fl, "%s", st1, MAX_LENGTH);
  newBI(hc, st1, 0);

  fscanf_s(fl, "%s", st1, MAX_LENGTH);
  newBI(hd, st1, 0);

  fscanf_s(fl, "%s", st1, MAX_LENGTH);
  newBI(he, st1, 0);

  fscanf_s(fl, "%s", st1, MAX_LENGTH);
  newBI(hf, st1, 0);

  //arr
  fscanf_s(fl, "%i", &harr[0]);
  fscanf_s(fl, "%i", &harr[1]);

  //num
  fscanf_s(fl, "%s", st1, MAX_LENGTH);
  newBI(hnum, st1, 0);

  fscanf_s(fl, "%s", st1, MAX_LENGTH);
  newBI(haxis, st1, 0);

  fscanf_s(fl, "%s", st1, MAX_LENGTH);
  newBI(hvalue, st1, 0);

  fclose(fl);

  //n (number)
  for (hi = 0; hi < (cn * cm); hi++) {
    _itoa_s(hi, st1, 10, 10);
    newBI(&hn[hi], st1, 0);
  }

  //o (offset)
  _itoa_s((cn * cm), st1, 10, 10);
  newBI(ho, st1, 0);

  //r (return)
  newBI(hr, "0", 0);

  //Before copying to device, reduce the number by using mcd
  memcpy(hmcd, he, sizeof(BigInteger));                                    //hmcd = he;
  memcpy(hmce, hd, sizeof(BigInteger));                                    //hmce = hd;
  mcd(hmcd, hmce, hm);                                                     //hmcd = mcd(hmcd, hmce);

  memcpy(hmce, hc, sizeof(BigInteger));                                    //hmce = hc;
  mcd(hmcd, hmce, hm);                                                     //hmcd = mcd(hmcd, hmce);

  //Once we have mcd, divide all three values by mcd
  dvs(he, hmcd, hm);                                                       //he /= hmcd;
  dvs(hd, hmcd, hm);                                                       //hd /= hmcd;
  dvs(hc, hmcd, hm);                                                       //hc /= hmcd;

  //copy from HOTST to DEVICE
  cuerr = cudaMemcpy(a, ha, sizeof(BigInteger), cudaMemcpyHostToDevice);           //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(b, hb, sizeof(BigInteger), cudaMemcpyHostToDevice);           //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(c, hc, sizeof(BigInteger), cudaMemcpyHostToDevice);           //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(d, hd, sizeof(BigInteger), cudaMemcpyHostToDevice);           //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(e, he, sizeof(BigInteger), cudaMemcpyHostToDevice);           //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(f, hf, sizeof(BigInteger), cudaMemcpyHostToDevice);           //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(arr, harr, sizeof(int) * 2, cudaMemcpyHostToDevice);          //2 (int)

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(num, hnum, sizeof(BigInteger), cudaMemcpyHostToDevice);       //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(n, hn, sizeof(BigInteger) * cn * cm, cudaMemcpyHostToDevice); //cn * cm

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(o, ho, sizeof(BigInteger), cudaMemcpyHostToDevice);           //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(r, hr, sizeof(BigInteger), cudaMemcpyHostToDevice);           //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(m, hmcd, sizeof(BigInteger), cudaMemcpyHostToDevice);         //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(ax, haxis, sizeof(BigInteger), cudaMemcpyHostToDevice);         //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaMemcpy(vl, hvalue, sizeof(BigInteger), cudaMemcpyHostToDevice);         //1

  if (cuerr != 0) {
    printf("Error on copy: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  cuerr = cudaDeviceSynchronize();
  printf("Data allocation - End @%i\n", clock());

  //once reached here, the HOST memory can be free'd
  free(ha);
  free(hb);
  free(hc);
  free(hd);
  free(he);
  free(hf);
  free(ho);
  free(hn);
  free(harr);
  free(hnum);
  free(hmcd);
  free(hmce);
  free(haxis);
  free(hvalue);

  kernelCal <<<cn, cn >>>(x, y, n, a, b, c, d, e, f, xa, xb, o, m, ax, num, arr, r);
  cuerr = cudaDeviceSynchronize();

  if (cuerr != 0) {
    printf("Error on sync: %s\n", cudaGetErrorString(cuerr));
    exit(-1);
  }

  //copy r to HOST
  cudaMemcpy(hr, r, sizeof(BigInteger), cudaMemcpyDeviceToHost);

  //check if found
  equals(hr, zro, &hi);
  toString(hr, st1);

  if (hi == 0) {
    printf("Result don't found under hiperbolic limit\n");
    printf("Factor is between [%s, 1]\n", st1);
  } else {
    printf("RESULT: %s\n", st1);
  }
  
  return 0;
}


void mcd(void* a, void* b, void* m) {
  BigInteger* t = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* z = (BigInteger*)malloc(sizeof(BigInteger));
  BigInteger* d = (BigInteger*)malloc(sizeof(BigInteger));

  int* r = (int*)malloc(sizeof(int));

  BImemcpy(z, 0);                           //z = 0;

  equals(a, b, r);                          //a > b?

  if (*r == 2) {
    //a < b, change order
    memcpy(d, a, sizeof(BigInteger));       //d = a;
    memcpy(a, b, sizeof(BigInteger));       //a = b;
    memcpy(b, d, sizeof(BigInteger));       //b = d;
  }

  equals(b, z, r);                          //b = 0?

  while (*r != 0) {
    memcpy(t, b, sizeof(BigInteger));       //  t = b;
    mod(a, b, m);                           //  a %= b;
    memcpy(b, a, sizeof(BigInteger));       //  b = a;
    memcpy(a, t, sizeof(BigInteger));       //  a = t;
    equals(b, z, r);                        //  b = 0?
  }

  free(t);
  free(z);
  free(d);
  free(r);
}

/////////////////////////// CALCULATION DEFINITION ///////////////////////////
//                        multi    multi    multi    single   single   single   single   single   single   multi     multi     single   single   single     single     2         single
__global__ void kernelCal(void* x, void* y, void* n, void* a, void* b, void* c, void* d, void* e, void* f, void* xa, void* xb, void* o, void* m, void* ax, void* num, int* arr, volatile void* r) {
  int ret;

  //check for axis value
  CUhardEquals(&((BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x], ax, &ret);

  //while(r == 0 || ret == 2) {ret = 2 means n < axis}
  while ((((BigInteger*)r)->count == 0 && ((BigInteger*)r)->n[0] == 0) || (ret == 2)) {
    //x = d
    memcpy(&((BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x], d, sizeof(BigInteger));

    //x *= n
    CUsMul(&((BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

    //x += e
    CUpAdd(&((BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x], e);

    //y = n
    memcpy(&((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x],
      sizeof(BigInteger));

    //y *= n
    CUsMul(&((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

    //y *= c
    CUsMul(&((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x], c,
      &((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

    //x += y
    CUpAdd(&((BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x]);

    //x *= m
    CUsMul(&((BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x],
      m,
      &((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

    //sqrt(x) > using y as temp var (will be overwritten)
    CUsqrt(&((BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
      &((BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

    //hack-way-check remainder of sqrt(x). Only continue if "x" is a perfect square (remainder = 0)
    if (((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x].count == 0 &&
      ((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x].n[0] == 0) {
      //y = b
      memcpy(&((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x], b, sizeof(BigInteger));

      //y *= n
      CUsMul(&((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
        &((BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x],
        &((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
        &((BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

      //y -= a
      CUsub(&((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x], a,
        &((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x]);

      //y += x
      CUpAdd(&((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
        &((BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x]);

      //y /= f
      CUsDvs(&((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x], f,
        &((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
        &((BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

      if (checkSolution(&((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
        &((BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x],
        &((BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
        &((BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x],
        arr, num) == 0)
        memcpy((void*)r, &((BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x], sizeof(BigInteger));
    }

    //check for axis value
    CUhardEquals(&((BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x], ax, &ret);

    //n += o
    CUpAdd(&((BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x], o);
  }
}

//                           single    single    single    single    single    single
__device__ int checkSolution(void* va, void* vb, void* xa, void* xb, int* arr, void* num) {
  int y;
  int i = 0;
  int acc = 0;

  //subtract 1 from va
  --((BigInteger*)va)->n[0];
  //CUcarrySub(va, 0);
  //CUrecount(va);

  //Mockup for carrysub and recount as compiler is failing to include these functions????
  for (i = 0; i <= ((BigInteger*)va)->count; i++) {
    //subtract carry to number
    ((BigInteger*)va)->n[i] -= acc;

    if (((BigInteger*)va)->n[i] < 0) {
      //normalize
      ((BigInteger*)va)->n[i] += 10;
      acc = 1;
    } else
      acc = 0;
  }

  while (((BigInteger*)va)->n[((BigInteger*)va)->count--] == 0);

  ++((BigInteger*)va)->count;

  if (((BigInteger*)va)->count < 0)
    ((BigInteger*)va)->count = 0;

  //Offset by 1 position
  y = ((BigInteger*)va)->count + 1;

  for (; y >= 1; y--)
    ((BigInteger*)va)->n[y] = ((BigInteger*)va)->n[y - 1];

  ++((BigInteger*)va)->count;

  //copy num to get original value
  memcpy(xa, num, sizeof(BigInteger));

  //try with arr[0]
  ((BigInteger*)va)->n[0] = arr[1];

  //divide it (va still has modification)
  CUsDvs(xa, va, vb, xb);

  //compute xa * va (va still modified)
  CUsMul(xa, va, vb, xb);

  //compare xa vs num
  CUhardEquals(xa, num, &y);

  //if they're equal, return
  if (y == 0)
    return 0;

  //else, try with arr[1]
  //copy num to get original value
  memcpy(xa, num, sizeof(BigInteger));

  //divide it (va still has modification)
  CUsDvs(xa, va, vb, xb);

  //compute xa * va (va still modified)
  CUsMul(xa, va, vb, xb);

  //compare xa vs num
  CUhardEquals(xa, num, &y);

  //return y whatever the result is
  return y;
}
