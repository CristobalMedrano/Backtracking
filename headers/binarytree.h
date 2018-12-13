#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#define YES 1
#define NO 0
#define INVALID -1
#define START 2

btree* backtracking(btree* currentInversion, int cost, int utility, int capital, int level, int maxLevel, invHistory** solution);
btree* createDecisionInversion(int status, int level, int currentCost, int currentUtility, int cost, int utility, btree* previousInversion, btree* leftInversion, btree* rightInversion);
btree* getleftInversion(btree* currentInversion);
btree* getrightInversion(btree* currentInversion);
int canInvest(int currentCost, int currentCapital);
int bestUtility(int currentUtility, int previousUtility);
int getStatusInversion(btree* currentInversion);
void inOrder(btree* currentInversion);
void preOrder(btree* currentInversion);
void postOrder(btree* currentInversion);

void freeTree(btree* decisionTree);

invHistory* inversionHistory(invHistory* solution, btree* currentInversion);
int bestSolution(int currentUtility, int previousUtility);
invHistory* updateSolution(invHistory* solution, btree* currentInversion);
invHistory* createInvHistory();
#endif