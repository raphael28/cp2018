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

void clearCache();
void startCounters();
long long unsigned stopCounters(int nThread);
std::tuple<long long unsigned, double,double,double> mediana(int thread);
void printResults (int nThreads, int sizeInput);
