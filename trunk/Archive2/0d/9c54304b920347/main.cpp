#include <iostream>

void print(double* x, int N) {
  for(int i=0; i<N; ++i)
  std::cout << 1.0 / x[i] << std::endl;
  (void)N;
}