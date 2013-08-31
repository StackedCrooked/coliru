#include <cstdio>

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

int main() {
  begin(a);
  puts(".");
}

struct A{};