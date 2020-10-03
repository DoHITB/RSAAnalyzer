/*
 * RSAWaitList.c
 *
 *  Created on: 01 oct. 2020
 *      Author: DoHITB
 */
#include "conio.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "Logging.h"

#pragma warning (disable: 4703)

int main() {
  FILE* fl;
  int efl = -1;
  int wait = 0;
  char ch;


  activateLog(9);
  _log("Waiting for dataset...", 0);

  inFunction();

  while (efl != 0) {
    efl = fopen_s(&fl, "RSAWL.dat", "r");
    wait = ++wait % 100000;

    if (wait == 0)
      _log("Waiting...", 0);
  }

  if (fl == NULL)
    exit(-1);

  outFunction();

  _log("Result found!", 0);
  deactivateLog();

  printf("\n-------------------------------\n");

  //dump it!
  while ((ch = fgetc(fl)) != EOF)
    printf("%c", ch);

  printf("\n-------------------------------\n");

  _getch();
}
