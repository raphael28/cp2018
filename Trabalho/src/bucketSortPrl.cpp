#include "bucketSortPrl.h"
#include "mergeSort.h"
#include "measurements.h"
#include <omp.h>

using namespace std;
int numThreads;

void criarBucketsPrl(int contadores[], int nBuckets){
	for (int i = 0; i < nBuckets; i++){
		contadores[i] = 0;
	}
}

void insereBucketsPrl(int buckets[], int contadores[], int numerosInput[],int sizeInput,int nBuckets){
	float numBucket;
	int index;
	float sizeInputFloat = (float) sizeInput; 
	float indexFloat;

	for (int i = 0; i < sizeInput; i++){

		numBucket = numerosInput[i]/sizeInputFloat;
		indexFloat = numBucket*nBuckets;
		index = (int) indexFloat;

		buckets[(index*sizeInput)+contadores[index]]=numerosInput[i];
		contadores[index]++;
	}
} 

void ordenaBucketsPrl(int buckets[], int contadores[], int sizeInput, int nBuckets){

	#pragma omp parallel for num_threads (numThreads) schedule (dynamic,nBuckets/numThreads) 
    for (int i = 0; i < nBuckets; i++){
			if(contadores[i]>0){
				mergesort(&buckets[i*sizeInput],contadores[i]);
            }
		}	
}

void ordenaInputPrl(int buckets[],int contadores[], int numerosInput[], int sizeInput, int nBuckets){
	int c=0, pos, max; 
	for (int i = 0; i < nBuckets; i++){
        pos = i*sizeInput;
        max = contadores[i];
		for (int j = 0; j < max ; j++){
            numerosInput[c++] = buckets[pos+j];
		}
	}
}

void bucketSortPrl(int numerosInput[], int sizeInput, int nBuckets){

    int sizeBuckets = sizeInput*nBuckets; //tamanho do array de buckets
	int contadores[nBuckets]; //conta quantos elementos estão num dado bucket, atualmente.
    int buckets[sizeBuckets];

    cout << "A criar buckets... " << nBuckets << endl;
	startCountersCriarB();
    criarBucketsPrl(contadores,nBuckets);
    stopCountersCriarB(numThreads);

    cout << "A inserir os elementos nos buckets..." << endl; 
    startCountersInsereB();
    insereBucketsPrl(buckets,contadores,numerosInput,sizeInput,nBuckets);
    stopCountersInsereB(numThreads);

    cout << "A ordenar os elementos nos buckets..." << endl;
    startCountersOrdenaB();
    ordenaBucketsPrl(buckets,contadores,sizeInput,nBuckets);
    stopCountersOrdenaB(numThreads);

    cout << "A ordenar o array inicial..." << endl;
    startCountersOrdenaArr();
    ordenaInputPrl(buckets,contadores,numerosInput,sizeInput, nBuckets);
    stopCountersOrdenaArr(numThreads);                  
}


