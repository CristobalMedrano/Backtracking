#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structs.h>
#include <files.h>
#include <utilities.h>

// Obtiene el nombre del archivo ingresado por pantalla.
char* getFileName()
{
    printf("Ingrese el nombre del archivo: ");
    char    file[256];
	char*   filename = (char*)malloc(sizeof(char)*256);
    
    if (NULL != filename) 
    {
        fflush(stdin);
        scanf("%s", file);
        fflush(stdin);
        strcpy(filename, file);
        return filename;
    }    
    printf("Memoria insuficiente: getFileName()\n");
    printf("Error: readfile.c\n");
    return NULL;
}

// Abre un archivo.
FILE* openFile(char* fileName)
{
    FILE* currentFile = fopen(fileName, "rb");
    if(NULL != currentFile)
    {
        #ifdef DEBUG
            printf("Archivo '%s' abierto\n", fileName);
        #endif
        return currentFile;
    }
    printf("Error: El archivo '%s' no existe.\n", fileName);
    return NULL;
}

// Lee el archivo de entrada y guarda los datos en la estructura inv.(ver structs.h para mas detalles)
// El formato a leer es: Capital disponible, numero de inversiones y cada inversion con su coste/utilidad.
inv* readFile(FILE* currentFile)
{
    if(NULL != currentFile)
    {
        int initCapital     = 0;
        int availableInv    = 0;

        fscanf(currentFile, "%d", &initCapital);
        fscanf(currentFile, "%d", &availableInv);

        inv* newInversion   = createInversion();
        int* listInversion  = createList(availableInv*2);

        if (NULL != listInversion && NULL != newInversion) 
        {
            int cost    = 0;
            int utility = 0;
            int count   = 0;
            while(count < availableInv*2)
            {
                fscanf(currentFile, "%d", &cost);
                fscanf(currentFile, "%d", &utility);
                listInversion = setListInversion(listInversion, count, cost, utility);
                count = count + 2;
            }
            #ifdef DEBUG
                showList(listInversion, availableInv*2);
            #endif

            newInversion = setNewInversion(newInversion, initCapital, availableInv, listInversion);
            return newInversion;
        }
    }
    return NULL;
}

// Inicia un puntero de inversion.
inv* createInversion()
{
    inv* newInv = (inv*)malloc(sizeof(inv));
    if(NULL != newInv)
    {
        newInv->initCapital     = 0;
        newInv->availableInv    = 0;
        newInv->listInversion   = NULL;
        return newInv;
    }
    printf("Memoria insuficiente: createInversion()\n");
    printf("Error: readfiles.c\n");
    return NULL;
}

// Guarda una inversion en la lista, las posiciones pares son los costos y las impares la utilidad.
int* setListInversion(int* currentList, int pos, int cost, int utility)
{
    if (NULL != currentList && pos >= 0) 
    {
        currentList[pos]        = cost;
        currentList[pos + 1]    = utility;
        return currentList;
    }
    return currentList;
}

// Guarda la nueva inversion.
inv* setNewInversion(inv* currentInversion, int initCapital, int availableInv, int* listInversion)
{
    if (NULL != currentInversion) 
    {
        currentInversion->initCapital   = initCapital;
        currentInversion->availableInv  = availableInv;
        currentInversion->listInversion = listInversion;
        return currentInversion;
    }
    return currentInversion;
}

// Cierra un archivo.
int closeFile(FILE* file, char* fileName)
{
    if (NULL != file && NULL != fileName) 
    {
        if(0 == fclose(file))
        {
            #ifdef DEBUG
                printf("Archivo '%s' cerrado.\n", fileName);
            #endif
            return SUCCESS;
        }
    }
    printf("Error al cerrar el archivo '%s'.\n", fileName);
    return ERROR_CLOSE;
}
/*
    Entrada: Vacia
    Procedimiento: Inicia la lectura del archivo
    Salida: Estructura de datos que contiene el capital inicial,
            el numero de inversiones y la lista de inversiones a
            realizar con sus respectivas utilidades.
*/
inv* getInversion()
{
    char* fileName = getFileName();
    if(NULL != fileName)
    {
        FILE* currentFile = openFile(fileName);
        if(NULL != currentFile)
        {
            inv* newInversion = readFile(currentFile);
            if(NULL != newInversion)
            {
                int status = closeFile(currentFile, fileName);
                if(SUCCESS == status)
                {
                    free(fileName);
                    printf("\nArchivo cargado correctamente.\n");
                    return newInversion;
                }
                #ifdef DEBUG
                    printf("No es posible cerrar el archivo '%s'\n", fileName);
                #endif
                free(newInversion->listInversion);
                free(newInversion);
            }
            #ifdef DEBUG
                printf("No es posible leer un listado de inversiones\n");
            #endif
        }
        #ifdef DEBUG
            printf("No es posible abrir el archivo '%s'\n", fileName);
        #endif
        free(fileName);
    }
    return NULL;
}

// Libera la memoria usada por la inversion
void freeInversion(inv* inversion)
{
    if (NULL != inversion) 
    {
        free(inversion->listInversion);
        free(inversion);
    }
}

// Guarda los datos obtenidos previamente por invHistory en un archivo de salida
// El formato es: Capital usado - Utilidad total obtenida y la lista de inversiones que se realizaron.
void saveFile(invHistory* solution)
{
    if (NULL != solution) 
    {
        FILE* newFile = fopen("Salida.out", "wb");

        if (NULL != newFile) 
        {
            fprintf(newFile, "%d ", solution->capital);
            fprintf(newFile, "%d\n", solution->utility);
            
            
            if (NULL != solution->details) 
            {
                int i = 0;
                for(i = 0; i < solution->length; i++)
                {
                    fprintf(newFile, "%d\n", solution->details[i]);
                }
            }
            else
            {
                fprintf(newFile, "No es posible invertir.");
            }
            printf("Archivo solucion creado correctamente.\n");      
            closeFile(newFile, "Salida.out"); 
        } 
    }
}