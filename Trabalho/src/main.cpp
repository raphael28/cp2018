#include "bucketSort.h"
#include "measurements.h"

int sizeInput, nBuckets, sizeBuckets;

int main(int argc, char **argv) {

    if(argc!=2) {
        printf("Não inseriu o tamanho do array input!\n");
        return 1;
    }
    
    sizeInput = atoi(argv[1]); //tamanho do array de Input
	nBuckets = (int)sqrt(sizeInput)+1; 
/*
    nº de buckets que irão ser criados, dado por raízquadrada(sizeInput)+1
    Tem de ser +1, pois ao inicializar o ciclo só vai até N
*/
    sizeBuckets = sizeInput*nBuckets; //tamanho do array de buckets

    printf("\nTAMANHO ARRAY INPUT = %d\n",sizeInput);
    printf("\nTAMANHO BUCKETS = %d\n",sizeBuckets);
    printf("\nNº BUCKETS = %d\n",nBuckets);

    int numerosInput[sizeInput]; //array input, com numeros random, dados por um intervalo [0,sizeMax]
	int contadores[nBuckets]; //conta quantos elementos estão num dado bucket, atualmente.
    int buckets[sizeBuckets];
/*
    Array de buckets
    Sempre que se quer aceder a um dado bucket -> pos * sizeInput
    Pois, cada bucket irá ter um tamanho máximo do size do array de Input
*/	
    geraInputs(numerosInput,sizeInput); //funçao que preenche o array de Input com numeros random
    printf("\nGEREI INPUTS!\n");

startCounters();
    for(int i = 0; i< 5; i++){
        criarBuckets(buckets,contadores,sizeBuckets,nBuckets); //Função que inicializa, a 0, todos os buckets e inicializa também todos os contadores, de cada bucket, a 0.
        printf("\nCRIEI BUCKETS!\n");

        insereBuckets(buckets,contadores,numerosInput,sizeInput); //Função que insere todos os numeros do array de input em cada bucket
        printf("\nINSERI NOS BUCKETS!\n");

    /*
        for(int i=0 ; i<nBuckets; i++){
            printArray(&buckets[i*sizeInput],contadores[i]);
        }
    */
        ordenaBuckets(buckets,contadores,sizeInput,nBuckets);
        printf("\nORDENEI OS ELEMENTOS EM CADA BUCKET!\n");
    /*
        for(int i=0 ; i<nBuckets; i++){
            printArray(&buckets[i*sizeInput],contadores[i]);
        }
    */
        ordenaInput(buckets,contadores,numerosInput,sizeInput, nBuckets);
        printf("\nORDENEI O ARRAY DE INPUT!\n");
    }
    stopCounters(-1);
    
    printResults(0);

    return 0;

}