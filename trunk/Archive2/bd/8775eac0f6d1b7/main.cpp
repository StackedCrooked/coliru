#include <iostream>
#include <limits>

void print(double* x, int N);

int main() {
  const int N = 2;
  double x[N];
  for(int i=0; i<N; ++i)
    x[i] = numeric_limits<double>::max();
  
  print(x, N);
  
  cout << numeric_limits<double>::min() << endl;
  
  return 0;
}