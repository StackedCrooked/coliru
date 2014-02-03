#include <iostream>

template<int N>
struct ptr_ptr {
    ptr_ptr<N-1> operator -> () { return {}; }
};

struct S { void foo() { std::cout << "Hello\n"; } } s;

template<>
struct ptr_ptr<0> {
    S *operator -> () { return &s; }
};
        
int main() {
  ptr_ptr<100> p;
  p->foo();
}