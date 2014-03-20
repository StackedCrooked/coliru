#include <iostream>

template<int stage> struct Fibonacci {
  static const std::uint64_t value = Fibonacci<stage-1>::value + Fibonacci<stage-2>::value;
};

template<> struct Fibonacci<0> {
  static const uint64_t value = 1;
};
 
template<> struct Fibonacci<1> {
  static const uint64_t value = 1;
};

int main(int argc, char* argv[]) {
    std::cout << Fibonacci<1800>::value << std::endl;
}