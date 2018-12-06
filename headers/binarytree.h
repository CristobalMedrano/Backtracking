#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#define YES 1
#define NO 0
#define INVALID -1
#define START 2
btree* insertInversion(btree* currentInversion, int cost, int utility);
btree* createDecisionInversion(int cost, int utility, btree* leftInversion, btree* rightInversion);
btree* getleftInversion(btree* currentInversion);
btree* getrightInversion(btree* currentInversion);
int getStatusInversion(btree* currentInversion);
void inOrder(btree* currentInversion);
void preOrder(btree* currentInversion);



#endif