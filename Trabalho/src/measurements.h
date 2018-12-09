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
long long unsigned stopCountersCriarB(int nThread);
void startCountersInsereB();
long long unsigned stopCountersInsereB(int nThread);
void startCountersOrdenaB();
long long unsigned stopCountersOrdenaB(int nThread);
void startCountersOrdenaArr();
long long unsigned stopCountersOrdenaArr(int nThread);
void clearCache();

std::tuple<long long unsigned, double,double,double> mediana(int thread);
void printResults (int nThreads, int sizeInput, int nBuckets);
std::tuple<long long unsigned,long long unsigned,long long unsigned,long long unsigned> medianaFunc(int nThreads);
void printResultsFunc(int nThreads);
