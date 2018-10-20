#include <complex>
#include <iostream>
#include <valarray>
 
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
 
int main()
{
  int N = 8;
  
  CArray input(0.0, N);
  CArray filter(0.0, N);
  CArray output(0.0, N);

  input[0] = 2;
  input[1] = 1;
  input[2] = 2;
  input[3] = 1;

  filter[0] = 1;
  filter[1] = 2;
  filter[2] = 3;
 
    // forward fft
    fft(input);
    fft(filter);

    /*
    std::cout << "fft" << std::endl;
    for (int i = 0; i < N; ++i)
    {
        std::cout << input[i] << std::endl;
    }

    std::cout << "fft" << std::endl;
    for (int i = 0; i < N; ++i)
    {
        std::cout << filter[i] << std::endl;
    }
    */

    // multiplication
    for (int i=0; i<N; ++i) {
      output[i] = input[i] * filter[i];
    }
 
    // inverse fft
    ifft(input);
    ifft(filter);
    ifft(output);
 
    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < N; ++i)
    {
        std::cout << input[i] << std::endl;
    }
    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < N; ++i)
    {
      std::cout << filter[i] << std::endl;
    }

    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < N; ++i)
    {
      std::cout << output[i] << std::endl;
    }

    
    return 0;
}
