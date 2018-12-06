#ifndef _BACKTRACKING_H
#define _BACKTRACKING_H

#define SIN_INGRESO -1
#define BRUTE_FORCE 1
#define ABOUT 2
#define EXIT 3
#define START 2
#define YES 1
#define NO 0

void initBacktracking();
void runBacktracking();
void backtracking();
btree* createDecisionTree(inv* currentInversion);
void printCurrent();

#endif