/*
 * Logging.h
 *
 *  Created on: 25 ene. 2020
 *      Author: DoHITB
 */

#ifndef LOGGING_H_
#define LOGGING_H_
void setFile(char* route);

void activateLog(int level);
static void openFile();

void deactivateLog();
void closeFile();

void inFunction();
void outFunction();

void setShowTime(int st);

static void printTab();
void _log(char* text, ...);

#endif /* LOGGING_H_ */
