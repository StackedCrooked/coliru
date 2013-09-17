#include <iostream>

template <class T> struct rcg {
    
  template <class Arg1>
  T operator()() const {
    auto arg1 = Arg1{};
    return T{arg1}; 
  }

};
}

class A {
  int a_;
  public:
  A(int a) : a_{a} {}
  int a() const { return a_; } 
};

int main() {
  auto my_a_generator = rcg::rcg<A>{};
  auto my_a = my_a_generator<int>(); 
  std::cout << my_a.a() << std::endl;
}