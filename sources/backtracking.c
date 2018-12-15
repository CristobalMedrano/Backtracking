#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <structs.h>
#include <backtracking.h>
#include <menu.h>
#include <files.h>
#include <binarytree.h>
#include <utilities.h>

/*
    Entrada: Vacia
    Procedimiento: Inicia el menu de la aplicacion.
    Salida: Vacia

*/
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

/*
    Entrada: Vacia
    Procedimiento: Comienza la ejecucion del programa, lee los datos del archivo, 
                   utiliza backtracking para obtener la mejor inversion y guarda
                   esos datos en otro archivo.
    Salida: Vacia
*/
void runBacktracking()
{
    // Se leen los datos desde el archivo.
    inv* currentInversion = getInversion();
    
    if (NULL != currentInversion) 
    {
        #ifdef DEBUG
            printf("Capital inicial: %d\n", currentInversion->initCapital);
            printf("Inversiones disponibles: %d\n", currentInversion->availableInv);
        #endif
        
        // Se genera la mejor solucion usando backtracking.
        invHistory* solution = getBestInversions(currentInversion);
        
        if (NULL != solution) 
        {   
            saveFile(solution);       

            if (NULL != solution->details) 
            {
                #ifdef DEBUG
                    printf("capital usado: %d, ut: %d\n", solution->capital, solution->utility);
                    showList(solution->details, solution->length);
                #endif
                free(solution->details);
            }
            free(solution);
        }
        freeInversion(currentInversion);
    }
}
/*
    Entrada: Estructura de datos con el capital inicial, numero de inversiones y
             su respectiva lista de inversiones.
    Procedimiento: A partir de los datos de entrada, realiza backtracking por cada
             inversion ingresada, al finalizar obtiene la solucion optima de las 
             inversiones a seguir.
    Salida:  Retorna una estructura de datos que contiene:
                - capital usado
                - utilidad de inversiones realizadas
                - largo de la lista de inversiones realizadas
                - detalles de las inversiones realizadas (lista con las inversiones
                  que se hicieron)
*/
invHistory* getBestInversions(inv* currentInversion)
{
    printf("Procesando inversiones...\n");
    if(NULL != currentInversion)
    {
        invHistory* solution    = NULL;

        // inversionTree es un arbol de decision que es generado usando backtracking.
        btree* inversionTree    = NULL;
        int capital             = currentInversion->initCapital;
        int availableInversions = currentInversion->availableInv;
        int inversionCost       = 0;
        int inversionUtility    = 0;
        int i                   = 0;
        int level               = 0;

        /*
            Se crea una solucion vacia para ser rellenada durante backtracking
            Esta solucion tiene capital usado, utilidad de las inversiones, 
            largo de la lista solucion y la lista de soluciones(inversiones 
            realizadas)
        */
        solution = createInvHistory();
        if (NULL != solution) 
        {
            /*
                Se genera el primer nodo del arbol de inversion.
            */
            inversionTree = backtracking(inversionTree, 0, 0, capital, 0, availableInversions, &solution);
            level++;

            /*
                Mientras existan inversiones por insertar, se realiza la insercion y se aplica
                backtracking para obtener la mejor utilidad.
            */
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
                // Se libera la memoria usada por backtracking al crear el arbol de decision.
                freeTree(inversionTree);
            }
            // Se retorna la mejor solucion del arbol.
            return solution;   
        }
        else
        {
            return NULL;
        }       
    }
    return NULL;
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

/*
    Entrada: 
        - nodo de un arbol de inversiones
        - coste de la nueva inversion
        - utilidad de la nueva inversion
        - capital disponible para invertir
        - nivel de la nueva inversion
        - maximo nivel de inversiones a realizar.
        - estructura de datos donde se almacena la solucion.
    Procedimiento: Por cada inversion ingresada, se crea o actualiza el
                   arbol de decision. Si el nivel de la inversion insertada
                   es el mismo que el total de inversiones disponibles,
                   entonces se actualiza la solucion con la mejor utilidad
                   obtenida hasta aquella inversion. El procedimiento que 
                   realiza backtracking para cumplir con lo anterior es:
                   - Recibe la inversion,recorre la rama izquierda hasta
                   insertarla, una vez que la inserta revisa si es la ultima,
                   si cumple lo anterior actualiza el valor de solution si es
                   que es necesario (La utilidad de esa inversion es mayor a la
                   utilidad de la solucion actual), si no, realiza el proceso de
                   insertar la rama derecha del nodo (realizar esa inversion) y 
                   repite el proceso de validacion. Esto ademas se acota segun
                   el capital disponible, si el capital inicial es superado por
                   alguna rama, esa rama no se revisa y se continua. Una vez
                   que se realizaron todas las inversiones, se retorna el arbol
                   con todas las inversiones realizadas.
    Salida: Arbol de decision con las inversiones validas a realizar.
*/
btree* backtracking(btree* currentInversion, int cost, int utility, int capital, int level, int maxLevel, invHistory** solution)
{
	if (NULL == currentInversion)
	{
        // Se crea el nodo inicial
		btree* newInversion = createDecisionInversion(START, level, cost, utility, cost, utility, NULL, NULL, NULL);
        #ifdef DEBUG
            printCurrent(newInversion);
        #endif
		return newInversion;
	}

    // Se calcula el capital invertido hasta el momento.
	int currentCost = currentInversion->currentCost;
    // Se calcula la utilidad obtenida hasta el momento.
	int currentUtility = currentInversion->currentUtility;
	int newCost = 0;
	int newUtility = 0;

    // Se revisa si no contiene inversion a la izquierda y a la derecha
	if(NULL == getleftInversion(currentInversion) && NULL == getrightInversion(currentInversion))
	{
		// Se decide no invertir, agregando la inversion al lado izquierdo del nodo actual.
		newCost = currentCost;
		newUtility = currentUtility;
		currentInversion->leftInversion = createDecisionInversion(NO, level, newCost, newUtility, cost, utility, currentInversion, NULL, NULL);
		
        printCurrent(currentInversion->leftInversion);
		
        // Se verifica el nivel de la inversion actual y se compara con el maximo nivel posible
        // si coincide se actualiza la solucion.
        if(level == maxLevel)
		{
			*solution = updateSolution(*solution, currentInversion->leftInversion);
		}
	
		// Se decide invertir, agregando la inversion al lado derecho del nodo actual.
        // Se calcula el coste de invertir, si supera al capital total, no se invierte.
		newCost = currentCost + cost;
		if (canInvest(newCost, capital) == YES) 
		{
            // Se calcula la nueva utilidad.
			newUtility = currentUtility + utility;
			currentInversion->rightInversion = createDecisionInversion(YES, level, newCost, newUtility, cost, utility, currentInversion, NULL, NULL);
			
            printCurrent(currentInversion->rightInversion);

            // Se verifica el nivel de la inversion actual y se compara con el maximo nivel posible
            // si coincide se actualiza la solucion.
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

/*
    Entrada: nodo actual de inversion, un nodo esta compusto por:
        - Status: Estado de la inversion (Fue invertida? Si/No (1/0))
        - Level: Nivel del nodo
        - CurrentCost: Costo acumulado hasta esa inversion(nodo)
        - CurrentUtility: Utilidad acumulada hasta esa inversion
        - Cost: Coste de la inversion
        - Utility: Utilidad de la inversion
        - Puntero a la Inversion anterior
        - Puntero a la inversion izquierda (no invertir)
        - Puntero a la inversion derecha (invertir)
    Procedimiento: Muestra todos los datos asociados la nodo ya descrito
    Salida: Vacia, solo muestra por pantalla los datos.
*/
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

// Se verifica si es posible invertir.
int canInvest(int currentCost, int currentCapital)
{
	if (currentCost > currentCapital) 
	{
		return NO;
	}
	return YES;	
}

// Se actualiza la solucion a una que tenga mejor utilidad.
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

// Se genera un historial de inversion, es decir, las inversiones que se han realizado
// hasta ese nodo.
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
            // Se inserta la inversion a la lista de inversiones.
			listInversion = insertData(listInversion, length, inversion->cost);
			length++;
		}
		inversion = inversion->previousInversion;
	}
	solution->length = length;
	solution->details = listInversion;

	return solution;
}
