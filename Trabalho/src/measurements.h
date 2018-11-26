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
std::pair<long long unsigned, double> mediana(int thread);
void printResults (int num_threads);