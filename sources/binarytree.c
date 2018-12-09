#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <binarytree.h>

#define CAPITAL 1400000

btree* backtracking(btree* currentInversion, int cost, int utility, int capital)
{
	if (NULL == currentInversion)
	{
		btree* newInversion = createDecisionInversion(cost, utility, NULL, NULL);
		return newInversion;
	}

	int currentCost = currentInversion->cost;
	int currentUtility = currentInversion->utility;
	int newCost = 0;
	int newUtilty = 0;

	if(NULL == getleftInversion(currentInversion) && NULL == getrightInversion(currentInversion))
	{
		// Dont invest
		newCost = currentCost;
		newUtilty = currentUtility;
		currentInversion->leftInversion = createDecisionInversion(newCost, newUtilty, NULL, NULL);

		// Do invest
		newCost = currentCost + cost;
		newUtilty = currentUtility + utility;
		if (canInvest(newCost, capital) == YES) 
		{
			currentInversion->rightInversion = createDecisionInversion(newCost, newUtilty, NULL, NULL);
		}
		return currentInversion;
	}
	
	// Esto evita que se generen resultados erroneos, si ya se descarto la rama, no la vuelvo a generar.
	if (NULL != getleftInversion(currentInversion))
	{
		currentInversion->leftInversion = backtracking(getleftInversion(currentInversion), cost, utility, capital);
	}
	
	if(NULL != getrightInversion(currentInversion))
	{
		currentInversion->rightInversion = backtracking(getrightInversion(currentInversion), cost, utility, capital);
	}
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

int canInvest(int currentCost, int currentCapital)
{
	if (currentCost > currentCapital) 
	{
		return NO;
	}
	return YES;	
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
		printf("Cost: %d, Utility: %d\n", currentInversion->cost, currentInversion->utility);
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

void backTrack(btree* currentInversion)
{
	if (currentInversion != NULL)
	{ 
		printf("%d\n", currentInversion->cost);
		preOrder(currentInversion->leftInversion);
		preOrder(currentInversion->rightInversion);
 	}
}