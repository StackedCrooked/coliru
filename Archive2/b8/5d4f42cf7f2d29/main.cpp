//: C07:MatrixMultiply.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Uses valarray to multiply matrices
#include <cassert>
#include <cstddef>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <valarray>
using namespace std;

// Prints a valarray as a square matrix
template<class T>
void printMatrix(const valarray<T>& a, size_t n) {
  size_t siz = n*n;
  assert(siz <= a.size());
  for(size_t i = 0; i < siz; ++i) {
    cout << setw(5) << a[i];
    cout << ((i+1)%n ? ' ' : '\n');
  }
  cout << endl;
}

// Multiplies compatible matrices in valarrays
template<class T>
valarray<T>
matmult(const valarray<T>& a, size_t arows, size_t acols,
        const valarray<T>& b, size_t brows, size_t bcols) {
  assert(acols == brows);
  valarray<T> result(arows * bcols);
  for(size_t i = 0; i < arows; ++i)
    for(size_t j = 0; j < bcols; ++j) {
      // Take dot product of row a[i] and col b[j]
      valarray<T> row = a[slice(acols*i, acols, 1)];
      valarray<T> col = b[slice(j, brows, bcols)];
      result[i*bcols + j] = (row * col).sum();
    }
  return result;
}

int main() {
  const int n = 3;
  int adata[n*n] = {1,0,-1,2,2,-3,3,4,0};
  int bdata[n*n] = {3,4,-1,1,-3,0,-1,1,2};
  valarray<int> a(adata, n*n);
  valarray<int> b(bdata, n*n);
  valarray<int> c(matmult(a, n, n, b, n, n));
  printMatrix(c, n);
} ///:~