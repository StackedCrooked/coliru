#include <algorithm>
#include <chrono>
#include <cstdio>
#include <random>
using namespace std;
using namespace std::chrono;
constexpr int ELEMENTS=1e+8; 
constexpr double p = 0.50;

int main() {
  printf("p = %.2f\n", p);
  int* a = new int[ELEMENTS];
  mt19937 mt(1759);
  bernoulli_distribution rnd(p);
  for (int i = 0 ; i < ELEMENTS; ++i){
    a[i] = rnd(mt)? i : -i;
  }
  auto start = high_resolution_clock::now();
  int lowerElementIndex = 0;
  for (int i=0; i<ELEMENTS; ++i) {
    if (a[i] < a[lowerElementIndex]) {
      lowerElementIndex = i;
    }
  } 
  auto finish = high_resolution_clock::now();
  printf("%ld  ms\n", duration_cast<milliseconds>(finish-start).count());
  printf("Ignore this line   %d\n", a[lowerElementIndex]);
  delete[] a;
}
