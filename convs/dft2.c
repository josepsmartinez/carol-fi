#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define N 3 // spatial resolution (input size)

void print_matrix(float matrix[N][N]) {
  for(int y=0; y<N; y++) {
    for(int x=0; x<N; x++) {
      printf("| %f ", matrix[y][x]);
    }
    printf("|\n");
  }
  printf("\n");
}

void dft2(float in[N][N], float out_real[N][N], float out_im[N][N]) {
  float mid_real[N][N] = {0};
  float mid_im[N][N] = {0} ;
  
  // rows first
  for(int y=0; y<N; y++) {
    for(int k=0; k<N; k++) {
      for(int n=0; n<N; n++) {
	mid_real[y][k] += in[y][n] * cos(2*PI*k*n/N);
	mid_im[y][k] -= in[y][n] * sin(2*PI*k*n/N);
      }
    }
  }

  // then columns
  for(int x=0; x<N; x++) {
    for(int n=0; n<N; n++) {
      for(int k=0; k<N; k++) {
	out_real[k][x] += mid_real[n][x] * cos(2*PI*k*n/N);
	out_im[k][x] -= mid_real[n][x] * sin(2*PI*k*n/N);

	out_real[k][x] += mid_im[n][x] * sin(2*PI*k*n/N);
	out_im[k][x] += mid_im[n][x] * cos(2*PI*k*n/N);
      }
    }
  }
}

void idft2(float in_real[N][N], float in_im[N][N], float out[N][N]) {
  float mid_real[N][N] = {0};
  float mid_im[N][N] = {0};

  // rows first
  for(int y=0; y<N; y++) {
    for(int k=0; k<N; k++) {
      for(int n=0; n<N; n++) {
	mid_real[y][k] += in_real[y][n] * cos(2*PI*k*n/N);
	mid_im[y][k] += in_real[y][n] * sin(2*PI*k*n/N);

	mid_real[y][k] -= in_im[y][n] * sin(2*PI*k*n/N);
	mid_im[y][k] += in_im[y][n] * cos(2*PI*k*n/N);
      }
    }
  }

  // then columns
  for(int x=0; x<N; x++) {
    for(int n=0; n<N; n++) {
      for(int k=0; k<N; k++) {
	out[n][x] += mid_real[k][x] * cos(2*PI*k*n/N);
	out[n][x] -= mid_im[k][x] * sin(2*PI*k*n/N);
      }
      out[n][x] /= N*N;
    }
  }
}

int main() {
  float x[N][N] = {{2,3},{4,5}};
  float y_cos[N][N] = {0};
  float y_sin[N][N] = {0};
  float y[N][N] = {0};
  
  print_matrix(x);
  print_matrix(y_cos);
  print_matrix(y_sin);

  dft2(x, y_cos, y_sin);
  
  print_matrix(x);
  print_matrix(y_cos);
  print_matrix(y_sin);

  idft2(y_cos, y_sin, y);

  print_matrix(y);


  return 0;
}
