#include "bucketSort.h"
#include "measurements.h"

using namespace std;

int sizeInput, nBuckets, sizeBuckets , nThreads, nRepeticoes;

int main(int argc, char **argv) {

    if(argc<4) {
        printf("Run: ./bin/main nElementos nThreads nRepeticoesRun\n");
        return 1;
    }
    
    sizeInput = atoi(argv[1]); //tamanho do array de Input
    nThreads = atoi(argv[2]);
    nRepeticoes = atoi(argv[3]);

    int numerosInputSeq[sizeInput]; //array input, com numeros random, dados por um intervalo [0,sizeMax]
	//int numerosInputPrl[sizeInput];
	
    for( int i = 0; i < nRepeticoes ; i++ ){
        geraInputs(numerosInputSeq,sizeInput);

        //copy(numerosInputSeq, numerosInputSeq+sizeInput, numerosInputPrl);

        cout << "\nA preencher array com " << sizeInput << " elementos ...\n" << endl;
        
        clearCache();
        startCounters();

        bucketSortSeq(numerosInputSeq, sizeInput);

        stopCounters(-1);

        //printArray(numerosInputSeq,sizeInput);
        
        //bucketSortPrl
    }
    
    printResults(nThreads, sizeInput);

    return 0;

}