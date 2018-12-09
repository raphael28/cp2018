#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

void geraInputs(int numerosInput[],int sizeInput);
void criarBuckets(int contadores[], int nBuckets);
void insereBuckets(int buckets[], int contadores[], int numerosInput[],int sizeInput,int nBuckets);
void ordenaBuckets(int buckets[], int contadores[], int sizeInput, int nBuckets);
void ordenaInput(int buckets[],int contadores[], int numerosInput[], int sizeInput, int nBuckets);
void bucketSortSeq(int numerosInput[], int sizeInput, int nBuckets);