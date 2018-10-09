#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define S 4 // spatial resolution (input size)
#define K 3 // kernel size
#define N (S+K-1)

void print_matrix(float matrix[N][N]) {
  for(int y=0; y<N; y++) {
    for(int x=0; x<N; x++) {
      printf("| %10f ", matrix[y][x]);
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

void complex_mul2(float a_real[N][N], float a_im[N][N], float b_real[N][N], float b_im[N][N], float out_real[N][N], float out_im[N][N]) {
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

void shift2d(float in[N][N], float out[N][N], int limit) {
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
  float x[N][N] = {{1,2,3},{4,5,6},{7,8,9}};
  float x_real[N][N] = {0};
  float x_im[N][N] = {0};
  float x_[N][N] = {0};


  // Instantiate filter signal (same as input signal)
  float k[N][N] = {{0,0,0}, {0,2,0}, {0,0,0}};
  float k_shifted[N][N] = {0};
  float k_real[N][N] = {0};
  float k_im[N][N] = {0};


  // Instantiate filter output (vectors for convolution output as frequency coefficientes, reversed spatial data as final output)
  float y_real[N][N] = {0};
  float y_im[N][N] = {0};
  float y_[N][N] = {0};

  printf("\nInput\n");
  print_matrix(x);
  print_matrix(k);


  // Shift filter signal
  shift2d(k, k_shifted, K);
  
  printf("\nShifted\n");
  print_matrix(k_shifted);
  
  dft2(x, x_real, x_im);
  dft2(k_shifted, k_real, k_im);

  complex_mul2(x_real, x_im, k_real, k_im, y_real, y_im);

  /*
  printf("\nEncoded\n");
  print_matrix(x_real);
  print_matrix(x_im);
  */

  idft2(x_real, x_im, x_);
  idft2(y_real, y_im, y_);

  printf("\nDecoded\n");
  print_matrix(x_);
  print_matrix(y_);


  return 0;
}
