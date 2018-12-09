#include "bucketSort.h"
#include "bucketSortPrl.h"
#include "measurements.h"

using namespace std;

int sizeInput, nBuckets, nThreads, nRepeticoes;

void printArray(int array[], int sizeArray){
	printf("[");
	for (int i = 0; i < sizeArray; i++){
		printf("%d, ", array[i]);
	}
	printf("]\n");

}

int testaOrdenado(int array[], int sizeArray){
    
    for(int i = 0; i < sizeArray-1; i++)
    {
        if(array[i+1]<array[i]) {
            printf("ARRAY NAO ORDENADO!");
            return 1;
        }
    }

    printf("ARRAY ORDENADO!");
    
    return 0;
}

int main(int argc, char **argv) {

    if(argc<5) {
        printf("Run: ./bin/main nElementos nBuckets nThreads nRepeticoesRun\n");
        return 1;
    }
    
    sizeInput = atoi(argv[1]); //tamanho do array de Input
    nBuckets = atoi(argv[2]);
    nThreads = atoi(argv[3]);
    numThreads = nThreads;
    nRepeticoes = atoi(argv[4]);

    int numerosInputSeq[sizeInput]; //array input, com numeros random, dados por um intervalo [0,sizeMax]
	int numerosInputPrl[sizeInput];

    //long long unsigned tf=0;
	
    cout << "\n-----------------------------------------------" << endl;

    for( int i = 0; i < nRepeticoes ; i++ ){
        geraInputs(numerosInputSeq,sizeInput);

        copy(numerosInputSeq, numerosInputSeq+sizeInput, numerosInputPrl);

        cout << "\nA preencher array com " << sizeInput << " elementos...\n" << endl;
        
        cout << "\nA iniciar versão sequencial...\n" << endl;

        clearCache();

        startCounters();

        bucketSortSeq(numerosInputSeq, sizeInput,nBuckets);

        stopCounters(-1);
        
        cout << "\nA iniciar versão paralela...\n" << endl;
        
        clearCache();
        startCounters();

        bucketSortPrl(numerosInputPrl,sizeInput,nBuckets);
        stopCounters(nThreads);

        testaOrdenado(numerosInputPrl,sizeInput);

        //cout << "TEMPO = " <<  << "\n" << endl;
    }
    
    cout << "\n- - - - - - - - - - - -" << endl;
    printResults(nThreads, sizeInput, nBuckets);
    cout << "- - - - - - - - - - - -" << endl;
    printResultsFunc(nThreads);
    cout << "- - - - - - - - - - - -\n" << endl;

    //printArray(numerosInputPrl,sizeInput);

    cout << "-----------------------------------------------\n" << endl;
    return 0;

}
