#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#define YES 1
#define NO 0
#define INVALID -1
#define START 2

btree* createDecisionInversion(int status, int level, int currentCost, int currentUtility, int cost, int utility, btree* previousInversion, btree* leftInversion, btree* rightInversion);
btree* getleftInversion(btree* currentTree);
btree* getrightInversion(btree* currentTree);
void inOrder(btree* currentInversion);
void preOrder(btree* currentInversion);
void postOrder(btree* currentInversion);
void freeTree(btree* decisionTree);

#endif