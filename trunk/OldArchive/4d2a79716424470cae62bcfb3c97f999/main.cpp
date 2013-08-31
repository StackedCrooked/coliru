#include <cstdlib>

    #ifdef REALLY
extern struct A a[2];

#define WELL 

template<typename T, int N>
T *begin(T (&x)[N]) {
#ifdef WELL
  return x;
#else
  return &x[0];
#endif
}
#endif

int main() {
    #ifdef REALLY
  begin(a);
  #endif
  return system(
    "echo 'struct A{}a;' > tu.cpp ;"
    "g++ tu.cpp -DREALLY main.cpp && ./a.out");
}
