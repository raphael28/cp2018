//#include "papi.h"
#include "measurements.h"   

using namespace std;

#define NUM_EVENTS 4
#define MAX_THREADS 64

vector<long long unsigned> tempos_sequencial; //vetores para guardar as medições
vector<double> miss_rates_L1_sequencial;
vector<double> miss_rates_L2_sequencial;
vector<double> miss_rates_L3_sequencial;

vector<long long unsigned> tempos_paralelo;
vector<double> miss_rates_paralelo;


timeval t; //tempos
long long unsigned tempoInicial; //tempo inicial, variavel global

long long unsigned tInicCriarB;
vector<long long unsigned> tempos_CriarB;
long long unsigned tInicInsereB;
vector<long long unsigned> tempos_InsereB;
long long unsigned tInicOrdenaB;
vector<long long unsigned> tempos_OrdenaB;
long long unsigned tInicOrdenaArr;
vector<long long unsigned> tempos_OrdenaArr;

vector<long long unsigned> tempos_paralelo_CriarB;
vector<long long unsigned> tempos_paralelo_InsereB;
vector<long long unsigned> tempos_paralelo_OrdenaB;
vector<long long unsigned> tempos_paralelo_OrdenaArr;

double clearcache [30000000]; //cache

long long values[NUM_EVENTS]; // para depois calcular as miss rates == values[0](LOAD_MISSES) / values[3](TOT_INS)

int events[] = { //tipo de eventos que estou a guardar
	PAPI_L1_LDM, //Level 1 load misses
    PAPI_L2_LDM, //Level 2 load misses
    PAPI_L3_LDM, //Level 3 load misses
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

void startCountersCriarB(){
	timeval tS;
    
    gettimeofday(&tS, NULL);
	tInicCriarB = tS.tv_sec * 1000000 + tS.tv_usec;
}

long long unsigned stopCountersCriarB(int nThread){
	timeval tS;
    
    gettimeofday(&tS, NULL);
	long long unsigned tF = tS.tv_sec * 1000000 + tS.tv_usec;

    if(nThread == -1) tempos_CriarB.push_back(tF - tInicCriarB);
    else  tempos_paralelo_CriarB.push_back(tF - tInicCriarB);

    return (tF - tInicCriarB); 
}

void startCountersInsereB(){
	timeval tS;
    
    gettimeofday(&tS, NULL);
	tInicInsereB = tS.tv_sec * 1000000 + tS.tv_usec;
}

long long unsigned stopCountersInsereB(int nThread){
	timeval tS;
    
    gettimeofday(&tS, NULL);
	long long unsigned tF = tS.tv_sec * 1000000 + tS.tv_usec;

    if(nThread == -1) tempos_InsereB.push_back(tF - tInicInsereB);
    else tempos_paralelo_InsereB.push_back(tF - tInicInsereB);

    return (tF - tInicInsereB); 
}


void startCountersOrdenaB(){
	timeval tS;
    
    gettimeofday(&tS, NULL);
	tInicOrdenaB = tS.tv_sec * 1000000 + tS.tv_usec;
}

long long unsigned stopCountersOrdenaB(int nThread){
	timeval tS;
    
    gettimeofday(&tS, NULL);
	long long unsigned tF = tS.tv_sec * 1000000 + tS.tv_usec;

    if(nThread == -1) tempos_OrdenaB.push_back(tF - tInicOrdenaB);
    else tempos_paralelo_OrdenaB.push_back(tF - tInicOrdenaB);

    return (tF - tInicOrdenaB); 
}

void startCountersOrdenaArr(){
	timeval tS;
    
    gettimeofday(&tS, NULL);
	tInicOrdenaArr = tS.tv_sec * 1000000 + tS.tv_usec;
}

long long unsigned stopCountersOrdenaArr(int nThread){
	timeval tS;
    
    gettimeofday(&tS, NULL);
	long long unsigned tF = tS.tv_sec * 1000000 + tS.tv_usec;

    if(nThread == -1) tempos_OrdenaArr.push_back(tF - tInicOrdenaArr);
    else tempos_paralelo_OrdenaArr.push_back(tF - tInicOrdenaArr);

    return (tF - tInicOrdenaArr); 
}

long long unsigned stopCounters(int nThread){
	PAPI_stop_counters(values, NUM_EVENTS);

	gettimeofday(&t, NULL);
	long long unsigned tempoFinal = t.tv_sec * 1000000 + t.tv_usec;

	if (nThread == -1){
		tempos_sequencial.push_back(tempoFinal - tempoInicial);
        miss_rates_L1_sequencial.push_back((double)((double)values[0]/(double)(values[3]))*100);
        miss_rates_L2_sequencial.push_back((double)((double)values[1]/(double)(values[3]))*100);
        miss_rates_L3_sequencial.push_back((double)((double)values[2]/(double)(values[3]))*100);
    }
	else {
		tempos_paralelo.push_back(tempoFinal - tempoInicial);
		miss_rates_paralelo.push_back((double)((double)values[0]/(double)(values[3]))*100);
    }
    
	cout << "(MISS_L1 = " << values[0]
	     << ", MISS_L2 = " << values[1]
	     << ", MISS_L3 = " << values[2]
	     << ", TOT_INS = " << values[3] << ")\n" << endl;
    
	return tempoFinal - tempoInicial;
}

std::tuple<long long unsigned, double, double, double> mediana(int thread) {
	long long unsigned melhorT = 0;
    double melhorM_L1 = 0.0,melhorM_L2 = 0.0,melhorM_L3 = 0.0;

	if (thread == - 1) {
        std::sort(tempos_sequencial.begin(), tempos_sequencial.end());
        const auto median_itT = tempos_sequencial.begin() + tempos_sequencial.size() / 2;
        std::nth_element(tempos_sequencial.begin(), median_itT , tempos_sequencial.end());
        melhorT = *median_itT;

        std::sort(miss_rates_L1_sequencial.begin(), miss_rates_L1_sequencial.end());
        const auto median_itM_L1 = miss_rates_L1_sequencial.begin() + miss_rates_L1_sequencial.size() / 2;
        std::nth_element(miss_rates_L1_sequencial.begin(), median_itM_L1 , miss_rates_L1_sequencial.end());
        melhorM_L1 = *median_itM_L1;

        std::sort(miss_rates_L2_sequencial.begin(), miss_rates_L2_sequencial.end());
        const auto median_itM_L2 = miss_rates_L2_sequencial.begin() + miss_rates_L2_sequencial.size() / 2;
        std::nth_element(miss_rates_L2_sequencial.begin(), median_itM_L2 , miss_rates_L2_sequencial.end());
        melhorM_L2 = *median_itM_L2;
        
        std::sort(miss_rates_L3_sequencial.begin(), miss_rates_L3_sequencial.end());
        const auto median_itM_L3 = miss_rates_L3_sequencial.begin() + miss_rates_L3_sequencial.size() / 2;
        std::nth_element(miss_rates_L3_sequencial.begin(), median_itM_L3 , miss_rates_L3_sequencial.end());
        melhorM_L3 = *median_itM_L3;
	} 
	else { //paralelo
        std::sort(tempos_paralelo.begin(), tempos_paralelo.end());
        const auto median_itT = tempos_paralelo.begin() + tempos_paralelo.size() / 2;
        std::nth_element(tempos_paralelo.begin(), median_itT , tempos_paralelo.end());
        melhorT = *median_itT;

        std::sort(miss_rates_paralelo.begin(), miss_rates_paralelo.end());
        const auto median_itM = miss_rates_paralelo.begin() + miss_rates_paralelo.size() / 2;
        std::nth_element(miss_rates_paralelo.begin(), median_itM , miss_rates_paralelo.end());
        melhorM_L1 = *median_itM;

	}

	return std::make_tuple(melhorT,melhorM_L1,melhorM_L2,melhorM_L3);
}

std::tuple<long long unsigned,long long unsigned,long long unsigned,long long unsigned > medianaFunc(int nThreads){
    long long unsigned melhorT1 = 0, melhorT2 = 0, melhorT3 = 0, melhorT4 = 0;

    if(nThreads== -1){
        std::sort(tempos_CriarB.begin(), tempos_CriarB.end());
        const auto median_itT = tempos_CriarB.begin() + tempos_CriarB.size() / 2;
        std::nth_element(tempos_CriarB.begin(), median_itT , tempos_CriarB.end());
        melhorT1 = *median_itT;

        std::sort(tempos_InsereB.begin(), tempos_InsereB.end());
        const auto median_itT2 = tempos_InsereB.begin() + tempos_InsereB.size() / 2;
        std::nth_element(tempos_InsereB.begin(), median_itT2 , tempos_InsereB.end());
        melhorT2 = *median_itT2;

        std::sort(tempos_OrdenaB.begin(), tempos_OrdenaB.end());
        const auto median_itT3 = tempos_OrdenaB.begin() + tempos_OrdenaB.size() / 2;
        std::nth_element(tempos_OrdenaB.begin(), median_itT3 , tempos_OrdenaB.end());
        melhorT3 = *median_itT3;
            
        std::sort(tempos_OrdenaArr.begin(), tempos_OrdenaArr.end());
        const auto median_itT4 = tempos_OrdenaArr.begin() + tempos_OrdenaArr.size() / 2;
        std::nth_element(tempos_OrdenaArr.begin(), median_itT4 , tempos_OrdenaArr.end());
        melhorT4 = *median_itT4;
    }
    else{
        std::sort(tempos_paralelo_CriarB.begin(), tempos_paralelo_CriarB.end());
        const auto median_itT = tempos_paralelo_CriarB.begin() + tempos_paralelo_CriarB.size() / 2;
        std::nth_element(tempos_paralelo_CriarB.begin(), median_itT , tempos_paralelo_CriarB.end());
        melhorT1 = *median_itT;

        std::sort(tempos_paralelo_InsereB.begin(), tempos_paralelo_InsereB.end());
        const auto median_itT2 = tempos_paralelo_InsereB.begin() + tempos_paralelo_InsereB.size() / 2;
        std::nth_element(tempos_paralelo_InsereB.begin(), median_itT2 , tempos_paralelo_InsereB.end());
        melhorT2 = *median_itT2;

        std::sort(tempos_paralelo_OrdenaB.begin(), tempos_paralelo_OrdenaB.end());
        const auto median_itT3 = tempos_paralelo_OrdenaB.begin() + tempos_paralelo_OrdenaB.size() / 2;
        std::nth_element(tempos_paralelo_OrdenaB.begin(), median_itT3 , tempos_paralelo_OrdenaB.end());
        melhorT3 = *median_itT3;
            
        std::sort(tempos_paralelo_OrdenaArr.begin(), tempos_paralelo_OrdenaArr.end());
        const auto median_itT4 = tempos_paralelo_OrdenaArr.begin() + tempos_paralelo_OrdenaArr.size() / 2;
        std::nth_element(tempos_paralelo_OrdenaArr.begin(), median_itT4 , tempos_paralelo_OrdenaArr.end());
        melhorT4 = *median_itT4;
    }

    return std::make_tuple(melhorT1,melhorT2,melhorT3,melhorT4);
}

void printResults (int nThreads, int sizeInput, int nBuckets) {
    auto sequencial = mediana(-1);
    auto paralelo = mediana(nThreads);
	
    cout << "\n----- Nº elementos = " << sizeInput << ", Nº buckets = " << nBuckets << " -----" << endl;

    cout << "Versão sequencial:\n" 
         << "\tTempo: " << std::get<0>(sequencial) << " usecs,\n"
         << "\tMiss rate (L1): " << std::get<1>(sequencial) << " %\n"
         << "\tMiss rate (L2): " << std::get<2>(sequencial) << " %\n"
         << "\tMiss rate (L3): " << std::get<3>(sequencial) << " %\n" << endl;
	
    cout << "Versão paralela (Nº threads = "<< nThreads << "):\n" 
		 << "\tTempo: " << std::get<0>(paralelo) << " usecs,\n"
         << "\tMiss rate (L1): " << std::get<1>(paralelo) << " %\n" << endl;
         //<< "\tMiss rate (L2): " << std::get<2>(paralelo) << " %\n"
         //<< "\tMiss rate (L3): " << std::get<3>(paralelo) << " %\n" << endl;

    cout << "Speed-up: " << (double)((double)(std::get<0>(sequencial))/(double)(std::get<0>(paralelo))) << endl;

    cout << "--------------------------------------------------\n" << endl;
}

void printResultsFunc(int nThreads){

    auto funcoes = medianaFunc(-1);
    auto funcoesP = medianaFunc(nThreads);

    long long unsigned tTot = std::get<0>(funcoes)  + std::get<1>(funcoes)  + std::get<2>(funcoes)  + std::get<3>(funcoes);

    long long unsigned tTotP = std::get<0>(funcoesP)  + std::get<1>(funcoesP)  + std::get<2>(funcoesP)  + std::get<3>(funcoesP);

    cout << "--- SEQUENCIAL ---" << endl;
    cout << "Tempo total = " << tTot << " usecs\n" << endl;

    cout << "Criar Buckets:\n" 
         << "\tTempo: " << std::get<0>(funcoes) << " usecs,\n" << endl;   

    cout << "Inserir nos Buckets:\n" 
         << "\tTempo: " << std::get<1>(funcoes) << " usecs,\n" << endl;
         
    cout << "Ordenar os Buckets:\n" 
         << "\tTempo: " << std::get<2>(funcoes) << " usecs,\n" << endl;

    cout << "Ordenar o array inicial:\n" 
         << "\tTempo: " << std::get<3>(funcoes) << " usecs,\n" << endl;

    cout << "--- PARALELO ---" << endl;

    cout << "Tempo total = " << tTotP<< " usecs\n" << endl;

    cout << "Criar Buckets:\n" 
         << "\tTempo: " << std::get<0>(funcoesP) << " usecs,\n" << endl;   

    cout << "Inserir nos Buckets:\n" 
         << "\tTempo: " << std::get<1>(funcoesP) << " usecs,\n" << endl;
         
    cout << "Ordenar os Buckets:\n" 
         << "\tTempo: " << std::get<2>(funcoesP) << " usecs,\n" << endl;

    cout << "Ordenar o array inicial:\n" 
         << "\tTempo: " << std::get<3>(funcoesP) << " usecs,\n" << endl;

    cout << "SPEED-UP: " << (double)((double)(tTot)/(double)(tTotP)) << endl;    
}