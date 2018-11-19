/*
	Autor/Author: Cristobal Medrano Alvarado.
	Funciones asociadas al menu.
	Functions associated with the menu
*/

#include <stdio.h>
#include <stdlib.h>
#include <menu.h>

void showMenu()
{
    printf("***------------------------------***\n");
    printf("**                                **\n");
    #ifdef DEBUG
    printf("*   Clover Inversions(Debug Mode)  *\n");
    #endif
    #ifndef DEBUG
    printf("*         Clover Inversions        *\n");
    #endif
    printf("*            Version 0.0           *\n");
    printf("**                                **\n");
    printf("***------------------------------***\n");
    printf("\n");
    printf("1.- Obtener el maximo de utilidad.\n");
    printf("2.- Acerca de.\n");
    printf("3.- Salir.\n\n");
    printf("Ingrese la opcion deseada: ");
}

void validateMenuOption(int* option, int min, int max)
{
    do
    {
        fflush(stdin);
        if ((scanf("%d", option) == 0) || (*option < min || *option > max))
        {
            while (getchar() != '\n');
            printf("Error. Ingrese una opcion valida: ");
            fflush(stdin);
        }
         
    } while (*option < min || *option > max);
}
  
void cleanScreen()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif
 
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void pressToContinue()
{
    fflush(stdin);
    printf("\nPresione intro para continuar...");
    getchar();
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        getchar();
    #endif      
}
 
void about()
{
	cleanScreen();
    printf("Clover Inversions (Lab 2: Backtracking - Algoritmos Avanzados).\n\n");
    printf("Nombre: Cristobal Nicolas Medrano Alvarado.\n");
    printf("Rut: 19.083.864-1\n");
    printf("Correo: cristobal.medrano@usach.cl\n");
	pressToContinue();
}

void menu(int* option, int min, int max)
{
	cleanScreen();
	showMenu();
	validateMenuOption(option, min, max);
}
