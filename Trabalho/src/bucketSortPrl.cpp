#include "bucketSortPrl.h"
#include "mergeSort.h"
#include "measurements.h"
#include <omp.h>

using namespace std;

void criarBucketsPrl(int contadores[], int nBuckets){
    #pragma omp parallel for num_threads (2)
	for (int i = 0; i < nBuckets; i++){
		contadores[i] = 0;
	}
}

void insereBucketsPrl(int buckets[], int contadores[], int numerosInput[],int sizeInput){
	int numBucket;
	for (int i = 0; i < sizeInput; i++){
		numBucket=(int)sqrt(numerosInput[i]);

		buckets[(numBucket*sizeInput)+contadores[numBucket]]=numerosInput[i];
		contadores[numBucket]++;
	}
} 

void ordenaBucketsPrl(int buckets[], int contadores[], int sizeInput, int nBuckets){
	#pragma omp parallel for num_threads (2) schedule (static,nBuckets/2) 
    for (int i = 0; i < nBuckets; i++){
			if(contadores[i]>0){
                //mergeSort(buckets,i*sizeInput,i*sizeInput+contadores[i]-1);
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

void bucketSortPrl(int numerosInput[], int sizeInput){

	int nBuckets = (int)sqrt(sizeInput)+1; // numero de Buckets
    int sizeBuckets = sizeInput*nBuckets; //tamanho do array de buckets
	int contadores[nBuckets]; //conta quantos elementos estão num dado bucket, atualmente.
    int buckets[sizeBuckets];

    //long long unsigned t1I, t2I, t3I, t4I, t1F, t2F, t3F, t4F, ttotal=0;

    
    cout << "A criar buckets..." << endl;
	startCountersCriarB();
    criarBucketsPrl(contadores,nBuckets);
    stopCountersCriarB();

    cout << "A inserir os elementos nos buckets..." << endl; 
    startCountersInsereB();
    insereBucketsPrl(buckets,contadores,numerosInput,sizeInput);
    stopCountersInsereB();

    cout << "A ordenar os elementos nos buckets..." << endl;
    startCountersOrdenaB();
    ordenaBucketsPrl(buckets,contadores,sizeInput,nBuckets);
    stopCountersOrdenaB();

    cout << "A ordenar o array inicial..." << endl;
    startCountersOrdenaArr();
    ordenaInputPrl(buckets,contadores,numerosInput,sizeInput, nBuckets);
    stopCountersOrdenaArr();

    //ttotal = (t1F - t1I)+(t2F - t2I)+(t3F - t3I)+(t4F - t4I);
/*
    cout << "\nTempo criar buckets = " << (t1F - t1I) << " --> (" 
         << (t1F - t1I) << " / " << ttotal << ") = " << ((t1F - t1I)/ttotal) << endl;

    cout << "\nTempo inserir elementos nos buckets = " << (t2F - t2I) << " --> (" 
         << (t2F - t2I) << " / " << ttotal << ") = " << ((t2F - t2I)/ttotal) << endl;

    cout << "\nTempo ordenar elementos nos buckets = " << (t3F - t3I) << " --> (" 
         << (t3F - t3I) << " / " << ttotal << ") = " << ((t3F - t3I)/ttotal) << endl;

    cout << "\nTempo ordenar array inicial = " << (t4F - t4I) << " --> (" 
         << (t4F - t4I) << " / " << ttotal << ") = " << ((t4F - t4I)/ttotal) << endl;*/                  
}


