#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <binarytree.h>

btree* insertInversion(btree* currentInversion, int cost, int utility)
{
	btree* newInversion = NULL;
	if (NULL == currentInversion)
	{
		newInversion = createDecisionInversion(cost, utility, NULL, NULL);
		return newInversion;
	}

	int currentCost = currentInversion->cost;
	int currentUtility = currentInversion->utility;
	int newCost = 0;
	int newUtilty = 0;

	if(NULL == getleftInversion(currentInversion) && NULL == getrightInversion(currentInversion))
	{
		newCost = currentCost;
		newUtilty = currentUtility;
		currentInversion->leftInversion = createDecisionInversion(newCost, newUtilty, NULL, NULL);

		newCost = currentCost + cost;
		newUtilty = currentUtility + utility;
		currentInversion->rightInversion = createDecisionInversion(newCost, newUtilty, NULL, NULL);
		return currentInversion;
	}
	currentInversion->leftInversion = insertInversion(getleftInversion(currentInversion), cost, utility);
	currentInversion->rightInversion = insertInversion(getrightInversion(currentInversion), cost, utility);
	return currentInversion;
}

btree* createDecisionInversion(int cost, int utility, btree* leftInversion, btree* rightInversion)
{
	btree* newInversion = (btree*)malloc(sizeof(btree)); 
	if(NULL != newInversion)
	{ 
	    newInversion->cost = cost;
	    newInversion->utility = utility;
		newInversion->leftInversion = leftInversion;
		newInversion->rightInversion = rightInversion;
		return newInversion;
	} 
	printf("No es posible asignar memoria para createDecisionInversion()");
	printf("Error in binarytree.c");
	return NULL;
}

btree* getleftInversion(btree* currentTree)
{
	if (currentTree == NULL)
	{
		return NULL;
	}
	else
	{
		return currentTree->leftInversion;
	}
}

btree* getrightInversion(btree* currentTree)
{
	if (currentTree == NULL)
	{
		return NULL;
	}
	else
	{
		return currentTree->rightInversion;
	}
}

void inOrder(btree* currentInversion)
{
	if (currentInversion != NULL)
	{ 
		inOrder(currentInversion->leftInversion);
		printf("%d\n", currentInversion->cost);
 		inOrder(currentInversion->rightInversion);

 	}
}

void preOrder(btree* currentInversion)
{
	if (currentInversion != NULL)
	{ 
		printf("%d\n", currentInversion->cost);
		preOrder(currentInversion->leftInversion);
		preOrder(currentInversion->rightInversion);
 	}
}

void postOrder(btree* currentInversion)
{
	if (currentInversion != NULL)
	{ 
		postOrder(currentInversion->leftInversion);
		postOrder(currentInversion->rightInversion);
		printf("%d\n", currentInversion->cost);
		
 	}
}

void freeTree(btree* decisionTree)
{
	if (decisionTree != NULL)
	{ 
		freeTree(decisionTree->leftInversion);
		freeTree(decisionTree->rightInversion);
		free(decisionTree);
		
 	}
}