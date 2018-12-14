#ifndef _STRUCTS_H
#define _STRUCTS_H
// Esta estructura es usada para obtener el historial de inversiones realizadas con
// su respectiva utilidad.
typedef struct invHistory
{
    int capital;
    int utility;
    int length;
    int* details;
} invHistory;

// Esta estructura es usada para mantener los datos de la inversion en el arbol de decision.
// La descripcion detalla del uso de esta estructura se encuentra en la funcion printCurrent.(backtracking.c linea 284)
typedef struct btree
{
    int status;
    int level;
    int currentCost;
    int currentUtility;
    int cost;
    int utility;
    struct btree* previousInversion;
    struct btree* leftInversion;
    struct btree* rightInversion;
 
} btree;

// Esta estructura es usada para almacenar los datos de entrada (los que se leen desde el archivo)
// Capital inicial, inversiones disponibles, lista de inversiones con sus respectivas utilidades.
typedef struct inv
{
    int initCapital;
    int availableInv;
    int* listInversion;

} inv;

#endif