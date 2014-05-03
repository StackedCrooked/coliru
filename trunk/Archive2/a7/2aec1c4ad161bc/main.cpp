#include <stdio.h>

constexpr int arr[1] = {2};

template<const int *P> struct S {

static constexpr int first = P[0];

};

template<int I> struct SS {

static constexpr int x = I;

};

int main() {

printf("test %d", SS<S<arr>::first>::x);
}