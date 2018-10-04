#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define N 6 // spatial resolution (input size)
#define K 3 // kernel size

void dft(int n_samples, float* x, float* y_sin, float* y_cos) {
  //float y_cos[n_samples] = {0};
  //float y_sin[n_samples] = {0};

  // Space -> Frequency
  for(int k=0; k<n_samples; k++) {
    for (int n=0; n<n_samples; n++) {
      y_cos[k] += x[n] * cos(2*PI*k*n/N);
    }
  }
  for(int k=0; k<n_samples; k++) {
    for (int n=0; n<n_samples; n++) {
      y_sin[k] -= x[n] * sin(2*PI*k*n/N);
    }
  }
}

void idft(int n_samples, float* y, float* y_sin, float* y_cos) {

  for (int n=0; n<n_samples; n++) {
    for(int k=0; k<n_samples; k++) {
      y[n] += y_cos[k] * cos(2*PI*k*n/N);
      y[n] -= y_sin[k] * sin(2*PI*k*n/N);
    }
    y[n] /= (float) n_samples;
  }
}

void complex_mul(int n_samples, float* a_real, float* a_im, float* b_real, float* b_im, float* out_real, float* out_im) {
  for(int n=0; n<n_samples; n++) {
    out_real[n] = 0;
    out_real[n] += a_real[n] * b_real[n];
    out_real[n] -= a_im[n] * b_im[n];

    out_im[n] = 0;
    out_im[n] += a_im[n] * b_real[n];
    out_im[n] += a_real[n] * b_im[n];
  }

}

int main () {
  float x[N] = {2, 1, 2, 1};
  float fx_cos[N] = {0};
  float fx_sin[N] = {0};
  float x_[N] = {0};

  float k[N] = {1, 2, 3};
  float fk_cos[N] = {0};
  float fk_sin[N] = {0};
  float k_[N] = {0};

  float fy_cos[N] = {0};
  float fy_sin[N] = {0};
  float y_[N] = {0};
   

  printf("\nInput \n");
  {
    for(int i=0; i<N; i++) printf("X: %f ", x[i]); printf("\n");
    for(int i=0; i<N; i++) printf("K: %f ", k[i]); printf("\n");
  }

  // Space -> Frequency
  dft(N, x, fx_sin, fx_cos);
  dft(N, k, fk_sin, fk_cos);

  // Point-wise multiplication
  complex_mul(N, fx_cos, fx_sin, fk_cos, fk_sin, fy_cos, fy_sin);
  
  printf("\nEncoded \n");
  /*
  {
    for(int i=0; i<N; i++) printf("F(X)_cos: %f ", fx_cos[i]); printf("\n");
    for(int i=0; i<N; i++) printf("F(X)_sin: %f ", fx_sin[i]); printf("\n");
    for(int i=0; i<N; i++) printf("F(K)_cos: %f ", fk_cos[i]); printf("\n");
    for(int i=0; i<N; i++) printf("F(K)_sin: %f ", fk_sin[i]); printf("\n");
    for(int i=0; i<N; i++) printf("F(Y)_cos: %f ", fy_cos[i]); printf("\n");
    for(int i=0; i<N; i++) printf("F(Y)_sin: %f ", fy_sin[i]); printf("\n");

  }
  */
  
  // Frequency -> Space
  idft(N, x_, fx_sin, fx_cos);
  idft(N, y_, fy_sin, fy_cos);
  printf("\nDecoded \n");
  {
    for(int i=0; i<N; i++) printf("Xf: %f ", x_[i]); printf("\n");
    for(int i=0; i<N; i++) printf("Yf: %f ", y_[i]); printf("\n");
  }
  
  
  
  printf("\ndeix \n");
  return(0);
}
