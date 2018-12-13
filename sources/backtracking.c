#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <structs.h>
#include <backtracking.h>
#include <menu.h>
#include <readfile.h>
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
            case BRUTE_FORCE:
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
    inv* currentInversion = getInversion();
    #ifdef DEBUG
        printf("Capital inicial: %d\n", currentInversion->initCapital);
        printf("Inversiones disponibles: %d\n", currentInversion->availableInv);
        showList(currentInversion->listInversion, (currentInversion->availableInv)*2);
    #endif
    
    btree* decisionTree = createDecisionTree(currentInversion);
    #ifdef DEBUG
        preOrder(decisionTree);
    #endif
    freeTree(decisionTree);
    freeInversion(currentInversion);
}

btree* createDecisionTree(inv* currentInversion)
{
    btree* decisionTree = NULL;
    int i = 0;
    int level = 0;
    int currentCost = 0;
    int currentUtility = 0;
    int capital = currentInversion->initCapital;
    int availableInversions = currentInversion->availableInv;
    invHistory* solution = createInvHistory();

    decisionTree = backtracking(decisionTree, 0, 0, capital, 0, availableInversions, &solution);
    level++;
    while(level <= availableInversions)
    {
        currentCost = currentInversion->listInversion[i];
        currentUtility = currentInversion->listInversion[i+1];
        decisionTree = backtracking(decisionTree, currentCost, currentUtility, capital, level, availableInversions, &solution);
        i = i + 2;
        level++;
    }
    
    
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
  
    /*
    for(int k = 0; k < availableInversions; k++)
    {
        printf(" %d-%d\n", bestListInversion[k], bestListInversion[k+1]);
    }*/
    
    return decisionTree;
}
