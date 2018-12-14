#ifndef _BACKTRACKING_H
#define _BACKTRACKING_H

#define SIN_INGRESO -1
#define BACKTRACKING 1
#define ABOUT 2
#define EXIT 3
#define START 2
#define YES 1
#define NO 0

void initBacktracking();
void runBacktracking();
invHistory* getBestInversions(inv* currentInversion);
invHistory* createInvHistory();

btree* backtracking(btree* currentInversion, int cost, int utility, int capital, int level, int maxLevel, invHistory** solution);
void printCurrent(btree* currentInversion);

int canInvest(int currentCost, int currentCapital);
invHistory* updateSolution(invHistory* solution, btree* currentInversion);
invHistory* inversionHistory(invHistory* solution, btree* currentInversion);


#endif