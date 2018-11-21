#ifndef _UTILITIES_H
#define _UTILITIES_H

int** createMatrix(int n, int m);
void showMatrix(int n, int m, int** matrix);
int* createList(int n);
void showList(int* list, int n);
unsigned long factorial(unsigned long f);

// Bubble Sort ~O(n^2)
int* bubbleSort(int* unsortedList, int end);

// QuickSort ~O(nlogn)
int* quickSort(int* unsortedList, int start, int end);
int searchPivot(int* unsortedList, int start, int end);
int makePartition(int* unsortedList, int start, int end, int indexPivot);
int* makeSwap(int* unsortedList, int i, int j);
// End QuickSort
#endif