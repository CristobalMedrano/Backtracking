#ifndef _FILES_H
#define _FILES_H

/*
    Funciones de lectura.
    Read Functions.
*/
#define SUCCESS 0
#define ERROR_CLOSE -1
#define SAVED 1
#define ERROR 2

char* getFileName();
FILE* openFile(char* fileName);
inv* readFile(FILE* currentFile);
inv* createInversion();
int* setListInversion(int* currentList, int pos, int cost, int utility);
inv* setNewInversion(inv* currentInversion, int initCapital, int availableInv, int* listInversion);
int closeFile(FILE* file, char* fileName);
inv* getInversion();
void freeInversion(inv* inversion);
void saveFile(invHistory* solution);

#endif