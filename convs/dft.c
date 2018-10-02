#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define N 9 // spatial resolution (input size)
#define K 3 // kernel size
#define M 18 // frequency resolution (encoded size)

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

int main () {
  float x[N] = {0, 0, -13.89, 1, 14.5567, 0, 0};
  float y_cos[N] = {0};
  float y_sin[N] = {0};
  float y_[N] = {0};
   

  printf("\nInput \n");
  {
    for(int i=0; i<N; i++) printf("X: %f ", x[i]); printf("\n");
    for(int i=0; i<N; i++) printf("Y_cos: %f ", y_cos[i]); printf("\n");
    for(int i=0; i<N; i++) printf("Y_sin: %f ", y_sin[i]); printf("\n");
  }

  dft(N, x, y_sin, y_cos);

  printf("\nEncoded \n");
  {
    for(int i=0; i<N; i++) printf("X: %f ", x[i]); printf("\n");
    for(int i=0; i<M; i++) printf("Y_cos: %f ", y_cos[i]); printf("\n");
    for(int i=0; i<M; i++) printf("Y_sin: %f ", y_sin[i]); printf("\n");
  }

  idft(N, y_, y_sin, y_cos);
  
  printf("\nDecoded \n");
  {
    for(int i=0; i<N; i++) printf("X : %f ", x[i]); printf("\n");
    for(int i=0; i<N; i++) printf("Y_: %f ", y_[i]); printf("\n");
  }
  
  
  
  printf("deix \n");
  return(0);
}
