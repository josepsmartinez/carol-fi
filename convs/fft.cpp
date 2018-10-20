#include <stdio.h> 

#include <complex>
#include <iostream>
#include <valarray>

#include "input_synth.h"
 
const double PI = 3.141592653589793238460;
 
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
typedef std::valarray<CArray> KernelsArray;
 
// Cooley–Tukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;
 
    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];
 
    // conquer
    fft(even);
    fft(odd);
 
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}
 
// inverse fft (in-place)
void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);
 
    // forward fft
    fft( x );
 
    // conjugate the complex numbers again
    x = x.apply(std::conj);
 
    // scale the numbers
    x /= x.size();
}

//

void print_carray(CArray& X, int size) {
  std::cout << '\n';

  for(int i=0; i<size; i++)
    std::cout << '|' << X[i] << '\t';
  
  std::cout << "|\n";
}

void read_persisted_line(CArray& X, char *matrix_file) {
  int matrix_dim;
  
  FILE *input_ptr;
  int buffer_i;
  float buffer_f;

  input_ptr = fopen(matrix_file, "rb");

  if (input_ptr == NULL) {
    printf("Failed to open matrix file\n");
    exit(-1);
  }

  // infers image size from header
  fread(&buffer_i, sizeof(int), 1, input_ptr);
  matrix_dim = buffer_i;

  // reads first line
  for(int x=0; x<matrix_dim; x++) {
    fread(&buffer_f, sizeof(float), 1, input_ptr);
    X[x] = (Complex) buffer_f;
  }

  
  fclose(input_ptr);
}

void read_persisted_kernels(KernelsArray& kernels, char *kernels_file) {
  int n_kernels=0;
  int filter_dim=0;

  FILE* input_ptr;
  int buffer_i;
  float buffer_f;

  input_ptr = fopen(kernels_file, "rb");
  if (input_ptr == NULL){
    printf("Failed to open kernels file\n");
    exit(-1);
  }

  // infers how many kernels and their size from header
  fread(&buffer_i, sizeof(int), 1, input_ptr);
  n_kernels = buffer_i;

  fread(&buffer_i, sizeof(int), 1, input_ptr);
  filter_dim = buffer_i;

  //std::cout << n_kernels << " kernels and " << filter_dim << " samples per kernel \n";

  for(int m=0; m<n_kernels; m++){
    kernels[m] = CArray(0.0, filter_dim);
    for(int k=0; k<filter_dim; k++) {
      fread(&buffer_f, sizeof(float), 1, input_ptr);

      kernels[m][k] = (Complex) buffer_f;
      //std::cout << buffer_f << '\n';
    }
  }
  
  fclose(input_ptr);
}

void output_line(FILE* output_ptr, CArray line, int size) {
  for(int x=0; x<(size-1); x++) {
    fprintf(output_ptr, "%f,", line[x].real());
  }
  fprintf(output_ptr, "%f\n", line[size-1].real());

}
 
int main(int argc, char **argv)
{
  const int N = S+K-1; //padding
  FILE* output_file_ptr;
  
  char* matrix_file = argv[1];
  char* kernels_file = argv[2];
  char* output_file = argv[3];

  // Instantiates 
  CArray input(0.0, N);
  CArray filter(0.0, N);
  CArray output(0.0, N);

  KernelsArray kernels(M);

  // Opens output file and reads persisted input
  output_file_ptr = fopen(output_file, "w");

  read_persisted_line(input, matrix_file);
  read_persisted_kernels(kernels, kernels_file);

  // Convolution
  for(int m=0; m<M; m++){

    // copy persisted kernel into filter buffer
    for(int k=0; k<K; k++)
      filter[k] = kernels[m][k];
 
    // forward fft
    fft(input);
    fft(filter);


    // multiplication
    for (int i=0; i<N; ++i) {
      output[i] = input[i] * filter[i];
    }
 
    // inverse fft
    //ifft(input);
    //ifft(filter);
    ifft(output);

    output_line(output_file_ptr, output, S);

  }

  fclose(output_file_ptr);

    
  return 0;
}
