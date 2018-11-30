#include "bucketSort.h"
#include "mergeSort.h"

void geraInputs(int numerosInput[], int sizeInput){
    srand (time(NULL)); //Vai gerar sempre numeros diferentes, cada vez que faço run!

	for (int i=0;i<sizeInput;i++){
		numerosInput[i]= rand() % sizeInput;
	}
}

void criarBuckets(int contadores[], int nBuckets){
	/*for (int i = 0; i < sizeBuckets; i++){ //nao sei se é preciso inicializar este array
		buckets[i]=0;
	}*/
	
	for (int i = 0; i < nBuckets; i++){
		contadores[i] = 0;
	}
}

void insereBuckets(int buckets[], int contadores[], int numerosInput[],int sizeInput){
	int numBucket;
	for (int i = 0; i < sizeInput; i++){
		numBucket=(int)sqrt(numerosInput[i]);

		buckets[(numBucket*sizeInput)+contadores[numBucket]]=numerosInput[i];
		contadores[numBucket]++;
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

void printArray(int array[], int sizeArray){
	printf("[");
	for (int i = 0; i < sizeArray; i++){
		printf("%d, ", array[i]);
	}
	printf("]\n");

}


void bucketSortSeq(int numerosInput[], int sizeInput){

	int nBuckets = (int)sqrt(sizeInput)+1; // numero de Buckets
    int sizeBuckets = sizeInput*nBuckets; //tamanho do array de buckets
	int contadores[nBuckets]; //conta quantos elementos estão num dado bucket, atualmente.
    int buckets[sizeBuckets];

	criarBuckets(contadores,nBuckets);

    insereBuckets(buckets,contadores,numerosInput,sizeInput);
        
    ordenaBuckets(buckets,contadores,sizeInput,nBuckets);

    ordenaInput(buckets,contadores,numerosInput,sizeInput, nBuckets);
}
