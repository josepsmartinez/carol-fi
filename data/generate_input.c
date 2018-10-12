#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <limits.h>

#define S 18
#define K 3

void print_matrix(float matrix[S][S]) { /* COPY-PASTE HAHA */
  for(int y=0; y<S; y++) {
    for(int x=0; x<S; x++) {
      printf("| %1.4f ", matrix[y][x]);
    }
    printf("|\n");
  }
  printf("\n");
}


void persist_input_matrix() {
  float im_in[S][S] = {0};

  time_t t;

  FILE *output_ptr;
  int buffer_i;
  float buffer_f;

  /* */
  time(&t); srand((unsigned int) t);
  

  //print_matrix(im_in);

  /* fills matrix with random float between (-1,1) */
  for(int y=0; y<S; y++){
    for(int x=0; x<S; x++) {
      im_in[y][x] = -1. + 2.*rand() / (float) INT_MAX;
    }
  }

  print_matrix(im_in);

  /* write output file */
  output_ptr = fopen("new_matrix.bin", "wb");

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

  fclose(output_ptr);

  
}

void read_persisted_matrix() {
  float im_out[S][S] = {0};

  FILE *input_ptr;
  int buffer_i;
  float buffer_f;

  /* */
  input_ptr = fopen("new_matrix.bin", "rb");

  // ignored header
  fread(&buffer_i, sizeof(int), 1, input_ptr);

  // data
  for(int y=0; y<S; y++){
    for(int x=0; x<S; x++) {
      fread(&buffer_f, 1, sizeof(float), input_ptr);
      im_out[y][x] = buffer_f;
    }
  }
  fclose(input_ptr);

  print_matrix(im_out);
}

int main() {
  persist_input_matrix();
  read_persisted_matrix();
  
  return 0;
}
