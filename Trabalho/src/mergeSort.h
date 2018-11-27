#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

//void merge(int arr[], int l, int m, int r);
//void mergeSort(int arr[], int l, int r);

void mergesort(int *v, int n);
void sort(int *v, int *c, int i, int f);
void merge(int *v, int *c, int i, int m, int f);