#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

void geraInputs(int numerosInput[],int sizeInput);
void criarBuckets(int buckets[],int contadores[], int sizeBuckets, int nBuckets);
void insereBuckets(int buckets[], int contadores[], int numerosInput[],int sizeInput);
void ordenaBuckets(int buckets[], int contadores[], int sizeInput, int nBuckets);
void ordenaInput(int buckets[],int contadores[], int numerosInput[], int sizeInput, int nBuckets);
void printArray(int array[], int sizeArray);