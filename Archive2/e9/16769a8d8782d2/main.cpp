#include <iostream>

template< int a, int b >
struct aa {
  template< int x, int y >
  struct att { int axx[ a + x ][ b + y ]; };
};   

template< int q >
struct b2 : public aa< 12, q > {
    typedef att< 1, 2 > x;
}; 

int main() {
}