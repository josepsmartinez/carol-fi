#include <stdlib.h>
#include <stdio.h>

#include "malloc2d.h"
#include "input_synth.h"


int main() {
  float **input_matrix = malloc_2d(S, S, 0.0);
  float **input_kernels = malloc_2d(M, K*K, 0.0);

  printf("Reading input matrix\n");
  read_persisted_matrix(input_matrix);
  print_matrix(input_matrix);

  printf("Reading input kernels\n");
  read_persisted_kernels(input_kernels);
  print_kernels(input_kernels);

  printf("Freeing\n");
  free_2d(S, input_matrix);
  free_2d(M, input_kernels);
}
