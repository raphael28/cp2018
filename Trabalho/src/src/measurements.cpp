#include "papi.h"
#include "measurements.h"   

using namespace std;

#define NUM_EVENTS 2
#define MAX_THREADS 64

vector<long long unsigned> tempos_sequencial; //vetores para guardar as medições
vector<double> miss_rates_sequencial;

vector<long long unsigned> tempos_paralelo;
vector<double> miss_rates_paralelo;

double clearcache [30000000]; //cache
timeval t; //tempos
long long unsigned tempoInicial; //tempo inicial, variavel global
//unsigned nThreads; //numero de threads, tem de ser uma variavel conhecida pela main (incluir no .h)

long long values[NUM_EVENTS]; // para depois calcular as miss rates == values[0](LOAD_MISSES) / values[1](TOT_INS)

int events[] = { //tipo de eventos que estou a guardar
	PAPI_L1_LDM, //Level 1 load misses
    PAPI_TOT_INS  //Total instructions executed
};


void clearCache() {
	for (unsigned i = 0; i < 30000000; ++i)
		clearcache[i] = i;
}

void startCounters(){
	gettimeofday(&t, NULL);
	tempoInicial = t.tv_sec * 1000000 + t.tv_usec;
    PAPI_library_init(PAPI_VER_CURRENT);
	PAPI_start_counters(events, NUM_EVENTS);
}

long long unsigned stopCounters(int nThread){
	PAPI_stop_counters(values, NUM_EVENTS);

	gettimeofday(&t, NULL);
	long long unsigned tempoFinal = t.tv_sec * 1000000 + t.tv_usec;

	if (nThread == -1){
		tempos_sequencial.push_back(tempoFinal - tempoInicial);
        miss_rates_sequencial.push_back((double)((double)values[0]/(double)(values[1])));
    }
	else {
		tempos_paralelo.push_back(tempoFinal - tempoInicial);
		miss_rates_paralelo.push_back((double)((double)values[0]/(double)(values[1])));
    }

    //cout << "Tempo = " << tempoFinal - tempoInicial << endl;
    //cout << "Miss = " << (double)((double)values[0]/(double)(values[1])) << endl;

	return tempoFinal - tempoInicial;
}

std::pair<long long unsigned, double> mediana(int thread) {
	long long unsigned melhorT = 0;
    double melhorM = 0.0;

	if (thread == - 1) {
        std::sort(tempos_sequencial.begin(), tempos_sequencial.end());
        const auto median_itT = tempos_sequencial.begin() + tempos_sequencial.size() / 2;
        std::nth_element(tempos_sequencial.begin(), median_itT , tempos_sequencial.end());
        melhorT = *median_itT;

        std::sort(miss_rates_sequencial.begin(), miss_rates_sequencial.end());
        const auto median_itM = miss_rates_sequencial.begin() + miss_rates_sequencial.size() / 2;
        std::nth_element(miss_rates_sequencial.begin(), median_itM , miss_rates_sequencial.end());
        melhorM = *median_itM;
        
	} 
	else {
        std::sort(tempos_paralelo.begin(), tempos_paralelo.end());
        const auto median_itT = tempos_paralelo.begin() + tempos_paralelo.size() / 2;
        std::nth_element(tempos_paralelo.begin(), median_itT , tempos_paralelo.end());
        melhorT = *median_itT;

        std::sort(miss_rates_paralelo.begin(), miss_rates_paralelo.end());
        const auto median_itM = miss_rates_paralelo.begin() + miss_rates_paralelo.size() / 2;
        std::nth_element(miss_rates_paralelo.begin(), median_itM , miss_rates_paralelo.end());
        melhorM = *median_itM;

	}

	return std::make_pair(melhorT, melhorM);
}

void printResults (int nThreads, int sizeInput) {
    auto sequencial = mediana(-1);
    //auto paralelo = mediana(nThreads);
    int nBuckets = (int)sqrt(sizeInput)+1; // numero de Buckets
	
    cout << "\n----- Nº elementos = " << sizeInput << ", Nº buckets = " << nBuckets << " -----" << endl;

    cout << "Versão sequencial:\n" 
		 << "\tTempo: " << std::get<0>(sequencial) << " usecs,\n"
         << "\tMiss rate (L1): " << std::get<1>(sequencial) << endl;
	/*
    cout << "Versão sequencial (Nº threads = "<< nThreads << "):\n" 
		 << "\tTempo: " << std::get<0>(paralelo) << " usecs,\n"
         << "\tMiss rate (L1): " << std::get<1>(paralelo) << endl;

    cout << "Speed-up: " << (double)((double)(std::get<0>(sequencial))/(double)(std::get<0>(paralelo))) << endl;*/

    cout << "--------------------------------------------------\n" << endl;
}