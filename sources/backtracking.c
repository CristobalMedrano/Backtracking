#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <structs.h>
#include <backtracking.h>
#include <menu.h>
#include <files.h>
#include <binarytree.h>
#include <utilities.h>

void initBacktracking()
{
    int option;
    do
    {
        option = SIN_INGRESO;
        menu(&option, 1, 3);
 
        switch(option)
        {
            case BACKTRACKING:
                runBacktracking();
                pressToContinue();
                break;
  
            case ABOUT:
                about();
                break;
 
            case EXIT:
                printf("Programa finalizado.\n");
                break;
        }

    }while(option != EXIT);
}

void runBacktracking()
{
    // Read file
    inv* currentInversion = getInversion();
    
    if (NULL != currentInversion) 
    {
        #ifdef DEBUG
            printf("Capital inicial: %d\n", currentInversion->initCapital);
            printf("Inversiones disponibles: %d\n", currentInversion->availableInv);
        #endif
        
        invHistory* solution = getBestInversions(currentInversion);
        
        if (NULL != solution) 
        {   
            saveFile(solution);       

            if (NULL != solution->details) 
            {
                #ifdef DEBUG
                    printf("capital usado: %d, ut: %d\n", solution->utility, solution->capital);
                    showList(solution->details, solution->length);
                #endif
                free(solution->details);
            }
            free(solution);
        }
        freeInversion(currentInversion);
    }
}

invHistory* getBestInversions(inv* currentInversion)
{
    if(NULL != currentInversion)
    {
        invHistory* solution    = NULL;
        btree* inversionTree    = NULL;
        int capital             = currentInversion->initCapital;
        int availableInversions = currentInversion->availableInv;
        int inversionCost       = 0;
        int inversionUtility    = 0;
        int i                   = 0;
        int level               = 0;

        solution = createInvHistory();
        if (NULL != solution) 
        {
            inversionTree = backtracking(inversionTree, 0, 0, capital, 0, availableInversions, &solution);
            level++;

            while(level <= availableInversions)
            {
                inversionCost       = currentInversion->listInversion[i];
                inversionUtility    = currentInversion->listInversion[i+1];
                inversionTree       = backtracking(inversionTree, inversionCost, inversionUtility, capital, level, availableInversions, &solution);
                i                   = i + 2;
                level++;
            }
            
            if (NULL != inversionTree) 
            {
                freeTree(inversionTree);
            }
            return solution;   
        }
        else
        {
            return NULL;
        }       
    }
    return NULL;
    
    
    /*
    if (NULL!= solution) {
          
    printf("ut: %d, capital usado: %d\n", solution->utility, solution->capital);
    
    if (solution->length == 0) 
    {
        printf("No hay inversiones realizadas");
    }
    
    showList(solution->details, solution->length);
    free(solution->details);
    free(solution);
    }
  */
    /*
    for(int k = 0; k < availableInversions; k++)
    {
        printf(" %d-%d\n", bestListInversion[k], bestListInversion[k+1]);
    }*/
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
	printf("No es posible asignar memoria para createInvHistory()");
	printf("Error in backtracking.c");
	return NULL;
}

btree* backtracking(btree* currentInversion, int cost, int utility, int capital, int level, int maxLevel, invHistory** solution)
{
	if (NULL == currentInversion)
	{
		btree* newInversion = createDecisionInversion(START, level, cost, utility, cost, utility, NULL, NULL, NULL);
        #ifdef DEBUG
            printCurrent(newInversion);
        #endif
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
		
        printCurrent(currentInversion->leftInversion);
		
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
			
            printCurrent(currentInversion->rightInversion);

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

void printCurrent(btree* currentInversion)
{
    if (NULL != currentInversion) 
    {
        #ifdef DEBUG
            
            if (YES == currentInversion->status) 
            {
                printf("Invertir: Si\n");
            }
            else
            {
                printf("Invertir: No\n");
            }
            printf("Nivel: %d\n", currentInversion->level);
            printf("Capital invertido: %d\n", currentInversion->currentCost);
            printf("Utilidad acumulada: %d\n", currentInversion->currentUtility);
            printf("Costo de la inversion: %d\n", currentInversion->cost);
            printf("Utilidad de la inversion: %d\n", currentInversion->utility);
            pressToContinue();

        #endif
    }
}

int canInvest(int currentCost, int currentCapital)
{
	if (currentCost > currentCapital) 
	{
		return NO;
	}
	return YES;	
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
    if (NULL == solution && NULL == currentInversion) 
	{
		return NULL;
	}

	btree* inversion    = currentInversion;
    int currentUtility  = inversion->currentUtility;
	int capital         = inversion->currentCost;
    solution->capital   = capital;
	solution->utility   = currentUtility;
	int* listInversion  = NULL;
	int length          = 0;

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
