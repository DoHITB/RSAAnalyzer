/*
 * Logging.c
 *
 *  Created on: 25 ene. 2019
 *    Author: DoHITB
 */
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "stdarg.h"
#include "Logging.h"

/*
 * CURR_DEPTH: variable to set the tabulation
 */
static int CURR_DEPTH = 0;

/*
 * DEBUG: variable that holds the threshold value
 */
static int DEBUG = 0;

/*
 *IS_ON: indicates if logging is active
 */
static int IS_ON = 0;

/*
 * rt: holds the file route
 */
static char* rt;

/*
 * IS_FILE: indicates if there's a setted file
 */
static int IS_FILE = 0;

/*
 * IS_OPEN: indicates if the setted file is open
 */
static int IS_OPEN = 0;

/*
 * fl: FILE handler
 */
static FILE* fl;

/*
 * showTime: indicates to show time (clock() function)
 */
static int showTime = 1;

/*
 * inFunction: increases CURR_DEPTH
 */
void inFunction() {
  CURR_DEPTH++;
}

/*
 * outFunction: decreases CURR_DEPTH
 */
void outFunction() {
  CURR_DEPTH--;
}

/*
 * activateLog: sets DEBUG to level value. If there's a file, it will be opened
 */
void activateLog(int level) {
  IS_ON = 1;
  DEBUG = level;

  if (IS_FILE == 1)
    openFile();

  _log("CLOCKS_PER_SEC: %i", 999, CLOCKS_PER_SEC);
}

/*
 * openFile: opens file handler fl, which route it's on rt variable.
 */
static void openFile() {
  int efl;

  if (IS_OPEN == 0) {
    IS_OPEN = 1;

    efl = fopen_s(&fl, rt, "a");

    if (efl != 0) {
      printf("Error on file open [%s]... going with printf\n", rt);
      IS_FILE = 0;
    }
  }
}

/*
 * deactivateLog: turns off the logger. If there's a file, it will close it.
 */
void deactivateLog() {
  IS_ON = -1;
  DEBUG = -1;

  if (IS_FILE == 1)
    closeFile();
}

/*
 * closeFile: closes file handler fl
 */
void closeFile() {
  if (IS_OPEN == 1) {
    IS_OPEN = 0;
    fflush(fl);
    fclose(fl);
  }
}

/*
 * setFile: sets the file route on rt variable
 */
void setFile(char* route) {
  IS_FILE = 1;
  rt = (char*)malloc(sizeof(char) * strlen(route));
  
  if (rt == NULL)
    return;

  memcpy(rt, route, sizeof(char) * strlen(route));

  rt[strlen(route)] = '\0';
}

/*
 * setShowTime: sets an indicator to show time (clock() function).
 * 1: show; 0: don't show. If "st" have neither values, an 1 it's assumed.
 */
void setShowTime(int st) {
    if (st == 0 || st == 1) {
        showTime = st;
    } else {
        showTime = 1;
    }
}

/*
 * printTab: sets the tabulation, based on CURRDEPTH
 */
static void printTab() {
  int c = 0;

  for (; c < CURR_DEPTH; c++) 
    if (IS_FILE == 1) 
      fputs("\t", fl);
    else 
      printf("\t");
}

/*
 * _log: logs the text on the output.
 */
void _log(char* text, ...) {
  char* p;
  va_list pa;
  va_start(pa, text);

  int lv = va_arg(pa, int);
  int write = 0;

  //if the current DEBUG it's greater than lv, do not log
  if (DEBUG > lv)
    return;

  //if there's no "activateLog", we'll do it with default value
  if (IS_ON == 0)
    activateLog(0);

  //if there was a "deactivateLog", we'll exit
  if (IS_ON == -1)
    return;

  //if no file was open, open it
  if (IS_FILE == 1)
    openFile();

  //print current execution tick (clock) only if wanted
  if (showTime == 1) {
      if (IS_FILE == 1)
          fprintf(fl, "%i:\t", clock());
      else
          printf("%d:\t", clock());
  }

  //set the tabulation
  printTab();

  //print the content, printf style
  for (p = text; *p; p++) 
    if (*p != '%')
      if (write == 0)
        if (IS_FILE == 1) 
          fputc(*p, fl);
        else 
          putchar(*p);
      else 
        write = 0;
    else
      switch (*++p) {
      case 'd':
        if (IS_FILE == 1) 
          fprintf(fl, "%d", va_arg(pa, int));
        else
          printf("%d", va_arg(pa, int));
        
        break;
      case 's':
        if (IS_FILE == 1) 
          fprintf(fl, "%s", va_arg(pa, char*));
        else 
          printf("%s", va_arg(pa, char*));

        break;
      case 'i':
        if (IS_FILE == 1) 
          fprintf(fl, "%i", va_arg(pa, int));
        else 
          printf("%i", va_arg(pa, int));
        
        break;
      default:
        if (IS_FILE == 1) 
          fputc(*p, fl);
        else
          putchar(*p);
        
        break;
      }

  va_end(pa);

  //put EOL
  if (IS_FILE == 1) {
    fputs("\n", fl);
    fflush(fl);
  }else 
    printf("\n");
}
