#include <algorithm>
#include <chrono>
#include <cstdio>
#include <random>

#include <boost/preprocessor/repetition.hpp>

#define ENUM_SIZE 200

typedef int (*enum_funct)(int );

#define FUNCTION(z, n, unused) static int f_##n(int i) { return n + i; };

BOOST_PP_REPEAT(ENUM_SIZE, FUNCTION, ~)

#undef FUNCTION

int execute(int fi, int arg) {

  #define CASES(z, n, unused) case n: return f_##n( arg );

  switch (fi) {

      BOOST_PP_REPEAT(ENUM_SIZE, CASES, ~)
  }
  
  #undef CASES
  return 0;
}


using namespace std;
using namespace std::chrono;
constexpr int ELEMENTS=1e+7; 

int main() {
  
  printf("Testing with %d elements\n", ELEMENTS);
  
  printf("Enum size is %d\n", ENUM_SIZE);
  
  int* a = new int[ELEMENTS];
  
  for (int i=0; i<ELEMENTS; ++i) {
    
    a[i] = i % ENUM_SIZE;
  }  
  
  shuffle(a, a+ELEMENTS, mt19937(1759));

  auto start = high_resolution_clock::now();
  
  int dummy = 0;

  for (int i=0; i<ELEMENTS; ++i) {
    
    dummy += execute(a[i], i);
  }
  
  auto finish = high_resolution_clock::now();
  
  printf("%ld  ms\n", duration_cast<milliseconds>(finish-start).count());
  
  printf("Ignore this value %d\n", dummy);

  delete[] a;  
}
