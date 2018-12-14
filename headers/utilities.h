#ifndef _UTILITIES_H
#define _UTILITIES_H

// For matrix
int** createMatrix(int n, int m);
void showMatrix(int n, int m, int** matrix);

// For list
int* createList(int length);
int* insertData(int* list, int length, int data);
void showList(int* list, int n);

// For math
unsigned long factorial(unsigned long f);

// Bubble Sort ~O(n^2)
int* bubbleSort(int* unsortedList, int end);

// QuickSort ~O(nlogn) necesita traza.
int* quickSort(int* unsortedList, int start, int end);
int searchPivot(int* unsortedList, int start, int end);
int makePartition(int* unsortedList, int start, int end, int indexPivot);
int* makeSwap(int* unsortedList, int i, int j);
// End QuickSort
#endif