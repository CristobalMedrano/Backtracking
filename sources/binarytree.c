#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <binarytree.h>
#include <utilities.h>

btree* backtracking(btree* currentInversion, int cost, int utility, int capital, int level, int maxLevel, invHistory** solution)
{
	if (NULL == currentInversion)
	{
		btree* newInversion = createDecisionInversion(START, level, cost, utility, cost, utility, NULL, NULL, NULL);
		return newInversion;
	}

	int currentCost = currentInversion->currentCost;
	int currentUtility = currentInversion->currentUtility;
	int newCost = 0;
	int newUtility = 0;

	if(NULL == getleftInversion(currentInversion) && NULL == getrightInversion(currentInversion))
	{
		// Dont invest
		newCost = currentCost;
		newUtility = currentUtility;
		currentInversion->leftInversion = createDecisionInversion(NO, level, newCost, newUtility, cost, utility, currentInversion, NULL, NULL);
		
		if(level == maxLevel)
		{
			*solution = updateSolution(*solution, currentInversion->leftInversion);
		}
		
		// Do invest
		newCost = currentCost + cost;
		if (canInvest(newCost, capital) == YES) 
		{
			newUtility = currentUtility + utility;
			currentInversion->rightInversion = createDecisionInversion(YES, level, newCost, newUtility, cost, utility, currentInversion, NULL, NULL);
			
			if(level == maxLevel)
			{
				*solution = updateSolution(*solution, currentInversion->rightInversion);
			}
		}		
		return currentInversion;
	}
	
	// Esto evita que se generen resultados erroneos, si ya se descarto la rama, no la vuelvo a generar.
	if (NULL != getleftInversion(currentInversion))
	{
		currentInversion->leftInversion = backtracking(getleftInversion(currentInversion), cost, utility, capital, level, maxLevel, solution);
	}
	
	if(NULL != getrightInversion(currentInversion))
	{
		currentInversion->rightInversion = backtracking(getrightInversion(currentInversion), cost, utility, capital, level, maxLevel, solution);
	}
	return currentInversion;
}

btree* createDecisionInversion(int status, int level, int currentCost, int currentUtility, int cost, int utility, btree* previousInversion, btree* leftInversion, btree* rightInversion)
{
	btree* newInversion = (btree*)malloc(sizeof(btree)); 
	if(NULL != newInversion)
	{ 
		newInversion->status = status;
		newInversion->level = level;
		newInversion->currentCost = currentCost;
		newInversion->currentUtility = currentUtility;
	    newInversion->cost = cost;
	    newInversion->utility = utility;
		newInversion->previousInversion = previousInversion;
		newInversion->leftInversion = leftInversion;
		newInversion->rightInversion = rightInversion;
		return newInversion;
	} 
	printf("No es posible asignar memoria para createDecisionInversion()");
	printf("Error in binarytree.c");
	return NULL;
}

invHistory* updateSolution(invHistory* solution, btree* currentInversion)
{
	int newUtility = currentInversion->currentUtility;
	if (newUtility > solution->utility) 
	{
		if (NULL != solution) 
		{
			free(solution->details);
		}
		solution = inversionHistory(solution, currentInversion);
	}
	return solution;
}

invHistory* inversionHistory(invHistory* solution, btree* currentInversion)
{
	int currentUtility = currentInversion->currentUtility;
	int capital = currentInversion->currentCost;
	if (NULL == solution) 
	{
		return NULL;
	}
	solution->capital = capital;
	solution->utility = currentUtility;

	btree* inversion = currentInversion;
	int* listInversion = NULL;
	int length = 0;

	while(NULL != inversion)
	{
		if(YES == inversion->status)
		{
			listInversion = insertData(listInversion, length, inversion->cost);
			length++;
		}
		inversion = inversion->previousInversion;
	}
	solution->length = length;
	solution->details = listInversion;

	return solution;
}

invHistory* createInvHistory()
{
	invHistory* newInvHistory = (invHistory*)malloc(sizeof(invHistory));

	if (NULL != newInvHistory) 
	{
		newInvHistory->capital	= 0;
		newInvHistory->utility	= 0;
		newInvHistory->length 	= 0;
		newInvHistory->details 	= NULL;
		return newInvHistory;
	}
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

void backTrack(btree* currentInversion)
{
	if (currentInversion != NULL)
	{ 
		printf("%d\n", currentInversion->cost);
		preOrder(currentInversion->leftInversion);
		preOrder(currentInversion->rightInversion);
 	}
}