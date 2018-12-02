#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <omp.h>
#include <sys/time.h>
#include <vector>
#include <tuple>
#include <algorithm>
#include "papi.h"

//void clearCache();
void startCounters();
long long unsigned stopCounters(int nThread);
void startCountersCriarB();
long long unsigned stopCountersCriarB();
void startCountersInsereB();
long long unsigned stopCountersInsereB();
void startCountersOrdenaB();
long long unsigned stopCountersOrdenaB();
void startCountersOrdenaArr();
long long unsigned stopCountersOrdenaArr();

std::tuple<long long unsigned, double,double,double> mediana(int thread);
void printResults (int nThreads, int sizeInput);
std::tuple<long long unsigned,long long unsigned,long long unsigned,long long unsigned> medianaFunc();
void printResultsFunc();
