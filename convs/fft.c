#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define N 9 // spatial resolution (input size)
#define K 3 // kernel size
#define M 18 // frequency resolution (encoded size)

int main () {
  float x[N] = {0, 0, -13.89, 1, 14.5567, 0, 0};
  float y_cos[M] = {0};
  float y_sin[M] = {0};
  float y_[N] = {0};
   

  printf("\nInput \n");
  {
    for(int i=0; i<N; i++) printf("X: %f ", x[i]); printf("\n");
    for(int i=0; i<N; i++) printf("Y_cos: %f ", y_cos[i]); printf("\n");
    for(int i=0; i<N; i++) printf("Y_sin: %f ", y_sin[i]); printf("\n");
  }

  // Space -> Frequency
  for(int m=0; m<=M-1; m++) {
    for (int n=0; n<=N-1; n++) {
      y_cos[m] += x[n] * cos(2*PI*m*n/N);
    }
  }
  for(int m=0; m<=M-1; m++) {
    for (int n=0; n<=N-1; n++) {
      y_sin[m] -= x[n] * sin(2*PI*m*n/N);
    }
  }


  printf("\nEncoded \n");
  {
    for(int i=0; i<N; i++) printf("X: %f ", x[i]); printf("\n");
    for(int i=0; i<M; i++) printf("Y_cos: %f ", y_cos[i]); printf("\n");
    for(int i=0; i<M; i++) printf("Y_sin: %f ", y_sin[i]); printf("\n");
  }

  // Frequency -> Space
  for (int n=0; n<=N-1; n++) {
    for(int m=0; m<=M-1; m++) {
      y_[n] += y_cos[m] * cos(2*PI*m*n/N);
      y_[n] -= y_sin[m] * sin(2*PI*m*n/N);
    }
    y_[n] /= (float) M;
  }
  
  printf("\nDecoded \n");
  {
    for(int i=0; i<N; i++) printf("X : %f ", x[i]); printf("\n");
    for(int i=0; i<N; i++) printf("Y_: %f ", y_[i]); printf("\n");
  }

  
  printf("deix \n");
  return(0);
}
