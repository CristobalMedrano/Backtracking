#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <utilities.h>

// Funciones utilitarias basicas, que aportan al desarrollo de la solucion.
int** createMatrix(int n, int m)
{
    int i = 0;
    int** matrix = (int **)calloc(n, sizeof(int *));
                        for (i = 0; i < n; i++)
                        matrix[i] = (int *)calloc(m, sizeof(int));
    if(NULL != matrix)
    {
        return matrix;
    }
    printf("Memoria insuficiente: createMatrix()\n");
    printf("Error: utilities.c\n");
    return NULL;
}

void showMatrix(int n, int m, int** matrix)
{
    if(NULL != matrix && n >= 0 && m >= 0)
    {
        int i = 0;
        for(i = 0; i < n; i++)
        {
            int j = 0;
            for(j = 0; j < m; j++)
            {
                if (matrix[i][j] > 9) 
                {
                    printf("%d  ", matrix[i][j]);
                }
                else
                {
                    printf("%d   ", matrix[i][j]);
                }
            }
            printf("\n");
        }
    }   
}

int* createList(int length)
{
    int* newList = (int*)calloc(length, sizeof(int));
    
    if (NULL != newList) 
    {
        return newList;
    }
    return NULL;
}

int* insertData(int* list, int length, int data)
{
    if (length >= 0) 
    {
        list = (int*)realloc(list, sizeof(int)*(length+1));
        if (NULL != list) 
        {
            list[length] = data;
            return list;
        }    
    }  
    return list;
}

void showList(int* list, int n)
{
    if (NULL != list && n >= 0)
    {
        int i;
        for(i = 0; i < n; i++)
        {
            printf("%d\n", list[i]);
        }
    }    
}

unsigned long factorial(unsigned long f)
{
    if ( f == 0 ) 
        return 1;
    return(f * factorial(f - 1));
}

int* quickSort(int* unsortedList, int start, int end)
{
   if (start < end) 
    {
        int indexPivot  = searchPivot(unsortedList, start, end);
        int cut         = makePartition(unsortedList, start, end, indexPivot);
        unsortedList    = quickSort(unsortedList, start, cut - 1);
        unsortedList    = quickSort(unsortedList, cut + 1, end);
        return unsortedList;
    }
    return unsortedList;
}

int searchPivot(int* unsortedList, int start, int end)
{
    int i = 0;
    for(i = start + 1; i < end; i++)
    {
        if (unsortedList[i] > unsortedList[start])
        {
            return i;
        }
        if(unsortedList[i] < unsortedList[start])
        {
            return start;            
        }
    }
    return end;
    
}

int makePartition(int* unsortedList, int start, int end, int indexPivot)
{
    int pivot       = unsortedList[indexPivot];
    unsortedList    = makeSwap(unsortedList, indexPivot, end);
    indexPivot      = end;   
    int left        = start;
    int right       = end - 1;
    do
    {
        unsortedList = makeSwap(unsortedList, left, right);

        while(unsortedList[left] < pivot)
        {
            left++;
        } 
        while(unsortedList[right] >= pivot)
        {
            right--;
        }
    } while (left < right);
    
    unsortedList  =  makeSwap(unsortedList,  left,  indexPivot);

    return left;
}

int* makeSwap(int* unsortedList, int i, int j)
{    
    int costAux;

    if (i != j) 
    {
        costAux = unsortedList[i];
        unsortedList[i]  = unsortedList[j];
        unsortedList[j]  = costAux;
    }
    return unsortedList;
}

int* bubbleSort(int* unsortedList, int end)
{
    int i;
    for(i = end; i > 1; i--)
    {
        int j;
        for(j = 0; j < i - 1; j++)
        {
            if (unsortedList[j] > unsortedList[j + 1])
            {
                unsortedList = makeSwap(unsortedList, j, j + 1);
            }   
        }
    }  
    printf("Memoria insuficiente: createList()\n");
    printf("Error: utilities.c\n");
    return unsortedList;
}