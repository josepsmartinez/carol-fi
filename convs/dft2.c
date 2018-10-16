#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "malloc2d.h"
#include "input_synth.h" // yields print_matrix, S, K

#define PI 3.14159265
#define N (S+K-1)

void dft2(float **in, float **out_real, float **out_im) {
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

void idft2(float **in_real, float **in_im, float **out) {
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

void complex_mul2(float **a_real, float **a_im, float **b_real, float **b_im, float **out_real, float **out_im) {
  for(int m=0; m<N; m++) {
    for(int n=0; n<N; n++) {
      out_real[m][n] = 0;
      out_real[m][n] += a_real[m][n] * b_real[m][n];
      out_real[m][n] -= a_im[m][n] * b_im[m][n];

      out_im[m][n] = 0;
      out_im[m][n] += a_im[m][n] * b_real[m][n];
      out_im[m][n] += a_real[m][n] * b_im[m][n];
    }
  }
}

void shift2d(float** in, float **out, int limit) {
  int mean_point = limit/2;

  // writes -1 on output (just to check every pixel gets rewritten)
  for(int i=0; i<limit; i++) {
    for(int j=0; j<limit; j++) {
      out[i][j] = -1;
    }
  }
  

  // 3 -> 1
  for(int i=mean_point; i<limit; i++) 
    for(int j=mean_point; j<limit; j++) 
      out[i-mean_point][j-mean_point] = in[i][j];

  // 1 -> 3
  for(int i=0; i<mean_point; i++)
    for(int j=0; j<mean_point; j++)
      out[i+mean_point+1][j+mean_point+1] = in[i][j];

  // non symmetric but symmetric shit
  for(int i=mean_point; i<limit; i++)
    for(int j=0; j<mean_point; j++)
      out[i-mean_point][j+mean_point+1] = in[i][j];

  for(int i=0; i<mean_point; i++)
    for(int j=mean_point; j<limit; j++)
      out[i+mean_point+1][j-mean_point] = in[i][j];
}

int main() {
  // Instantiate input signal (spatial data, vectors for frequency coefficients, reversed spatial data)
  float **x = malloc_2d(N, N, 0.0);
  x[0][0] = 1;
  x[0][1] = 2;
  x[0][2] = 3; //
  x[1][0] = 4;
  x[1][1] = 5;
  x[1][2] = 6; //
  x[2][0] = 7;
  x[2][1] = 8;
  x[2][2] = 9;
  
  float **x_real = malloc_2d(N, N, 0.0);
  float **x_im = malloc_2d(N, N, 0.0);
  float **x_ = malloc_2d(N, N, 0.0);


  // Instantiate filter signal (same as input signal)
  float **k = malloc_2d(N, N, 0.0);
  k[1][1] = 2;
    
  float **k_shifted = malloc_2d(N, N, 0.0);
  float **k_real = malloc_2d(N, N, 0.0);
  float **k_im = malloc_2d(N, N, 0.0);


  // Instantiate filter output (vectors for convolution output as frequency coefficientes, reversed spatial data as final output)
  float **y_real = malloc_2d(N, N, 0.0);
  float **y_im = malloc_2d(N, N, 0.0);
  float **y_ = malloc_2d(N, N, 0.0);

  printf("\nInput\n");
  print_matrix(x, 10, 10);
  print_matrix(k, 10, 10);

  
  // Shift filter signal
  shift2d(k, k_shifted, K);
  
  printf("\nShifted\n");
  print_matrix(k_shifted, 10, 10);

  
  dft2(x, x_real, x_im);
  dft2(k_shifted, k_real, k_im);

  printf("\nEncoded\n");
  print_matrix(x_real, 10, 10);
  print_matrix(x_im, 10, 10);

  complex_mul2(x_real, x_im, k_real, k_im, y_real, y_im);

  printf("\nFiltered\n");
  print_matrix(y_real, 10, 10);
  print_matrix(y_im, 10, 10);
  
  
  idft2(x_real, x_im, x_);
  idft2(y_real, y_im, y_);

  printf("\nDecoded\n");
  print_matrix(x_, 10, 10);
  print_matrix(y_, 10, 10);

  // Frees allocated instances
  free_2d(N, x);
  free_2d(N, x_im);
  free_2d(N, x_real);
  free_2d(N, x_);

  free_2d(N, k);
  free_2d(N, k_shifted);
  free_2d(N, k_im);
  free_2d(N, k_real);

  free_2d(N, y_im);
  free_2d(N, y_real);
  free_2d(N, y_);

  return 0;
 
}
