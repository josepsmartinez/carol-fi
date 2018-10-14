#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "malloc2d.h"
#include "input_synth.h"

int main() {
  float **input_matrix = malloc_2d(S, S, 0.0);
  float **input_kernels = malloc_2d(M, K, 0.0);
  
  time_t t;

  
  printf("Generating random seed\n");
  time(&t);
  srand((unsigned int) t);
  
  printf("Persisting input matrix\n");
  persist_input_matrix();
  
  printf("Persisting input kernels\n");
  persist_input_kernels();

  printf("Freeing\n");
  free_2d(S, input_matrix);
  free_2d(M, input_kernels);
  
  return 0;
}

