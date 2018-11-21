#include <stdio.h>
#include <stdalign.h>
#include <structs.h>
#include <backtracking.h>
#include <menu.h>
#include <readfile.h>
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
}