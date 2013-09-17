#include <iostream>

template <class T> struct rcg {
    
  template <class Arg1>
  T operator()() const {
    auto arg1 = Arg1{5};
    return T{arg1}; 
  }

};

class A {
  int a_;
  public:
  A(int a) : a_{a} {}
  int a() const { return a_; } 
};

template <class Arg1>
Arg1 foo() {
    return Arg1{5};
}

int main() {
  auto a1 = foo<A>();
  auto my_a_generator = rcg<A>{};
  auto my_a = my_a_generator.operator()<int>(); 
  std::cout << my_a.a() << std::endl;
}