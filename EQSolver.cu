/*
 * EQSolver.cu
 *
 *  Created on: 30 nov. 2020
 *      Author: DoHITB under MIT Liscense
 */
#include "conio.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

/////////////////////////// FUNCTION DEFINITION ///////////////////////////
__device__ void CUnewBI(void* dst, char* s, int sig);
__device__ static void CUclean(void* va);
__device__ static int cu_strlen(char* s);
__device__ void CUiniStr(char** dst);
__device__ void CUtoString(void* vb, char* dst);
__device__ void CUsMul(void* va, void* vb, void* vc, void* vd);
__device__ void CUpAdd(void* va, void* vb);
__device__ void CUpSub(void* va, void* vb);
__device__ static void CUsubtract(void* va, void* vb);
__device__ static void CUcarrySub(void* va, int carryType);
__device__ static void CUrecount(void* va);
__device__ static void CUaddition(void* va, void* vb);
__device__ static void CUpMul(int pos, void* vpart);
__device__ void CUcarryAdd(void* va, int move, int min);
__device__ void CUhardEquals(void* va, void* vb, int* ret);
__device__ static int CUsignum(int a, int b);
__device__ void CUsub(void* va, void* vb, void* vc);
__device__ void CUsDvs(void* va, void* vb, void* xa, void* xb);
__device__ static void CUdivide(void* va, void* vb, void* xa, void* xb);
__device__ void CUpAppend(void* va, int b);
__device__ void CUsqrt(void* va, void* vb, void* vc, void* vd);

__global__ void kernelCal(void* x, void* y, void* n, void* a, void* b, void* c, void* d, void* e, void* f, void* xa, void* xb, void* num, int* arr, void* r);
__global__ void makeString(void* a, int count);
__device__ int checkSolution(void* va, void* vb, void* xa, void* xb, int* arr, void* num);
__global__ void propagateAdd(void* va, void* vb)
/////////////////////////// FUNCTION DEFINITION ///////////////////////////

/////////////////////////// BIGINTEGER MOCKUP ///////////////////////////
static void _BI_initialize();
void BImemcpy(void* dst, int value);
void newBI(void* dst, char* s, int sig);
static void clean(void* va);
void hardEquals(void* va, void* vb, int* ret);
static int signum(int a, int b);
void toString(void* vb, char* dst);

static int MAX_LENGTH = 1024;
//struct
struct BigInteger {
  char k;
  int count;
  char n[1024];
};

/*
 * Variables útiles
 */
static struct BigInteger _ZERO;
static struct BigInteger _ONE;
static struct BigInteger _TWO;
static struct BigInteger _THREE;
static struct BigInteger _FOUR;
static struct BigInteger _FIVE;
static struct BigInteger _SIX;
static struct BigInteger _SEVEN;
static struct BigInteger _EIGHT;
static struct BigInteger _NINE;
static struct BigInteger _TEN;
static struct BigInteger _HUND;
static struct BigInteger _MIN;
/////////////////////////// BIGINTEGER MOCKUP ///////////////////////////

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
    cn = 1;
    cm = 1;
  }

  //heap memory control
  size_t maxMem;

  //loop control
  int ex = 0;

  //measurement
  float str;
  float end;
  float freq;

  //HOST data
  char* st1 = (char*)malloc(sizeof(char) * 1025);
  int* harr = (int*)malloc(sizeof(int) * 2);
  struct BigInteger* hnum = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* ho = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* ha = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* hb = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* hc = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* hd = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* he = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* hf = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* hn = (struct BigInteger*)malloc(sizeof(struct BigInteger) * cn * cm);
  struct BigInteger* zro = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  struct BigInteger* hr = (struct BigInteger*)malloc(sizeof(struct BigInteger));
  int hi = 0;
  cudaError_t cuerr;
  char* st = (char*)malloc(sizeof(char) * 1025);

  //////////// DEVICE DATA ////////////
  //BI Creation
  char* dst;
  struct BigInteger* a;
  struct BigInteger* b;
  struct BigInteger* c;
  struct BigInteger* d;
  struct BigInteger* e;
  struct BigInteger* f;
  struct BigInteger* n;
  struct BigInteger* o;
  struct BigInteger* x;
  struct BigInteger* y;
  struct BigInteger* num;
  int* arr;

  //AUX
  struct BigInteger* xa;
  struct BigInteger* xb;

  //Linkage
  struct BigInteger* r;

  _BI_initialize();
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
  cudaMalloc(&dst, sizeof(char) * 1025);
  cudaMalloc(&arr, sizeof(int) * 2);
  cudaMalloc(&a, sizeof(struct BigInteger));
  cudaMalloc(&b, sizeof(struct BigInteger));
  cudaMalloc(&c, sizeof(struct BigInteger));
  cudaMalloc(&d, sizeof(struct BigInteger));
  cudaMalloc(&e, sizeof(struct BigInteger));
  cudaMalloc(&f, sizeof(struct BigInteger));
  cudaMalloc(&n, sizeof(struct BigInteger) * cn * cm);
  cudaMalloc(&o, sizeof(struct BigInteger));
  cudaMalloc(&x, sizeof(struct BigInteger) * cn * cm);
  cudaMalloc(&y, sizeof(struct BigInteger) * cn * cm);
  cudaMalloc(&num, sizeof(struct BigInteger));
  cudaMalloc(&xa, sizeof(struct BigInteger) * cn * cm);
  cudaMalloc(&xb, sizeof(struct BigInteger) * cn * cm);
  cudaMalloc(&r, sizeof(struct BigInteger));

  printf("CLOCKS PER SECOND: %i\n", CLOCKS_PER_SEC);
  printf("Data allocation - Start @%i\n", clock());
  printf("\t Allocated memory:\n");
  printf("\t\t%i BigInteger\n", (5 * cn * cm) + 9);
  printf("\t\t2-position int array\n");
  printf("\t\t1025-position char array\n");

  //a, b, c, d, e, f
  fscanf_s(fl, "%s", st1, 1025);
  newBI(ha, st1, 0);

  fscanf_s(fl, "%s", st1, 1025);
  newBI(hb, st1, 0);

  fscanf_s(fl, "%s", st1, 1025);
  newBI(hc, st1, 0);

  fscanf_s(fl, "%s", st1, 1025);
  newBI(hd, st1, 0);

  fscanf_s(fl, "%s", st1, 1025);
  newBI(he, st1, 0);

  fscanf_s(fl, "%s", st1, 1025);
  newBI(hf, st1, 0);

  //arr
  fscanf_s(fl, "%i", &harr[0]);
  fscanf_s(fl, "%i", &harr[1]);

  //num
  fscanf_s(fl, "%s", st1, 5000);
  newBI(hnum, st1, 0);

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

  //copy from HOTST to DEVICE
  cudaMemcpy(a, ha, sizeof(struct BigInteger), cudaMemcpyHostToDevice);           //1
  cudaMemcpy(b, hb, sizeof(struct BigInteger), cudaMemcpyHostToDevice);           //1
  cudaMemcpy(c, hc, sizeof(struct BigInteger), cudaMemcpyHostToDevice);           //1
  cudaMemcpy(d, hd, sizeof(struct BigInteger), cudaMemcpyHostToDevice);           //1
  cudaMemcpy(e, he, sizeof(struct BigInteger), cudaMemcpyHostToDevice);           //1
  cudaMemcpy(f, hf, sizeof(struct BigInteger), cudaMemcpyHostToDevice);           //1
  cudaMemcpy(arr, harr, sizeof(int) * 2, cudaMemcpyHostToDevice);                 //2 (int)
  cudaMemcpy(num, hnum, sizeof(struct BigInteger), cudaMemcpyHostToDevice);       //1
  cudaMemcpy(n, hn, sizeof(struct BigInteger) * cn * cm, cudaMemcpyHostToDevice); //cn * cm
  cudaMemcpy(o, ho, sizeof(struct BigInteger), cudaMemcpyHostToDevice);           //1
  cudaMemcpy(r, hr, sizeof(struct BigInteger), cudaMemcpyHostToDevice);           //1
  cudaDeviceSynchronize();
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

  //init loop
  ex = 0;

  //calculation begins
  while (ex == 0) {
    printf("Calculation - Loop Start @%i\n", clock());
    str = clock();

    kernelCal <<<cn, cn>>>(x, y, n, a, b, c, d, e, f, xa, xb, num, arr, r);
    cuerr = cudaDeviceSynchronize();

    if (cuerr != 0) {
      printf("Error on sync: %s\n", cudaGetErrorString(cuerr));
      exit(-1);
    }

    end = clock();
    freq =  (cn * cm) / (end - str);
    printf("Calculation - Loop End @%i {%i values checked} ~ %f equations / msec\n", clock(), cn * cm, freq);

    //makeString<<<1, 1>>>(y, cn * cm);
    //copy r to HOST
    cudaMemcpy(hr, r, sizeof(struct BigInteger), cudaMemcpyDeviceToHost);
    hardEquals(hr, zro, &ex);

    propagateAdd <<<cn, cm>>>(n, o);
  }

  //Loop exit. Display result
  toString(hr, st1);
  printf("RESULT: %s\n", st1);

  return 0;
}


/////////////////////////// CALCULATION DEFINITION ///////////////////////////
//                        multi    multi    multi    single   single   single   single   single   single   multi     multi     single     2         single
__global__ void kernelCal(void* x, void* y, void* n, void* a, void* b, void* c, void* d, void* e, void* f, void* xa, void* xb, void* num, int* arr, void* r) {
  //x = d
  memcpy(&((struct BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x], d, sizeof(struct BigInteger));

  //x *= n
  CUsMul(&((struct BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

  //x += e
  CUpAdd(&((struct BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x], e);

  //y = n
  memcpy(&((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x],
         sizeof(struct BigInteger));

  //y *= n
  CUsMul(&((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

  //y *= c
  CUsMul(&((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x], c,
         &((struct BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

  //x += y
  CUpAdd(&((struct BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x]);

  //sqrt(x) > using y as temp var (will be overwritten)
  CUsqrt(&((struct BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

  //y = b
  memcpy(&((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x], b, sizeof(struct BigInteger));

  //y *= n
  CUsMul(&((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)n)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

  //y -= a
  CUsub(&((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x], a,
        &((struct BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x]);

  //y += x
  CUpAdd(&((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x]);

  //y /= f
  CUsDvs(&((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x], f,
         &((struct BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
         &((struct BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x]);

  if (checkSolution(&((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x],
                    &((struct BigInteger*)x)[blockIdx.x * blockDim.x + threadIdx.x],
                    &((struct BigInteger*)xa)[blockIdx.x * blockDim.x + threadIdx.x],
                    &((struct BigInteger*)xb)[blockIdx.x * blockDim.x + threadIdx.x],
                    arr, num) == 0)
    memcpy(r, &((struct BigInteger*)y)[blockIdx.x * blockDim.x + threadIdx.x], sizeof(struct BigInteger));
}

//                         multi
__global__ void makeString(void* a, int count) { 
  int i = 0;
  char* st;
  CUiniStr(&st);

  for (i = 0; i < count; i++) {
    CUtoString(&((struct BigInteger*)a)[i], st);
    printf("[%i]: %s\n", i, st);
  }

  free(st);
}

//                           single    single    single    single    single    single
__device__ int checkSolution(void* va, void* vb, void* xa, void* xb, int* arr, void* num) {
  int y;

  //restamos 1 a va
  --((struct BigInteger*)va)->n[0];
  CUcarrySub(va, 0);
  CUrecount(va);

  //Desplazamos va una posición
  y = ((struct BigInteger*)va)->count + 1;

  for (; y >= 1; y--)
    ((struct BigInteger*)va)->n[y] = ((struct BigInteger*)va)->n[y - 1];

  ++((struct BigInteger*)va)->count;

  //copiamos num para tener el valor original
  memcpy(xa, num, sizeof(struct BigInteger));

  //probamos con arr[0]
  ((struct BigInteger*)va)->n[0] = arr[1];

  //dividimos como podemos (va sigue con la modificación)
  CUdivide(xa, va, vb, xb);

  //multiplicamos xa * va (va sigue con la modificación)
  CUsMul(xa, va, vb, xb);

  //comparamos xa contra num
  CUhardEquals(xa, num, &y);

  //si hay un resultado satisfactorio retornamos
  if (y == 0)
    return 0;

  //sino, probamos con arr[1]
  //copiamos num para tener el valor original
  memcpy(xa, num, sizeof(struct BigInteger));

  //dividimos como podemos (va sigue con la modificación)
  CUdivide(xa, va, vb, xb);

  //multiplicamos xa * va (va sigue con la modificación)
  CUsMul(xa, va, vb, xb);

  //comparamos xa contra num
  CUhardEquals(xa, num, &y);

  //retornamos y sea cual sea el resultado
  return y;
}

//                           multi     single
__global__ void propagateAdd(void* va, void* vb) {
  //va += vb
  CUpAdd(&((struct BigInteger*)va)[blockIdx.x * blockDim.x + threadIdx.x], vb);
}

/////////////////////////// MOCK-UP DEFINITION ///////////////////////////
__device__ void CUnewBI(void* dst, char* s, int sig) {
  int i = cu_strlen(s) - 1;
  int f = i;
  int j = 0;
  int c;
  int ssig = sig;

  //ajustamos el tipo
  ((struct BigInteger*)dst)->k = 'i';

  //limpiamos el array
  CUclean(dst);

  //recorremos el string y lo guardamos en integers
  for (; i >= 0; i--) {
    c = (int)(s[i] - 48);

    if (c >= 0 && c <= 9)
      ((struct BigInteger*)dst)->n[j++] = c;
    else
      if (s[i] == '-')
        ssig = -1;
  }

  //si nos envían un negativo, restamos una posición
  if (s[0] == '-')
    --f;

  ((struct BigInteger*)dst)->count = f;

  if (ssig == -1)
    ((struct BigInteger*)dst)->n[((struct BigInteger*)dst)->count] *= -1;
}

//mock-up for clean
__device__ static void CUclean(void* va) {
  int i = 0;

  for (i = 0; i < 1024; i++)
    ((struct BigInteger*)va)->n[i] = 0;

  ((struct BigInteger*)va)->count = 0;
}

//mock-up for iniStr
__device__ void CUiniStr(char** dst) {
  *dst = (char*)malloc(sizeof(char) * 1025);
}

//mock-up for toString
__device__ void CUtoString(void* vb, char* dst) {
  int i = 0;
  int m = ((struct BigInteger*)vb)->count;
  int sig = 0;

  //si el primer dígito es negativo, lo volvemos positivo y marcamos el caracter
  if (((struct BigInteger*)vb)->n[m] < 0) {
    ((struct BigInteger*)vb)->n[m] *= -1;
    dst[i++] = '-';
    sig = 1;
  }

  for (; m >= 0; m--)
    dst[i++] = (char)(((struct BigInteger*)vb)->n[m] + 48);

  dst[i] = '\0';

  //estamos trabajando sobre el puntero, revisamos y reestablecemos valores
  if (sig == 1)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
}

//mock-up for sMul
__device__ void CUsMul(void* va, void* vb, void* vc, void* vd) {
  int sig;
  int i;
  int x;

  CUclean(vc);
  CUclean(vd);

  sig = CUsignum(((struct BigInteger*)va)->n[((struct BigInteger*)va)->count],
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count]);

  if (sig == 1)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  else if (sig == 10)
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;
  else if (sig == 11) {
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  }

  for (i = 0; i <= ((struct BigInteger*)vb)->count; i++) {
    for (x = 0; x <= ((struct BigInteger*)va)->count; x++)
      ((struct BigInteger*)vc)->n[x] = ((struct BigInteger*)va)->n[x] * ((struct BigInteger*)vb)->n[i];

    ((struct BigInteger*)vc)->count = x - 1;
    CUcarryAdd(vc, 0, 0);

    //multiplicación parcial
    CUpMul(i, vc);

    //sumamos
    CUaddition(vd, vc);
  }

  //copiamos resultado
  memcpy(va, vd, sizeof(struct BigInteger));

  //si los signos son diferentes, invertimos el signo
  if (sig == 1 || sig == 10)
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;

  //desnormalizamos vb
  if (sig == 1)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  else if (sig == 11)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;

  CUrecount(va);
}

//mock-up for pAdd
__device__ void CUpAdd(void* va, void* vb) {
  int sig = CUsignum(((struct BigInteger*)va)->n[((struct BigInteger*)va)->count],
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count]);

  //normalizamos los operandos
  if (sig == 10)
    //a negativo, b positivo. Cambiamos el signo de "a" y hacemos suma
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;
  else if (sig == 1)
    //b negativo, a positivo. Cambiamos el signo de "b" y hacemos suma
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  else if (sig == 11) {
    //a negativo, b negativo. Cambiamos signos y hacemos suma
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  }

  //si ambos signos son iguales, se suma, sino, se resta
  if (sig == 0 || sig == 11)
    CUaddition(va, vb);
  else
    CUsubtract(va, vb);

  if (sig == 10 || sig == 11)
    //en estos casos, siempre se le va la vuelta al signo
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;

  //desnormalizamos b
  if (sig == 1)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  else if (sig == 11)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
}

//mock-up for pSub
__device__ void CUpSub(void* va, void* vb) {
  int sig;

  sig = CUsignum(((struct BigInteger*)va)->n[((struct BigInteger*)va)->count],
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count]);

  //normalizamos los signos
  if (sig == 1)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  else if (sig == 10)
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;
  else if (sig == 11) {
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  }

  //si tienen el mismo signo, se resta, sino se suma
  if (sig == 0 || sig == 11)
    CUsubtract(va, vb);
  else
    CUaddition(va, vb);

  if (sig == 10 || sig == 11)
    //en estos casos, siempre se le va la vuelta al signo
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;

  //desnormalizamos b
  if (sig == 1)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  else if (sig == 11)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
}

//mock-up for subtract
__device__ static void CUsubtract(void* va, void* vb) {
  int i = 0;

  //restamos los dígitos comunes
  for (; i <= ((struct BigInteger*)vb)->count; i++)
    ((struct BigInteger*)va)->n[i] -= ((struct BigInteger*)vb)->n[i];

  //si el último dígito es negativo
  if (((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] < 0)
    CUcarrySub(va, 1);
  else
    CUcarrySub(va, 0); 
}

//mock-up for carrySub
__device__ static void CUcarrySub(void* va, int carryType) {
  int i = 0;
  int acc = 0;

  if (carryType == 0) {
    for (; i <= ((struct BigInteger*)va)->count; i++) {
      //restamos el acarreo al número
      ((struct BigInteger*)va)->n[i] -= acc;

      if (((struct BigInteger*)va)->n[i] < 0) {
        //normalizamos el número
        ((struct BigInteger*)va)->n[i] += 10;
        acc = 1;
      } else
        acc = 0;
    }
  } else {
    //en esta opción, no es necesario pasar una segunda vez por acarreos.
    for (i = 0; i < ((struct BigInteger*)va)->count; i++)
      if (((struct BigInteger*)va)->n[i] < 0)
        //normalizamos el número
        ((struct BigInteger*)va)->n[i] = ((struct BigInteger*)va)->n[i] * -1;
  }

  //contamos de nuevo los dígitos
  CUrecount(va);
}

//mock-up for recount
__device__ static void CUrecount(void* va) {
  while (((struct BigInteger*)va)->n[((struct BigInteger*)va)->count--] == 0);

  ++((struct BigInteger*)va)->count;

  if (((struct BigInteger*)va)->count < 0)
    ((struct BigInteger*)va)->count = 0;
}

//mock-up for addition
__device__ static void CUaddition(void* va, void* vb) {
  int limit;
  int min;
  int swap;
  int move;
  int i;

  //asumimos que a tiene la mayor longitud
  limit = ((struct BigInteger*)va)->count;

  //asumimos que b tiene la menor longitud
  min = ((struct BigInteger*)vb)->count;

  //indicador de necesidad de arrastre
  move = 0;
  i = 0;

  //si no es así, rectificamos
  if (((struct BigInteger*)vb)->count > limit) {
    //intercambiamos limit y min
    swap = limit;
    limit = min;
    min = swap;

    move = 1;
  }

  //sumamos los dígitos que coinciden
  for (; i <= min; i++)
    ((struct BigInteger*)va)->n[i] += ((struct BigInteger*)vb)->n[i];

  //los dígitos que no coinciden los traspasamos
  if (move == 1) {
    for (; i <= limit; i++)
      ((struct BigInteger*)va)->n[i] = ((struct BigInteger*)vb)->n[i];

    ((struct BigInteger*)va)->count = limit;
  }

  //gestionamos el acarreo
  CUcarryAdd(va, 1, min);
}

//mock-up for pMul
__device__ static void CUpMul(int pos, void* vpart) {
  int i;

  i = ((struct BigInteger*)vpart)->count + pos;

  //generamos offset
  for (; i >= pos; i--)
    ((struct BigInteger*)vpart)->n[i] = ((struct BigInteger*)vpart)->n[i - pos];

  //noramlizamos las posiciones de offset
  for (i = 0; i < pos; i++)
    ((struct BigInteger*)vpart)->n[i] = 0;

  ((struct BigInteger*)vpart)->count += pos;
}

//mock-up for carryAdd
__device__ void CUcarryAdd(void* va, int move, int min) {
  int i = 0;
  int acc;
  int limit;

  acc = 0;

  //move == 1 --> sabemos que hay una parte no común. En min está el límite de la parte común
  if (move == 1)
    limit = min;
  else
    limit = ((struct BigInteger*)va)->count;

  //recorremos a y vamos sumando el acarreo de la parte común
  for (; i <= limit; i++) {
    //sumamos acarreo
    ((struct BigInteger*)va)->n[i] += acc;

    //como acc es int, podemos dividir entre 10 y sacar el acarreo
    acc = ((struct BigInteger*)va)->n[i] / 10;

    if (acc > 0)
      //normalizamos el número
      ((struct BigInteger*)va)->n[i] = ((struct BigInteger*)va)->n[i] % 10;
  }

  if (move == 1) {
    //queda parte no común. Acarreamos hatsa que acc sea 0, ya que la parte no común ya está normalizada
    while (acc > 0 && i <= ((struct BigInteger*)va)->count) {
      //sumamos acarreo
      ((struct BigInteger*)va)->n[i] += acc;

      //como acc es int, podemos dividir entre 10 y sacar el acarreo
      acc = ((struct BigInteger*)va)->n[i] / 10;

      if (acc > 0)
        //normalizamos el número
        ((struct BigInteger*)va)->n[i] = ((struct BigInteger*)va)->n[i] % 10;

      i++;
    }
  }

  //si ha quedado acarreo, lo guardamos al final;
  if (acc > 0)
    ((struct BigInteger*)va)->n[++(((struct BigInteger*)va)->count)] = acc;
}

//mock-up for hardEquals
__device__ void CUhardEquals(void* va, void* vb, int* ret) {
  int i;
  int sig;

  /*calculamos el signo
   *
   *00: a >= 0, b >= 0
   *01: a >= 0, b <  0
   *10: a <  0, b >= 0
   *11: a <  0, b <  0
   */
  sig = CUsignum(((struct BigInteger*)va)->n[((struct BigInteger*)va)->count],
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count]);

  if (sig == 1)
    //a >= 0, b < 0, por tanto a > b
    *ret = 1;
  else if (sig == 10)
    //a < 0, b >= 0, por tanto a < b
    *ret = 2;
  else {
    //comparten signo. Hacemos comparación manual
    *ret = 0;

    if (((struct BigInteger*)va)->count < ((struct BigInteger*)vb)->count)
      //si "a" tiene menos dígitos que "b"
      *ret = 2;
    else if (((struct BigInteger*)va)->count > ((struct BigInteger*)vb)->count)
      //si "a" tiene más dítigos que "b"
      *ret = 1;
    else {
      //tienen los mismos dígitos. Comparamos uno a uno.
      for (i = ((struct BigInteger*)va)->count; i >= 0; i--) {
        if (((struct BigInteger*)va)->n[i] < ((struct BigInteger*)vb)->n[i])
          *ret = 2;
        else if ((((struct BigInteger*)va)->n[i] > ((struct BigInteger*)vb)->n[i]))
          *ret = 1;

        if (*ret > 0)
          break;
      }
    }

    if (sig == 11) {
      //ambos tienen signo negativo. Cambiamos el retorno
      //ya que se p. ej. -1 > -10
      if (*ret == 2)
        *ret = 1;
      else if (*ret == 1)
        *ret = 2;
    }
  }
}

//mock-up for signum
__device__ static int CUsignum(int a, int b) {
  int ret = 0;

  if (a < 0)
    ret = 10;

  if (b < 0)
    ++ret;

  return ret;
}

//mock-up for sDvs
__device__ void CUsDvs(void* va, void* vb, void* xa, void* xb) {
  int sig;
  int comp;

  CUnewBI(xa, "0", 0);
  CUnewBI(xb, "1", 0);

  sig = CUsignum(((struct BigInteger*)va)->n[((struct BigInteger*)va)->count],
               ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count]);

  //normalizamos los operandos
  if (sig == 1)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  else if (sig == 10)
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;
  else if (sig == 11) {
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  }

  CUhardEquals(va, vb, &comp);

  if (comp == 0) {
    //si a = b, a/b = 1
    CUhardEquals(va, xa, &comp);

    if (comp == 0)
      //si a = 0 (por tanto, b = 0), retornamos 0
      memcpy(va, xa, sizeof(struct BigInteger));
    else
      //en caso contrario, retornamos 1
      memcpy(va, xb, sizeof(struct BigInteger));
  } else if (comp == 2) {
    //si a < b, a / b = 0
    memcpy(va, xa, sizeof(struct BigInteger));
  } else if (comp == 1) {
    //si a > b, buscamos un número que solucione ax = n
    CUhardEquals(vb, xb, &comp);

    if (comp != 0)
      CUdivide(va, vb, xa, xb);
  }

  //si los signos son diferentes, invertimos el signo
  if (sig == 1 || sig == 10)
    ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] *= -1;

  //desnormalizamos b
  if (sig == 1)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
  else if (sig == 11)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
}

//mock-up for divide
__device__ static void CUdivide(void* va, void* vb, void* xa, void* xb) {
  int len;
  int i = 0;
  int x = 0;
  int res = 0;
  int mLen;
  int eq;

  len = ((struct BigInteger*)va)->count - ((struct BigInteger*)vb)->count;

  CUclean(xa);
  CUclean(xb);

  /*
   * Nos quedamos con los "b.count" primeros dígitos. Si "b" tiene un único
   * dígito, no movemos nada, porque ya moveremos el siguiente dígito más adelante
   */
  if (((struct BigInteger*)vb)->count > 0)
    for (; i < ((struct BigInteger*)vb)->count; i++)
      ((struct BigInteger*)xb)->n[((struct BigInteger*)vb)->count - i - 1] = ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count - i];
  else
    ((struct BigInteger*)xb)->n[0] = 0;

  ((struct BigInteger*)xb)->count = ((struct BigInteger*)vb)->count - 1;

  if (((struct BigInteger*)xb)->count == -1)
    ++((struct BigInteger*)xb)->count;

  //si "b" tiene una cifra, b.len será 0 pero tenemos que restar una cifra igualmente
  if (((struct BigInteger*)vb)->count == 0)
    mLen = len - 1;
  else
    mLen = len;

  //por cada cifra decimal que hemos generado
  for (i = 0; i <= len; i++) {
    CUpAppend(xb, ((struct BigInteger*)va)->n[len - i]);

    for (x = 0; x < 10; x++) {
      if (((struct BigInteger*)xb)->n[((struct BigInteger*)xb)->count] == 0) {
        //el valor es 0
        res = x;
        x = 99;
      } else if (((struct BigInteger*)xb)->n[((struct BigInteger*)xb)->count] < 0) {
        //el valor es negativo
        CUaddition(xb, vb);
        res = (x - 1);
        x = 99;
      } else {
        CUhardEquals(xb, vb, &eq);

        if (eq == 2) {
          //xb < vb --> found
          res = x;
          x = 99;
        } else {
          //xb >= vb
          CUsubtract(xb, vb);
        }
      }
    }

    ((struct BigInteger*)xa)->n[len - i] = res;
  }

  ((struct BigInteger*)xa)->count = mLen;

  memcpy(va, (struct BigInteger*)xa, sizeof(struct BigInteger));

  CUrecount(va);

  //evitar error de falso desbordamiento
  if (((struct BigInteger*)va)->n[((struct BigInteger*)va)->count + 1] > 0)
    ++((struct BigInteger*)va)->count;
}

//mock-up for pAppend
__device__ void CUpAppend(void* va, int b) {
  int i;

  for (i = ((struct BigInteger*)va)->count; i >= 0; i--)
    ((struct BigInteger*)va)->n[i + 1] = ((struct BigInteger*)va)->n[i];

  ((struct BigInteger*)va)->n[0] = b;
  ++((struct BigInteger*)va)->count;
}

//mock-up for sub
__device__ void CUsub(void* va, void* vb, void* vc) {
  int comp;
  int sig;

  CUhardEquals(va, vb, &comp);
  sig = CUsignum(((struct BigInteger*)va)->n[((struct BigInteger*)va)->count],
               ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count]);

  //si ambos son negativos, comp = 1 significa a < b
  if ((comp == 2 && sig < 11) || (comp == 1 && sig == 11)) {
    memcpy(vc, vb, sizeof(struct BigInteger)); //tmp = b; stmp = m[0]

    CUpSub(vc, va);

    //cambiamos el signo
    //((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
    ((struct BigInteger*)vc)->n[((struct BigInteger*)vc)->count] *= -1;

    //reasignamos
    memcpy(va, vc, sizeof(struct BigInteger));

    //rescatamos el valor original de vb
    //memcpy(vb, &((struct BigInteger*)m)[0], sizeof(struct BigInteger));
  } else {
    CUpSub(va, vb);
  }
}

__device__ void CUsqrt(void* va, void* vb, void* vc, void* vd) {
  char even = ((struct BigInteger*)va)->count % 2;
  int digits = ((struct BigInteger*)va)->count + 1;
  char fstep;
  int x = 0;
  int y = 0;
  int eq;
  char z;

  CUclean(vb);
  CUclean(vc);
  CUclean(vd);

  ///// PRIMER RESTO /////
  //creamos el primer resto
  if (even == 1) {
    //si even == 1 es que count es impar y por tanto hay un numero par de cifras
    fstep = ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count] * 10 + ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count - 1];
  } else {
    //sino, es un numero impar de cifras
    fstep = ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count];
  }

  //calculamos la raíz simple
  while (x * x++ <= fstep);
  if (--x * x > fstep)
    --x;

  //x es el primer dígito de la raiz
  ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] = x;

  //guardaremos el resto en vc. Siempre se dará fstep >= x
  ((struct BigInteger*)vc)->n[((struct BigInteger*)vc)->count] = fstep - (x * x);

  //recontamos
  CUrecount(vc);
  ///// PRIMER RESTO /////

  //utilizamos "digits" como contador. 
  if (digits == 1 || digits == 2) {
    //caso especial, para 1 y 2 dígitos el resultado tiene 1 dígito
    digits = 0;
  } else {
    //el count incluye el 0, restamos 1
    digits = (digits / 2 + digits % 2) - 1;
  }

  //usamos "x" como contador temporal, sumando 1 porque ya hemos colocado 1 dígito
  x = 1;

  ///// RESTO DE DÍGITOS /////
  //mientras haya dígitos por colocar
  while (x <= digits) {
    //bajamos las dos siguientes cifras.
    //  primero corremos dos posiciones el resto (vc)
    y = ((struct BigInteger*)vc)->count + 2;

    for (; y >= 2; y--)
      ((struct BigInteger*)vc)->n[y] = ((struct BigInteger*)vc)->n[y - 2];

    //  luego movemos de va a vc las dos posiciones correlativas
    ((struct BigInteger*)vc)->n[1] = ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count - (2 * x) - even + 1];
    ((struct BigInteger*)vc)->n[0] = ((struct BigInteger*)va)->n[((struct BigInteger*)va)->count - (2 * x) - even];

    // ajustamos la longitud de vc
    ((struct BigInteger*)vc)->count += 2;

    //ajustamos
    CUrecount(vc);

    //copiamos el resultado actual (vb) a vd
    memcpy(vd, vb, sizeof(struct BigInteger));

    //calculamos vb + vb. Da igual el órden en que sumemos
    for (y = 0; y <= ((struct BigInteger*)vd)->count; y++)
      ((struct BigInteger*)vd)->n[y] += ((struct BigInteger*)vd)->n[y];

    //gesionamos acarreo
    CUcarryAdd(vd, 0, 0);

    //buscamos un número n = [1, 9] tal que vd * 10 + n * n = vc
    // primero montamos el valor relativo a n = 1
    y = ((struct BigInteger*)vd)->count + 1;

    for (; y >= 1; y--)
      ((struct BigInteger*)vd)->n[y] = ((struct BigInteger*)vd)->n[y - 1];

    ((struct BigInteger*)vd)->n[0] = 1;
    ++((struct BigInteger*)vd)->count;

    //inicializamos z, que será la cifra a colocar
    z = 1;

    //asumimos que no llegamos a igualar vb
    eq = 2;

    ///// BUSQUEDA DEL DÍGITO /////
    while (eq == 2) {
      //comparmos vd con vb
      CUhardEquals(vd, vc, &eq);

      if (eq == 1) {
        //vd > vb. La cifra que buscamos es la anterior.
        //restauramos vd al estado anterior
        if (z == 1) {
          //si z = 1 estamos en la primera iteración, y el valor anterior será 0
          CUnewBI(vd, "0", 0);
          --z;
        } else {
          //restamos z y restauramos vd. El decremento de vd es (vd * 10) + (2(n - 1) + 1)
          --z;
        }
      } else if (eq == 2) {
        //vd < vb. La cifra que buscamos puede ser la siguiente
        //incrementamos vd y z. El incremento de vd es (vd * 10) + (2n + 1).
        //Obtenemos la primera parte de vb

        //(vd * 10)
        for (y = 0; y <= ((struct BigInteger*)vb)->count; y++)
          ((struct BigInteger*)vd)->n[y + 1] += (((struct BigInteger*)vb)->n[y] * 2);

        //+2n + 1
        ((struct BigInteger*)vd)->n[0] += (2 * z) + 1;

        //gestionamos acarreo
        CUcarryAdd(vd, 0, 0);

        ++z;
      }

      //si hemos iterado 10 veces, la cifra será 9
      if (z == 10) {
        //volvemos a 9
        --z;

        //forzamos salida
        eq = 1;
      }
    }
    ///// BUSQUEDA DEL DÍGITO /////

    ///// RESTAURAR /////
    if (eq == 1) {
      //si nos hemos pasado, restauramos el valor de vd
      //copiamos el resultado actual (vb) a vd
      memcpy(vd, vb, sizeof(struct BigInteger));

      //calculamos vb + vb. Da igual el órden en que sumemos
      for (y = 0; y <= ((struct BigInteger*)vd)->count; y++)
        ((struct BigInteger*)vd)->n[y] += ((struct BigInteger*)vd)->n[y];

      //gesionamos acarreo
      CUcarryAdd(vd, 0, 0);

      //buscamos un número n = [1, 9] tal que vd * 10 + n * n = vc
      // primero montamos el valor relativo a n = 1
      y = ((struct BigInteger*)vd)->count + 1;

      for (; y >= 1; y--)
        ((struct BigInteger*)vd)->n[y] = ((struct BigInteger*)vd)->n[y - 1];

      ((struct BigInteger*)vd)->n[0] = z;
      ++((struct BigInteger*)vd)->count;

      //multiplicamos por z
      for (y = 0; y <= ((struct BigInteger*)vd)->count; y++)
        ((struct BigInteger*)vd)->n[y] *= z;

      //gestionamos acarreo
      CUcarryAdd(vd, 0, 0);
    }

    ///// COLOCAR DÍTIGTO /////
    //Al salir del bucle tendremos en "z" la cifra a colocar, en vd el dato a restar, y en vc el cociente actual
    //Restamos vc -= vd (siempre se dará vc >= vd) para actualizar el cociente
    CUsubtract(vc, vd);

    //Desplazamos vb una posición y colocamos z
    y = ((struct BigInteger*)vb)->count + 1;

    for (; y >= 1; y--)
      ((struct BigInteger*)vb)->n[y] = ((struct BigInteger*)vb)->n[y - 1];

    ((struct BigInteger*)vb)->n[0] = z;
    ++((struct BigInteger*)vb)->count;
    ///// COLOCAR DÍTIGTO /////

    //incrementamos x
    x++;
  }
  ///// RESTO DE DÍGITOS /////

  //copiamos el resultado
  memcpy(va, vb, sizeof(struct BigInteger));
}
/////////////////////////// MOCK-UP DEFINITION ///////////////////////////

/////////////////////////// AUX DEFINITION ///////////////////////////
__device__ static int cu_strlen(char* s) {
  int ret = 0;

  while (*s != '\0') {
    ++s;
    ++ret;
  }

  return ret;
}
/////////////////////////// AUX DEFINITION ///////////////////////////

/////////////////////////// BIGINTEGER DEFINITION ///////////////////////////
static void _BI_initialize() {
  int i = 0;

  //lo creamos manualmente ya que clean copia de _ZERO
  for (; i < MAX_LENGTH; i++)
    _ZERO.n[i] = 0;

  _ZERO.count = 0;
  _ZERO.k = 'i';

  newBI(&_ONE, "1", 0);
  newBI(&_TWO, "2", 0);
  newBI(&_THREE, "3", 0);
  newBI(&_FOUR, "4", 0);
  newBI(&_FIVE, "5", 0);
  newBI(&_SIX, "6", 0);
  newBI(&_SEVEN, "7", 0);
  newBI(&_EIGHT, "8", 0);
  newBI(&_NINE, "9", 0);
  newBI(&_TEN, "10", 0);
  newBI(&_HUND, "100", 0);
  newBI(&_MIN, "1", -1);
}

void BImemcpy(void* dst, int value) {
  if (value == 0)
    memcpy(dst, &_ZERO, sizeof(struct BigInteger));
  else if (value == 1)
    memcpy(dst, &_ONE, sizeof(struct BigInteger));
  else if (value == 2)
    memcpy(dst, &_TWO, sizeof(struct BigInteger));
  else if (value == 3)
    memcpy(dst, &_THREE, sizeof(struct BigInteger));
  else if (value == 4)
    memcpy(dst, &_FOUR, sizeof(struct BigInteger));
  else if (value == 5)
    memcpy(dst, &_FIVE, sizeof(struct BigInteger));
  else if (value == 6)
    memcpy(dst, &_SIX, sizeof(struct BigInteger));
  else if (value == 7)
    memcpy(dst, &_SEVEN, sizeof(struct BigInteger));
  else if (value == 8)
    memcpy(dst, &_EIGHT, sizeof(struct BigInteger));
  else if (value == 9)
    memcpy(dst, &_NINE, sizeof(struct BigInteger));
  else if (value == 10)
    memcpy(dst, &_TEN, sizeof(struct BigInteger));
  else if (value == 100)
    memcpy(dst, &_HUND, sizeof(struct BigInteger));
  else if (value == -1)
    memcpy(dst, &_MIN, sizeof(struct BigInteger));
  else
    BImemcpy(dst, 0);
}

void newBI(void* dst, char* s, int sig) {
  int i = (int)strlen(s) - 1;
  int f = i;
  int j = 0;
  int c;
  int ssig = sig;

  //ajustamos el tipo
  ((struct BigInteger*)dst)->k = 'i';

  //limpiamos el array
  clean(dst);

  //recorremos el string y lo guardamos en integers
  for (; i >= 0; i--) {
    c = (int)(s[i] - 48);

    if (c >= 0 && c <= 9) {
      ((struct BigInteger*)dst)->n[j++] = c;
    } else {
      if (s[i] == '-')
        ssig = -1;
    }
  }

  //si nos envían un negativo, restamos una posición
  if (s[0] == '-')
    --f;

  ((struct BigInteger*)dst)->count = f;

  if (ssig == -1)
    ((struct BigInteger*)dst)->n[((struct BigInteger*)dst)->count] *= -1;
}

static void clean(void* va) {
  BImemcpy(va, 0);
}

void hardEquals(void* va, void* vb, int* ret) {
  int i;
  int sig;

  /*calculamos el signo
   *
   *00: a >= 0, b >= 0
   *01: a >= 0, b <  0
   *10: a <  0, b >= 0
   *11: a <  0, b <  0
   */
  sig = signum(((struct BigInteger*)va)->n[((struct BigInteger*)va)->count],
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count]);

  if (sig == 1)
    //a >= 0, b < 0, por tanto a > b
    *ret = 1;
  else if (sig == 10)
    //a < 0, b >= 0, por tanto a < b
    *ret = 2;
  else {
    //comparten signo. Hacemos comparación manual
    *ret = 0;

    if (((struct BigInteger*)va)->count < ((struct BigInteger*)vb)->count)
      //si "a" tiene menos dígitos que "b"
      *ret = 2;
    else if (((struct BigInteger*)va)->count > ((struct BigInteger*)vb)->count)
      //si "a" tiene más dítigos que "b"
      *ret = 1;
    else {
      //tienen los mismos dígitos. Comparamos uno a uno.
      for (i = ((struct BigInteger*)va)->count; i >= 0; i--) {
        if (((struct BigInteger*)va)->n[i] < ((struct BigInteger*)vb)->n[i])
          *ret = 2;
        else if ((((struct BigInteger*)va)->n[i] > ((struct BigInteger*)vb)->n[i]))
          *ret = 1;

        if (*ret > 0)
          break;
      }
    }

    if (sig == 11) {
      //ambos tienen signo negativo. Cambiamos el retorno
      //ya que se p. ej. -1 > -10
      if (*ret == 2)
        *ret = 1;
      else if (*ret == 1)
        *ret = 2;
    }
  }
}

static int signum(int a, int b) {
  int ret = 0;

  if (a < 0)
    ret = 10;

  if (b < 0)
    ++ret;

  return ret;
}

void toString(void* vb, char* dst) {
  int i = 0;
  int m = ((struct BigInteger*)vb)->count;
  int sig = 0;

  //si el primer dígito es negativo, lo volvemos positivo y marcamos el caracter
  if (((struct BigInteger*)vb)->n[m] < 0) {
    ((struct BigInteger*)vb)->n[m] *= -1;
    dst[i++] = '-';
    sig = 1;
  }

  for (; m >= 0; m--)
    dst[i++] = (char)(((struct BigInteger*)vb)->n[m] + 48);

  dst[i] = '\0';

  //estamos trabajando sobre el puntero, revisamos y reestablecemos valores
  if (sig == 1)
    ((struct BigInteger*)vb)->n[((struct BigInteger*)vb)->count] *= -1;
}
/////////////////////////// BIGINTEGER DEFINITION ///////////////////////////
