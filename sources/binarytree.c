#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <binarytree.h>
#include <utilities.h>

/*
	Crea un nodo de inversion.
*/
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

// Obtiene la inversion de la izquierda
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

// Obtiene la inversion de la derecha.
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

// Recorrido en in orden
void inOrder(btree* currentInversion)
{
	if (currentInversion != NULL)
	{ 
		inOrder(currentInversion->leftInversion);
		printf("%d\n", currentInversion->cost);
 		inOrder(currentInversion->rightInversion);

 	}
}

// Recorrido en pre orden
void preOrder(btree* currentInversion)
{
	if (currentInversion != NULL)
	{ 
		printf("Cost: %d, Utility: %d\n", currentInversion->currentCost, currentInversion->currentUtility);
		preOrder(currentInversion->leftInversion);
		preOrder(currentInversion->rightInversion);
 	}
}

// Recorrido en post orden
void postOrder(btree* currentInversion)
{
	if (currentInversion != NULL)
	{ 
		postOrder(currentInversion->leftInversion);
		postOrder(currentInversion->rightInversion);
		printf("%d\n", currentInversion->cost);
		
 	}
}

// Libera la memoria de un arbol de decision.
void freeTree(btree* decisionTree)
{
	if (decisionTree != NULL)
	{ 
		freeTree(decisionTree->leftInversion);
		freeTree(decisionTree->rightInversion);
		free(decisionTree);
		
 	}
}