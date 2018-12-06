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
    free(currentInversion->listInversion);
    free(currentInversion);
}

btree* createDecisionTree(inv* currentInversion)
{
    btree* decisionTree = NULL;
    int i = 0;
    int j = 0;
    int currentCost = 0;
    int currentUtility = 0;

    decisionTree = insertInversion(decisionTree, 0, 0);
    while(j < currentInversion->availableInv)
    {
        currentCost = currentInversion->listInversion[i];
        currentUtility = currentInversion->listInversion[i+1];
        decisionTree = insertInversion(decisionTree, currentCost, currentUtility);
        i = i + 2;
        j++;
    }
    return decisionTree;
}

void backtracking()
{
    
}