#include "bucketSort.h"
#include "mergeSort.h"
#include "measurements.h"

using namespace std;

void geraInputs(int numerosInput[], int sizeInput){
    srand (time(NULL)); //Vai gerar sempre numeros diferentes, cada vez que faço run!

	for (int i=0;i<sizeInput;i++){
		numerosInput[i]= rand() % sizeInput;
	}
}

void criarBuckets(int contadores[], int nBuckets){

	for (int i = 0; i < nBuckets; i++){
		contadores[i] = 0;
	}
}

void insereBuckets(int buckets[], int contadores[], int numerosInput[],int sizeInput, int nBuckets){
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

void ordenaBuckets(int buckets[], int contadores[], int sizeInput, int nBuckets){
	for (int i = 0; i < nBuckets; i++){
			if(contadores[i]>0){
                //mergeSort(buckets,i*sizeInput,i*sizeInput+contadores[i]-1);
				mergesort(&buckets[i*sizeInput],contadores[i]);
            }
		}	
}

void ordenaInput(int buckets[],int contadores[], int numerosInput[], int sizeInput, int nBuckets){
	int c=0, pos, max; 
	for (int i = 0; i < nBuckets; i++){
        pos = i*sizeInput;
        max = contadores[i];
		for (int j = 0; j < max ; j++){
            numerosInput[c++] = buckets[pos+j];
		}
	}
}

void bucketSortSeq(int numerosInput[], int sizeInput){

	int nBuckets = (int)sqrt(sizeInput) + 1;
    int sizeBuckets = sizeInput*nBuckets; //tamanho do array de buckets
	int contadores[nBuckets]; //conta quantos elementos estão num dado bucket, atualmente.
    int buckets[sizeBuckets];

	cout << "A criar buckets... " << nBuckets << endl;
	startCountersCriarB();
	criarBuckets(contadores,nBuckets);
	stopCountersCriarB(-1);

	cout << "A inserir os elementos nos buckets..." << endl; 
	startCountersInsereB();
    insereBuckets(buckets,contadores,numerosInput,sizeInput,nBuckets);
    stopCountersInsereB(-1);    

	cout << "A ordenar os elementos nos buckets..." << endl;
	startCountersOrdenaB();	
    ordenaBuckets(buckets,contadores,sizeInput,nBuckets);
	stopCountersOrdenaB(-1);


	cout << "A ordenar o array inicial..." << endl;
	startCountersOrdenaArr();
    ordenaInput(buckets,contadores,numerosInput,sizeInput, nBuckets);
	stopCountersOrdenaArr(-1);
}
