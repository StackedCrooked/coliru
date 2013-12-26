#include <iostream>

struct Obj {int x;};

template<int N>
 int get_int_offset (Obj& x) {
  return *(reinterpret_cast<int*> (&x) + N);
}

int main () {
  Obj x {};
 
  std::cout << get_int_offset<0> (x) << get_int_offset<1> (x) << get_int_offset<2> (x);
}