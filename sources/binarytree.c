#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <binarytree.h>
#include <utilities.h>

btree* createDecisionInversion(int status, int level, int currentCost, int currentUtility, int cost, int utility, btree* previousInversion, btree* leftInversion, btree* rightInversion)
{
	btree* newInversion = (btree*)malloc(sizeof(btree)); 
	if(NULL != newInversion)
	{ 
		newInversion->status 			= status;
		newInversion->level 			= level;
		newInversion->currentCost 		= currentCost;
		newInversion->currentUtility 	= currentUtility;
	    newInversion->cost 				= cost;
	    newInversion->utility 			= utility;
		newInversion->previousInversion = previousInversion;
		newInversion->leftInversion 	= leftInversion;
		newInversion->rightInversion 	= rightInversion;
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
		printf("Cost: %d, Utility: %d\n", currentInversion->currentCost, currentInversion->currentUtility);
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