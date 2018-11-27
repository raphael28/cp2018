#include "mergeSort.h"

void mergesort(int *v, int n) {
  int *c = (int *)malloc(sizeof(int) * n);
  sort(v, c, 0, n - 1);
  free(c);
}

void sort(int *v, int *c, int i, int f) {
  	if (i >= f) return;

  	int m = (i + f) / 2;

  	sort(v, c, i, m);
  	sort(v, c, m + 1, f);

  	/* Se v[m] <= v[m + 1], então v[i..f] já está ordenado. */
  	if (v[m] <= v[m + 1]) return;

  	merge(v, c, i, m, f);
}

void merge(int *v, int *c, int i, int m, int f) {
  int z,
      iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = v[z];

  z = i;

  while (iv <= m && ic <= f) {
    /* Invariante: v[i..z] possui os valores de v[iv..m] e v[ic..f] em ordem crescente. */

    if (c[iv] < c[ic]) v[z++] = c[iv++];
    else /* if (c[iv] > c[ic]) */ v[z++] = c[ic++];
  }

  while (iv <= m) v[z++] = c[iv++];

  while (ic <= f) v[z++] = c[ic++];
}