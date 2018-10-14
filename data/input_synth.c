#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <limits.h>

#include "malloc2d.h"
#include "input_synth.h"

// VISUALIZATION
void print_matrix(float **matrix){
  for(int y=0; y<10; y++) {
    for(int x=0; x<10; x++) {
      printf("| %1.4f ", matrix[y][x]);
    }
    printf("|\n");
  }
  printf("\n");
}

void print_kernels(float **kernels){
  for(int m=0; m<10; m++) {
    for(int k=0; k<K; k++) {
      printf("| %1.4f ", kernels[m][k]);
    }
    printf("|\n");
  }
  printf("\n");
}

// WRITE
float random_float() {
  return -1. + 2.*rand() / (float) INT_MAX;
}

void persist_input_matrix() {
  float **im_in = malloc_2d(S, S, 0.0);

  FILE *output_ptr;
  int buffer_i;
  float buffer_f;

  for(int y=0; y<S; y++){
    for(int x=0; x<S; x++) {
      im_in[y][x] = random_float();
    }
  }

  print_matrix(im_in);

  /* file output */
  output_ptr = fopen("new_matrix.bin", "wb");
  {
    // header
    buffer_i = S;
    fwrite(&buffer_i, sizeof(int), 1, output_ptr);

    // data
    for(int y=0; y<S; y++){
      for(int x=0; x<S; x++) {
	buffer_f = im_in[y][x];
	fwrite(&buffer_f, sizeof(float), 1, output_ptr);
      }
    }
  }

  // close and free
  fclose(output_ptr);
  free_2d(S, im_in);
}

void persist_input_kernels() {
  float **kernels_in = malloc_2d(M, K, 0.0);

  FILE *output_ptr;
  int buffer_i;
  float buffer_f;

  /* fills matrix with random float between (-1,1) */
  for(int m=0; m<M; m++){
    for(int k=0; k<K; k++) {
      kernels_in[m][k] = random_float();
    }
  }

  print_kernels(kernels_in);
  
  /* write output file */
  output_ptr = fopen("new_kernels.bin", "wb");
  {
    // header (#kernels, #kernel_size)
    buffer_i = M;
    fwrite(&buffer_i, sizeof(int), 1, output_ptr);

    buffer_i = K;
    fwrite(&buffer_i, sizeof(int), 1, output_ptr);

    // data
    for(int m=0; m<M; m++){
      for(int k=0; k<K; k++) {
	buffer_f = kernels_in[m][k];
	fwrite(&buffer_f, sizeof(float), 1, output_ptr);
      }
    }
  }
  
  // close and free
  fclose(output_ptr);
  free_2d(M, kernels_in);

}

// READ
void read_persisted_matrix(float **im_out) {
  FILE *input_ptr;
  int buffer_i;
  float buffer_f;

  input_ptr = fopen("new_matrix.bin", "rb");

  // ignoring header
  fread(&buffer_i, sizeof(int), 1, input_ptr);

  // data
  for(int y=0; y<S; y++){
    for(int x=0; x<S; x++) {
      fread(&buffer_f, sizeof(float), 1, input_ptr);
      im_out[y][x] = buffer_f;
    }
  }

  // close
  fclose(input_ptr);
}

void read_persisted_kernels(float **kernels_out){
  FILE *input_ptr;
  int buffer_i;
  float buffer_f;

  input_ptr = fopen("new_kernels.bin", "rb");

  // ignoring header
  fread(&buffer_i, sizeof(int), 1, input_ptr);
  fread(&buffer_i, sizeof(int), 1, input_ptr);

  for(int m=0; m<M; m++){
    for(int k=0; k<K; k++) {
      fread(&buffer_f, sizeof(float), 1, input_ptr);
      kernels_out[m][k] = buffer_f;
    }
  }

  fclose(input_ptr);
}
