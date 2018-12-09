#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

extern int numThreads;

void criarBucketsPrl(int contadores[], int nBuckets);
void insereBucketsPrl(int buckets[], int contadores[], int numerosInput[],int sizeInput, int nBuckets);
void ordenaBucketsPrl(int buckets[], int contadores[], int sizeInput, int nBuckets);
void ordenaInputPrl(int buckets[],int contadores[], int numerosInput[], int sizeInput, int nBuckets);
void bucketSortPrl(int numerosInput[], int sizeInput, int nBuckets);